/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "gl_rend_state.hpp"
#include "shared.hpp"

enum gl_rend_state_update_flags : uint32_t {
    GL_REND_STATE_UPDATE_PROGRAM                 = 1u <<  0,
    GL_REND_STATE_UPDATE_TEXTURE                 = 1u <<  1,
    GL_REND_STATE_UPDATE_ACTIVE_TEXTURE          = 1u <<  2,
    GL_REND_STATE_UPDATE_SAMPLER                 = 1u <<  3,
    GL_REND_STATE_UPDATE_BLEND                   = 1u <<  4,
    GL_REND_STATE_UPDATE_BLEND_FUNC              = 1u <<  5,
    GL_REND_STATE_UPDATE_BLEND_EQUATION          = 1u <<  6,
    GL_REND_STATE_UPDATE_READ_FRAMEBUFFER        = 1u <<  7,
    GL_REND_STATE_UPDATE_DRAW_FRAMEBUFFER        = 1u <<  8,
    GL_REND_STATE_UPDATE_VERTEX_ARRAY            = 1u <<  9,
    GL_REND_STATE_UPDATE_UNIFORM_BUFFER          = 1u << 10,
    GL_REND_STATE_UPDATE_SHADER_STORAGE_BUFFER   = 1u << 11,
    GL_REND_STATE_UPDATE_COLOR_MASK              = 1u << 12,
    GL_REND_STATE_UPDATE_CULL_FACE               = 1u << 13,
    GL_REND_STATE_UPDATE_CULL_FACE_MODE          = 1u << 14,
    GL_REND_STATE_UPDATE_DEPTH_TEST              = 1u << 15,
    GL_REND_STATE_UPDATE_DEPTH_MASK              = 1u << 16,
    GL_REND_STATE_UPDATE_DEPTH_FUNC              = 1u << 17,
    GL_REND_STATE_UPDATE_LINE_WIDTH              = 1u << 18,
    GL_REND_STATE_UPDATE_MULTISAMPLE             = 1u << 19,
    GL_REND_STATE_UPDATE_PRIMITIVE_RESTART       = 1u << 20,
    GL_REND_STATE_UPDATE_PRIMITIVE_RESTART_INDEX = 1u << 21,
    GL_REND_STATE_UPDATE_SCISSOR_TEST            = 1u << 22,
    GL_REND_STATE_UPDATE_SCISSOR                 = 1u << 23,
    GL_REND_STATE_UPDATE_STENCIL_TEST            = 1u << 24,
    GL_REND_STATE_UPDATE_STENCIL_MASK            = 1u << 25,
    GL_REND_STATE_UPDATE_STENCIL_FUNC            = 1u << 26,
    GL_REND_STATE_UPDATE_STENCIL_OP              = 1u << 27,
    GL_REND_STATE_UPDATE_VIEWPORT                = 1u << 28,
    GL_REND_STATE_UPDATE_CLEAR_COLOR             = 1u << 29,
    GL_REND_STATE_UPDATE_CLEAR_DEPTH             = 1u << 30,
    GL_REND_STATE_UPDATE_CLEAR_STENCIL           = 1u << 31,
};

enum gl_rend_state_flags {
    GL_REND_STATE_EXECUTE = 1u << 0,
};

struct gl_rend_state {
    gl_rend_state_index index;

    GLuint curr_program;
    GLuint program;

    GLuint curr_active_texture_index;
    GLuint active_texture_index;

    int32_t texture_binding_start_index;
    int32_t texture_binding_end_index;
    GLuint curr_texture_binding_2d[32];
    GLuint texture_binding_2d[32];
    GLuint curr_texture_binding_cube_map[32];
    GLuint texture_binding_cube_map[32];

    int32_t sampler_binding_start_index;
    int32_t sampler_binding_end_index;
    GLuint curr_sampler_binding[32];
    GLuint sampler_binding[32];

    GLboolean curr_blend;
    GLboolean blend;
    GLenum curr_blend_src_rgb;
    GLenum blend_src_rgb;
    GLenum curr_blend_src_alpha;
    GLenum blend_src_alpha;
    GLenum curr_blend_dst_rgb;
    GLenum blend_dst_rgb;
    GLenum curr_blend_dst_alpha;
    GLenum blend_dst_alpha;
    GLenum curr_blend_mode_rgb;
    GLenum blend_mode_rgb;
    GLenum curr_blend_mode_alpha;
    GLenum blend_mode_alpha;

    GLuint curr_read_framebuffer_binding;
    GLuint read_framebuffer_binding;
    GLuint curr_draw_framebuffer_binding;
    GLuint draw_framebuffer_binding;

    GLuint curr_vertex_array_binding;
    GLuint vertex_array_binding;

    GLuint array_buffer_binding;
    GLuint element_array_buffer_binding;

    GLuint uniform_buffer_binding;

    int32_t uniform_buffer_start_index;
    int32_t uniform_buffer_end_index;
    GLuint curr_uniform_buffer_bindings[14];
    GLuint uniform_buffer_bindings[14];
    GLintptr curr_uniform_buffer_offsets[14];
    GLintptr uniform_buffer_offsets[14];
    GLsizeiptr curr_uniform_buffer_sizes[14];
    GLsizeiptr uniform_buffer_sizes[14];

    GLuint shader_storage_buffer_binding;

    int32_t shader_storage_buffer_start_index;
    int32_t shader_storage_buffer_end_index;
    GLuint curr_shader_storage_buffer_bindings[14];
    GLuint shader_storage_buffer_bindings[14];
    GLintptr curr_shader_storage_buffer_offsets[14];
    GLintptr shader_storage_buffer_offsets[14];
    GLsizeiptr curr_shader_storage_buffer_sizes[14];
    GLsizeiptr shader_storage_buffer_sizes[14];

    GLboolean curr_color_mask[4];
    GLboolean color_mask[4];

    GLboolean curr_cull_face;
    GLboolean cull_face;
    GLenum curr_cull_face_mode;
    GLenum cull_face_mode;

    GLboolean curr_depth_test;
    GLboolean depth_test;
    GLenum curr_depth_func;
    GLenum depth_func;
    GLboolean curr_depth_mask;
    GLboolean depth_mask;

    GLfloat curr_line_width;
    GLfloat line_width;

    GLboolean curr_multisample;
    GLboolean multisample;

    GLboolean curr_primitive_restart;
    GLboolean primitive_restart;
    GLuint curr_primitive_restart_index;
    GLuint primitive_restart_index;

    gl_rend_state_rect curr_scissor_box;
    gl_rend_state_rect scissor_box;
    GLboolean curr_scissor_test;
    GLboolean scissor_test;

    GLboolean curr_stencil_test;
    GLboolean stencil_test;
    GLenum curr_stencil_func;
    GLenum stencil_func;
    GLenum curr_stencil_fail;
    GLenum stencil_fail;
    GLenum curr_stencil_dpfail;
    GLenum stencil_dpfail;
    GLenum curr_stencil_dppass;
    GLenum stencil_dppass;
    GLuint curr_stencil_mask;
    GLuint stencil_mask;
    GLint curr_stencil_ref;
    GLint stencil_ref;
    GLuint curr_stencil_value_mask;
    GLuint stencil_value_mask;

    gl_rend_state_rect curr_viewport;
    gl_rend_state_rect viewport;

    GLfloat curr_clear_color_value[4];
    GLfloat clear_color_value[4];

    GLfloat curr_clear_depth_value;
    GLfloat clear_depth_value;

    GLint curr_clear_stencil_value;
    GLint clear_stencil_value;

