/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "render_texture.hpp"
#include "gl_rend_state.hpp"
#include "gl_state.hpp"
#include <Helpers.h>

int32_t& RenderTexture::m_tex_count = *(int32_t*)0x00000001411AD648;

// 0x140503310
int32_t RenderTexture::create_fbo(int32_t level) {
    int32_t level_count = level + 1;
    m_fb = prj::MemoryManager::alloc<GLuint>(prj::MemCSystem, level_count, "FBO");
    if (!m_fb)
        return -1;

    glGenFramebuffers(level_count, m_fb);
    return gl_get_error_print() != GL_ZERO ? -1 : 0;
}

// 0x1405036A0
int32_t RenderTexture::set_render_target(GLuint color, int32_t level, GLuint depth, bool stencil) {
    if (level < 0 || level > m_level)
        return -1;

    gl_state.bind_framebuffer(m_fb[level]);
    gl_get_error_print();

    if (color) {
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, color, level);
        gl_get_error_print();
        glDrawBufferDLL(GL_COLOR_ATTACHMENT0);
        glReadBufferDLL(GL_COLOR_ATTACHMENT0);
    }
    else {
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 0, 0);
        gl_get_error_print();
        glDrawBufferDLL(GL_ZERO);
        glReadBufferDLL(GL_ZERO);
    }
    gl_get_error_print();

    if (!level) {
        GLenum attechment = stencil ? GL_DEPTH_STENCIL_ATTACHMENT : GL_DEPTH_ATTACHMENT;
        if (depth)
            glFramebufferTexture(GL_FRAMEBUFFER, attechment, depth, 0);
        /*else if (m_rb_depth) {
            glBindRenderbuffer(GL_RENDERBUFFER, m_rb_depth);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, attechment, GL_RENDERBUFFER, m_rb_depth);
        }*/
        else
            glFramebufferTexture(GL_FRAMEBUFFER, attechment, 0, 0);
        gl_get_error_print();
    }

    int32_t ret = 0;
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        ret = -1;
    gl_state.bind_framebuffer(0);
    gl_get_error_print();
    return ret;
}

// 0x140503260
/*int32_t RenderTexture::create_depth_buffer(GLenum internal_format, int32_t width, int32_t height) {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fb[0]);
    glGenRenderbuffers(1, &m_rb_depth);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rb_depth);
    glRenderbufferStorage(GL_RENDERBUFFER, internal_format, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rb_depth);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return gl_get_error_print() != GL_ZERO ? -1 : 0;
}*/

// 0x140503370
/*int32_t RenderTexture::create_stencil_buffer(GLenum internal_format, int32_t width, int32_t height) {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fb[0]);
    glGenRenderbuffers(1, &m_rb_stencil);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rb_stencil);
    glRenderbufferStorage(GL_RENDERBUFFER, internal_format, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rb_stencil);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return gl_get_error_print() != GL_ZERO ? -1 : 0;
}*/

// 0x140503680
void RenderTexture::init() {
    m_tex_count = 0;
}

// 0x1405030C0
RenderTexture::RenderTexture() : m_txhd_color(), m_txhd_depth(),
m_tex_unit(), m_level(), m_fb(), m_rb_depth(), m_rb_stencil() {

}

// 0x1405030F0
RenderTexture::~RenderTexture() {
    destroy();
}

