/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../../KKdLib/default.hpp"
#include "../wrap.hpp"
#include "buffer.hpp"

struct gl_state_struct;
struct p_gl_rend_state;

namespace GL {
    struct ShaderStorageBuffer {
    private:
        GLuint buffer;

    public:
        inline ShaderStorageBuffer() : buffer() {

        }

        inline ShaderStorageBuffer(GLuint buffer) : buffer(buffer) {

        }

        inline ~ShaderStorageBuffer() {

        }

        void Create(gl_state_struct& gl_st, size_t size, BufferUsage usage = BUFFER_USAGE_STREAM);
        void Create(gl_state_struct& gl_st, size_t size, const void* data, BufferUsage usage = BUFFER_USAGE_STATIC);
        void Destroy();
        void Recreate(gl_state_struct& gl_st, size_t size, BufferUsage usage = BUFFER_USAGE_STREAM);
        void Recreate(gl_state_struct& gl_st, size_t size, const void* data, BufferUsage usage = BUFFER_USAGE_STATIC);

        inline bool IsNull() {
            return !buffer;
        }

        inline bool NotNull() {
            return !!buffer;
        }

        inline operator GLuint() const {
            return buffer;
        }
    };
}
