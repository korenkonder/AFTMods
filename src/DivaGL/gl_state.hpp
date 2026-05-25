/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../KKdLib/default.hpp"
#include "wrap.hpp"

struct gl_state_struct {
    GLuint texture_binding_2d;
    GLuint texture_binding_cube_map;
    GLuint read_framebuffer_binding;
    GLuint draw_framebuffer_binding;
    GLuint vertex_array_binding;
    GLuint array_buffer_binding;
    GLuint element_array_buffer_binding;
    GLuint uniform_buffer_binding;
    GLuint shader_storage_buffer_binding;

    void bind_framebuffer(GLuint framebuffer, bool force = false);
    void bind_read_framebuffer(GLuint framebuffer, bool force = false);
    void bind_draw_framebuffer(GLuint framebuffer, bool force = false);
    void bind_vertex_array(GLuint array, bool force = false);
    void bind_array_buffer(GLuint buffer, bool force = false);
    void bind_element_array_buffer(GLuint buffer, bool force = false);
    void bind_uniform_buffer(GLuint buffer, bool force = false);
    void bind_shader_storage_buffer(GLuint buffer, bool force = false);
    void bind_texture_2d(GLuint texture, bool force = false);
    void bind_texture_cube_map(GLuint texture, bool force = false);
    bool check_uniform_buffer_binding();
    bool check_shader_storage_buffer_binding();
    bool check_texture_binding_2d();
    bool check_texture_binding_cube_map();
    void get();
    void* map_array_buffer(GLuint buffer);
    void* map_element_array_buffer(GLuint buffer);
    void* map_uniform_buffer(GLuint buffer);
    void* map_shader_storage_buffer(GLuint buffer);
    void unmap_array_buffer(GLuint buffer);
    void unmap_element_array_buffer(GLuint buffer);
    void unmap_uniform_buffer(GLuint buffer);
    void unmap_shader_storage_buffer(GLuint buffer);
    void write_array_buffer(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data);
    void write_element_array_buffer(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data);
    void write_uniform_buffer(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data);
    void write_shader_storage_buffer(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data);

    template<typename T>
    inline void write_array_buffer(GLuint buffer, const T& data) {
        write_array_buffer(buffer, 0, sizeof(T), &data);
    }

    template<typename T>
    inline void write_element_array_buffer(GLuint buffer, const T& data) {
        write_element_array_buffer(buffer, 0, sizeof(T), &data);
    }

    template<typename T>
    inline void write_uniform_buffer(GLuint buffer, const T& data) {
        write_uniform_buffer(buffer, 0, sizeof(T), &data);
    }

    template<typename T>
    inline void write_shader_storage_buffer(GLuint buffer, const T& data) {
        write_shader_storage_buffer(buffer, 0, sizeof(T), &data);
    }
};

extern gl_state_struct gl_state;
