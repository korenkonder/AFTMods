/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "sss.hpp"
#include "../AFTModsShared/rob/rob.hpp"
#include "camera.hpp"
#include "reflect_full.hpp"
#include "render_context.hpp"
#include "shader_ft.hpp"

vec4 sss_param = 0.0f;
vec4 sss_param_reflect = 0.0f;

sss_data& _sss_data = *(sss_data*)0x000000014CC924E0;

static void sss_calc_coef(const double_t step, const int32_t size,
    const double_t inverse_scale, const int32_t iterations, const double_t* weights,
    const double_t* r_radius, const double_t* g_radius, const double_t* b_radius, vec4 coef[64]);
static void sss_draw_quad(render_data_context& rend_data_ctx,
    int32_t width, int32_t height, float_t s, float_t t,
    float_t param_x, float_t param_y, float_t param_z, float_t param_w);

// 0x00000001406411E0
void sss_data::apply_filter(struct render_data_context& rend_data_ctx) {
    const int32_t sss_count = 6;
    vec3 interest = camera_data.interest;
    vec3 view_point = camera_data.view_point;

    vec3 chara_position[2];
    chara_position[0] = 0.0f;
    chara_position[1] = 0.0f;
    float_t chara_distance[2];
    size_t rob_chara_smth = get_rob_chara_smth();
    for (int32_t i = 0; i < 2; i++) {
        chara_position[i] = interest;
        chara_distance[i] = 999999.0f;
        size_t rob_bone_data = rob_chara_array_get_bone_data(rob_chara_smth, i);
        if (rob_chara_pv_data_array_check_chara_id(rob_chara_smth, i)
            && rob_chara_array_check_visibility(rob_chara_smth, i)) {
            const mat4* mat = rob_chara_bone_data_get_mats_mat(rob_bone_data, 0);
            if (mat) {
                mat4 temp;
                mat4_transpose(mat, &temp);
                mat4_get_translation(&temp, &chara_position[i]);
                if (reflect_draw)
                    mat4_transform_point(&reflect_mat, &chara_position[i], &chara_position[i]);
                chara_distance[i] = vec3::distance(view_point, chara_position[i]);
            }
        }
    }

    vec3 closest_chara_position = chara_distance[0] <= chara_distance[1]
        ? chara_position[0] : chara_position[1];

    float_t length = vec3::distance(interest, closest_chara_position);
    if (length > 1.25f)
        interest = chara_position[0];

    float_t distance_to_interest = max_def(vec3::distance(view_point, interest), 0.25f);
    float_t fov_scale = max_def(tanf(camera_data.fov * 0.5f * DEG_TO_RAD_FLOAT) * 5.0f, 0.25f);
    float_t sss_strength = 0.6f;
    float_t inverse_scale = (float_t)(1.0 / clamp_def(fov_scale * distance_to_interest, 0.25f, 100.0f));
    if (inverse_scale < 0.145f)
        sss_strength = max_def(inverse_scale - 0.02f, 0.0f) * 8.0f * 0.6f;
    if (reflect_draw)
        sss_param_reflect = { sss_strength, 0.0f, 0.0f, 0.0f };
    else
        sss_param = { sss_strength, 0.0f, 0.0f, 0.0f };

    rend_data_ctx.state.active_texture(0);
    if (downsample) {
        textures[0].Bind(rend_data_ctx.state);
        rend_data_ctx.state.set_viewport(0, 0, 640, 360);
        rndr::Render* rend = render_get();
        rend_data_ctx.shader_flags.arr[U_REDUCE] = 0;
        shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_REDUCE);
        RenderTexture& rt = reflect_draw
            ? reflect_full_ptr->reflect_texture
            : rend->rend_texture[0];
        rend_data_ctx.state.bind_texture_2d(rt.GetColorTex());
        rend_data_ctx.state.bind_sampler(0, rctx->render_samplers[0]);
        sss_draw_quad(rend_data_ctx, rt.GetWidth(), rt.GetHeight(),
            1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
    }

    textures[2].Bind(rend_data_ctx.state);
    rend_data_ctx.state.set_viewport(0, 0, 320, 180);
    rend_data_ctx.shader_flags.arr[U_SSS_FILTER] = 0;
    shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_SSS_FILT);
    rend_data_ctx.state.bind_texture_2d(textures[0].GetColorTex());
    rend_data_ctx.state.bind_sampler(0, rctx->render_samplers[0]);
    sss_draw_quad(rend_data_ctx, textures[0].GetWidth(), textures[0].GetHeight(),
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);

    sss_filter_gaussian_coef_shader_data shader_data = {};
    shader_data.g_param = { (float_t)(sss_count - 1), 0.0f, 1.0f, 1.0f };

    const double_t weights[] = { 0.4, 0.3, 0.3 };
    const double_t r_radius[] = { 1.0, 2.0, 5.0 };
    const double_t g_radius[] = { 0.2, 0.4, 1.2 };
    const double_t b_radius[] = { 0.3, 0.7, 2.0 };
    sss_calc_coef(1.0, sss_count, inverse_scale,
        3, weights, r_radius, g_radius, b_radius, shader_data.g_coef);

    rctx->sss_filter_gaussian_coef_ubo.WriteMemory(rend_data_ctx.state, shader_data);
    textures[reflect_draw ? 3 : 1].Bind(rend_data_ctx.state);
    rend_data_ctx.state.set_viewport(0, 0, 320, 180);
    rend_data_ctx.shader_flags.arr[U_SSS_FILTER] = 3;
    shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_SSS_FILT);
    rend_data_ctx.state.bind_texture_2d(textures[2].GetColorTex());
    rend_data_ctx.state.bind_sampler(0, rctx->render_samplers[0]);
    rend_data_ctx.state.bind_uniform_buffer_base(1, rctx->sss_filter_gaussian_coef_ubo);
    sss_draw_quad(rend_data_ctx, textures[2].GetWidth(), textures[2].GetHeight(),
        1.0f, 1.0f, 1.0f, 0.96f, 1.0f, 0.0f);
    rend_data_ctx.state.bind_texture_2d(0);
}