    gl_rend_state_flags flags;
    gl_rend_state_update_flags update_flags;

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
    void draw_arrays_instanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
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
    void tex_sub_image_2d(GLenum target, GLint level, GLint xoffset, GLint yoffset,
        GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
    void update();
    void update_program();
    void update_active_texture();
    void update_curr_active_texture();
    void update_texture();
    void update_sampler();
    void update_blend();
    void update_blend_func();
    void update_blend_equation();
    void update_read_framebuffer();
    void update_draw_framebuffer();
    void update_vertex_array();
    void update_uniform_buffer();
    void update_shader_storage_buffer();
    void update_color_mask();
    void update_cull_face();
    void update_cull_face_mode();
    void update_depth_test();
    void update_depth_mask();
    void update_depth_func();
    void update_line_width();
    void update_multisample();
    void update_primitive_restart();
    void update_primitive_restart_index();
    void update_scissor_test();
    void update_scissor();
    void update_stencil_test();
    void update_stencil_mask();
    void update_stencil_func();
    void update_stencil_op();
    void update_viewport();
    void update_clear_color();
    void update_clear_depth();
    void update_clear_stencil();
    void use_program(GLuint program);
};

gl_rend_state gl_rend_state_data[GL_REND_STATE_COUNT] = {
    { GL_REND_STATE_PRE_3D  },
    { GL_REND_STATE_3D      },
    { GL_REND_STATE_2D      },
    { GL_REND_STATE_POST_2D },
};

p_gl_rend_state::p_gl_rend_state(gl_rend_state_index index) : ptr(gl_rend_state_data[index]) {

}

void p_gl_rend_state::active_bind_texture_2d(int32_t index, GLuint texture) {
    ptr.active_bind_texture_2d(index, texture);
}

void p_gl_rend_state::active_bind_texture_cube_map(int32_t index, GLuint texture) {
    ptr.active_bind_texture_cube_map(index, texture);
}

void p_gl_rend_state::active_texture(int32_t index) {
    ptr.active_texture(index);
}

void p_gl_rend_state::begin_event(const char* message, int32_t length) {
    ptr.begin_event(message, length);
}

void p_gl_rend_state::bind_framebuffer(GLuint framebuffer) {
    ptr.bind_framebuffer(framebuffer);
}

void p_gl_rend_state::bind_read_framebuffer(GLuint framebuffer) {
    ptr.bind_read_framebuffer(framebuffer);
}

void p_gl_rend_state::bind_draw_framebuffer(GLuint framebuffer) {
    ptr.bind_draw_framebuffer(framebuffer);
}

void p_gl_rend_state::bind_vertex_array(GLuint array) {
    ptr.bind_vertex_array(array);
}

void p_gl_rend_state::bind_array_buffer(GLuint buffer) {
    ptr.bind_array_buffer(buffer);
}

void p_gl_rend_state::bind_element_array_buffer(GLuint buffer) {
    ptr.bind_element_array_buffer(buffer);
}

void p_gl_rend_state::bind_uniform_buffer(GLuint buffer) {
    ptr.bind_uniform_buffer(buffer);
}

void p_gl_rend_state::bind_uniform_buffer_base(GLuint index, GLuint buffer) {
    ptr.bind_uniform_buffer_base(index, buffer);
}

void p_gl_rend_state::bind_uniform_buffer_range(GLuint index,
    GLuint buffer, GLintptr offset, GLsizeiptr size) {
    ptr.bind_uniform_buffer_range(index, buffer, offset, size);
}

void p_gl_rend_state::bind_shader_storage_buffer(GLuint buffer) {
    ptr.bind_shader_storage_buffer(buffer);
}

void p_gl_rend_state::bind_shader_storage_buffer_base(GLuint index, GLuint buffer) {
    ptr.bind_shader_storage_buffer_base(index, buffer);
}

void p_gl_rend_state::bind_shader_storage_buffer_range(GLuint index,
    GLuint buffer, GLintptr offset, GLsizeiptr size) {
    ptr.bind_shader_storage_buffer_range(index, buffer, offset, size);
}

void p_gl_rend_state::bind_texture_2d(GLuint texture) {
    ptr.bind_texture_2d(texture);
}

void p_gl_rend_state::bind_texture_cube_map(GLuint texture) {
    ptr.bind_texture_cube_map(texture);
}

void p_gl_rend_state::bind_sampler(int32_t index, GLuint sampler) {
    ptr.bind_sampler(index, sampler);
}

void p_gl_rend_state::blit_framebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
    GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {
    ptr.blit_framebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

GLenum p_gl_rend_state::check_framebuffer_status(GLenum target) {
    return ptr.check_framebuffer_status(target);
}

void p_gl_rend_state::clear(GLbitfield mask) {
    ptr.clear(mask);
}

void p_gl_rend_state::clear_buffer(GLenum buffer, GLint drawbuffer, const GLfloat* value) {
    ptr.clear_buffer(buffer, drawbuffer, value);
}

void p_gl_rend_state::clear_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    ptr.clear_color(red, green, blue, alpha);
}

void p_gl_rend_state::clear_depth(GLfloat depth) {
    ptr.clear_depth(depth);
}

void p_gl_rend_state::clear_stencil(GLint stencil) {
    ptr.clear_stencil(stencil);
}

void p_gl_rend_state::copy_image_sub_data(GLuint srcName, GLenum srcTarget, GLint srcLevel,
    GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel,
    GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) {
    ptr.copy_image_sub_data(srcName, srcTarget, srcLevel, srcX, srcY, srcZ,
        dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
}

void p_gl_rend_state::copy_tex_sub_image_2d(GLenum target, GLint level,
    GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    ptr.copy_tex_sub_image_2d(target, level, xoffset, yoffset, x, y, width, height);
}

void p_gl_rend_state::disable_blend() {
    ptr.disable_blend();
}

void p_gl_rend_state::disable_cull_face() {
    ptr.disable_cull_face();
}

void p_gl_rend_state::disable_depth_test() {
    ptr.disable_depth_test();
}

void p_gl_rend_state::disable_multisample() {
    ptr.disable_multisample();
}

void p_gl_rend_state::disable_primitive_restart() {
    ptr.disable_primitive_restart();
}

void p_gl_rend_state::disable_scissor_test() {
    ptr.disable_scissor_test();
}

void p_gl_rend_state::disable_stencil_test() {
    ptr.disable_stencil_test();
}

void p_gl_rend_state::draw_arrays(GLenum mode, GLint first, GLsizei count) {
    ptr.draw_arrays(mode, first, count);
}

void p_gl_rend_state::draw_arrays_instanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) {
    ptr.draw_arrays_instanced(mode, first, count, instancecount);
}

void p_gl_rend_state::draw_elements(GLenum mode,
    GLsizei count, GLenum type, const void* indices) {
    ptr.draw_elements(mode, count, type, indices);
}

void p_gl_rend_state::draw_range_elements(GLenum mode,
    GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices) {
    ptr.draw_range_elements(mode, start, end, count, type, indices);
}

void p_gl_rend_state::enable_blend() {
    ptr.enable_blend();
}

void p_gl_rend_state::enable_cull_face() {
    ptr.enable_cull_face();
}

void p_gl_rend_state::enable_depth_test() {
    ptr.enable_depth_test();
}

void p_gl_rend_state::enable_multisample() {
    ptr.enable_multisample();
}

void p_gl_rend_state::enable_primitive_restart() {
    ptr.enable_primitive_restart();
}

void p_gl_rend_state::enable_scissor_test() {
    ptr.enable_scissor_test();
}

void p_gl_rend_state::enable_stencil_test() {
    ptr.enable_stencil_test();
}

void p_gl_rend_state::end_event() {
    ptr.end_event();
}

void p_gl_rend_state::generate_mipmap(GLenum target) {
    ptr.generate_mipmap(target);
}

void p_gl_rend_state::generate_texture_mipmap(GLuint texture) {
    ptr.generate_texture_mipmap(texture);
}

void p_gl_rend_state::get() {
    ptr.get();
}

void p_gl_rend_state::get_clear_color(GLfloat& red, GLfloat& green, GLfloat& blue, GLfloat& alpha) {
    ptr.get_clear_color(red, green, blue, alpha);
}

GLuint p_gl_rend_state::get_program() {
    return ptr.get_program();
}

gl_rend_state_rect p_gl_rend_state::get_scissor() {
    return ptr.get_scissor();
}

void p_gl_rend_state::get_scissor(GLint& x, GLint& y, GLsizei& width, GLsizei& height) {
    ptr.get_scissor(x, y, width, height);
}

gl_rend_state_rect p_gl_rend_state::get_viewport() {
    return ptr.get_viewport();
}

void p_gl_rend_state::get_viewport(GLint& x, GLint& y, GLsizei& width, GLsizei& height) {
    ptr.get_viewport(x, y, width, height);
}

void p_gl_rend_state::set_blend_func(GLenum src, GLenum dst) {
    ptr.set_blend_func(src, dst);
}

void p_gl_rend_state::set_blend_func_separate(GLenum src_rgb, GLenum dst_rgb,
    GLenum src_alpha, GLenum dst_alpha) {
    ptr.set_blend_func_separate(src_rgb, dst_rgb, src_alpha, dst_alpha);
}

void p_gl_rend_state::set_blend_equation(GLenum mode) {
    ptr.set_blend_equation(mode);
}

void p_gl_rend_state::set_blend_equation_separate(
    GLenum mode_rgb, GLenum mode_alpha) {
    ptr.set_blend_equation_separate(mode_rgb, mode_alpha);
}

void p_gl_rend_state::set_color_mask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    ptr.set_color_mask(red, green, blue, alpha);
}

