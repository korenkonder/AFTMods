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
#include "../shader_ft.hpp"
#include <streambuf>

struct dof_common_shader_data {
    vec4 g_depth_params; //x=(n-f)/(nf), y=1/n, z=coc_from_z_scale, w=coc_from_z_offset
    vec4 g_spread_scale; //x=scale_from_meter_to_pixel, y=scale_from_meter_to_sample,
        //  z=scale_from_pixel_to_sample, w=scale_from_sample_to_pixel
    vec4 g_depth_params2; //x=distance_to_focus_m, y=focus_range,
        // z=k/(fuzzing_range*fuzzing_range), w=max_coc_radius_in_pixel   //yzw=for_f2
};

static_assert(sizeof(dof_common_shader_data) == 0x30, "\"dof_common_shader_data\" struct should have a size of 0x30");

dof_debug* dof_debug_data = (dof_debug*)0x00000001411AB650;
dof_pv* dof_pv_data = (dof_pv*)0x0000001411AB630;

namespace renderer {
    DOF3::DOF3(int32_t width, int32_t height)
        : textures(), samplers(), vao(), program() {
        this->width = width;
        this->height = height;

        init(width, height);
    }

    DOF3::~DOF3() {

    }

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

                            mat4 view;
                            mat4_transpose(&camera_data.view, &view);
                            focus = -vec3::dot(*(vec3*)&view.row2, chara_trans) - view.row2.w - 0.1f;
                            break;
                        }
                    }

                    focus = max_def(focus, camera_data.min_distance);
                    apply_physical(rend_data_ctx, rt, buf_rt, rt->GetColorTex(), rt->GetDepthTex(),
                        camera_data.min_distance, camera_data.max_distance,
                        focus, dof_debug_data->focal_length,
                        camera_data.fov * DEG_TO_RAD_FLOAT,
                        dof_debug_data->f_number);
                }
                else {
                    float_t fuzzing_range = max_def(dof_debug_data->f2.fuzzing_range, 0.01f);
                    apply_f2(rend_data_ctx, rt, buf_rt, rt->GetColorTex(), rt->GetDepthTex(),
                        camera_data.min_distance, camera_data.max_distance,
                        camera_data.fov * DEG_TO_RAD_FLOAT,
                        dof_debug_data->f2.focus, dof_debug_data->f2.focus_range,
                        fuzzing_range, dof_debug_data->f2.ratio);
                }
            }
        }
        else if (dof_pv_data->enable && dof_pv_data->f2.ratio > 0.0f) {
            float_t fuzzing_range = max_def(dof_pv_data->f2.fuzzing_range, 0.01f);
            apply_f2(rend_data_ctx, rt, buf_rt, rt->GetColorTex(), rt->GetDepthTex(),
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

    void DOF3::resize(int32_t width, int32_t height) {
        if (textures[0]) {
            glDeleteTextures(6, textures);
            textures[0] = 0;
        }

        this->width = width;
        this->height = height;

        init_textures(width, height);
    }

    void DOF3::free() {
        if (vao) {
            glDeleteVertexArrays(1, &vao);
            vao = 0;
        }

        common_ubo.Destroy();
        texcoords_ubo.Destroy();

        if (samplers[0]) {
            glDeleteSamplers(2, samplers);
            samplers[0] = 0;
        }

        if (textures[0]) {
            glDeleteTextures(6, textures);
            textures[0] = 0;
        }
    }

    void DOF3::init(int32_t width, int32_t height) {
        free();

        init_textures(width, height);

        glGenSamplers(2, samplers);
        glSamplerParameteri(samplers[0], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glSamplerParameteri(samplers[0], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glSamplerParameteri(samplers[0], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(samplers[0], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(samplers[1], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glSamplerParameteri(samplers[1], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glSamplerParameteri(samplers[1], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(samplers[1], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        common_ubo.Create(gl_state, sizeof(dof_common_shader_data));

        vec2 data[50] = {};
        renderer::DOF3::calculate_texcoords(data, 3.0f);
        texcoords_ubo.Create(gl_state, sizeof(data), data);

        glGenVertexArrays(1, &vao);
    }

    void DOF3::apply_f2(render_data_context& rend_data_ctx,
        RenderTexture* rt, RenderTexture* buf_rt, GLuint color_texture,
        GLuint depth_texture, float_t min_distance, float_t max_distance, float_t fov,
        float_t focus, float_t focus_range, float_t fuzzing_range, float_t ratio) {
        rend_data_ctx.state.begin_event("renderer::DOF3::apply_f2");
        rend_data_ctx.state.disable_blend();
        rend_data_ctx.state.set_depth_mask(GL_FALSE);
        rend_data_ctx.state.set_depth_func(GL_ALWAYS);
        update_data(rend_data_ctx, min_distance, max_distance,
            fov, focus, 0.0f, 1.0f, focus_range, fuzzing_range, ratio);

        rend_data_ctx.shader_flags.arr[U_DOF] = 1;

        rend_data_ctx.state.bind_vertex_array(vao);
        render_tiles(rend_data_ctx, depth_texture, true);
        downsample(rend_data_ctx, color_texture, depth_texture, true);
        apply_main_filter(rend_data_ctx, true);
        upsample(rend_data_ctx, rt, buf_rt, color_texture, depth_texture, true);

        rend_data_ctx.state.use_program(0);
        for (int32_t i = 0; i < 8; i++) {
            rend_data_ctx.state.bind_sampler(i, 0);
            rend_data_ctx.state.active_bind_texture_2d(i, 0);
        }
        rend_data_ctx.state.bind_vertex_array(0);
        rend_data_ctx.state.end_event();
    }

    void DOF3::apply_physical(render_data_context& rend_data_ctx,
        RenderTexture* rt, RenderTexture* buf_rt, GLuint color_texture,
        GLuint depth_texture, float_t min_distance, float_t max_distance,
        float_t focus, float_t focal_length, float_t fov, float_t f_number) {
        rend_data_ctx.state.begin_event("renderer::DOF3::apply_physical");
        rend_data_ctx.state.disable_blend();
        rend_data_ctx.state.set_depth_mask(GL_FALSE);
        rend_data_ctx.state.set_depth_func(GL_ALWAYS);
        update_data(rend_data_ctx, min_distance, max_distance,
            fov, focus, focal_length, f_number, 0.0f, 0.1f, 0.0f);

        rend_data_ctx.shader_flags.arr[U_DOF] = 0;

        rend_data_ctx.state.bind_vertex_array(vao);
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

    void DOF3::render_tiles(render_data_context& rend_data_ctx, GLuint depth_texture, bool f2) {
        rend_data_ctx.state.begin_event("renderer::DOF3::render_tiles");
        rend_data_ctx.state.bind_framebuffer(fbo[0].buffer);
        rend_data_ctx.state.set_viewport(0, 0, fbo[0].width, fbo[0].height);
        rend_data_ctx.shader_flags.arr[U_DOF_STAGE] = 0;
        shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_DOF);
        rend_data_ctx.state.bind_uniform_buffer_base(0, common_ubo);
        rend_data_ctx.state.active_bind_texture_2d(0, depth_texture);
        rend_data_ctx.state.bind_sampler(0, samplers[1]);
        rend_data_ctx.state.draw_arrays(GL_TRIANGLE_STRIP, 0, 4);

        rend_data_ctx.state.bind_framebuffer(fbo[1].buffer);
        rend_data_ctx.state.set_viewport(0, 0, fbo[1].width, fbo[1].height);
        rend_data_ctx.shader_flags.arr[U_DOF_STAGE] = 1;
        shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_DOF);
        rend_data_ctx.state.active_bind_texture_2d(0, textures[0]);
        rend_data_ctx.state.bind_sampler(0, samplers[1]);
        rend_data_ctx.state.draw_arrays(GL_TRIANGLE_STRIP, 0, 4);
        rend_data_ctx.state.end_event();

    }

    void DOF3::downsample(render_data_context& rend_data_ctx, GLuint color_texture, GLuint depth_texture, bool f2) {
        rend_data_ctx.state.begin_event("renderer::DOF3::downsample");
        rend_data_ctx.state.bind_framebuffer(fbo[2].buffer);
        rend_data_ctx.state.set_viewport(0, 0, fbo[2].width, fbo[2].height);
        rend_data_ctx.shader_flags.arr[U_DOF_STAGE] = 2;
        shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_DOF);
        rend_data_ctx.state.bind_uniform_buffer_base(0, common_ubo);
        rend_data_ctx.state.active_bind_texture_2d(0, depth_texture);
        rend_data_ctx.state.bind_sampler(0, samplers[1]);
        rend_data_ctx.state.active_bind_texture_2d(1, color_texture);
        rend_data_ctx.state.bind_sampler(1, samplers[0]);
        rend_data_ctx.state.active_bind_texture_2d(2, textures[1]);
        rend_data_ctx.state.bind_sampler(2, samplers[1]);
        rend_data_ctx.state.draw_arrays(GL_TRIANGLE_STRIP, 0, 4);
        rend_data_ctx.state.end_event();
    }

    void DOF3::apply_main_filter(render_data_context& rend_data_ctx, bool f2) {
        rend_data_ctx.state.begin_event("renderer::DOF3::apply_main_filter");
        rend_data_ctx.state.bind_framebuffer(fbo[3].buffer);
        rend_data_ctx.state.set_viewport(0, 0, fbo[3].width, fbo[3].height);
        rend_data_ctx.shader_flags.arr[U_DOF_STAGE] = 3;
        shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_DOF);
        rend_data_ctx.state.bind_uniform_buffer_base(0, common_ubo);
        rend_data_ctx.state.bind_uniform_buffer_base(1, texcoords_ubo);
        rend_data_ctx.state.active_bind_texture_2d(0, textures[3]);
        rend_data_ctx.state.bind_sampler(0, samplers[1]);
        rend_data_ctx.state.active_bind_texture_2d(1, textures[2]);
        rend_data_ctx.state.bind_sampler(1, samplers[1]);
        rend_data_ctx.state.active_bind_texture_2d(2, textures[1]);
        rend_data_ctx.state.bind_sampler(2, samplers[1]);
        rend_data_ctx.state.draw_arrays(GL_TRIANGLE_STRIP, 0, 4);
        rend_data_ctx.state.end_event();
    }

    void DOF3::upsample(render_data_context& rend_data_ctx,
        RenderTexture* rt, RenderTexture* buf_rt,
        GLuint color_texture, GLuint depth_texture, bool f2) {
        rend_data_ctx.state.begin_event("renderer::DOF3::upsample");
        buf_rt->Bind(rend_data_ctx.state);
        rend_data_ctx.state.set_viewport(0, 0, width, height);
        rend_data_ctx.shader_flags.arr[U_DOF_STAGE] = 4;
        shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_DOF);
        rend_data_ctx.state.bind_uniform_buffer_base(0, common_ubo);
        rend_data_ctx.state.active_bind_texture_2d(0, textures[4]);
        rend_data_ctx.state.bind_sampler(0, samplers[1]);
        rend_data_ctx.state.active_bind_texture_2d(1, textures[5]);
        rend_data_ctx.state.bind_sampler(1, samplers[1]);
        rend_data_ctx.state.active_bind_texture_2d(2, textures[1]);
        rend_data_ctx.state.bind_sampler(2, samplers[1]);
        rend_data_ctx.state.active_bind_texture_2d(3, color_texture);
        rend_data_ctx.state.bind_sampler(3, samplers[1]);
        rend_data_ctx.state.active_bind_texture_2d(4, depth_texture);
        rend_data_ctx.state.bind_sampler(4, samplers[1]);
        rend_data_ctx.state.draw_arrays(GL_TRIANGLE_STRIP, 0, 4);

        if (DIVA_GL_VERSION_4_3)
            rend_data_ctx.state.copy_image_sub_data(
                buf_rt->GetColorTex(), GL_TEXTURE_2D, 0, 0, 0, 0,
                rt->GetColorTex(), GL_TEXTURE_2D, 0, 0, 0, 0, width, height, 1);
        else
            fbo_blit(rend_data_ctx.state, buf_rt->fbos[0], rt->fbos[0],
                0, 0, width, height,
                0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        rend_data_ctx.state.end_event();
    }

    void DOF3::init_textures(int32_t width, int32_t height) {
        int32_t w20 = max_def(width / 20, 1);
        int32_t h20 = max_def(height / 20, 1);
        int32_t w2 = max_def(width / 2, 1);
        int32_t h2 = max_def(height / 2, 1);

        glGenTextures(6, textures);
        gl_state.bind_texture_2d(textures[0]);
        glTexImage2DDLL(GL_TEXTURE_2D, 0, GL_RG16F, w20, h20, 0, GL_RG, GL_HALF_FLOAT, 0);
        fbo[0].init(w20, h20, &textures[0], 1, 0);

        gl_state.bind_texture_2d(textures[1]);
        glTexImage2DDLL(GL_TEXTURE_2D, 0, GL_RG16F, w20, h20, 0, GL_RG, GL_HALF_FLOAT, 0);
        fbo[1].init(w20, h20, &textures[1], 1, 0);

        gl_state.bind_texture_2d(textures[2]);
        glTexImage2DDLL(GL_TEXTURE_2D, 0, GL_R11F_G11F_B10F, w2, h2, 0, GL_RGB, GL_UNSIGNED_INT_10F_11F_11F_REV, 0);
        gl_state.bind_texture_2d(textures[3]);
        glTexImage2DDLL(GL_TEXTURE_2D, 0, GL_R11F_G11F_B10F, w2, h2, 0, GL_RGB, GL_UNSIGNED_INT_10F_11F_11F_REV, 0);
        fbo[2].init(w2, h2, &textures[2], 2, 0);

        gl_state.bind_texture_2d(textures[4]);
        glTexImage2DDLL(GL_TEXTURE_2D, 0, GL_R11F_G11F_B10F, w2, h2, 0, GL_RGB, GL_UNSIGNED_INT_10F_11F_11F_REV, 0);
        gl_state.bind_texture_2d(textures[5]);
        glTexImage2DDLL(GL_TEXTURE_2D, 0, GL_R8, w2, h2, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
        fbo[3].init(w2, h2, &textures[4], 2, 0);
    }

    void DOF3::update_data(render_data_context& rend_data_ctx,
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
        common_ubo.WriteMemory(rend_data_ctx.state, shader_data);
    }

    void DOF3::calculate_texcoords(vec2* data, float_t size) {
        size_t i;
        size_t j;
        float_t v6;
        float_t v7;
        float_t v8;
        float_t v9;
        float_t v11;

        const float_t t = (float_t)(1.0 / 3.0);
        size *= 3.0f;
        for (i = 0; i < 7; i++) {
            v6 = (float_t)i * t - 1.0f;
            for (j = 0; j < 7; j++) {
                v7 = (float_t)j * t - 1.0f;
                if (-v6 >= v7) {
                    if (v7 < v6) {
                        v8 = -v7;
                        v9 = (v6 / v7) + 4.0f;
                    }
                    else if (v6 == 0.0f) {
                        v8 = 0.0f;
                        v9 = 0.0f;
                    }
                    else {
                        v8 = -v6;
                        v9 = 6.0f - (v7 / v6);
                    }
                }
                else if (v6 < v7) {
                    v8 = (float_t)j * t - 1.0f;
                    v9 = v6 / v7;
                }
                else {
                    v8 = (float_t)i * t - 1.0f;
                    v9 = 2.0f - (v7 / v6);
                }
                v8 *= size;
                v11 = v9 * (float_t)(M_PI * 0.25);

                *data++ = vec2(cosf(v11), sinf(v11)) * v8;
            }
        }
    }
}
