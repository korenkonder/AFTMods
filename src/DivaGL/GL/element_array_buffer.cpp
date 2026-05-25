/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "element_array_buffer.hpp"
#include "../gl_rend_state.hpp"
#include "../gl_state.hpp"

namespace GL {
    void ElementArrayBuffer::Create(gl_state_struct& gl_st, size_t size, BufferUsage usage) {
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
                    gl_st.bind_element_array_buffer(buffer, true);
                    glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)size, 0, flags);
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
            gl_st.bind_element_array_buffer(buffer, true);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)size, 0, BufferUsageToGLenum(usage));
        }
    }

    void ElementArrayBuffer::Create(gl_state_struct& gl_st, size_t size, const void* data, BufferUsage usage) {
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
                    gl_st.bind_element_array_buffer(buffer, true);
                    glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)size, data, flags);
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
            gl_st.bind_element_array_buffer(buffer, true);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)size, data, BufferUsageToGLenum(usage));
        }
    }

    void ElementArrayBuffer::Destroy() {
        if (buffer) {
            glDeleteBuffers(1, &buffer);
            buffer = 0;
        }
    }

    void ElementArrayBuffer::Recreate(gl_state_struct& gl_st, size_t size, BufferUsage usage) {
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
                gl_st.bind_element_array_buffer(buffer);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)size, 0, BufferUsageToGLenum(usage));
            }
        }
    }

    void ElementArrayBuffer::Recreate(gl_state_struct& gl_st, size_t size, const void* data, BufferUsage usage) {
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
                gl_st.bind_element_array_buffer(buffer);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)size, data, BufferUsageToGLenum(usage));
            }
        }
    }
}
