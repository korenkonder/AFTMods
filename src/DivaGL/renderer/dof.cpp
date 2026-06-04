/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "dof.hpp"
#include "../rob/rob.hpp"
#include "../camera.hpp"
#include "../gl_rend_state.hpp"
#include "../gl_state.hpp"
#include "../render_context.hpp"
#include "../render_texture.hpp"
#include "../shader_ft.hpp"
#include "../static_var.hpp"

struct dof_common_shader_data {
    vec4 g_depth_params; //x=(n-f)/(nf), y=1/n, z=coc_from_z_scale, w=coc_from_z_offset
    vec4 g_spread_scale; //x=scale_from_meter_to_pixel, y=scale_from_meter_to_sample,
        //  z=scale_from_pixel_to_sample, w=scale_from_sample_to_pixel
    vec4 g_depth_params2; //x=distance_to_focus_m, y=focus_range,
        // z=k/(fuzzing_range*fuzzing_range), w=max_coc_radius_in_pixel   //yzw=for_f2
    vec4i g_dof_param; //x=tile_size, y=prefilter_tap_num, z=sample_division, w=upsample_tap_num
};

dof_debug* dof_debug_data = (dof_debug*)0x00000001411AB650;
dof_pv* dof_pv_data = (dof_pv*)0x0000001411AB630;

int32_t dof_param_tile_size = 20;
int32_t dof_param_prefilter_tap_num = 8;
int32_t dof_param_sample_division = 7;
int32_t dof_param_upsample_tap_num = 8;

namespace renderer {
    template <int32_t sample_division>
    static void CalcTexcoord(vec2* data, const float_t size);

    static void calc_texcoord(vec2& dst, const vec2& src);

    DOF3::DOF3(int32_t width, int32_t height) : m_tex(), m_sampler(), m_vao() {
        m_width = width;
        m_height = height;

        create_render_buffer(width, height);
    }

    // Inlined
    DOF3::~DOF3() {

    }

    // Inlined
    void DOF3::apply(render_data_context& rend_data_ctx, RenderTexture* rt, RenderTexture* buf_rt) {
        if (dof_debug_data->flags & DOF_DEBUG_USE_UI_PARAMS) {
            if (dof_debug_data->flags & DOF_DEBUG_ENABLE_DOF) {
                if (dof_debug_data->flags & DOF_DEBUG_ENABLE_PHYS_DOF) {
                    float_t focus = dof_debug_data->focus;
                    if (dof_debug_data->flags & DOF_DEBUG_AUTO_FOCUS) {
                        size_t rob_chara_smth = get_rob_chara_smth();

                        for (int32_t i = 0; i < ROB_CHARA_COUNT; i++) {
                            rob_chara* rob_chr = rob_chara_array_get(rob_chara_smth, i);
                            if (!rob_chr || !rob_chr->is_visible())
                                continue;

                            mat4 mat;
                            sub_1405163C0(rob_chr, 4, &mat);
                            mat4_transpose(&mat, &mat);

                            vec3 chara_trans = 0.0f;
                            mat4_get_translation(&mat, &chara_trans);

                            mat4 view = camera_data.view;
                            focus = -vec3::dot(*(vec3*)&view.row2, chara_trans) - view.row2.w - 0.1f;
                            break;
                        }
                    }

                    focus = max_def(focus, camera_data.min_distance);
                    apply(rend_data_ctx, rt, buf_rt, rt->get_texture_glid(), rt->get_depth_texture_glid(),
                        camera_data.min_distance, camera_data.max_distance, focus,
                        dof_debug_data->focal_length, camera_data.fov * DEG_TO_RAD_FLOAT, dof_debug_data->f_number);
                }
                else {
                    float_t fuzzing_range = max_def(dof_debug_data->f2.fuzzing_range, 0.01f);
                    apply_f2(rend_data_ctx, rt, buf_rt, rt->get_texture_glid(), rt->get_depth_texture_glid(),
                        camera_data.min_distance, camera_data.max_distance, camera_data.fov * DEG_TO_RAD_FLOAT,
                        dof_debug_data->f2.focus, dof_debug_data->f2.focus_range,
                        fuzzing_range, dof_debug_data->f2.ratio);
                }
            }
        }
        else if (dof_pv_data->enable && dof_pv_data->f2.ratio > 0.0f) {
            float_t fuzzing_range = max_def(dof_pv_data->f2.fuzzing_range, 0.01f);
            apply_f2(rend_data_ctx, rt, buf_rt, rt->get_texture_glid(), rt->get_depth_texture_glid(),
                camera_data.min_distance, camera_data.max_distance,
                camera_data.fov * DEG_TO_RAD_FLOAT,
                dof_pv_data->f2.focus, dof_pv_data->f2.focus_range,
                fuzzing_range, dof_pv_data->f2.ratio);
            enum_or(dof_debug_data->flags, DOF_DEBUG_ENABLE_DOF);
            dof_debug_data->f2 = dof_pv_data->f2;
        }
        else
            enum_and(dof_debug_data->flags, ~DOF_DEBUG_ENABLE_DOF);
    }

