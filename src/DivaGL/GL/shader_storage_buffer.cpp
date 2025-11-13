/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "shader_storage_buffer.hpp"
#include "../gl_rend_state.hpp"
#include "../gl_state.hpp"

namespace GL {
    void ShaderStorageBuffer::Create(gl_state_struct& gl_st, size_t size, BufferUsage usage) {
        if (buffer || !BufferUsageCheck(usage, false))
            return;

        if (usage != BUFFER_USAGE_STREAM) {
            if (DIVA_GL_VERSION_4_4) {
                GLbitfield flags = GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT;
                if (DIVA_GL_VERSION_4_5) {
                    glCreateBuffers(1, &buffer);
                    glNamedBufferStorage(buffer, (GLsizeiptr)size, 0, flags);
                }
                else {
                    glGenBuffers(1, &buffer);
                    gl_st.bind_shader_storage_buffer(buffer, true);
                    glBufferStorage(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)size, 0, flags);
                }
                return;
            }
        }

        if (DIVA_GL_VERSION_4_5) {
            glCreateBuffers(1, &buffer);
            glNamedBufferData(buffer, (GLsizeiptr)size, 0, BufferUsageToGLenum(usage));
        }
        else {
            glGenBuffers(1, &buffer);
            gl_st.bind_shader_storage_buffer(buffer, true);
            glBufferData(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)size, 0, BufferUsageToGLenum(usage));
        }
    }

    void ShaderStorageBuffer::Create(gl_state_struct& gl_st, size_t size, const void* data, BufferUsage usage) {
        if (buffer || !BufferUsageCheck(usage))
            return;

        if (usage != BUFFER_USAGE_STREAM) {
            if (DIVA_GL_VERSION_4_4) {
                GLbitfield flags = usage == BUFFER_USAGE_DYNAMIC
                    ? GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT : 0;
                if (DIVA_GL_VERSION_4_5) {
                    glCreateBuffers(1, &buffer);
                    glNamedBufferStorage(buffer, (GLsizeiptr)size, data, flags);
                }
                else {
                    glGenBuffers(1, &buffer);
                    gl_st.bind_shader_storage_buffer(buffer, true);
                    glBufferStorage(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)size, data, flags);
                }
                return;
            }
        }

        if (DIVA_GL_VERSION_4_5) {
            glCreateBuffers(1, &buffer);
            glNamedBufferData(buffer, (GLsizeiptr)size, data, BufferUsageToGLenum(usage));
        }
        else {
            glGenBuffers(1, &buffer);
            gl_st.bind_shader_storage_buffer(buffer, true);
            glBufferData(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)size, data, BufferUsageToGLenum(usage));
        }
    }

    void ShaderStorageBuffer::Destroy() {
        if (buffer) {
            glDeleteBuffers(1, &buffer);
            buffer = 0;
        }
    }

    void* ShaderStorageBuffer::MapMemory(gl_state_struct& gl_st) {
        if (!buffer)
            return 0;

        void* data;
        if (DIVA_GL_VERSION_4_5)
            data = glMapNamedBuffer(buffer, GL_WRITE_ONLY);
        else {
            gl_st.bind_shader_storage_buffer(buffer);
            data = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
        }

        if (data)
            return data;

        if (DIVA_GL_VERSION_4_5)
            glUnmapNamedBuffer(buffer);
        else {
            glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
            gl_st.bind_shader_storage_buffer(0);
        }
        return 0;
    }

    void* ShaderStorageBuffer::MapMemory(p_gl_rend_state& p_gl_rend_st) {
        if (!buffer)
            return 0;

        void* data;
        if (DIVA_GL_VERSION_4_5)
            data = glMapNamedBuffer(buffer, GL_WRITE_ONLY);
        else {
            p_gl_rend_st.bind_shader_storage_buffer(buffer);
            data = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
        }

        if (data)
            return data;

        if (DIVA_GL_VERSION_4_5)
            glUnmapNamedBuffer(buffer);
        else {
            glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
            p_gl_rend_st.bind_shader_storage_buffer(0);
        }
        return 0;
    }

    void ShaderStorageBuffer::Recreate(gl_state_struct& gl_st, size_t size, BufferUsage usage) {
        if (DIVA_GL_VERSION_4_4 && usage != BUFFER_USAGE_STREAM) {
            Destroy();
            Create(gl_st, size, usage);
        }
        else {
            if (!buffer)
                Create(gl_st, size, usage);

            if (DIVA_GL_VERSION_4_5)
                glNamedBufferData(buffer, (GLsizeiptr)size, 0, BufferUsageToGLenum(usage));
            else {
                gl_st.bind_shader_storage_buffer(buffer);
                glBufferData(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)size, 0, BufferUsageToGLenum(usage));
            }
        }
    }

    void ShaderStorageBuffer::Recreate(gl_state_struct& gl_st, size_t size, const void* data, BufferUsage usage) {
        if (DIVA_GL_VERSION_4_4 && usage != BUFFER_USAGE_STREAM) {
            Destroy();
            Create(gl_st, size, data, usage);
        }
        else {
            if (!buffer)
                Create(gl_st, size, data, usage);

            if (DIVA_GL_VERSION_4_5)
                glNamedBufferData(buffer, (GLsizeiptr)size, data, BufferUsageToGLenum(usage));
            else {
                gl_st.bind_shader_storage_buffer(buffer);
                glBufferData(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)size, data, BufferUsageToGLenum(usage));
            }
        }
    }

    void ShaderStorageBuffer::UnmapMemory(gl_state_struct& gl_st) {
        if (!buffer)
            return;

        if (DIVA_GL_VERSION_4_5)
            glUnmapNamedBuffer(buffer);
        else {
            glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
            gl_st.bind_shader_storage_buffer(0);
        }
    }

    void ShaderStorageBuffer::UnmapMemory(p_gl_rend_state& p_gl_rend_st) {
        if (!buffer)
            return;

        if (DIVA_GL_VERSION_4_5)
            glUnmapNamedBuffer(buffer);
        else {
            glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
            p_gl_rend_st.bind_shader_storage_buffer(0);
        }
    }

    void ShaderStorageBuffer::WriteMemory(gl_state_struct& gl_st, size_t offset, size_t size, const void* data) {
        if (!buffer || !size)
            return;

        if (DIVA_GL_VERSION_4_5)
            glNamedBufferSubData(buffer, (GLsizeiptr)offset, (GLsizeiptr)size, data);
        else {
            gl_st.bind_shader_storage_buffer(buffer);
            glBufferSubData(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)offset, (GLsizeiptr)size, data);
        }
    }

    void ShaderStorageBuffer::WriteMemory(p_gl_rend_state& p_gl_rend_st, size_t offset, size_t size, const void* data) {
        if (!buffer || !size)
            return;

        if (DIVA_GL_VERSION_4_5)
            glNamedBufferSubData(buffer, (GLsizeiptr)offset, (GLsizeiptr)size, data);
        else {
            p_gl_rend_st.bind_shader_storage_buffer(buffer);
            glBufferSubData(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)offset, (GLsizeiptr)size, data);
        }
    }
}
