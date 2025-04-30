/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "uniform_buffer.hpp"
#include "../gl_rend_state.hpp"
#include "../gl_state.hpp"

namespace GL {
    void UniformBuffer::Create(gl_state_struct& gl_st, size_t size) {
        if (buffer)
            return;

        if (DIVA_GL_VERSION_4_5) {
            glCreateBuffers(1, &buffer);
            glNamedBufferStorage(buffer, (GLsizeiptr)size, 0, GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
        }
        else {
            glGenBuffers(1, &buffer);
            gl_st.bind_uniform_buffer(buffer, true);
            if (DIVA_GL_VERSION_4_4)
                glBufferStorage(GL_UNIFORM_BUFFER, (GLsizeiptr)size,
                    0, GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
            else
                glBufferData(GL_UNIFORM_BUFFER, (GLsizeiptr)size, 0, GL_DYNAMIC_DRAW);
        }
    }

    void UniformBuffer::Create(gl_state_struct& gl_st, size_t size, const void* data, bool dynamic) {
        if (buffer)
            return;

        if (DIVA_GL_VERSION_4_5) {
            glCreateBuffers(1, &buffer);
            glNamedBufferStorage(buffer, (GLsizeiptr)size, data,
                dynamic ? GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT : 0);
        }
        else {
            glGenBuffers(1, &buffer);
            gl_st.bind_uniform_buffer(buffer, true);
            if (DIVA_GL_VERSION_4_4)
                glBufferStorage(GL_UNIFORM_BUFFER, (GLsizeiptr)size, data,
                    dynamic ? GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT : 0);
            else
                glBufferData(GL_UNIFORM_BUFFER, (GLsizeiptr)size, data,
                    dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        }
    }

    void UniformBuffer::Destroy() {
        if (buffer) {
            glDeleteBuffers(1, &buffer);
            buffer = 0;
        }
    }

    void* UniformBuffer::MapMemory(gl_state_struct& gl_st) {
        if (!buffer)
            return 0;

        void* data;
        if (DIVA_GL_VERSION_4_5)
            data = glMapNamedBuffer(buffer, GL_WRITE_ONLY);
        else {
            gl_st.bind_uniform_buffer(buffer);
            data = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
        }

        if (data)
            return data;

        if (DIVA_GL_VERSION_4_5)
            glUnmapNamedBuffer(buffer);
        else {
            glUnmapBuffer(GL_UNIFORM_BUFFER);
            gl_st.bind_uniform_buffer(0);
        }
        return 0;
    }

    void* UniformBuffer::MapMemory(p_gl_rend_state& p_gl_rend_st) {
        if (!buffer)
            return 0;

        void* data;
        if (DIVA_GL_VERSION_4_5)
            data = glMapNamedBuffer(buffer, GL_WRITE_ONLY);
        else {
            p_gl_rend_st.bind_uniform_buffer(buffer);
            data = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
        }

        if (data)
            return data;

        if (DIVA_GL_VERSION_4_5)
            glUnmapNamedBuffer(buffer);
        else {
            glUnmapBuffer(GL_UNIFORM_BUFFER);
            p_gl_rend_st.bind_uniform_buffer(0);
        }
        return 0;
    }

    void UniformBuffer::UnmapMemory(gl_state_struct& gl_st) {
        if (!buffer)
            return;

        if (DIVA_GL_VERSION_4_5)
            glUnmapNamedBuffer(buffer);
        else {
            glUnmapBuffer(GL_UNIFORM_BUFFER);
            gl_st.bind_uniform_buffer(0);
        }
    }

    void UniformBuffer::UnmapMemory(p_gl_rend_state& p_gl_rend_st) {
        if (!buffer)
            return;

        if (DIVA_GL_VERSION_4_5)
            glUnmapNamedBuffer(buffer);
        else {
            glUnmapBuffer(GL_UNIFORM_BUFFER);
            p_gl_rend_st.bind_uniform_buffer(0);
        }
    }

    void UniformBuffer::WriteMemory(gl_state_struct& gl_st, size_t offset, size_t size, const void* data) {
        if (!buffer || !size)
            return;

        if (DIVA_GL_VERSION_4_5)
            glNamedBufferSubData(buffer, (GLsizeiptr)offset, (GLsizeiptr)size, data);
        else {
            gl_st.bind_uniform_buffer(buffer);
            glBufferSubData(GL_UNIFORM_BUFFER, (GLsizeiptr)offset, (GLsizeiptr)size, data);
        }
    }

    void UniformBuffer::WriteMemory(p_gl_rend_state& p_gl_rend_st, size_t offset, size_t size, const void* data) {
        if (!buffer || !size)
            return;

        if (DIVA_GL_VERSION_4_5)
            glNamedBufferSubData(buffer, (GLsizeiptr)offset, (GLsizeiptr)size, data);
        else {
            p_gl_rend_st.bind_uniform_buffer(buffer);
            glBufferSubData(GL_UNIFORM_BUFFER, (GLsizeiptr)offset, (GLsizeiptr)size, data);
        }
    }
};