    // Added
    void DOF3::resize(int32_t width, int32_t height) {
        if (m_tex[0]) {
            glDeleteTexturesDLL(6, m_tex);
            m_tex[0] = 0;
        }

        m_width = width;
        m_height = height;

        init_textures(width, height);
    }

    // 0x1404ABBF0
    void DOF3::destroy() {
        if (m_vao) {
            glDeleteVertexArrays(1, &m_vao);
            m_vao = 0;
        }

        for (int32_t i = 0; i < 7; i++)
            m_texcoord_ubo[i].Destroy();
        m_common_ubo.Destroy();

        if (m_sampler[0]) {
            glDeleteSamplers(2, m_sampler);
            m_sampler[0] = 0;
        }

        if (m_tex[0]) {
            glDeleteTexturesDLL(6, m_tex);
            m_tex[0] = 0;
        }
    }

    // 0x1404AB550
    void DOF3::create_render_buffer(int32_t width, int32_t height) {
        destroy();

        init_textures(width, height);

        glGenSamplers(2, m_sampler);
        glSamplerParameteri(m_sampler[0], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glSamplerParameteri(m_sampler[0], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glSamplerParameteri(m_sampler[0], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(m_sampler[0], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(m_sampler[1], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glSamplerParameteri(m_sampler[1], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glSamplerParameteri(m_sampler[1], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(m_sampler[1], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        m_common_ubo.Create(gl_state, sizeof(dof_common_shader_data));

        vec2 data[7 * 7 + 1] = {};
        CalcTexcoord<1>(data, 0.0f);
        m_texcoord_ubo[0].Create(gl_state, sizeof(data), data);
        CalcTexcoord<3>(data, 0.0f);
        m_texcoord_ubo[1].Create(gl_state, sizeof(data), data);
        CalcTexcoord<3>(data, 6.0f);
        m_texcoord_ubo[2].Create(gl_state, sizeof(data), data);
        CalcTexcoord<4>(data, 5.0f);
        m_texcoord_ubo[3].Create(gl_state, sizeof(data), data);
        CalcTexcoord<5>(data, 4.0f);
        m_texcoord_ubo[4].Create(gl_state, sizeof(data), data);
        CalcTexcoord<6>(data, 3.5f);
        m_texcoord_ubo[5].Create(gl_state, sizeof(data), data);
        CalcTexcoord<7>(data, 3.0f);
        m_texcoord_ubo[6].Create(gl_state, sizeof(data), data);

        glGenVertexArrays(1, &m_vao);
    }

    // 0x1404A8EC0
    void DOF3::apply(render_data_context& rend_data_ctx,
        RenderTexture* rt, RenderTexture* buf_rt, GLuint color_texture,
        GLuint depth_texture, float_t min_distance, float_t max_distance,
        float_t focus, float_t focal_length, float_t fov, float_t f_number) {
        rend_data_ctx.state.begin_event("renderer::DOF3::apply");
        rend_data_ctx.state.disable_blend();
        rend_data_ctx.state.set_depth_mask(GL_FALSE);
        rend_data_ctx.state.set_depth_func(GL_ALWAYS);
        write_data(rend_data_ctx, min_distance, max_distance,
            fov, focus, focal_length, f_number, 0.0f, 0.1f, 0.0f);

        rend_data_ctx.shader_flags.arr[U_DOF] = 0;

        render_tiles(rend_data_ctx, depth_texture, false);
        downsample(rend_data_ctx, color_texture, depth_texture, false);
        apply_main_filter(rend_data_ctx, false);
        upsample(rend_data_ctx, rt, buf_rt, color_texture, depth_texture, false);

        shader::unbind(rend_data_ctx.state);
        for (int32_t i = 0; i < 8; i++) {
            rend_data_ctx.state.bind_sampler(i, 0);
            rend_data_ctx.state.active_bind_texture_2d(i, 0);
        }
        rend_data_ctx.state.bind_vertex_array(0);
        rend_data_ctx.state.end_event();
    }

    // 0x1404A9000
    void DOF3::apply_f2(render_data_context& rend_data_ctx,
        RenderTexture* rt, RenderTexture* buf_rt, GLuint color_texture,
        GLuint depth_texture, float_t min_distance, float_t max_distance, float_t fov,
        float_t focus, float_t focus_range, float_t fuzzing_range, float_t ratio) {
        rend_data_ctx.state.begin_event("renderer::DOF3::apply_f2");
        rend_data_ctx.state.disable_blend();
        rend_data_ctx.state.set_depth_mask(GL_FALSE);
        rend_data_ctx.state.set_depth_func(GL_ALWAYS);
        write_data(rend_data_ctx, min_distance, max_distance,
            fov, focus, 0.0f, 1.0f, focus_range, fuzzing_range, ratio);

        rend_data_ctx.shader_flags.arr[U_DOF] = 1;

        render_tiles(rend_data_ctx, depth_texture, true);
        downsample(rend_data_ctx, color_texture, depth_texture, true);
        apply_main_filter(rend_data_ctx, true);
        upsample(rend_data_ctx, rt, buf_rt, color_texture, depth_texture, true);

        shader::unbind(rend_data_ctx.state);
        for (int32_t i = 0; i < 8; i++) {
            rend_data_ctx.state.bind_sampler(i, 0);
            rend_data_ctx.state.active_bind_texture_2d(i, 0);
        }
        rend_data_ctx.state.bind_vertex_array(0);
        rend_data_ctx.state.end_event();
    }

    // 0x1404B1950
    void DOF3::render_tiles(render_data_context& rend_data_ctx, GLuint depth_texture, bool f2) {
        rend_data_ctx.state.begin_event("renderer::DOF3::render_tiles");
        m_fbo[0].bind_fbo(rend_data_ctx.state);
        rend_data_ctx.shader_flags.arr[U_DOF_STAGE] = 0;
        shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_DOF);
        rend_data_ctx.state.bind_uniform_buffer_base(0, m_common_ubo);
        rend_data_ctx.state.active_bind_texture_2d(0, depth_texture);
        rend_data_ctx.state.bind_sampler(0, m_sampler[1]);
        draw_quad(rend_data_ctx);

        m_fbo[1].bind_fbo(rend_data_ctx.state);
        rend_data_ctx.shader_flags.arr[U_DOF_STAGE] = 1;
        shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_DOF);
        bind_texture(rend_data_ctx.state, 0, 0, 1);
        draw_quad(rend_data_ctx);
        rend_data_ctx.state.end_event();
    }

    // 0x1404ABC90
    void DOF3::downsample(render_data_context& rend_data_ctx, GLuint color_texture, GLuint depth_texture, bool f2) {
        rend_data_ctx.state.begin_event("renderer::DOF3::downsample");
        m_fbo[2].bind_fbo(rend_data_ctx.state);
        rend_data_ctx.shader_flags.arr[U_DOF_STAGE] = 2;
        shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_DOF);
        rend_data_ctx.state.bind_uniform_buffer_base(0, m_common_ubo);
        rend_data_ctx.state.active_bind_texture_2d(0, depth_texture);
        rend_data_ctx.state.bind_sampler(0, m_sampler[1]);
        rend_data_ctx.state.active_bind_texture_2d(1, color_texture);
        rend_data_ctx.state.bind_sampler(1, m_sampler[0]);
        bind_texture(rend_data_ctx.state, 2, 1, 1);
        draw_quad(rend_data_ctx);
        rend_data_ctx.state.end_event();
    }

    // 0x1404A91A0
    void DOF3::apply_main_filter(render_data_context& rend_data_ctx, bool f2) {
        rend_data_ctx.state.begin_event("renderer::DOF3::apply_main_filter");
        m_fbo[3].bind_fbo(rend_data_ctx.state);
        rend_data_ctx.shader_flags.arr[U_DOF_STAGE] = 3;
        shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_DOF);
        rend_data_ctx.state.bind_uniform_buffer_base(0, m_common_ubo);
        rend_data_ctx.state.bind_uniform_buffer_base(1, m_texcoord_ubo[dof_param_sample_division - 1]);
        bind_texture(rend_data_ctx.state, 0, 3, 1);
        bind_texture(rend_data_ctx.state, 1, 2, 1);
        bind_texture(rend_data_ctx.state, 2, 1, 1);
        draw_quad(rend_data_ctx);
        rend_data_ctx.state.end_event();
    }

    // 0x1404B3120
    void DOF3::upsample(render_data_context& rend_data_ctx,
        RenderTexture* rt, RenderTexture* buf_rt,
        GLuint color_texture, GLuint depth_texture, bool f2) {
        rend_data_ctx.state.begin_event("renderer::DOF3::upsample");
        buf_rt->begin_render(rend_data_ctx.state);
        rend_data_ctx.state.set_viewport(0, 0, m_width, m_height);
        rend_data_ctx.shader_flags.arr[U_DOF_STAGE] = 4;
        shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_DOF);
        rend_data_ctx.state.bind_uniform_buffer_base(0, m_common_ubo);
        bind_texture(rend_data_ctx.state, 0, 4, 1);
        bind_texture(rend_data_ctx.state, 1, 5, 1);
        bind_texture(rend_data_ctx.state, 2, 1, 1);
        rend_data_ctx.state.active_bind_texture_2d(3, color_texture);
        rend_data_ctx.state.bind_sampler(3, m_sampler[1]);
        rend_data_ctx.state.active_bind_texture_2d(4, depth_texture);
        rend_data_ctx.state.bind_sampler(4, m_sampler[1]);
        draw_quad(rend_data_ctx);

        if (DIVA_GL_VERSION_4_3)
            rend_data_ctx.state.copy_image_sub_data(
                buf_rt->get_texture_glid(), GL_TEXTURE_2D, 0, 0, 0, 0,
                rt->get_texture_glid(), GL_TEXTURE_2D, 0, 0, 0, 0, m_width, m_height, 1);
        else
            fbo_blit(rend_data_ctx.state, buf_rt->get_fb(), rt->get_fb(),
                0, 0, m_width, m_height,
                0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        rend_data_ctx.state.end_event();
    }

    // 0x1404A9420
    inline void DOF3::bind_texture(p_gl_rend_state& p_gl_rend_st,
        GLuint unit, int32_t tex_index, int32_t sampler_index) {
        p_gl_rend_st.active_bind_texture_2d(unit, m_tex[tex_index]);
        p_gl_rend_st.bind_sampler(unit, m_sampler[sampler_index]);
    }

    // 0x1404AD370
    inline void DOF3::draw_quad(render_data_context& rend_data_ctx) {
        rend_data_ctx.state.bind_vertex_array(m_vao);
        rend_data_ctx.state.draw_arrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    // Inlined
    inline void DOF3::init_textures(int32_t width, int32_t height) {
        int32_t w20 = max_def(width / 20, 1);
        int32_t h20 = max_def(height / 20, 1);
        int32_t w2 = max_def(width / 2, 1);
        int32_t h2 = max_def(height / 2, 1);

        glGenTexturesDLL(6, m_tex);
        gl_state.bind_texture_2d(m_tex[0]);
        glTexImage2DDLL(GL_TEXTURE_2D, 0, GL_RG16F, w20, h20, 0, GL_RG, GL_HALF_FLOAT, 0);
        m_fbo[0].init(w20, h20, &m_tex[0], 1, 0);

        gl_state.bind_texture_2d(m_tex[1]);
        glTexImage2DDLL(GL_TEXTURE_2D, 0, GL_RG16F, w20, h20, 0, GL_RG, GL_HALF_FLOAT, 0);
        m_fbo[1].init(w20, h20, &m_tex[1], 1, 0);

        gl_state.bind_texture_2d(m_tex[2]);
        glTexImage2DDLL(GL_TEXTURE_2D, 0, GL_R11F_G11F_B10F, w2, h2, 0, GL_RGB, GL_UNSIGNED_INT_10F_11F_11F_REV, 0);
        gl_state.bind_texture_2d(m_tex[3]);
        glTexImage2DDLL(GL_TEXTURE_2D, 0, GL_R11F_G11F_B10F, w2, h2, 0, GL_RGB, GL_UNSIGNED_INT_10F_11F_11F_REV, 0);
        m_fbo[2].init(w2, h2, &m_tex[2], 2, 0);

        gl_state.bind_texture_2d(m_tex[4]);
        glTexImage2DDLL(GL_TEXTURE_2D, 0, GL_R11F_G11F_B10F, w2, h2, 0, GL_RGB, GL_UNSIGNED_INT_10F_11F_11F_REV, 0);
        gl_state.bind_texture_2d(m_tex[5]);
        glTexImage2DDLL(GL_TEXTURE_2D, 0, GL_R8, w2, h2, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
        m_fbo[3].init(w2, h2, &m_tex[4], 2, 0);

        gl_state.bind_texture_2d(0);
    }

    // 0x1404B33E0
    void DOF3::write_data(render_data_context& rend_data_ctx,
        float_t min_dist, float_t max_dist, float_t fov, float_t dist, float_t focal_length,
        float_t f_number, float_t focus_range, float_t fuzzing_range, float_t ratio) {
        float_t fl = focal_length;
        if (dist <= focal_length)
            fl = dist + 0.1f;
        fl = fl / (dist - fl) * fl / f_number;

        dof_common_shader_data shader_data = {};
        shader_data.g_depth_params.x = 1.0f / (min_dist * max_dist) * (min_dist - max_dist);
        shader_data.g_depth_params.y = 1.0f / min_dist;
        shader_data.g_depth_params.z = -((fl * dist * (min_dist - max_dist)) * (1.0f / (min_dist * max_dist)));
        shader_data.g_depth_params.w = (1.0f - 1.0f / min_dist * dist) * fl;
        shader_data.g_spread_scale.x = 720.0f / (tanf(fov * 0.5f) * (min_dist * 2.0f));
        shader_data.g_spread_scale.y = shader_data.g_spread_scale.x * (float_t)(1.0 / 3.0);
        shader_data.g_spread_scale.z = (float_t)(1.0 / 3.0);
        shader_data.g_spread_scale.w = 3.0f;
        shader_data.g_depth_params2.x = dist;
        shader_data.g_depth_params2.y = focus_range;
        shader_data.g_depth_params2.z = -4.5f / (fuzzing_range * fuzzing_range);
        shader_data.g_depth_params2.w = ratio * 8.0f;
        shader_data.g_dof_param.x = dof_param_tile_size;
        shader_data.g_dof_param.y = dof_param_prefilter_tap_num;
        shader_data.g_dof_param.z = dof_param_sample_division;
        shader_data.g_dof_param.w = dof_param_upsample_tap_num;
        rend_data_ctx.state.write_uniform_buffer(m_common_ubo, shader_data);
    }

    // 0x1404A7FA0
    template <int32_t sample_division>
    static void CalcTexcoord(vec2* data, const float_t size) {
        if (sample_division > 2 && size > 0.0f) {
            constexpr float_t scale = (float_t)(sample_division - 1) / 2.0f;
            constexpr float_t step = sample_division > 2 ? 1.0f / scale : 0.0f;
            const float_t radius = size * scale;

            for (int32_t i = 0, k = 0; i < sample_division; i++) {
                float_t x_coord = (float_t)i * step - 1.0f;
                for (int32_t j = 0; j < sample_division; j++, k++) {
                    float_t y_coord = (float_t)j * step - 1.0f;

                    vec2 coord;
                    calc_texcoord(coord, vec2(x_coord, y_coord));
                    data[k] = vec2(coord.x * radius, coord.y * radius);
                }
            }
        }
    }

    // 0x1404A9910
    static void calc_texcoord(vec2& dst, const vec2& src) {
        float_t size;
        float_t angle_mult;
        if (-src.x >= src.y) {
            if (src.y < src.x) {
                size = -src.y;
                angle_mult = (src.x / src.y) + 4.0f;
            }
            else if (src.x == 0.0f) {
                size = 0.0f;
                angle_mult = 0.0f;
            }
            else {
                size = -src.x;
                angle_mult = 6.0f - (src.y / src.x);
            }
        }
        else if (src.x < src.y) {
            size = src.y;
            angle_mult = src.x / src.y;
        }
        else {
            size = src.x;
            angle_mult = 2.0f - (src.y / src.x);
        }

        const float_t angle = angle_mult * (float_t)(M_PI * 0.25);
        dst = { cosf(angle) * size, sinf(angle) * size };
    }
}
