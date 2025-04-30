/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "transparency.hpp"
#include "../../KKdLib/str_utils.hpp"
#include "../gl_rend_state.hpp"
#include "../render_context.hpp"
#include "../shader_ft.hpp"

extern render_context* rctx;

namespace renderer {
    Transparency::Transparency(GLuint color_texture, GLuint depth_texture,
        int32_t width, int32_t height) : sampler(), program(), vao() {
        GLuint color_textures[1];
        color_textures[0] = color_texture;
        fbo.init(width, height, color_textures, 1, depth_texture);

        glGenSamplers(1, &sampler);
        glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glGenVertexArrays(1, &vao);
    }

    Transparency::~Transparency() {
        if (vao) {
            glDeleteVertexArrays(1, &vao);
            vao = 0;
        }

        if (sampler) {
            glDeleteSamplers(1, &sampler);
            sampler = 0;
        }
    }

    void Transparency::combine(render_data_context& rend_data_ctx, RenderTexture* rt, float_t alpha) {
        transparency_batch_shader_data shader_data = {};
        shader_data.g_opacity = { alpha, 0.0f, 0.0f, 0.0f };
        rctx->transparency_batch_ubo.WriteMemory(rend_data_ctx.state, shader_data);

        rend_data_ctx.state.disable_blend();
        rend_data_ctx.state.disable_depth_test();
        rctx->render_buffer.Bind(rend_data_ctx.state);
        shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_TRANSPARENCY);
        rend_data_ctx.state.bind_uniform_buffer_base(0, rctx->transparency_batch_ubo);
        rend_data_ctx.state.active_bind_texture_2d(0, fbo.textures[0]);
        rend_data_ctx.state.active_bind_texture_2d(1, rt->GetColorTex());
        rend_data_ctx.state.bind_vertex_array(vao);
        rend_data_ctx.state.draw_arrays(GL_TRIANGLE_STRIP, 0, 4);
        rend_data_ctx.state.enable_depth_test();

        if (DIVA_GL_VERSION_4_3)
            rend_data_ctx.state.copy_image_sub_data(
                rctx->render_buffer.GetColorTex(), GL_TEXTURE_2D, 0, 0, 0, 0,
                rt->GetColorTex(), GL_TEXTURE_2D, 0, 0, 0, 0, fbo.width, fbo.height, 1);
        else
            fbo_blit(rend_data_ctx.state, rctx->render_buffer.fbos[0], rt->fbos[0],
                0, 0, fbo.width, fbo.height,
                0, 0, fbo.width, fbo.height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }

    void Transparency::copy(render_data_context& rend_data_ctx, GLuint texture) {
        if (DIVA_GL_VERSION_4_3)
            rend_data_ctx.state.copy_image_sub_data(texture, GL_TEXTURE_2D, 0, 0, 0, 0,
                fbo.textures[0], GL_TEXTURE_2D, 0, 0, 0, 0, fbo.width, fbo.height, 1);

        rend_data_ctx.state.bind_framebuffer(fbo.buffer);
        rend_data_ctx.state.set_viewport(0, 0, fbo.width, fbo.height);

        if (!DIVA_GL_VERSION_4_3) {
            rend_data_ctx.state.disable_depth_test();
            rend_data_ctx.shader_flags.arr[U_REDUCE] = 0;
            shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_REDUCE);
            rend_data_ctx.state.active_bind_texture_2d(0, texture);
            rend_data_ctx.state.bind_sampler(0, rctx->render_samplers[1]);
            render_get()->draw_quad(rend_data_ctx, fbo.width, fbo.height,
                1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
            rend_data_ctx.state.enable_depth_test();
        }
    }

    void Transparency::resize(GLuint color_texture, GLuint depth_texture, int32_t width, int32_t height) {
        GLuint color_textures[1];
        color_textures[0] = color_texture;
        fbo.init(width, height, color_textures, 1, depth_texture);
    }
}
