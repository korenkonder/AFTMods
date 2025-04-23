/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../AFTModsShared/shared.hpp"
#include "wrap.hpp"

extern void fbo_blit(GLuint src_fbo, GLuint dst_fbo,
    GLint src_x, GLint src_y, GLint src_width, GLint src_height,
    GLint dst_x, GLint dst_y, GLint dst_width, GLint dst_height, GLbitfield mask, GLenum filter);

extern void gl_get_error_all_print();
extern GLenum gl_get_error_print();
