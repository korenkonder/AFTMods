/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../../KKdLib/default.hpp"
#include "../gl.hpp"
#include "../shared.hpp"

struct p_gl_rend_state;

namespace renderer {
    class FBO {
    private:
        enum {
            DEPTH_ATTACHMENT = 0x01,
        };

        uint32_t m_flag;
        int32_t m_width;
        int32_t m_height;
        GLuint m_fbo;
        int32_t m_num_tex;
        GLuint* m_tex;

    public:
        FBO();
        ~FBO();

        void init(int32_t width, int32_t height,
            const GLuint* color_tex, int32_t num_tex, GLuint depth_tex);
        void free();

        void bind_fbo(p_gl_rend_state& p_gl_rend_st);

        int32_t get_width() const;
        int32_t get_height() const;
        GLuint get_fbo() const;
        GLuint get_tex(int32_t index = 0) const;
    };

    static_assert(sizeof(renderer::FBO) == 0x20, "\"renderer::FBO\" struct should have a size of 0x20");

    // Inlined
    inline int32_t FBO::get_width() const {
        return m_width;
    }

    // Inlined
    inline int32_t FBO::get_height() const {
        return m_height;
    }

    // Inlined
    inline GLuint FBO::get_fbo() const {
        return m_fbo;
    }

    // Inlined
    inline GLuint FBO::get_tex(int32_t index) const {
        return m_tex[index];
    }
}