void p_gl_rend_state::set_cull_face_mode(GLenum mode) {
    ptr.set_cull_face_mode(mode);
}

void p_gl_rend_state::set_depth_func(GLenum func) {
    ptr.set_depth_func(func);
}

void p_gl_rend_state::set_depth_mask(GLboolean flag) {
    ptr.set_depth_mask(flag);
}

void p_gl_rend_state::set_line_width(GLfloat width) {
    ptr.set_line_width(width);
}

void p_gl_rend_state::set_primitive_restart_index(GLuint index) {
    ptr.set_primitive_restart_index(index);
}

void p_gl_rend_state::set_scissor(const gl_rend_state_rect& rect) {
    ptr.set_scissor(rect);
}

void p_gl_rend_state::set_scissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    ptr.set_scissor(x, y, width, height);
}

void p_gl_rend_state::set_stencil_func(GLenum func, GLint ref, GLuint mask) {
    ptr.set_stencil_func(func, ref, mask);
}

void p_gl_rend_state::set_stencil_mask(GLuint mask) {
    ptr.set_stencil_mask(mask);
}

void p_gl_rend_state::set_stencil_op(GLenum sfail, GLenum dpfail, GLenum dppass) {
    ptr.set_stencil_op(sfail, dpfail, dppass);
}

void p_gl_rend_state::set_viewport(const gl_rend_state_rect& rect) {
    ptr.set_viewport(rect);
}

void p_gl_rend_state::set_viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    ptr.set_viewport(x, y, width, height);
}

void p_gl_rend_state::tex_sub_image_2d(GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) {
    ptr.tex_sub_image_2d(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void p_gl_rend_state::update() {
    ptr.update();
}

void p_gl_rend_state::use_program(GLuint program) {
    ptr.use_program(program);
}

inline void gl_rend_state::active_bind_texture_2d(int32_t index, GLuint texture) {
    active_texture(index);
    bind_texture_2d(texture);
}

inline void gl_rend_state::active_bind_texture_cube_map(int32_t index, GLuint texture) {
    active_texture(index);
    bind_texture_cube_map(texture);
}

inline void gl_rend_state::active_texture(int32_t index) {
    active_texture_index = index;
    enum_or(update_flags, GL_REND_STATE_UPDATE_ACTIVE_TEXTURE);
}

inline void gl_rend_state::begin_event(const char* message, int32_t length) {
    if (DIVA_GL_VERSION_4_3)
        glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, (GLsizei)length, message);
}

inline void gl_rend_state::bind_framebuffer(GLuint framebuffer) {
    read_framebuffer_binding = framebuffer;
    draw_framebuffer_binding = framebuffer;
    enum_or(update_flags, GL_REND_STATE_UPDATE_DRAW_FRAMEBUFFER
        | GL_REND_STATE_UPDATE_READ_FRAMEBUFFER);
}

inline void gl_rend_state::bind_read_framebuffer(GLuint framebuffer) {
    read_framebuffer_binding = framebuffer;
    enum_or(update_flags, GL_REND_STATE_UPDATE_READ_FRAMEBUFFER);
}

inline void gl_rend_state::bind_draw_framebuffer(GLuint framebuffer) {
    draw_framebuffer_binding = framebuffer;
    enum_or(update_flags, GL_REND_STATE_UPDATE_DRAW_FRAMEBUFFER);
}

inline void gl_rend_state::bind_vertex_array(GLuint array) {
    vertex_array_binding = array;
    enum_or(update_flags, GL_REND_STATE_UPDATE_VERTEX_ARRAY);
}

inline void gl_rend_state::bind_array_buffer(GLuint buffer) {
    if (array_buffer_binding != buffer) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        array_buffer_binding = buffer;
    }
}

inline void gl_rend_state::bind_element_array_buffer(GLuint buffer) {
    if (element_array_buffer_binding != buffer) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        element_array_buffer_binding = buffer;
    }
}

inline void gl_rend_state::bind_uniform_buffer(GLuint buffer) {
    if (uniform_buffer_binding != buffer) {
        glBindBuffer(GL_UNIFORM_BUFFER, buffer);
        uniform_buffer_binding = buffer;
    }
}

inline void gl_rend_state::bind_uniform_buffer_base(GLuint index, GLuint buffer) {
    uniform_buffer_bindings[index] = buffer;
    uniform_buffer_offsets[index] = 0;
    uniform_buffer_sizes[index] = -1;
    uniform_buffer_start_index = min_def(uniform_buffer_start_index, (int32_t)index);
    uniform_buffer_end_index = max_def(uniform_buffer_end_index, (int32_t)index);
    enum_or(update_flags, GL_REND_STATE_UPDATE_UNIFORM_BUFFER);
}

inline void gl_rend_state::bind_uniform_buffer_range(GLuint index,
    GLuint buffer, GLintptr offset, GLsizeiptr size) {
    uniform_buffer_bindings[index] = buffer;
    uniform_buffer_offsets[index] = offset;
    uniform_buffer_sizes[index] = size;
    uniform_buffer_start_index = min_def(uniform_buffer_start_index, (int32_t)index);
    uniform_buffer_end_index = max_def(uniform_buffer_end_index, (int32_t)index);
    enum_or(update_flags, GL_REND_STATE_UPDATE_UNIFORM_BUFFER);
}

inline void gl_rend_state::bind_shader_storage_buffer(GLuint buffer) {
    if (DIVA_GL_VERSION_4_3 && shader_storage_buffer_binding != buffer) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
        shader_storage_buffer_binding = buffer;
    }
}

inline void gl_rend_state::bind_shader_storage_buffer_base(GLuint index, GLuint buffer) {
    shader_storage_buffer_bindings[index] = buffer;
    shader_storage_buffer_offsets[index] = 0;
    shader_storage_buffer_sizes[index] = -1;
    shader_storage_buffer_start_index = min_def(shader_storage_buffer_start_index, (int32_t)index);
    shader_storage_buffer_end_index = max_def(shader_storage_buffer_end_index, (int32_t)index);
    enum_or(update_flags, GL_REND_STATE_UPDATE_SHADER_STORAGE_BUFFER);
}

inline void gl_rend_state::bind_shader_storage_buffer_range(GLuint index,
    GLuint buffer, GLintptr offset, GLsizeiptr size) {
    shader_storage_buffer_bindings[index] = buffer;
    shader_storage_buffer_offsets[index] = offset;
    shader_storage_buffer_sizes[index] = size;
    shader_storage_buffer_start_index = min_def(shader_storage_buffer_start_index, (int32_t)index);
    shader_storage_buffer_end_index = max_def(shader_storage_buffer_end_index, (int32_t)index);
    enum_or(update_flags, GL_REND_STATE_UPDATE_SHADER_STORAGE_BUFFER);
}

inline void gl_rend_state::bind_texture_2d(GLuint texture) {
    texture_binding_2d[active_texture_index] = texture;
    texture_binding_start_index = min_def(texture_binding_start_index, (int32_t)active_texture_index);
    texture_binding_end_index = max_def(texture_binding_end_index, (int32_t)active_texture_index);
    enum_or(update_flags, GL_REND_STATE_UPDATE_TEXTURE);
}

inline void gl_rend_state::bind_texture_cube_map(GLuint texture) {
    texture_binding_cube_map[active_texture_index] = texture;
    texture_binding_start_index = min_def(texture_binding_start_index, (int32_t)active_texture_index);
    texture_binding_end_index = max_def(texture_binding_end_index, (int32_t)active_texture_index);
    enum_or(update_flags, GL_REND_STATE_UPDATE_TEXTURE);
}

inline void gl_rend_state::bind_sampler(int32_t index, GLuint sampler) {
    sampler_binding[index] = sampler;
    sampler_binding_start_index = min_def(sampler_binding_start_index, (int32_t)index);
    sampler_binding_end_index = max_def(sampler_binding_end_index, (int32_t)index);
    enum_or(update_flags, GL_REND_STATE_UPDATE_SAMPLER);
}

