/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "gl_state.hpp"
#include "shared.hpp"

gl_state_struct gl_state;

void gl_state_struct::bind_framebuffer(GLuint framebuffer, bool force) {
    if (force || read_framebuffer_binding != framebuffer
        || draw_framebuffer_binding != framebuffer) {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        read_framebuffer_binding = framebuffer;
        draw_framebuffer_binding = framebuffer;
    }
}

void gl_state_struct::bind_read_framebuffer(GLuint framebuffer, bool force) {
    if (force || read_framebuffer_binding != framebuffer) {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
        read_framebuffer_binding = framebuffer;
    }
}

void gl_state_struct::bind_draw_framebuffer(GLuint framebuffer, bool force) {
    if (force || draw_framebuffer_binding != framebuffer) {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
        draw_framebuffer_binding = framebuffer;
    }
}

void gl_state_struct::bind_vertex_array(GLuint array, bool force) {
    if (force || vertex_array_binding != array) {
        glBindVertexArray(array);
        vertex_array_binding = array;
    }
}

void gl_state_struct::bind_array_buffer(GLuint buffer, bool force) {
    if (force || array_buffer_binding != buffer) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        array_buffer_binding = buffer;
    }
}

void gl_state_struct::bind_element_array_buffer(GLuint buffer, bool force) {
    if (force || element_array_buffer_binding != buffer) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        element_array_buffer_binding = buffer;
    }
}

void gl_state_struct::bind_uniform_buffer(GLuint buffer, bool force) {
    if (force || uniform_buffer_binding != buffer) {
        glBindBuffer(GL_UNIFORM_BUFFER, buffer);
        uniform_buffer_binding = buffer;
    }
}

void gl_state_struct::bind_shader_storage_buffer(GLuint buffer, bool force) {
    if (force || shader_storage_buffer_binding != buffer) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
        shader_storage_buffer_binding = buffer;
    }
}

void gl_state_struct::bind_texture_2d(GLuint texture, bool force) {
    if (texture_binding_2d != texture) {
        glBindTextureDLL(GL_TEXTURE_2D, texture);
        texture_binding_2d = texture;
    }
}

void gl_state_struct::bind_texture_cube_map(GLuint texture, bool force) {
    if (force || texture_binding_cube_map != texture) {
        glBindTextureDLL(GL_TEXTURE_CUBE_MAP, texture);
        texture_binding_cube_map = texture;
    }
}

bool gl_state_struct::check_uniform_buffer_binding() {
    return uniform_buffer_binding != 0;
}

bool gl_state_struct::check_shader_storage_buffer_binding() {
    return shader_storage_buffer_binding != 0;
}

bool gl_state_struct::check_texture_binding_2d() {
    return texture_binding_2d != 0;
}

bool gl_state_struct::check_texture_binding_cube_map() {
    return texture_binding_cube_map != 0;
}

void gl_state_struct::get() {
    gl_get_error_all_print();

    glGetIntegervDLL(GL_TEXTURE_BINDING_2D, (GLint*)&texture_binding_2d);
    glGetIntegervDLL(GL_TEXTURE_BINDING_CUBE_MAP, (GLint*)&texture_binding_cube_map);

    glGetIntegervDLL(GL_READ_FRAMEBUFFER_BINDING, (GLint*)&read_framebuffer_binding);
    glGetIntegervDLL(GL_DRAW_FRAMEBUFFER_BINDING, (GLint*)&draw_framebuffer_binding);
    glGetIntegervDLL(GL_VERTEX_ARRAY_BINDING, (GLint*)&vertex_array_binding);
    glGetIntegervDLL(GL_ARRAY_BUFFER_BINDING, (GLint*)&array_buffer_binding);
    glGetIntegervDLL(GL_ELEMENT_ARRAY_BUFFER_BINDING, (GLint*)&element_array_buffer_binding);

    glGetIntegervDLL(GL_UNIFORM_BUFFER_BINDING, (GLint*)&uniform_buffer_binding);
    if (DIVA_GL_VERSION_4_3)
        glGetIntegervDLL(GL_SHADER_STORAGE_BUFFER_BINDING, (GLint*)&shader_storage_buffer_binding);
}

