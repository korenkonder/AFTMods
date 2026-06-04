/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "shared.hpp"
#include "gl_rend_state.hpp"
#include "texture.hpp"

class RenderTexture {
private:
    static int32_t& m_tex_count;

public:
    texture* m_txhd_color;
    texture* m_txhd_depth;
    int32_t m_tex_unit;
    int32_t m_level;
    GLuint* m_fb;
    GLuint m_rb_depth;
    GLuint m_rb_stencil;

private:
    int32_t create_fbo(int32_t level);
    int32_t set_render_target(GLuint color, int32_t level, GLuint depth, bool stencil);
    //int32_t create_depth_buffer(GLenum internal_format, int32_t width, int32_t height);
    //int32_t create_stencil_buffer(GLenum internal_format, int32_t width, int32_t height);

public:
    static void init();

    RenderTexture();
    virtual ~RenderTexture();

    int32_t create_texture(int32_t width, int32_t height, int32_t level, GLenum pixel_format, GLenum depth_format);
    int32_t attach_texture(texture* color_tex, int32_t level = 0, texture* depth_tex = 0, bool stencil = false);
    int32_t attach_texture(GLuint color_tex, int32_t level = 0, GLuint depth_tex = 0, bool stencil = false);
    void destroy();
    int32_t begin_render(struct gl_state_struct& gl_st, int32_t level = 0);
    int32_t begin_render(struct p_gl_rend_state& p_gl_rend_st, int32_t level = 0);
    void end_render(struct gl_state_struct& gl_st);
    void end_render(struct p_gl_rend_state& p_gl_rend_st);
    texture* get_texture();
    void bind_texture(struct p_gl_rend_state& p_gl_rend_st, uint32_t tex_unit);
    void unbind_texture(struct p_gl_rend_state& p_gl_rend_st);
    texture* get_depth_texture();

    void set_viewport(struct p_gl_rend_state& p_gl_rend_st); // Added

    // Added
    inline GLuint get_fb(int32_t level = 0) {
        return m_fb[level];
    }

    // Added
    inline GLuint get_texture_glid() {
        return m_txhd_color->glid;
    }

    // Added
    inline GLuint get_depth_texture_glid() {
        return m_txhd_depth->glid;
    }

    // Added
    inline int32_t get_width() {
        return m_txhd_color->width;
    }

    // Added
    inline int32_t get_height() {
        return m_txhd_color->height;
    }
};

static_assert(sizeof(RenderTexture) == 0x30, "\"RenderTexture\" struct should have a size of 0x30");

extern void render_texture_patch();

// Inlined
inline texture* RenderTexture::get_texture() {
    return m_txhd_color;
}

// Inlined
inline texture* RenderTexture::get_depth_texture() {
    return m_txhd_depth;
}
