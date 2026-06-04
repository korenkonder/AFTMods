/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "shadow.hpp"
#include "../AFTModsShared/light_param/light.hpp"
#include "../AFTModsShared/object.hpp"
#include "gl_state.hpp"
#include "render_context.hpp"
#include "shader_ft.hpp"
#include <Helpers.h>

#define MIN_SHADOW_RANGE (1.2f)
#define SHADOW_RANGE_SEPARATE (MIN_SHADOW_RANGE * 2.0f)

struct ShadowTexParam {
    GLenum target;
    int32_t width;
    int32_t height;
    int32_t level;
    GLenum pixel_format;
    GLenum depth_format;
};

static_assert(sizeof(ShadowTexParam) == 0x18, "\"ShadowTexParam\" struct should have a size of 0x18");

void(FASTCALL* finish_shadow)() = (void(FASTCALL*)())0x00000001405E8610;
void(FASTCALL* init_shadow)() = (void(FASTCALL*)())0x00000001405E8890;

static Shadow*& g_shadow = *(Shadow**)0x000000014CC587B8;

// 0x140A81E00
static const ShadowTexParam* shadow_tex_param_table = (const ShadowTexParam*)0x0000000140A81E00;

static void M_calc_light_up(vec3* light_up, const vec3* light_pos, const vec3* light_target);

// 0x1405E8690
void Shadow::init_members() {
    m_view_region = MIN_SHADOW_RANGE;
    m_shadow_range = 1.0f;

    for (int32_t i = 0; i < 2; i++) {
        m_light_pos[i] = 1.0f;
        m_light_target[i] = 0.0f;
        m_ground_ypos[i] = 0.0f;
        m_proj_dist_base_range[i] = 0.0f;
        m_enable_group[i] = false;
        m_enable[i] = true;
        m_proj_dist_base_vec[i].clear();
        m_group[i] = i;
    }

    rtex_shadowmap = 0;
    for (RenderTexture*& i : rtex_soft)
        i = 0;

    m_view_mtx = mat4_identity;
    m_iview_mtx = mat4_identity;

    m_proj_near_repeat = 1;
    m_proj_near_sampl = IMGF_BOX_SAMPL_9;
    m_proj_far_repeat = 1;
    m_proj_far_sampl = IMGF_BOX_SAMPL_16;

    m_proj_dist_attn = 4.0f;
    m_proj_dist_attn_offset = 0.4f;
    m_shadowmap_near_clip = 0.1f;
    m_shadowmap_far_clip = 20.0f;
    m_polyoffset_factor = 1.4f;
    m_polyoffset_unit = 10000.0f;
    m_esm_exponent = 80.0f;
    m_gauss_sigma = 2.0f;
    m_gauss_offset = 0.05f;
    m_shadow_ambient = 0.4f;
    m_num_group = 0;
    m_light_dir = vec3(0.0f, -1.0f, -1.0f) * (1.0f / sqrtf(2.0f));
    m_enable_show_textures = false;
    m_enable_self_shadow = true;
    m_separate = false;
    m_shadow_depth_range = (m_shadowmap_far_clip - m_shadowmap_near_clip) * 0.5f;
}

// 0x1405E7820
bool Shadow::check_culling0(const BSphere* bsphere) {
    Shadow* shad = get_shadow();
    mat4 lview;
    vec3 light_up;
    M_calc_light_up(&light_up, &shad->m_light_pos[0], &shad->m_light_target[0]);
    mat4_look_at(&shad->m_light_pos[0], &shad->m_light_target[0], &light_up, &lview);
    return check_culling_sub(bsphere, &lview);
}

// 0x1405E78C0
bool Shadow::check_culling1(const BSphere* bsphere) {
    Shadow* shad = get_shadow();
    mat4 lview;
    vec3 light_up;
    M_calc_light_up(&light_up, &shad->m_light_pos[1], &shad->m_light_target[1]);
    mat4_look_at(&shad->m_light_pos[1], &shad->m_light_target[1], &light_up, &lview);
    return check_culling_sub(bsphere, &lview);
}

// 0x1405E7960
bool Shadow::check_culling_sub(const BSphere* bsphere, const mat4* lview) {
    mat4 view;
    mat4_transpose(&camera_data.view, &view);

    vec3 center;
    mat4_transform_point(&view, &bsphere->center, &center);
    mat4_transform_point(lview, &center, &center);
    float_t radius = bsphere->radius;

    Shadow* shad = get_shadow();
    float_t distance = shad->get_distance();
    if ((center.x + radius) < -distance
        || (center.x - radius) > distance
        || (center.y + radius) < -distance
        || (center.y - radius) > distance
        || (center.z - radius) > -shad->m_shadowmap_near_clip
        || (center.z + radius) < -shad->m_shadowmap_far_clip)
        return false;
    return true;
}