inline void gl_rend_state::blit_framebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
    GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {
    update_read_framebuffer();
    update_draw_framebuffer();

    if (mask & GL_COLOR_BUFFER_BIT)
        update_color_mask();

    if (mask & GL_DEPTH_BUFFER_BIT) {
        update_depth_test();
        update_depth_mask();
    }

    if (mask & GL_STENCIL_BUFFER_BIT) {
        update_stencil_test();
        update_stencil_mask();
    }

    glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

inline GLenum gl_rend_state::check_framebuffer_status(GLenum target) {
    switch (target) {
    case GL_READ_FRAMEBUFFER:
        update_read_framebuffer();
        break;
    case GL_DRAW_FRAMEBUFFER:
    case GL_FRAMEBUFFER:
        update_draw_framebuffer();
        break;
    }

    return glCheckFramebufferStatus(target);
}

inline void gl_rend_state::clear(GLbitfield mask) {
    update_draw_framebuffer();

    if (mask & GL_COLOR_BUFFER_BIT)
        update_color_mask();

    if (mask & GL_DEPTH_BUFFER_BIT) {
        update_depth_test();
        update_depth_mask();
    }

    update_scissor_test();
    update_scissor();

    if (mask & GL_STENCIL_BUFFER_BIT) {
        update_stencil_test();
        update_stencil_mask();
    }

    if (mask & GL_COLOR_BUFFER_BIT)
        update_clear_color();

    if (mask & GL_DEPTH_BUFFER_BIT)
        update_clear_depth();

    if (mask & GL_STENCIL_BUFFER_BIT)
        update_clear_stencil();

    glClearDLL(mask);
    enum_or(flags, GL_REND_STATE_EXECUTE);
}

inline void gl_rend_state::clear_buffer(GLenum buffer, GLint drawbuffer, const GLfloat* value) {
    update_draw_framebuffer();

    if (buffer == GL_COLOR)
        update_color_mask();

    if (buffer == GL_DEPTH) {
        update_depth_test();
        update_depth_mask();
    }

    update_scissor_test();
    update_scissor();

    if (buffer == GL_STENCIL) {
        update_stencil_test();
        update_stencil_mask();
    }

    glClearBufferfv(buffer, drawbuffer, value);
    enum_or(flags, GL_REND_STATE_EXECUTE);
}

inline void gl_rend_state::clear_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    clear_color_value[0] = red;
    clear_color_value[1] = green;
    clear_color_value[2] = blue;
    clear_color_value[3] = alpha;
    enum_or(update_flags, GL_REND_STATE_UPDATE_CLEAR_COLOR);
}

inline void gl_rend_state::clear_depth(GLfloat depth) {
    clear_depth_value = depth;
    enum_or(update_flags, GL_REND_STATE_UPDATE_CLEAR_DEPTH);
}

inline void gl_rend_state::clear_stencil(GLint stencil) {
    clear_stencil_value = stencil;
    enum_or(update_flags, GL_REND_STATE_UPDATE_CLEAR_STENCIL);
}

inline void gl_rend_state::copy_image_sub_data(GLuint srcName, GLenum srcTarget, GLint srcLevel,
    GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel,
    GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) {
    glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ,
        dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
    enum_or(flags, GL_REND_STATE_EXECUTE);
}

inline void gl_rend_state::copy_tex_sub_image_2d(GLenum target, GLint level,
    GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    update_active_texture();
    update_curr_active_texture();
    update_read_framebuffer();
    glCopyTexSubImage2DDLL(target, level, xoffset, yoffset, x, y, width, height);
    enum_or(flags, GL_REND_STATE_EXECUTE);
}

inline void gl_rend_state::disable_blend() {
    blend = GL_FALSE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_BLEND);
}

inline void gl_rend_state::disable_cull_face() {
    cull_face = GL_FALSE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_CULL_FACE);
}

inline void gl_rend_state::disable_depth_test() {
    depth_test = GL_FALSE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_DEPTH_TEST);
}

inline void gl_rend_state::disable_multisample() {
    multisample = GL_FALSE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_MULTISAMPLE);
}

inline void gl_rend_state::disable_primitive_restart() {
    primitive_restart = GL_FALSE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_PRIMITIVE_RESTART);
}

inline void gl_rend_state::disable_scissor_test() {
    scissor_test = GL_FALSE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_SCISSOR_TEST);
}

inline void gl_rend_state::disable_stencil_test() {
    stencil_test = GL_FALSE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_STENCIL_TEST);
}

inline void gl_rend_state::draw_arrays(GLenum mode, GLint first, GLsizei count) {
    update();
    glDrawArraysDLL(mode, first, count);
}

inline void gl_rend_state::draw_arrays_instanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) {
    update();
    glDrawArraysInstanced(mode, first, count, instancecount);
}

inline void gl_rend_state::draw_elements(GLenum mode,
    GLsizei count, GLenum type, const void* indices) {
    switch (mode) {
    case GL_TRIANGLE_STRIP:
        uint32_t index;
        switch (type) {
        case GL_UNSIGNED_BYTE:
            index = 0xFF;
            break;
        case GL_UNSIGNED_SHORT:
            index = 0xFFFF;
            break;
        case GL_UNSIGNED_INT:
        default:
            index = 0xFFFFFFFF;
            break;
        }

        enable_primitive_restart();
        set_primitive_restart_index(index);
        break;
    }

    update();
    glDrawElementsDLL(mode, count, type, indices);

    switch (mode) {
    case GL_TRIANGLE_STRIP:
        disable_primitive_restart();
        break;
    }
}

inline void gl_rend_state::draw_range_elements(GLenum mode,
    GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices) {
    switch (mode) {
    case GL_TRIANGLE_STRIP:
        uint32_t index;
        switch (type) {
        case GL_UNSIGNED_BYTE:
            index = 0xFF;
            break;
        case GL_UNSIGNED_SHORT:
            index = 0xFFFF;
            break;
        case GL_UNSIGNED_INT:
        default:
            index = 0xFFFFFFFF;
            break;
        }

        enable_primitive_restart();
        set_primitive_restart_index(index);
        break;
    }

    update();
    glDrawRangeElements(mode, start, end, count, type, indices);

    switch (mode) {
    case GL_TRIANGLE_STRIP:
        disable_primitive_restart();
        break;
    }
}

inline void gl_rend_state::enable_blend() {
    blend = GL_TRUE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_BLEND);
}

inline void gl_rend_state::enable_cull_face() {
    cull_face = GL_TRUE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_CULL_FACE);
}

inline void gl_rend_state::enable_depth_test() {
    depth_test = GL_TRUE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_DEPTH_TEST);
}

inline void gl_rend_state::enable_multisample() {
    multisample = GL_TRUE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_MULTISAMPLE);
}

inline void gl_rend_state::enable_primitive_restart() {
    primitive_restart = GL_TRUE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_PRIMITIVE_RESTART);
}

inline void gl_rend_state::enable_scissor_test() {
    scissor_test = GL_TRUE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_SCISSOR_TEST);
}

inline void gl_rend_state::enable_stencil_test() {
    stencil_test = GL_TRUE;
    enum_or(update_flags, GL_REND_STATE_UPDATE_STENCIL_TEST);
}

inline void gl_rend_state::end_event() {
    if (DIVA_GL_VERSION_4_3)
        glPopDebugGroup();
}

inline void gl_rend_state::generate_mipmap(GLenum target) {
    update_curr_active_texture();
    glGenerateMipmap(target);
    enum_or(flags, GL_REND_STATE_EXECUTE);
}

inline void gl_rend_state::generate_texture_mipmap(GLuint texture) {
    glGenerateTextureMipmap(texture);
    enum_or(flags, GL_REND_STATE_EXECUTE);
}

