/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "transparency.hpp"
#include "../../KKdLib/str_utils.hpp"
#include "../gl_rend_state.hpp"
#include "../render.hpp"
#include "../render_context.hpp"
#include "../render_texture.hpp"
#include "../shader_ft.hpp"

extern render_context* rctx;

namespace renderer {
    // 0x1404A88F0
    Transparency::Transparency(GLuint color_tex, GLuint depth_tex,
        int32_t width, int32_t height) : m_sampler(), m_program(), m_vao() {
        GLuint color_tex_arr[1];
        color_tex_arr[0] = color_tex;
        m_fbo.init(width, height, color_tex_arr, 1, depth_tex);

        glGenSamplers(1, &m_sampler);
        glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glGenVertexArrays(1, &m_vao);
    }

    // 0x1404A8C90
    Transparency::~Transparency() {
        if (m_vao) {
            glDeleteVertexArrays(1, &m_vao);
            m_vao = 0;
        }

        if (m_sampler) {
            glDeleteSamplers(1, &m_sampler);
            m_sampler = 0;
        }
    }

    // 0x1404A92C0
    void Transparency::begin_render(render_data_context& rend_data_ctx, GLuint texture) {
        if (DIVA_GL_VERSION_4_3)
            rend_data_ctx.state.copy_image_sub_data(texture, GL_TEXTURE_2D, 0, 0, 0, 0,
                m_fbo.get_tex(), GL_TEXTURE_2D, 0, 0, 0, 0, m_fbo.get_width(), m_fbo.get_height(), 1);

        rend_data_ctx.state.bind_framebuffer(m_fbo.get_fbo());
        rend_data_ctx.state.set_viewport(0, 0, m_fbo.get_width(), m_fbo.get_height());

        if (!DIVA_GL_VERSION_4_3) {
            rend_data_ctx.state.disable_depth_test();
            rend_data_ctx.shader_flags.arr[U_REDUCE_TEX] = 0;
            shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_REDUCE);
            rend_data_ctx.state.active_bind_texture_2d(0, texture);
            rend_data_ctx.state.bind_sampler(0, rctx->render_samplers[1]);
            render_get()->draw_quad(rend_data_ctx, m_fbo.get_width(), m_fbo.get_height(),
                1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
            rend_data_ctx.state.enable_depth_test();
        }
    }

    // 0x1404AE550
    void Transparency::end_render(render_data_context& rend_data_ctx, RenderTexture* rt, float_t alpha) {
        transparency_batch_shader_data shader_data = {};
        shader_data.g_opacity = { alpha, 0.0f, 0.0f, 0.0f };
        rend_data_ctx.state.write_uniform_buffer(rctx->transparency_batch_ubo, shader_data);

        rend_data_ctx.state.disable_blend();
        rend_data_ctx.state.disable_depth_test();
        rctx->render_buffer.Bind(rend_data_ctx.state);
        shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_TRANSPARENCY);
        rend_data_ctx.state.bind_uniform_buffer_base(0, rctx->transparency_batch_ubo);
        rend_data_ctx.state.active_bind_texture_2d(0, m_fbo.get_tex());
        rend_data_ctx.state.active_bind_texture_2d(1, rt->GetColorTex());
        rend_data_ctx.state.bind_vertex_array(m_vao);
        rend_data_ctx.state.draw_arrays(GL_TRIANGLE_STRIP, 0, 4);
        rend_data_ctx.state.enable_depth_test();

        if (DIVA_GL_VERSION_4_3)
            rend_data_ctx.state.copy_image_sub_data(
                rctx->render_buffer.GetColorTex(), GL_TEXTURE_2D, 0, 0, 0, 0,
                rt->GetColorTex(), GL_TEXTURE_2D, 0, 0, 0, 0, m_fbo.get_width(), m_fbo.get_height(), 1);
        else
            fbo_blit(rend_data_ctx.state, rctx->render_buffer.fbos[0], rt->fbos[0],
                0, 0, m_fbo.get_width(), m_fbo.get_height(),
                0, 0, m_fbo.get_width(), m_fbo.get_height(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
        rt->Bind(rend_data_ctx.state);
    }

    // Added
    void Transparency::resize(GLuint color_tex, GLuint depth_tex, int32_t width, int32_t height) {
        GLuint color_tex_arr[1];
        color_tex_arr[0] = color_tex;
        m_fbo.init(width, height, color_tex_arr, 1, depth_tex);
    }
}
