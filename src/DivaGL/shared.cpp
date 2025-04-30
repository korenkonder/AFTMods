/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "shared.hpp"
#include "gl_rend_state.hpp"

void fbo_blit(p_gl_rend_state& p_gl_rend_st, GLuint src_fbo, GLuint dst_fbo,
    GLint src_x, GLint src_y, GLint src_width, GLint src_height,
    GLint dst_x, GLint dst_y, GLint dst_width, GLint dst_height, GLbitfield mask, GLenum filter) {
    p_gl_rend_st.bind_read_framebuffer(src_fbo);
    p_gl_rend_st.bind_draw_framebuffer(dst_fbo);
    p_gl_rend_st.blit_framebuffer(src_x, src_y, src_x + src_width, src_y + src_height,
        dst_x, dst_y, dst_x + dst_width, dst_y + dst_height, mask, filter);
}

void gl_get_error_all_print() {
    GLenum error;
    while (error = glGetErrorDLL())
        printf_debug("GL Error: 0x%04X\n", error);
}

GLenum gl_get_error_print() {
    GLenum error = glGetErrorDLL();
    if (error)
        printf_debug("GL Error: 0x%04X\n", error);
    return error;
}