void gl_rend_state::get() {
    gl_get_error_all_print();

    glGetIntegervDLL(GL_CURRENT_PROGRAM, (GLint*)&program);

    GLenum active_texture = GL_TEXTURE0;
    glGetIntegervDLL(GL_ACTIVE_TEXTURE, (GLint*)&active_texture);
    active_texture_index = active_texture - GL_TEXTURE0;

    texture_binding_start_index = 32;
    texture_binding_end_index = -1;
    sampler_binding_start_index = 32;
    sampler_binding_end_index = -1;

    if (DIVA_GL_VERSION_4_5) {
        for (GLuint i = 0; i < 32; i++) {
            glGetIntegeri_v(GL_TEXTURE_BINDING_2D, i, (GLint*)&texture_binding_2d[i]);
            glGetIntegeri_v(GL_TEXTURE_BINDING_CUBE_MAP, i, (GLint*)&texture_binding_cube_map[i]);
            glGetIntegeri_v(GL_SAMPLER_BINDING, i, (GLint*)&sampler_binding[i]);
        }
    }
    else {
        for (GLuint i = 0; i < 32; i++) {
            glActiveTexture((GLenum)(GL_TEXTURE0 + i));
            glGetIntegervDLL(GL_TEXTURE_BINDING_2D, (GLint*)&texture_binding_2d[i]);
            glGetIntegervDLL(GL_TEXTURE_BINDING_CUBE_MAP, (GLint*)&texture_binding_cube_map[i]);
            glGetIntegervDLL(GL_SAMPLER_BINDING, (GLint*)&sampler_binding[i]);
        }
        glActiveTexture(active_texture);
    }

    glGetBooleanvDLL(GL_BLEND, &blend);
    glGetIntegervDLL(GL_BLEND_SRC_RGB, (GLint*)&blend_src_rgb);
    glGetIntegervDLL(GL_BLEND_SRC_ALPHA, (GLint*)&blend_src_alpha);
    glGetIntegervDLL(GL_BLEND_DST_RGB, (GLint*)&blend_dst_rgb);
    glGetIntegervDLL(GL_BLEND_DST_ALPHA, (GLint*)&blend_dst_alpha);
    glGetIntegervDLL(GL_BLEND_EQUATION_RGB, (GLint*)&blend_mode_rgb);
    glGetIntegervDLL(GL_BLEND_EQUATION_ALPHA, (GLint*)&blend_mode_alpha);

    glGetIntegervDLL(GL_READ_FRAMEBUFFER_BINDING, (GLint*)&read_framebuffer_binding);
    glGetIntegervDLL(GL_DRAW_FRAMEBUFFER_BINDING, (GLint*)&draw_framebuffer_binding);

    glGetIntegervDLL(GL_VERTEX_ARRAY_BINDING, (GLint*)&vertex_array_binding);

    glGetIntegervDLL(GL_ARRAY_BUFFER_BINDING, (GLint*)&array_buffer_binding);
    glGetIntegervDLL(GL_ELEMENT_ARRAY_BUFFER_BINDING, (GLint*)&element_array_buffer_binding);

    uniform_buffer_start_index = 14;
    uniform_buffer_end_index = -1;

    glGetIntegervDLL(GL_UNIFORM_BUFFER_BINDING, (GLint*)&uniform_buffer_binding);
    for (GLuint i = 0; i < 14; i++) {
        glGetIntegeri_v(GL_UNIFORM_BUFFER_BINDING, i, (GLint*)&uniform_buffer_bindings[i]);
        glGetInteger64i_v(GL_UNIFORM_BUFFER_START, i, (GLint64*)&uniform_buffer_offsets[i]);
        glGetInteger64i_v(GL_UNIFORM_BUFFER_SIZE, i, (GLint64*)&uniform_buffer_sizes[i]);
    }

    if (DIVA_GL_VERSION_4_3) {
        shader_storage_buffer_start_index = 14;
        shader_storage_buffer_end_index = -1;

        glGetIntegervDLL(GL_SHADER_STORAGE_BUFFER_BINDING, (GLint*)&shader_storage_buffer_binding);
        for (GLuint i = 0; i < 14; i++) {
            glGetIntegeri_v(GL_SHADER_STORAGE_BUFFER_BINDING, i, (GLint*)&shader_storage_buffer_bindings[i]);
            glGetInteger64i_v(GL_SHADER_STORAGE_BUFFER_START, i, (GLint64*)&shader_storage_buffer_offsets[i]);
            glGetInteger64i_v(GL_SHADER_STORAGE_BUFFER_SIZE, i, (GLint64*)&shader_storage_buffer_sizes[i]);
        }
    }

    glGetBooleanvDLL(GL_COLOR_WRITEMASK, color_mask);

    glGetBooleanvDLL(GL_CULL_FACE, &cull_face);
    glGetIntegervDLL(GL_CULL_FACE_MODE, (GLint*)&cull_face_mode);

    glGetBooleanvDLL(GL_DEPTH_TEST, &depth_test);
    glGetIntegervDLL(GL_DEPTH_FUNC, (GLint*)&depth_func);
    glGetBooleanvDLL(GL_DEPTH_WRITEMASK, &depth_mask);

    glGetFloatvDLL(GL_LINE_WIDTH, &line_width);

    glGetBooleanvDLL(GL_MULTISAMPLE, &multisample);

    glGetBooleanvDLL(GL_PRIMITIVE_RESTART, &primitive_restart);
    glGetIntegervDLL(GL_PRIMITIVE_RESTART_INDEX, (GLint*)&primitive_restart_index);

    glGetIntegervDLL(GL_SCISSOR_BOX, (GLint*)&scissor_box);
    glGetBooleanvDLL(GL_SCISSOR_TEST, &scissor_test);

    glGetBooleanvDLL(GL_STENCIL_TEST, &stencil_test);
    glGetIntegervDLL(GL_STENCIL_FUNC, (GLint*)&stencil_func);
    glGetIntegervDLL(GL_STENCIL_VALUE_MASK, (GLint*)&stencil_value_mask);
    glGetIntegervDLL(GL_STENCIL_FAIL, (GLint*)&stencil_fail);
    glGetIntegervDLL(GL_STENCIL_PASS_DEPTH_FAIL, (GLint*)&stencil_dpfail);
    glGetIntegervDLL(GL_STENCIL_PASS_DEPTH_PASS, (GLint*)&stencil_dppass);
    glGetIntegervDLL(GL_STENCIL_REF, &stencil_ref);
    glGetIntegervDLL(GL_STENCIL_WRITEMASK, (GLint*)&stencil_mask);

    glGetIntegervDLL(GL_VIEWPORT, (GLint*)&viewport);

    glGetFloatvDLL(GL_COLOR_CLEAR_VALUE, clear_color_value);

    glGetFloatvDLL(GL_DEPTH_CLEAR_VALUE, &clear_depth_value);

    glGetIntegervDLL(GL_STENCIL_CLEAR_VALUE, &clear_stencil_value);

    curr_program = program;

    curr_active_texture_index = active_texture_index;

    for (GLuint i = 0; i < 32; i++) {
        curr_texture_binding_2d[i] = texture_binding_2d[i];
        curr_texture_binding_cube_map[i] = texture_binding_cube_map[i];
        curr_sampler_binding[i] = sampler_binding[i];
    }

    curr_blend = blend;
    curr_blend_src_rgb = blend_src_rgb;
    curr_blend_src_alpha = blend_src_alpha;
    curr_blend_dst_rgb = blend_dst_rgb;
    curr_blend_dst_alpha = blend_dst_alpha;
    curr_blend_mode_rgb = blend_mode_rgb;
    curr_blend_mode_alpha = blend_mode_alpha;

    curr_read_framebuffer_binding = read_framebuffer_binding;
    curr_draw_framebuffer_binding = draw_framebuffer_binding;

    curr_vertex_array_binding = vertex_array_binding;

    for (GLuint i = 0; i < 14; i++) {
        curr_uniform_buffer_bindings[i] = uniform_buffer_bindings[i];
        curr_uniform_buffer_offsets[i] = uniform_buffer_offsets[i];
        curr_uniform_buffer_sizes[i] = uniform_buffer_sizes[i];
    }

    if (DIVA_GL_VERSION_4_3)
        for (GLuint i = 0; i < 14; i++) {
            curr_shader_storage_buffer_bindings[i] = shader_storage_buffer_bindings[i];
            curr_shader_storage_buffer_offsets[i] = shader_storage_buffer_offsets[i];
            curr_shader_storage_buffer_sizes[i] = shader_storage_buffer_sizes[i];
        }

    memcpy(curr_color_mask, color_mask, sizeof(GLboolean) * 4);

    curr_cull_face = cull_face;
    curr_cull_face_mode = cull_face_mode;

    curr_depth_test = depth_test;
    curr_depth_func = depth_func;
    curr_depth_mask = depth_mask;

    curr_line_width = line_width;
    curr_multisample = multisample;

    curr_primitive_restart = primitive_restart;
    curr_primitive_restart_index = primitive_restart_index;

    curr_scissor_box = scissor_box;
    curr_scissor_test = scissor_test;

    curr_stencil_test = stencil_test;
    curr_stencil_func = stencil_func;
    curr_stencil_value_mask = stencil_value_mask;
    curr_stencil_fail = stencil_fail;
    curr_stencil_dpfail = stencil_dpfail;
    curr_stencil_dppass = stencil_dppass;
    curr_stencil_ref = stencil_ref;
    curr_stencil_mask = stencil_mask;

    curr_viewport = viewport;

    memcpy(curr_clear_color_value, clear_color_value, sizeof(GLboolean) * 4);
    curr_clear_depth_value = clear_depth_value;
    curr_clear_stencil_value = clear_stencil_value;

    flags = (gl_rend_state_flags)0;
    update_flags = (gl_rend_state_update_flags)0;
}

