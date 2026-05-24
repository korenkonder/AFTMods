/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../KKdLib/default.hpp"
#include "../AFTModsShared/ogl_buffer_object.hpp"
#include "../AFTModsShared/object.hpp"
#include "../AFTModsShared/types.hpp"
#include "GL/buffer.hpp"
#include "config.hpp"

// Added
struct IndexBufferDivaGL : IndexBuffer {
    IndexBufferDivaGL();
    IndexBufferDivaGL(const IndexBuffer& other);

    bool create(uint32_t size, const void* buf);
#if SHARED_OBJECT_BUFFER
    void create(GLuint in_ib);
#endif
    void destroy();
#if SHARED_OBJECT_BUFFER
    void destroy_shared();
#endif
};

struct VertexBufferDivaGL : VertexBuffer {
#if SHARED_OBJECT_BUFFER
    uint32_t vb_size; // Added
    uint32_t vb_offset; // Added
#endif

    VertexBufferDivaGL();
    VertexBufferDivaGL(const VertexBuffer& other);
    ~VertexBufferDivaGL();

    bool create(uint32_t size, const void* buf,
        uint32_t num_flip, GL::BufferUsage usage = GL::BUFFER_USAGE_STATIC);
#if SHARED_OBJECT_BUFFER
    void create(AFTGLuint in_vb, uint32_t size, uint32_t offset); // Added
#endif
    void destroy();
#if SHARED_OBJECT_BUFFER
    void destroy_shared(); // Added
#endif
    uint32_t get_glvb_offset() const; // Added
    uint32_t get_size() const;
};