// 0x1405E8B90
void Shadow::set_light_view_proj_mtx(cam_data& cam, const vec3* light_pos,
    const vec3* light_target, float_t range, float_t offset, float_t scale) {
    mat4 temp;
    mat4_translate(offset, 0.0f, 0.0f, &temp);

    mat4 proj;
    mat4_ortho(-range, range, -range, range, m_shadowmap_near_clip, m_shadowmap_far_clip, &proj);
    mat4_mul(&proj, &temp, &proj);

    vec3 light_up;
    M_calc_light_up(&light_up, light_pos, light_target);

    cam.set_view_point(*light_pos);
    cam.set_interest(*light_target);
    cam.set_up(light_up);

    cam.calc_view_mat();
    cam.set_min_distance(m_shadowmap_near_clip);
    cam.set_max_distance(m_shadowmap_far_clip);
    cam.calc_ortho_proj_mat(-range, range, -range, range, scale, { offset, 0.0f });
    cam.calc_view_proj_mat();
}

// 0x1405E76D0
void Shadow::calc_tex_mtx(const vec3* light_pos,
    const vec3* light_target, float_t range, float_t offset, mat4* tex_mtx) {
    mat4 temp;
    mat4_translate(0.5f, 0.5f, 0.5f, &temp);
    mat4_scale_rot(&temp, 0.5f, 0.5f, 0.5f, &temp);
    mat4_mul_translate(&temp, offset, 0.0f, 0.0f, &temp);

    mat4 proj;
    mat4_ortho(-range, range, -range, range, m_shadowmap_near_clip, m_shadowmap_far_clip, &proj);
    mat4_mul(&proj, &temp, &proj);

    mat4 view;
    vec3 light_up;
    M_calc_light_up(&light_up, light_pos, light_target);
    mat4_look_at(light_pos, light_target, &light_up, &view);
    mat4_mul(&view, &proj, tex_mtx);
}