inline void gl_rend_state::get_clear_color(GLfloat& red, GLfloat& green, GLfloat& blue, GLfloat& alpha) {
    red = clear_color_value[0];
    green = clear_color_value[1];
    blue = clear_color_value[2];
    alpha = clear_color_value[3];
}

inline GLuint gl_rend_state::get_program() {
    return program;
}

inline gl_rend_state_rect gl_rend_state::get_scissor() {
    return scissor_box;
}

inline void gl_rend_state::get_scissor(GLint& x, GLint& y, GLsizei& width, GLsizei& height) {
    x = scissor_box.x;
    y = scissor_box.y;
    width = scissor_box.width;
    height = scissor_box.height;
}

inline gl_rend_state_rect gl_rend_state::get_viewport() {
    return viewport;
}

inline void gl_rend_state::get_viewport(GLint& x, GLint& y, GLsizei& width, GLsizei& height) {
    x = viewport.x;
    y = viewport.y;
    width = viewport.width;
    height = viewport.height;
}

inline void gl_rend_state::set_blend_func(GLenum src, GLenum dst) {
    blend_src_rgb = src;
    blend_dst_rgb = dst;
    blend_src_alpha = GL_ONE;
    blend_dst_alpha = GL_ONE_MINUS_SRC_ALPHA;
    enum_or(update_flags, GL_REND_STATE_UPDATE_BLEND_FUNC);
}

inline void gl_rend_state::set_blend_func_separate(GLenum src_rgb, GLenum dst_rgb,
    GLenum src_alpha, GLenum dst_alpha) {
    blend_src_rgb = src_rgb;
    blend_dst_rgb = dst_rgb;
    blend_src_alpha = src_alpha;
    blend_dst_alpha = dst_alpha;
    enum_or(update_flags, GL_REND_STATE_UPDATE_BLEND_FUNC);
}

inline void gl_rend_state::set_blend_equation(GLenum mode) {
    blend_mode_rgb = mode;
    blend_mode_alpha = mode;
    enum_or(update_flags, GL_REND_STATE_UPDATE_BLEND_EQUATION);
}

inline void gl_rend_state::set_blend_equation_separate(GLenum mode_rgb, GLenum mode_alpha) {
    blend_mode_rgb = mode_rgb;
    blend_mode_alpha = mode_alpha;
    enum_or(update_flags, GL_REND_STATE_UPDATE_BLEND_EQUATION);
}

inline void gl_rend_state::set_color_mask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    color_mask[0] = red;
    color_mask[1] = green;
    color_mask[2] = blue;
    color_mask[3] = alpha;
    enum_or(update_flags, GL_REND_STATE_UPDATE_COLOR_MASK);
}

inline void gl_rend_state::set_cull_face_mode(GLenum mode) {
    cull_face_mode = mode;
    enum_or(update_flags, GL_REND_STATE_UPDATE_CULL_FACE_MODE);
}

inline void gl_rend_state::set_depth_func(GLenum func) {
    depth_func = func;
    enum_or(update_flags, GL_REND_STATE_UPDATE_DEPTH_FUNC);
}

inline void gl_rend_state::set_depth_mask(GLboolean flag) {
    depth_mask = flag;
    enum_or(update_flags, GL_REND_STATE_UPDATE_DEPTH_MASK);
}

inline void gl_rend_state::set_line_width(GLfloat width) {
    line_width = width;
    enum_or(update_flags, GL_REND_STATE_UPDATE_LINE_WIDTH);
}

inline void gl_rend_state::set_primitive_restart_index(GLuint index) {
    primitive_restart_index = index;
    enum_or(update_flags, GL_REND_STATE_UPDATE_PRIMITIVE_RESTART_INDEX);
}

inline void gl_rend_state::set_scissor(const gl_rend_state_rect& rect) {
    scissor_box = rect;
    enum_or(update_flags, GL_REND_STATE_UPDATE_SCISSOR);
}

inline void gl_rend_state::set_scissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    scissor_box.x = x;
    scissor_box.y = y;
    scissor_box.width = width;
    scissor_box.height = height;
    enum_or(update_flags, GL_REND_STATE_UPDATE_SCISSOR);
}

inline void gl_rend_state::set_stencil_func(GLenum func, GLint ref, GLuint mask) {
    stencil_func = func;
    stencil_ref = ref;
    stencil_value_mask = mask;
    enum_or(update_flags, GL_REND_STATE_UPDATE_STENCIL_FUNC);
}

inline void gl_rend_state::set_stencil_mask(GLuint mask) {
    stencil_mask = mask;
    enum_or(update_flags, GL_REND_STATE_UPDATE_STENCIL_MASK);
}

inline void gl_rend_state::set_stencil_op(GLenum sfail, GLenum dpfail, GLenum dppass) {
    stencil_fail = sfail;
    stencil_dpfail = dpfail;
    stencil_dppass = dppass;
    enum_or(update_flags, GL_REND_STATE_UPDATE_STENCIL_OP);
}

inline void gl_rend_state::set_viewport(const gl_rend_state_rect& rect) {
    viewport = rect;
    enum_or(update_flags, GL_REND_STATE_UPDATE_VIEWPORT);
}

inline void gl_rend_state::set_viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    viewport.x = x;
    viewport.y = y;
    viewport.width = width;
    viewport.height = height;
    enum_or(update_flags, GL_REND_STATE_UPDATE_VIEWPORT);
}

inline void gl_rend_state::tex_sub_image_2d(GLenum target, GLint level, GLint xoffset, GLint yoffset,
    GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) {
    update_curr_active_texture();
    glTexSubImage2DDLL(target, level, xoffset, yoffset, width, height, format, type, pixels);
    enum_or(flags, GL_REND_STATE_EXECUTE);
}

void gl_rend_state::update() {
    if (!update_flags)
        return;

    update_program();
    update_texture();
    update_active_texture();
    update_sampler();
    update_blend();
    update_blend_func();
    update_blend_equation();
    update_read_framebuffer();
    update_draw_framebuffer();
    update_vertex_array();
    update_uniform_buffer();
    update_shader_storage_buffer();
    update_color_mask();
    update_cull_face();
    update_cull_face_mode();
    update_depth_test();
    update_depth_mask();
    update_depth_func();
    update_line_width();
    update_multisample();
    update_primitive_restart();
    update_primitive_restart_index();
    update_scissor_test();
    update_scissor();
    update_stencil_test();
    update_stencil_mask();
    update_stencil_func();
    update_stencil_op();
    update_viewport();
    update_clear_color();
    update_clear_depth();
    update_clear_stencil();

    enum_or(flags, GL_REND_STATE_EXECUTE);
}

inline void gl_rend_state::update_program() {
    if (update_flags & GL_REND_STATE_UPDATE_PROGRAM) {
        if (curr_program != program) {
            glUseProgram(program);
            curr_program = program;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_PROGRAM);
    }
}

inline void gl_rend_state::update_active_texture() {
    if (update_flags & GL_REND_STATE_UPDATE_ACTIVE_TEXTURE) {
        if (curr_active_texture_index != active_texture_index) {
            glActiveTexture((GLenum)(GL_TEXTURE0 + active_texture_index));
            curr_active_texture_index = active_texture_index;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_ACTIVE_TEXTURE);
    }
}

inline void gl_rend_state::update_curr_active_texture() {
    if (update_flags & GL_REND_STATE_UPDATE_TEXTURE) {
        GLuint index = curr_active_texture_index;
        bool bind = false;
        if (curr_texture_binding_2d[index] != texture_binding_2d[index]) {
            glBindTextureDLL(GL_TEXTURE_2D, texture_binding_2d[curr_active_texture_index]);
            curr_texture_binding_2d[index] = texture_binding_2d[index];
            bind = true;
        }
        else if (curr_texture_binding_cube_map[index] != texture_binding_cube_map[index]) {
            glBindTextureDLL(GL_TEXTURE_CUBE_MAP, texture_binding_cube_map[index]);
            curr_texture_binding_cube_map[index] = texture_binding_cube_map[index];
            bind = true;
        }

        if (bind) {
            if (texture_binding_start_index == curr_active_texture_index)
                texture_binding_start_index++;
            else if (texture_binding_end_index == curr_active_texture_index)
                texture_binding_end_index--;

            if (texture_binding_start_index > texture_binding_end_index) {
                texture_binding_start_index = 32;
                texture_binding_end_index = -1;
                enum_and(update_flags, ~GL_REND_STATE_UPDATE_TEXTURE);
            }
        }
    }
}

