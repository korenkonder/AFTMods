/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../KKdLib/default.hpp"
#include "wrap.hpp"

struct gl_rend_state_rect {
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
};

struct gl_rend_state_struct {
    GLint program;
    GLuint active_texture_index;
    GLint texture_binding_2d[32];
    GLint texture_binding_cube_map[32];
    GLint sampler_binding[32];
    GLboolean blend;
    GLenum blend_src_rgb;
    GLenum blend_src_alpha;
    GLenum blend_dst_rgb;
    GLenum blend_dst_alpha;
    GLenum blend_mode_rgb;
    GLenum blend_mode_alpha;
    GLuint framebuffer_binding;
    GLuint read_framebuffer_binding;
    GLuint draw_framebuffer_binding;
    GLuint vertex_array_binding;
    GLuint array_buffer_binding;
    GLuint element_array_buffer_binding;
    GLuint uniform_buffer_binding;
    GLuint uniform_buffer_bindings[14];
    GLintptr uniform_buffer_offsets[14];
    GLsizeiptr uniform_buffer_sizes[14];
    GLuint shader_storage_buffer_binding;
    GLuint shader_storage_buffer_bindings[14];
    GLintptr shader_storage_buffer_offsets[14];
    GLsizeiptr shader_storage_buffer_sizes[14];
    GLboolean color_mask[4];
    GLboolean cull_face;
    GLenum cull_face_mode;
    GLboolean depth_test;
    GLenum depth_func;
    GLboolean depth_mask;
    GLfloat line_width;
    GLenum polygon_mode;
    GLboolean multisample;
    GLboolean primitive_restart;
    GLuint primitive_restart_index;
    gl_rend_state_rect scissor_box;
    GLboolean scissor_test;
    GLboolean stencil_test;
    GLenum stencil_func;
    GLenum stencil_fail;
    GLenum stencil_dpfail;
    GLenum stencil_dppass;
    GLuint stencil_mask;
    GLint stencil_ref;
    GLuint stencil_value_mask;
    gl_rend_state_rect viewport;

    void active_bind_texture_2d(int32_t index, GLuint texture, bool force = false);
    void active_bind_texture_cube_map(int32_t index, GLuint texture, bool force = false);
    void active_texture(size_t index, bool force = false);
    void bind_framebuffer(GLuint framebuffer, bool force = false);
    void bind_read_framebuffer(GLuint framebuffer, bool force = false);
    void bind_draw_framebuffer(GLuint framebuffer, bool force = false);
    void bind_vertex_array(GLuint array, bool force = false);
    void bind_array_buffer(GLuint buffer, bool force = false);
    void bind_element_array_buffer(GLuint buffer, bool force = false);
    void bind_uniform_buffer(GLuint buffer, bool force = false);
    void bind_uniform_buffer_base(GLuint index, GLuint buffer, bool force = false);
    void bind_uniform_buffer_range(GLuint index,
        GLuint buffer, GLintptr offset, GLsizeiptr size, bool force = false);
    void bind_shader_storage_buffer(GLuint buffer, bool force = false);
    void bind_shader_storage_buffer_base(GLuint index, GLuint buffer, bool force = false);
    void bind_shader_storage_buffer_range(GLuint index,
        GLuint buffer, GLintptr offset, GLsizeiptr size, bool force = false);
    void bind_texture_2d(GLuint texture, bool force = false);
    void bind_texture_cube_map(GLuint texture, bool force = false);
    void bind_sampler(int32_t index, GLuint sampler, bool force = false);
    bool check_uniform_buffer_binding();
    bool check_uniform_buffer_binding_base(size_t index);
    bool check_shader_storage_buffer_binding();
    bool check_shader_storage_buffer_binding_base(size_t index);
    bool check_texture_binding_2d(size_t index);
    bool check_texture_binding_cube_map(size_t index);
    bool check_sampler_binding(int32_t index, GLuint sampler);
    void disable_blend(bool force = false);
    void disable_cull_face(bool force = false);
    void disable_depth_test(bool force = false);
    void disable_multisample(bool force = false);
    void disable_primitive_restart(bool force = false);
    void disable_scissor_test(bool force = false);
    void disable_stencil_test(bool force = false);
    void enable_blend(bool force = false);
    void enable_cull_face(bool force = false);
    void enable_depth_test(bool force = false);
    void enable_multisample(bool force = false);
    void enable_primitive_restart(bool force = false);
    void enable_scissor_test(bool force = false);
    void enable_stencil_test(bool force = false);
    void get();
    GLuint get_program();
    gl_rend_state_rect get_scissor();
    void get_scissor(GLint& x, GLint& y, GLsizei& width, GLsizei& height);
    gl_rend_state_rect get_viewport();
    void get_viewport(GLint& x, GLint& y, GLsizei& width, GLsizei& height);
    void set_blend_func(GLenum src, GLenum dst, bool force = false);
    void set_blend_func_separate(GLenum src_rgb, GLenum dst_rgb,
        GLenum src_alpha, GLenum dst_alpha, bool force = false);
    void set_blend_equation(GLenum mode, bool force = false);
    void set_blend_equation_separate(
        GLenum mode_rgb, GLenum mode_alpha, bool force = false);
    void set_color_mask(GLboolean red, GLboolean green,
        GLboolean blue, GLboolean alpha, bool force = false);
    void set_cull_face_mode(GLenum mode, bool force = false);
    void set_depth_func(GLenum func, bool force = false);
    void set_depth_mask(GLboolean flag, bool force = false);
    void set_line_width(GLfloat width, bool force = false);
    void set_polygon_mode(GLenum face, GLenum mode, bool force = false);
    void set_primitive_restart_index(GLuint index, bool force = false);
    void set_scissor(const gl_rend_state_rect& rect, bool force = false);
    void set_scissor(GLint x, GLint y, GLsizei width, GLsizei height, bool force = false);
    void set_stencil_func(GLenum func, GLint ref, GLuint mask, bool force = false);
    void set_stencil_mask(GLuint mask, bool force = false);
    void set_stencil_op(GLenum sfail, GLenum dpfail, GLenum dppass, bool force = false);
    void set_viewport(const gl_rend_state_rect& rect, bool force = false);
    void set_viewport(GLint x, GLint y, GLsizei width, GLsizei height, bool force = false);
    void use_program(GLuint program, bool force = false);

    template <size_t size>
    inline void begin_event(const char(&str)[size]) {
        glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, (GLsizei)(size - 1), str);
    }

    inline void end_event() {
        glPopDebugGroup();
    }

};

extern gl_rend_state_struct gl_rend_state;