// 0x140503420
int32_t RenderTexture::create_texture(int32_t width, int32_t height, int32_t level, GLenum pixel_format, GLenum depth_format) {
    if (level < 0)
        return -1;

    destroy();

    GLuint color;
    if (pixel_format) {
        m_txhd_color = texture_load_tex_2d(0x23000000 | m_tex_count,
            pixel_format, width, height, level, 0, 0);
        if (!m_txhd_color)
            return -1;

        m_tex_count++;
        color = get_texture_glid();
        if (pixel_format == GL_RGBA32F) {
            gl_state.bind_texture_2d(color);
            glTexParameteriDLL(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteriDLL(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gl_state.bind_texture_2d(0);
        }
    }
    else {
        m_txhd_color = 0;
        color = 0;
    }

    GLuint depth;
    bool stencil;
    if (depth_format) {
        m_txhd_depth = texture_load_tex_2d(0x23000000 | m_tex_count,
            depth_format, width, height, 0, 0, 0);
        if (!m_txhd_depth)
            return -1;

        m_tex_count++;
        depth = get_depth_texture_glid();
        stencil = depth_format == GL_DEPTH24_STENCIL8 || depth_format == GL_DEPTH32F_STENCIL8;
    }
    else {
        m_txhd_depth = 0;
        depth = 0;
        stencil = false;
    }
    m_level = level;

    if (create_fbo(level) < 0)
        return -1;

    for (int32_t i = 0; i <= level; i++)
        if (set_render_target(color, i, depth, stencil) < 0)
            return -1;
    return 0;
}

// Missing
int32_t RenderTexture::attach_texture(texture* color_tex, int32_t level, texture* depth_tex, bool stencil) {
    m_level = level;

    int32_t error = 0;
    if (!m_fb)
        error = create_fbo(level);

    m_txhd_color = color_tex;
    m_txhd_depth = depth_tex;
    set_render_target(color_tex ? color_tex->glid : 0, level, depth_tex ? depth_tex->glid : 0, stencil);
    return error;
}

// 0x140503130
int32_t RenderTexture::attach_texture(GLuint color_tex, int32_t level, GLuint depth_tex, bool stencil) {
    m_level = level;

    int32_t error = 0;
    if (!m_fb)
        error = create_fbo(level);

    set_render_target(color_tex, level, depth_tex, stencil);
    return error;
}

// 0x1405035C0
void RenderTexture::destroy() {
    if (m_txhd_depth) {
        texture_release(m_txhd_depth);
        m_txhd_depth = 0;
    }

    if (m_txhd_color) {
        texture_release(m_txhd_color);
        m_txhd_color = 0;
    }

    /*if (m_rb_depth) {
        glDeleteRenderbuffers(1, &m_rb_depth);
        m_rb_depth = 0;
    }

    if (m_rb_stencil) {
        glDeleteRenderbuffers(1, &m_rb_stencil);
        m_rb_stencil = 0;
    }*/

    if (m_fb) {
        glDeleteFramebuffers(m_level + 1, m_fb);
        prj::MemoryManager::free(prj::MemCSystem, m_fb);
        m_fb = 0;
    }
    m_level = 0;
}

// 0x1405031A0
int32_t RenderTexture::begin_render(gl_state_struct& gl_st, int32_t level) {
    if (level < 0 || level > m_level)
        return -1;

    gl_st.bind_framebuffer(m_fb[level]);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return -1;

    gl_get_error_print();
    return 0;
}

// 0x1405031A0
int32_t RenderTexture::begin_render(p_gl_rend_state& p_gl_rend_st, int32_t level) {
    if (level < 0 || level > m_level)
        return -1;

    p_gl_rend_st.bind_framebuffer(m_fb[level]);
    if (p_gl_rend_st.check_framebuffer_status(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return -1;

    gl_get_error_print();
    return 0;
}

// 0x140503660
void RenderTexture::end_render(gl_state_struct& gl_st) {
    gl_st.bind_framebuffer(0);
    gl_get_error_print();
}

// 0x140503660
void RenderTexture::end_render(p_gl_rend_state& p_gl_rend_st) {
    p_gl_rend_st.bind_framebuffer(0);
    gl_get_error_print();
}

// 0x140503200
void RenderTexture::bind_texture(p_gl_rend_state& p_gl_rend_st, uint32_t tex_unit) {
    m_tex_unit = tex_unit;
    p_gl_rend_st.active_bind_texture_2d(tex_unit, m_txhd_color->glid);
}

// 0x1405037F0
void RenderTexture::unbind_texture(p_gl_rend_state& p_gl_rend_st) {
    p_gl_rend_st.bind_texture_2d(m_tex_unit);
}

// Added
void RenderTexture::set_viewport(p_gl_rend_state& p_gl_rend_st) {
    p_gl_rend_st.set_viewport(0, 0, get_width(), get_height());
}

void render_texture_patch() {

}