inline void gl_rend_state::update_texture() {
    if (update_flags & GL_REND_STATE_UPDATE_TEXTURE) {
        for (int32_t index = texture_binding_start_index;
            index <= texture_binding_end_index; index++)
            if (curr_texture_binding_2d[index] != texture_binding_2d[index]) {
                if (DIVA_GL_VERSION_4_5)
                    glBindTextureUnit(index, texture_binding_2d[index]);
                else {
                    if (curr_active_texture_index != index)
                        glActiveTexture((GLenum)(GL_TEXTURE0 + index));

                    glBindTextureDLL(GL_TEXTURE_2D, texture_binding_2d[index]);
                    curr_active_texture_index = index;
                }
                curr_texture_binding_2d[index] = texture_binding_2d[index];
            }
            else if (curr_texture_binding_cube_map[index] != texture_binding_cube_map[index]) {
                if (DIVA_GL_VERSION_4_5)
                    glBindTextureUnit(index, texture_binding_cube_map[index]);
                else {
                    if (curr_active_texture_index != index)
                        glActiveTexture((GLenum)(GL_TEXTURE0 + index));

                    glBindTextureDLL(GL_TEXTURE_CUBE_MAP, texture_binding_cube_map[index]);
                    curr_active_texture_index = index;
                }
                curr_texture_binding_cube_map[index] = texture_binding_cube_map[index];
            }

        texture_binding_start_index = 32;
        texture_binding_end_index = -1;
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_TEXTURE);
    }
}

inline void gl_rend_state::update_sampler() {
    if (update_flags & GL_REND_STATE_UPDATE_SAMPLER) {
        for (int32_t index = sampler_binding_start_index;
            index <= sampler_binding_end_index; index++)
            if (curr_sampler_binding[index] != sampler_binding[index]) {
                glBindSampler(index, sampler_binding[index]);
                curr_sampler_binding[index] = sampler_binding[index];
            }

        sampler_binding_start_index = 32;
        sampler_binding_end_index = -1;
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_SAMPLER);
    }
}

inline void gl_rend_state::update_blend() {
    if (update_flags & GL_REND_STATE_UPDATE_BLEND) {
        if (curr_blend != blend) {
            (blend ? glEnableDLL : glDisableDLL)(GL_BLEND);
            curr_blend = blend;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_BLEND);
    }
}

inline void gl_rend_state::update_blend_func() {
    if (curr_blend && (update_flags & GL_REND_STATE_UPDATE_BLEND_FUNC)) {
        if (curr_blend_src_rgb != blend_src_rgb || curr_blend_dst_rgb != blend_dst_rgb
            || curr_blend_src_alpha != blend_src_alpha || curr_blend_dst_alpha != blend_dst_alpha) {
            glBlendFuncSeparate(blend_src_rgb, blend_dst_rgb, blend_src_alpha, blend_dst_alpha);
            curr_blend_src_rgb = blend_src_rgb;
            curr_blend_dst_rgb = blend_dst_rgb;
            curr_blend_src_alpha = blend_src_alpha;
            curr_blend_dst_alpha = blend_dst_alpha;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_BLEND_FUNC);
    }
}

inline void gl_rend_state::update_blend_equation() {
    if (curr_blend && (update_flags & GL_REND_STATE_UPDATE_BLEND_EQUATION)) {
        if (curr_blend_mode_rgb != blend_mode_rgb || curr_blend_mode_alpha != blend_mode_alpha) {
            glBlendEquationSeparate(blend_mode_rgb, blend_mode_alpha);
            curr_blend_mode_rgb = blend_mode_rgb;
            curr_blend_mode_alpha = blend_mode_alpha;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_BLEND_EQUATION);
    }
}

inline void gl_rend_state::update_read_framebuffer() {
    if (update_flags & GL_REND_STATE_UPDATE_READ_FRAMEBUFFER) {
        if (curr_read_framebuffer_binding != read_framebuffer_binding) {
            glBindFramebuffer(GL_READ_FRAMEBUFFER, read_framebuffer_binding);
            if (read_framebuffer_binding) {
                GLenum status = glCheckFramebufferStatus(GL_READ_FRAMEBUFFER);
                if (status != GL_FRAMEBUFFER_COMPLETE && status != GL_NO_ERROR)
                    printf_debug("GL Error: Bind Read Framebuffer Status - 0x%04X\n", status);
                gl_get_error_print();
            }
            curr_read_framebuffer_binding = read_framebuffer_binding;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_READ_FRAMEBUFFER);
    }
}

inline void gl_rend_state::update_draw_framebuffer() {
    if (update_flags & GL_REND_STATE_UPDATE_DRAW_FRAMEBUFFER) {
        if (curr_draw_framebuffer_binding != draw_framebuffer_binding) {
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_framebuffer_binding);
            if (draw_framebuffer_binding) {
                GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
                if (status != GL_FRAMEBUFFER_COMPLETE && status != GL_NO_ERROR)
                    printf_debug("GL Error: Bind Draw Framebuffer Status - 0x%04X\n", status);
                gl_get_error_print();
            }
            curr_draw_framebuffer_binding = draw_framebuffer_binding;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_DRAW_FRAMEBUFFER);
    }
}

inline void gl_rend_state::update_vertex_array() {
    if (update_flags & GL_REND_STATE_UPDATE_VERTEX_ARRAY) {
        if (curr_vertex_array_binding != vertex_array_binding) {
            glBindVertexArray(vertex_array_binding);
            curr_vertex_array_binding = vertex_array_binding;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_VERTEX_ARRAY);
    }
}

inline void gl_rend_state::update_uniform_buffer() {
    if (update_flags & GL_REND_STATE_UPDATE_UNIFORM_BUFFER) {
        for (int32_t index = uniform_buffer_start_index;
            index <= uniform_buffer_end_index; index++) {
            if (curr_uniform_buffer_bindings[index] == uniform_buffer_bindings[index]
                && curr_uniform_buffer_offsets[index] == uniform_buffer_offsets[index]
                && curr_uniform_buffer_sizes[index] == uniform_buffer_sizes[index])
                continue;

            if (uniform_buffer_offsets[index] == 0 && uniform_buffer_sizes[index] == -1)
                glBindBufferBase(GL_UNIFORM_BUFFER, index, uniform_buffer_bindings[index]);
            else
                glBindBufferRange(GL_UNIFORM_BUFFER, index, uniform_buffer_bindings[index],
                    uniform_buffer_offsets[index], uniform_buffer_sizes[index]);
            uniform_buffer_binding = uniform_buffer_bindings[index];
            curr_uniform_buffer_bindings[index] = uniform_buffer_bindings[index];
            curr_uniform_buffer_offsets[index] = uniform_buffer_offsets[index];
            curr_uniform_buffer_sizes[index] = uniform_buffer_sizes[index];
        }

        uniform_buffer_start_index = 14;
        uniform_buffer_end_index = -1;
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_UNIFORM_BUFFER);
    }
}

inline void gl_rend_state::update_shader_storage_buffer() {
    if (DIVA_GL_VERSION_4_3 && (update_flags & GL_REND_STATE_UPDATE_SHADER_STORAGE_BUFFER)) {
        for (int32_t index = shader_storage_buffer_start_index;
            index <= shader_storage_buffer_end_index; index++) {
            if (curr_shader_storage_buffer_bindings[index] == shader_storage_buffer_bindings[index]
                && curr_shader_storage_buffer_offsets[index] == shader_storage_buffer_offsets[index]
                && curr_shader_storage_buffer_sizes[index] == shader_storage_buffer_sizes[index])
                continue;

            if (shader_storage_buffer_offsets[index] == 0 && shader_storage_buffer_sizes[index] == -1)
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, shader_storage_buffer_bindings[index]);
            else
                glBindBufferRange(GL_SHADER_STORAGE_BUFFER, index, shader_storage_buffer_bindings[index],
                    shader_storage_buffer_offsets[index], shader_storage_buffer_sizes[index]);
            shader_storage_buffer_binding = shader_storage_buffer_bindings[index];
            curr_shader_storage_buffer_bindings[index] = shader_storage_buffer_bindings[index];
            curr_shader_storage_buffer_offsets[index] = shader_storage_buffer_offsets[index];
            curr_shader_storage_buffer_sizes[index] = shader_storage_buffer_sizes[index];
        }

        shader_storage_buffer_start_index = 14;
        shader_storage_buffer_end_index = -1;
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_SHADER_STORAGE_BUFFER);
    }
}