// 0x0000000140641920
void sss_data::free() {
    if (init_data)
        for (RenderTexture& i : textures)
            i.Free();
}

// 0x0000000140641890
void sss_data::init() {
    if (init_data)
        return;

    textures[0].Init(640, 360, 0, GL_RGBA16F, GL_ZERO /*GL_DEPTH_COMPONENT32F*/);
    textures[1].Init(320, 180, 0, GL_RGBA16F, GL_ZERO);
    textures[2].Init(320, 180, 0, GL_RGBA16F, GL_ZERO);
    textures[3].Init(320, 180, 0, GL_RGBA16F, GL_ZERO);

    param = { 0.0f, 0.0f, 0.0f, 1.0f };
    init_data = true;
}

// 0x0000000140641B40
void sss_data::reset(struct render_data_context& rend_data_ctx) {
    if (init_data)
        rend_data_ctx.state.bind_framebuffer(0);
}

// 0x0000000140641060
bool sss_data::set(struct render_data_context& rend_data_ctx) {
    if (!init_data)
        return false;
    else if (!enable) {
        rend_data_ctx.set_batch_sss_param(0.0f);
        return false;
    }

    rndr::Render* rend = render_get();
    float_t render_width;
    float_t render_height;
    rend->get_render_resolution(&render_width, &render_height, 0, 0);

    if (render_width > 1280.0f)
        downsample = false;
    downsample = true; // Added

    if (downsample) {
        rend->rend_texture[0].Bind(rend_data_ctx.state);
        rend_data_ctx.state.set_viewport(0, 0, (int32_t)render_width, (int32_t)render_height);
    }
    else {
        textures[0].Bind(rend_data_ctx.state);
        rend_data_ctx.state.set_viewport(0, 0, 640, 360);
    }

    rend_data_ctx.state.clear_color(param.x, param.y, param.z, 0.0f);
    rend_data_ctx.state.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return true;
}

// Added
bool sss_data::set(struct render_data_context& rend_data_ctx, RenderTexture& rt) {
    if (!init_data)
        return false;
    else if (!enable) {
        rend_data_ctx.set_batch_sss_param(0.0f);
        return false;
    }

    float_t render_width = (float_t)rt.GetWidth();
    float_t render_height = (float_t)rt.GetHeight();

    if (render_width > 1280.0f)
        downsample = false;
    downsample = true; // Added

    if (downsample) {
        rt.Bind(rend_data_ctx.state);
        rend_data_ctx.state.set_viewport(0, 0, (int32_t)render_width, (int32_t)render_height);
    }
    else {
        textures[0].Bind(rend_data_ctx.state);
        rend_data_ctx.state.set_viewport(0, 0, 640, 360);
    }

    rend_data_ctx.state.clear_color(param.x, param.y, param.z, 0.0f);
    rend_data_ctx.state.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return true;
}

// 0x0000000140641190
void sss_data::set_texture(struct p_gl_rend_state& p_gl_rend_st, int32_t texture_index) {
    p_gl_rend_st.active_bind_texture_2d(16, textures[texture_index].GetColorTex());
    p_gl_rend_st.active_texture(0);
}

// 0x0000000140641B70
sss_data* sss_data_get() {
    return &_sss_data;
}

// 0x0000000140641B80
static void sss_calc_coef(const double_t step, const int32_t size,
    const double_t inverse_scale, const int32_t iterations, const double_t* weights,
    const double_t* r_radius, const double_t* g_radius, const double_t* b_radius, vec4 coef[64]) {
    if (size > 8)
        return;

    for (int32_t it = 0; it < iterations; it++) {
        const double_t it_weight = weights[it];
        const double_t ch_radius[] = { r_radius[it], g_radius[it], b_radius[it] };

        for (int32_t ch = 0; ch < 3; ch++) {
            double_t kernel[8];
            double_t pos = 0.0;
            double_t kernel_sum = 0.0;
            double_t scale = 1.0 / (inverse_scale * ch_radius[ch]);
            for (int32_t k = 0; k < size; k++) {
                double_t weight = exp(-0.5 * (scale * pos) * (scale * pos));
                kernel[k] = weight;
                pos += step;
                kernel_sum += weight;
            }

            double_t inv_sum = 1.0 / kernel_sum;
            for (int32_t k = 0; k < size; k++)
                kernel[k] *= inv_sum;

            float_t* ptr = (float_t*)coef + ch;
            for (int32_t k = 0; k < size; k++)
                for (size_t l = 0; l < size; l++) {
                    *ptr = (float_t)(kernel[k] * it_weight * kernel[l] + *ptr);
                    ptr += 4;
                }
        }
    }
}

// 0x0000000140641960
static void sss_draw_quad(render_data_context& rend_data_ctx,
    int32_t width, int32_t height, float_t s, float_t t,
    float_t param_x, float_t param_y, float_t param_z, float_t param_w) {
    render_get()->draw_quad(rend_data_ctx, width, height,
        s, t, 0.0f, 0.0f, 1.0f, param_x, param_y, param_z, param_w);
}
