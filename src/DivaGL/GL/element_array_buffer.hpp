/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../../KKdLib/default.hpp"
#include "../wrap.hpp"

struct gl_state_struct;
struct p_gl_rend_state;

namespace GL {
    struct ElementArrayBuffer {
    private:
        GLuint buffer;

    public:
        inline ElementArrayBuffer() : buffer() {

        }

        inline ElementArrayBuffer(GLuint buffer) : buffer(buffer) {

        }

        inline ~ElementArrayBuffer() {

        }

        void Create(gl_state_struct& gl_st, size_t size);
        void Create(gl_state_struct& gl_st, size_t size, const void* data, bool dynamic = false);
        void Destroy();
        void* MapMemory(gl_state_struct& gl_st);
        void* MapMemory(p_gl_rend_state& p_gl_rend_st);
        void Recreate(gl_state_struct& gl_st, size_t size);
        void Recreate(gl_state_struct& gl_st, size_t size, const void* data, bool dynamic = false);
        void UnmapMemory(gl_state_struct& gl_st);
        void UnmapMemory(p_gl_rend_state& p_gl_rend_st);
        void WriteMemory(gl_state_struct& gl_st, size_t offset, size_t size, const void* data);
        void WriteMemory(p_gl_rend_state& p_gl_rend_st, size_t offset, size_t size, const void* data);

        inline bool IsNull() {
            return !buffer;
        }

        inline bool NotNull() {
            return !!buffer;
        }

        template<typename T>
        inline void WriteMemory(gl_state_struct& gl_st, T& data) {
            WriteMemory(gl_st, 0, sizeof(T), &data);
        }

        template<typename T>
        inline void WriteMemory(p_gl_rend_state& p_gl_rend_st, T& data) {
            WriteMemory(p_gl_rend_st, 0, sizeof(T), &data);
        }

        inline operator GLuint() const {
            return buffer;
        }
    };
}