inline void gl_rend_state::update_color_mask() {
    if (update_flags & GL_REND_STATE_UPDATE_COLOR_MASK) {
        if (memcmp(&curr_color_mask, &color_mask, sizeof(GLboolean) * 4)) {
            glColorMaskDLL(color_mask[0], color_mask[1], color_mask[2], color_mask[3]);
            memcpy(&curr_color_mask, &color_mask, sizeof(GLboolean) * 4);
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_COLOR_MASK);
    }
}

inline void gl_rend_state::update_cull_face() {
    if (update_flags & GL_REND_STATE_UPDATE_CULL_FACE) {
        if (curr_cull_face != cull_face) {
            (cull_face ? glEnableDLL : glDisableDLL)(GL_CULL_FACE);
            curr_cull_face = cull_face;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_CULL_FACE);
    }
}

inline void gl_rend_state::update_cull_face_mode() {
    if (curr_cull_face && (update_flags & GL_REND_STATE_UPDATE_CULL_FACE_MODE)) {
        if (curr_cull_face_mode != cull_face_mode) {
            glCullFaceDLL(cull_face_mode);
            curr_cull_face_mode = cull_face_mode;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_CULL_FACE_MODE);
    }
}

inline void gl_rend_state::update_depth_test() {
    if (update_flags & GL_REND_STATE_UPDATE_DEPTH_TEST) {
        if (curr_depth_test != depth_test) {
            (depth_test ? glEnableDLL : glDisableDLL)(GL_DEPTH_TEST);
            curr_depth_test = depth_test;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_DEPTH_TEST);
    }
}

inline void gl_rend_state::update_depth_mask() {
    if (curr_depth_test && (update_flags & GL_REND_STATE_UPDATE_DEPTH_MASK)) {
        if (curr_depth_mask != depth_mask) {
            glDepthMaskDLL(depth_mask);
            curr_depth_mask = depth_mask;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_DEPTH_MASK);
    }
}

inline void gl_rend_state::update_depth_func() {
    if (curr_depth_test && (update_flags & GL_REND_STATE_UPDATE_DEPTH_FUNC)) {
        if (curr_depth_func != depth_func) {
            glDepthFuncDLL(depth_func);
            curr_depth_func = depth_func;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_DEPTH_FUNC);
    }
}

inline void gl_rend_state::update_line_width() {
    if (update_flags & GL_REND_STATE_UPDATE_LINE_WIDTH) {
        if (curr_line_width != line_width) {
            glLineWidthDLL(line_width);
            curr_line_width = line_width;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_LINE_WIDTH);
    }
}

inline void gl_rend_state::update_multisample() {
    if (update_flags & GL_REND_STATE_UPDATE_MULTISAMPLE) {
        if (curr_multisample != multisample) {
            (multisample ? glEnableDLL : glDisableDLL)(GL_MULTISAMPLE);
            curr_multisample = multisample;
        }

        enum_and(update_flags, ~GL_REND_STATE_UPDATE_MULTISAMPLE);
    }
}

inline void gl_rend_state::update_primitive_restart() {
    if (update_flags & GL_REND_STATE_UPDATE_PRIMITIVE_RESTART) {
        if (curr_primitive_restart != primitive_restart) {
            (primitive_restart ? glEnableDLL : glDisableDLL)(GL_PRIMITIVE_RESTART);
            curr_primitive_restart = primitive_restart;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_PRIMITIVE_RESTART);
    }
}

inline void gl_rend_state::update_primitive_restart_index() {
    if (curr_primitive_restart && (update_flags & GL_REND_STATE_UPDATE_PRIMITIVE_RESTART_INDEX)) {
        if (curr_primitive_restart_index != primitive_restart_index) {
            glPrimitiveRestartIndex(primitive_restart_index);
            curr_primitive_restart_index = primitive_restart_index;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_PRIMITIVE_RESTART_INDEX);
    }
}

inline void gl_rend_state::update_scissor_test() {
    if (update_flags & GL_REND_STATE_UPDATE_SCISSOR_TEST) {
        if (curr_scissor_test != scissor_test) {
            (scissor_test ? glEnableDLL : glDisableDLL)(GL_SCISSOR_TEST);
            curr_scissor_test = scissor_test;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_SCISSOR_TEST);
    }
}

inline void gl_rend_state::update_scissor() {
    if (curr_scissor_test && (update_flags & GL_REND_STATE_UPDATE_SCISSOR)) {
        if (memcmp(&curr_scissor_box, &scissor_box, sizeof(gl_rend_state_rect))) {
            glScissorDLL(scissor_box.x, scissor_box.y, scissor_box.width, scissor_box.height);
            curr_scissor_box = scissor_box;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_SCISSOR);
    }
}

inline void gl_rend_state::update_stencil_test() {
    if (update_flags & GL_REND_STATE_UPDATE_STENCIL_TEST) {
        if (curr_stencil_test != stencil_test) {
            (stencil_test ? glEnableDLL : glDisableDLL)(GL_STENCIL_TEST);
            curr_stencil_test = stencil_test;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_STENCIL_TEST);
    }
}

inline void gl_rend_state::update_stencil_mask() {
    if (curr_stencil_test && (update_flags & GL_REND_STATE_UPDATE_STENCIL_MASK)) {
        if (curr_stencil_mask != stencil_mask) {
            glStencilMask(stencil_mask);
            curr_stencil_mask = stencil_mask;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_STENCIL_MASK);
    }
}

inline void gl_rend_state::update_stencil_func() {
    if (curr_stencil_test && (update_flags & GL_REND_STATE_UPDATE_STENCIL_FUNC)) {
        if (curr_stencil_func != stencil_func || curr_stencil_ref != stencil_ref
            || curr_stencil_value_mask != stencil_value_mask) {
            glStencilFunc(stencil_func, stencil_ref, stencil_ref);
            curr_stencil_func = stencil_func;
            curr_stencil_ref = stencil_ref;
            curr_stencil_value_mask = stencil_value_mask;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_STENCIL_FUNC);
    }
}

inline void gl_rend_state::update_stencil_op() {
    if (curr_stencil_test && (update_flags & GL_REND_STATE_UPDATE_STENCIL_OP)) {
        if (curr_stencil_fail != stencil_fail || curr_stencil_dpfail != stencil_dpfail
            || curr_stencil_dppass != stencil_dppass) {
            glStencilOp(stencil_fail, stencil_dpfail, stencil_dppass);
            curr_stencil_fail = stencil_fail;
            curr_stencil_dpfail = stencil_dpfail;
            curr_stencil_dppass = stencil_dppass;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_STENCIL_OP);
    }
}

inline void gl_rend_state::update_viewport() {
    if (update_flags & GL_REND_STATE_UPDATE_VIEWPORT) {
        if (memcmp(&curr_viewport, &viewport, sizeof(gl_rend_state_rect))) {
            glViewportDLL(viewport.x, viewport.y, viewport.width, viewport.height);
            curr_viewport = viewport;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_VIEWPORT);
    }
}

inline void gl_rend_state::update_clear_color() {
    if (update_flags & GL_REND_STATE_UPDATE_CLEAR_COLOR) {
        if (curr_clear_color_value[0] != clear_color_value[0]
            || curr_clear_color_value[1] != clear_color_value[1]
            || curr_clear_color_value[2] != clear_color_value[2]
            || curr_clear_color_value[3] != clear_color_value[3]) {
            glClearColorDLL(clear_color_value[0], clear_color_value[1],
                clear_color_value[2], clear_color_value[3]);
            curr_clear_color_value[0] = clear_color_value[0];
            curr_clear_color_value[1] = clear_color_value[1];
            curr_clear_color_value[2] = clear_color_value[2];
            curr_clear_color_value[3] = clear_color_value[3];
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_CLEAR_COLOR);
    }
}

inline void gl_rend_state::update_clear_depth() {
    if (update_flags & GL_REND_STATE_UPDATE_CLEAR_DEPTH) {
        if (curr_clear_depth_value != clear_depth_value) {
            glClearDepthf(clear_depth_value);
            curr_clear_depth_value = clear_depth_value;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_CLEAR_DEPTH);
    }
}

inline void gl_rend_state::update_clear_stencil() {
    if (update_flags & GL_REND_STATE_UPDATE_CLEAR_STENCIL) {
        if (curr_clear_stencil_value != clear_stencil_value) {
            glClearStencilDLL(clear_stencil_value);
            curr_clear_stencil_value = clear_stencil_value;
        }
        enum_and(update_flags, ~GL_REND_STATE_UPDATE_CLEAR_STENCIL);
    }
}

inline void gl_rend_state::use_program(GLuint program) {
    this->program = program;
    enum_or(update_flags, GL_REND_STATE_UPDATE_PROGRAM);
}