// 0x1405E7BA0
int32_t Shadow::create() {
    const ShadowTexParam* param = shadow_tex_param_table;
    for (int32_t i = 0; i < 7; i++, param++)
        if (rtex_table[i].create_texture(
            (int32_t)(float_t)param->width, (int32_t)(float_t)param->height,
            param->level, param->pixel_format, param->depth_format) < 0)
            return -1;

    for (int32_t i = 0; i < 3; i++) {
        gl_state.bind_texture_2d(rtex_table[i].get_texture_glid());
        glTexParameteriDLL(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteriDLL(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        static const vec4 border_color = 1.0f;
        glTexParameterfvDLL(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, (GLfloat*)&border_color);
    }

    gl_state.bind_texture_2d(rtex_table[0].get_depth_texture_glid());
    GLint swizzle[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzle);
    gl_state.bind_texture_2d(0);
    gl_get_error_print();
    return 0;
}

// 0x1405E8350
void Shadow::destroy() {
    for (RenderTexture& i : rtex_table)
        i.destroy();

    init_members();
}

// 0x1405E8B70
void Shadow::set_light_dir(const vec3* dir) {
    m_light_dir = *dir;
}

// 0x1405E83A0
void Shadow::enable_group(int32_t group) {
    m_enable_group[group] = true;
}

// 0x1405E8A20
void Shadow::set_dist_base(int32_t group, const vec3* pos) {
    if (group >= 0 && group < 2)
        m_proj_dist_base_vec[group].push_back(vec3(pos->x, pos->y - 0.2f, pos->z));
}

// 0x1405E5A90
void Shadow::begin_make_shadow_textures(int32_t group[2]) {
    if (group) {
        group[0] = m_group[0];
        group[1] = m_group[1];
    }

    rtex_shadowmap = &get_rtex(0);
    rtex_soft[0] = &get_rtex(1);
    rtex_soft[1] = &get_rtex(2);
}

// 0x1405E83B0
void Shadow::end_make_shadow_textures(p_gl_rend_state& p_gl_rend_st) {
    shader::unbind(p_gl_rend_st);
    p_gl_rend_st.bind_framebuffer(0);
}

// 0x1405E5AD0
void Shadow::begin_make_silhouette_map(render_data_context& rend_data_ctx,
    struct cam_data& cam, int32_t group, int32_t index) {
    rtex_shadowmap->begin_render(rend_data_ctx.state);
    texture* tex = rtex_shadowmap->m_txhd_color;
    rend_data_ctx.state.set_viewport(1, 1, tex->width - 2, tex->width - 2);
    rend_data_ctx.state.enable_depth_test();
    rend_data_ctx.state.clear_color(1.0f, 1.0f, 1.0f, 1.0f);
    if (!index)
        rend_data_ctx.state.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    else if (m_separate)
        rend_data_ctx.state.clear(GL_COLOR_BUFFER_BIT);

    float_t shadow_range = get_distance();
    float_t offset;
    const vec3* light_targe;
    const vec3* light_pos;
    if (m_separate) {
        offset = group ? 0.5f : -0.5f;
        light_targe = &m_light_target[group];
        light_pos = &m_light_pos[group];
    }
    else {
        offset = 0.0f;
        light_targe = &m_avg_light_target;
        light_pos = &m_avg_light_pos;
    }

    const float_t scale = (float_t)(tex->width / 2) / (float_t)((tex->width - 2) / 2);
    set_light_view_proj_mtx(cam, light_pos, light_targe, shadow_range, offset, scale);
    rctx->draw_state_rend_data[rend_data_ctx.index].shader_index = SHADER_FT_SIL;
    rend_data_ctx.shader_flags.arr[U_DEPTH] = 0;
}

extern void apply_blur_filter_sub(render_data_context& rend_data_ctx, RenderTexture* dst, RenderTexture* src,
    ImgfBoxSampl filter, const vec2 res_scale, const vec4 scale, const vec4 offset);
extern void apply_esm_filter(render_data_context& rend_data_ctx,
    RenderTexture* dst, RenderTexture* buf, RenderTexture* src,
    float_t sigma, float_t offset, bool enable_lit_proj);
extern void apply_esm_min_filter(render_data_context& rend_data_ctx,
    RenderTexture* dst, RenderTexture* buf, RenderTexture* src);

// 0x1405E83D0
void Shadow::end_make_silhouette_map(render_data_context& rend_data_ctx, int32_t group, int32_t index) {
    rend_data_ctx.state.disable_depth_test();

    rctx->draw_state_rend_data[rend_data_ctx.index].shader_index = -1;
    if (index == m_num_group - 1) {
        apply_esm_filter(rend_data_ctx, &get_rtex(3), &get_rtex(4), rtex_shadowmap,
            m_gauss_sigma, m_gauss_offset / (m_shadow_depth_range * 2.0f), false);
        apply_esm_min_filter(rend_data_ctx, &get_rtex(5), &get_rtex(6), &get_rtex(3));
    }

    RenderTexture* rend_tex = rtex_soft[group];
    RenderTexture& rend_buf_tex = rctx->shadow_buffer;

    image_filter_scale(rend_data_ctx, rend_tex, rtex_shadowmap->get_texture());

    if (m_enable[group]) {
        for (int32_t i = m_proj_near_repeat, j = 0; i > 0; i--, j++) {
            apply_blur_filter_sub(rend_data_ctx, &rend_buf_tex, rend_tex,
                m_proj_near_sampl, 1.0f, 1.0f, 0.0f);
            image_filter_scale(rend_data_ctx, rend_tex, rend_buf_tex.get_texture());
        }
    }
    else {
        rend_buf_tex.begin_render(rend_data_ctx.state);
        rend_data_ctx.state.clear_color(1.0f, 1.0f, 1.0f, 1.0f);
        rend_data_ctx.state.clear(GL_COLOR_BUFFER_BIT);
    }
    rend_buf_tex.end_render(rend_data_ctx.state);

    if (DIVA_GL_VERSION_4_5)
        rend_data_ctx.state.generate_texture_mipmap(rend_tex->get_texture_glid());
    else {
        rend_data_ctx.state.bind_texture_2d(rend_tex->get_texture_glid());
        rend_data_ctx.state.generate_mipmap(GL_TEXTURE_2D);
        rend_data_ctx.state.bind_texture_2d(0);
    }
}

// 0x1405E5CA0
void Shadow::bind_shadow(render_data_context& rend_data_ctx) {
    float_t esm_param;
    if (m_enable_self_shadow && m_num_group > 0) {
        rend_data_ctx.state.active_bind_texture_2d(19, get_rtex(3).get_texture_glid());
        rend_data_ctx.state.active_bind_texture_2d(20, get_rtex(5).get_texture_glid());
        rend_data_ctx.state.active_texture(0);
        esm_param = (m_esm_exponent * m_shadow_depth_range * 2.0f) * 1.442695f;
        rend_data_ctx.set_self_shadow(true);
    }
    else {
        rend_data_ctx.state.active_bind_texture_2d(19, rctx->empty_texture_2d->glid);
        rend_data_ctx.state.active_bind_texture_2d(20, rctx->empty_texture_2d->glid);
        rend_data_ctx.state.active_texture(0);
        esm_param = 0.0f;
        rend_data_ctx.set_self_shadow(false);
    }

    rend_data_ctx.state.bind_sampler(19, rctx->render_samplers[0]);
    rend_data_ctx.state.bind_sampler(20, rctx->render_samplers[0]);

    mat4 mats[2];
    mats[0] = mat4_identity;
    mats[1] = mat4_identity;
    vec4 shadow_ambient;
    vec4 shadow_ambient1;
    if (m_num_group > 0) {
        rctx->draw_state_rend_data[rend_data_ctx.index].shadow = true;
        rend_data_ctx.shader_flags.arr[U_NUM_SHADOWMAP] = m_num_group > 1 ? 1 : 0;

        float_t distance = get_distance();
        for (int32_t i = 0; i < 2; i++) {
            float_t offset;
            vec3* target;
            vec3* pos;
            if (m_separate) {
                offset = i ? 0.5f : -0.5f;

                target = &m_light_target[i];
                pos = &m_light_pos[i];
            }
            else {
                offset = 0.0f;
                target = &m_avg_light_target;
                pos = &m_avg_light_pos;
            }

            calc_tex_mtx(pos, target, distance, offset, &mats[i]);
        }

        int32_t index = 0;
        for (int32_t i = 0; i < 2; i++)
            if (m_enable_group[i]) {
                rend_data_ctx.state.active_bind_texture_2d(6 + index, rtex_soft[i]->get_texture_glid());
                index++;
            }

        for (; index < 2; index++)
            rend_data_ctx.state.active_bind_texture_2d(6 + index, rctx->empty_texture_2d->glid);
        rend_data_ctx.state.active_texture(0);

        light_set* set = &light_set_data[LIGHT_SET_MAIN];
        light_data* data = &set->lights[LIGHT_SHADOW];

        vec4 ambient;
        if (data->get_type() == LIGHT_PARALLEL)
            data->get_ambient(ambient);
        else
            *(vec3*)&ambient.x = m_shadow_ambient;

        shadow_ambient = { ambient.x, ambient.y, ambient.z, 1.0f };
        shadow_ambient1 = { 1.0f - ambient.x, 1.0f - ambient.y, 1.0f - ambient.z, 0.0f };
    }
    else {
        rctx->draw_state_rend_data[rend_data_ctx.index].shadow = false;

        for (int32_t i = 0; i < 2; i++)
            rend_data_ctx.state.active_bind_texture_2d(6 + i, rtex_soft[i]->get_texture_glid());
        rend_data_ctx.state.active_texture(0);

        shadow_ambient = 1.0f;
        shadow_ambient1 = 0.0f;
    }

    rend_data_ctx.set_scene_shadow_params(esm_param, mats, shadow_ambient, shadow_ambient1);

    rend_data_ctx.state.bind_sampler(6, 0);
    rend_data_ctx.state.bind_sampler(7, 0);
}

// 0x1405E8D40
void Shadow::unbind_shadow(render_data_context& rend_data_ctx) {
    rend_data_ctx.state.active_bind_texture_2d(6, rctx->empty_texture_2d->glid);
    rend_data_ctx.state.active_bind_texture_2d(7, rctx->empty_texture_2d->glid);
    rend_data_ctx.set_self_shadow(false);
    rend_data_ctx.set_shadow(false);
}

// 0x1405E7AF0
void Shadow::clear(p_gl_rend_state& p_gl_rend_st) {
    for (int32_t i = 0; i < 2; i++)
        for (int32_t j = 0; j < 4; j++) {
            rtex_soft[i]->begin_render(p_gl_rend_st, j);
            p_gl_rend_st.clear_color(1.0f, 1.0f, 1.0f, 1.0f);
            p_gl_rend_st.clear(GL_COLOR_BUFFER_BIT);
        }
    p_gl_rend_st.bind_framebuffer(0);
}

// 0x1405E89C0
void Shadow::set_cull_func(int32_t group) {
    if (group >= 0 && group < 2) {
        if (!group)
            disp_manager->set_culling_func(check_culling0);
        else
            disp_manager->set_culling_func(check_culling1);
    }
}

// 0x1405E8640
float_t Shadow::get_distance() const {
    return m_view_region * m_shadow_range;
}

HOOK(void, FASTCALL, Shadow__create, 0x00000001405E7BA0, Shadow* This) {
    This->create();
}

HOOK(void, FASTCALL, Shadow__destroy, 0x00000001405E8350, Shadow* This) {
    This->destroy();
}

// 0x1405E8680
Shadow* get_shadow() {
    return g_shadow;
}

void shadow_patch() {
    INSTALL_HOOK(Shadow__create);
    INSTALL_HOOK(Shadow__destroy);
}

// 0x1405E56B0
static void M_calc_light_up(vec3* light_up, const vec3* light_pos, const vec3* light_target) {
    *light_up = { 0.0f, 1.0f, 0.0f };
    const vec3 dir = *light_target - *light_pos;
    if (fabsf(dir.x * dir.x + dir.z * dir.z) <= 0.000001f) {
        light_up->x = 0.0f;
        light_up->y = 0.0f;
        if (dir.y < 0.0f)
            light_up->z = 1.0f;
        else
            light_up->z = -1.0f;
    }
}