void* gl_state_struct::map_array_buffer(GLuint buffer) {
    if (!buffer)
        return 0;

    void* data;
    if (DIVA_GL_VERSION_4_5)
        data = glMapNamedBuffer(buffer, GL_WRITE_ONLY);
    else {
        bind_array_buffer(buffer);
        data = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    }

    if (data)
        return data;

    if (DIVA_GL_VERSION_4_5)
        glUnmapNamedBuffer(buffer);
    else {
        glUnmapBuffer(GL_ARRAY_BUFFER);
        bind_array_buffer(0);
    }
    return 0;
}

void* gl_state_struct::map_element_array_buffer(GLuint buffer) {
    if (!buffer)
        return 0;

    void* data;
    if (DIVA_GL_VERSION_4_5)
        data = glMapNamedBuffer(buffer, GL_WRITE_ONLY);
    else {
        bind_element_array_buffer(buffer);
        data = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    }

    if (data)
        return data;

    if (DIVA_GL_VERSION_4_5)
        glUnmapNamedBuffer(buffer);
    else {
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        bind_element_array_buffer(0);
    }
    return 0;
}

void* gl_state_struct::map_uniform_buffer(GLuint buffer) {
    if (!buffer)
        return 0;

    void* data;
    if (DIVA_GL_VERSION_4_5)
        data = glMapNamedBuffer(buffer, GL_WRITE_ONLY);
    else {
        bind_uniform_buffer(buffer);
        data = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
    }

    if (data)
        return data;

    if (DIVA_GL_VERSION_4_5)
        glUnmapNamedBuffer(buffer);
    else {
        glUnmapBuffer(GL_UNIFORM_BUFFER);
        bind_uniform_buffer(0);
    }
    return 0;
}

void* gl_state_struct::map_shader_storage_buffer(GLuint buffer) {
    if (!buffer)
        return 0;

    void* data;
    if (DIVA_GL_VERSION_4_5)
        data = glMapNamedBuffer(buffer, GL_WRITE_ONLY);
    else {
        bind_shader_storage_buffer(buffer);
        data = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
    }

    if (data)
        return data;

    if (DIVA_GL_VERSION_4_5)
        glUnmapNamedBuffer(buffer);
    else {
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        bind_shader_storage_buffer(0);
    }
    return 0;
}

void gl_state_struct::unmap_array_buffer(GLuint buffer) {
    if (!buffer)
        return;

    if (DIVA_GL_VERSION_4_5)
        glUnmapNamedBuffer(buffer);
    else {
        glUnmapBuffer(GL_ARRAY_BUFFER);
        bind_array_buffer(0);
    }
}

void gl_state_struct::unmap_element_array_buffer(GLuint buffer) {
    if (!buffer)
        return;

    if (DIVA_GL_VERSION_4_5)
        glUnmapNamedBuffer(buffer);
    else {
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        bind_element_array_buffer(0);
    }
}

void gl_state_struct::unmap_uniform_buffer(GLuint buffer) {
    if (!buffer)
        return;

    if (DIVA_GL_VERSION_4_5)
        glUnmapNamedBuffer(buffer);
    else {
        glUnmapBuffer(GL_UNIFORM_BUFFER);
        bind_uniform_buffer(0);
    }
}

void gl_state_struct::unmap_shader_storage_buffer(GLuint buffer) {
    if (!buffer)
        return;

    if (DIVA_GL_VERSION_4_5)
        glUnmapNamedBuffer(buffer);
    else {
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        bind_shader_storage_buffer(0);
    }
}

void gl_state_struct::write_array_buffer(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) {
    if (!buffer || !size)
        return;

    if (DIVA_GL_VERSION_4_5)
        glNamedBufferSubData(buffer, offset, size, data);
    else {
        bind_array_buffer(buffer);
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }
}

void gl_state_struct::write_element_array_buffer(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) {
    if (!buffer || !size)
        return;

    if (DIVA_GL_VERSION_4_5)
        glNamedBufferSubData(buffer, offset, size, data);
    else {
        bind_element_array_buffer(buffer);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
    }
}

void gl_state_struct::write_uniform_buffer(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) {
    if (!buffer || !size)
        return;

    if (DIVA_GL_VERSION_4_5)
        glNamedBufferSubData(buffer, offset, size, data);
    else {
        bind_uniform_buffer(buffer);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    }
}

void gl_state_struct::write_shader_storage_buffer(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) {
    if (!buffer || !size)
        return;

    if (DIVA_GL_VERSION_4_5)
        glNamedBufferSubData(buffer, offset, size, data);
    else {
        bind_shader_storage_buffer(buffer);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
    }
}
