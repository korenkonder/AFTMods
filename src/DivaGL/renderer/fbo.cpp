/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "fbo.hpp"
#include "../../AFTModsShared/types.hpp"
#include "../gl_rend_state.hpp"
#include "../gl_state.hpp"

namespace renderer {
    // 0x1404A8330
    FBO::FBO() : m_flag(), m_width(), m_height(), m_fbo(), m_num_tex(), m_tex() {

    }

    // 0x1404A8AA0
    FBO::~FBO() {
        free();
    }

#pragma warning(push)
#pragma warning(disable: 6385)
#pragma warning(disable: 6386)
    // 0x1404AEF40
    void FBO::init(int32_t width, int32_t height,
        const GLuint* color_tex, int32_t num_tex, GLuint depth_tex) {
        free();

        num_tex = min_def(num_tex, 8);

        m_width = width;
        m_height = height;
        m_num_tex = num_tex;
        m_flag = 0;
        if (depth_tex) {
            m_flag |= DEPTH_ATTACHMENT;
            m_num_tex++;
        }

        m_tex = new GLuint[m_num_tex];
        for (int32_t i = 0; i < num_tex; i++)
            m_tex[i] = color_tex[i];

        if (m_flag & DEPTH_ATTACHMENT)
            m_tex[num_tex] = depth_tex;

        glGenFramebuffers(1, &m_fbo);
        gl_state.bind_framebuffer(m_fbo, true);
        for (int32_t i = 0; i < num_tex; i++)
            glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, m_tex[i], 0);

        if (m_flag & DEPTH_ATTACHMENT)
            glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_tex[num_tex], 0);

        GLenum color_attachments[8];
        for (int32_t i = 0; i < num_tex; i++)
            color_attachments[i] = GL_COLOR_ATTACHMENT0 + i;
        glDrawBuffers(num_tex, color_attachments);
        glCheckFramebufferStatus(GL_FRAMEBUFFER);
        gl_state.bind_framebuffer(0);
    }
#pragma warning(pop)

    // Inlined
    void FBO::free() {
        if (m_fbo) {
            glDeleteFramebuffers(1, &m_fbo);
            m_fbo = 0;
        }

        if (m_tex) {
            _operator_delete(m_tex);
            m_tex = 0;
        }
    }

    // 0x1404A93D0
    void FBO::bind_fbo(p_gl_rend_state& p_gl_rend_st) {
        p_gl_rend_st.bind_framebuffer(m_fbo);
        p_gl_rend_st.set_viewport(0, 0, m_width, m_height);
    }
}
