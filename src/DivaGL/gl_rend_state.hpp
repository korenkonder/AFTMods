/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../KKdLib/default.hpp"
#include "gl.hpp"

enum gl_rend_state_index {
    GL_REND_STATE_PRE_3D = 0,
    GL_REND_STATE_3D,
    GL_REND_STATE_2D,
    GL_REND_STATE_POST_2D,
    GL_REND_STATE_COUNT,
};

struct gl_rend_state_rect {
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
};

struct p_gl_rend_state {
    struct gl_rend_state& ptr;

    p_gl_rend_state(gl_rend_state_index index);

    void active_bind_texture_2d(int32_t index, GLuint texture);
    void active_bind_texture_cube_map(int32_t index, GLuint texture);
    void active_texture(int32_t index);
    void begin_event(const char* message, int32_t length);
    void bind_framebuffer(GLuint framebuffer);
    void bind_read_framebuffer(GLuint framebuffer);
    void bind_draw_framebuffer(GLuint framebuffer);
    void bind_vertex_array(GLuint array);
    void bind_array_buffer(GLuint buffer);
    void bind_element_array_buffer(GLuint buffer);
    void bind_uniform_buffer(GLuint buffer);
    void bind_uniform_buffer_base(GLuint index, GLuint buffer);
    void bind_uniform_buffer_range(GLuint index,
        GLuint buffer, GLintptr offset, GLsizeiptr size);
    void bind_shader_storage_buffer(GLuint buffer);
    void bind_shader_storage_buffer_base(GLuint index, GLuint buffer);
    void bind_shader_storage_buffer_range(GLuint index,
        GLuint buffer, GLintptr offset, GLsizeiptr size);
    void bind_texture_2d(GLuint texture);
    void bind_texture_cube_map(GLuint texture);
    void bind_sampler(int32_t index, GLuint sampler);
    void blit_framebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
        GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
    GLenum check_framebuffer_status(GLenum target);
    void clear(GLbitfield mask);
    void clear_buffer(GLenum buffer, GLint drawbuffer, const GLfloat* value);
    void clear_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    void clear_depth(GLfloat depth);
    void clear_stencil(GLint stencil);
    void copy_image_sub_data(GLuint srcName, GLenum srcTarget, GLint srcLevel,
        GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel,
        GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
    void copy_tex_sub_image_2d(GLenum target, GLint level,
        GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
    void disable_blend();
    void disable_cull_face();
    void disable_depth_test();
    void disable_multisample();
    void disable_primitive_restart();
    void disable_scissor_test();
    void disable_stencil_test();
    void draw_arrays(GLenum mode, GLint first, GLsizei count);
    void draw_elements(GLenum mode,
        GLsizei count, GLenum type, const void* indices);
    void draw_range_elements(GLenum mode,
        GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices);
    void enable_blend();
    void enable_cull_face();
    void enable_depth_test();
    void enable_multisample();
    void enable_primitive_restart();
    void enable_scissor_test();
    void enable_stencil_test();
    void end_event();
    void generate_mipmap(GLenum target);
    void generate_texture_mipmap(GLuint texture);
    void get();
    void get_clear_color(GLfloat& red, GLfloat& green, GLfloat& blue, GLfloat& alpha);
    GLuint get_program();
    gl_rend_state_rect get_scissor();
    void get_scissor(GLint& x, GLint& y, GLsizei& width, GLsizei& height);
    gl_rend_state_rect get_viewport();
    void get_viewport(GLint& x, GLint& y, GLsizei& width, GLsizei& height);
    void set_blend_func(GLenum src, GLenum dst);
    void set_blend_func_separate(GLenum src_rgb, GLenum dst_rgb,
        GLenum src_alpha, GLenum dst_alpha);
    void set_blend_equation(GLenum mode);
    void set_blend_equation_separate(
        GLenum mode_rgb, GLenum mode_alpha);
    void set_color_mask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
    void set_cull_face_mode(GLenum mode);
    void set_depth_func(GLenum func);
    void set_depth_mask(GLboolean flag);
    void set_line_width(GLfloat width);
    void set_primitive_restart_index(GLuint index);
    void set_scissor(const gl_rend_state_rect& rect);
    void set_scissor(GLint x, GLint y, GLsizei width, GLsizei height);
    void set_stencil_func(GLenum func, GLint ref, GLuint mask);
    void set_stencil_mask(GLuint mask);
    void set_stencil_op(GLenum sfail, GLenum dpfail, GLenum dppass);
    void set_viewport(const gl_rend_state_rect& rect);
    void set_viewport(GLint x, GLint y, GLsizei width, GLsizei height);
    void update();
    void use_program(GLuint program);

    template <size_t size>
    inline void begin_event(const char(&str)[size]) {
        begin_event(str, (GLsizei)(size - 1));
    }
};
