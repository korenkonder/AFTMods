/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "ogl_buffer_object.hpp"

IndexBufferDivaGL::IndexBufferDivaGL() {

}

IndexBufferDivaGL::IndexBufferDivaGL(const IndexBuffer& other) : IndexBuffer(other) {

}

// Added
bool IndexBufferDivaGL::create(uint32_t size, const void* buf) {
    if (!size)
        return false;

    ib = create_index_buffer(size, buf);
    return true;
}

#if SHARED_OBJECT_BUFFER
// Added
void IndexBufferDivaGL::create(GLuint in_ib) {
    ib = in_ib;
}
#endif

// Added
void IndexBufferDivaGL::destroy() {
    free_index_buffer(ib);
    ib = 0;
}

#if SHARED_OBJECT_BUFFER
// Added
void IndexBufferDivaGL::destroy_shared() {
    ib = 0;
}
#endif

#if SHARED_OBJECT_BUFFER
VertexBufferDivaGL::VertexBufferDivaGL() : vb_size(), vb_offset() {
#else
VertexBufferDivaGL::VertexBufferDivaGL() {
#endif

}

#if SHARED_OBJECT_BUFFER
VertexBufferDivaGL::VertexBufferDivaGL(const VertexBuffer& other) : VertexBuffer(other), vb_size(), vb_offset() {
#else
VertexBufferDivaGL::VertexBufferDivaGL(const VertexBuffer& other) : VertexBuffer(other) {
#endif

}

VertexBufferDivaGL::~VertexBufferDivaGL() {

}

// 0x140461650
bool VertexBufferDivaGL::create(uint32_t size, const void* buf, uint32_t num_flip, GL::BufferUsage usage) {
    if (!size || num_flip > VertexBuffer::NUM_FLIP_MAX)
        return false;

    num_flip_chain = num_flip;
    flip_index = 0;
#if SHARED_OBJECT_BUFFER
    vb_size = size;
    vb_offset = 0;
#endif

    uint32_t _size = ((uint32_t)usage << 30) | ((uint32_t)size & ((1u << 30) - 1u));
    for (uint32_t i = 0; i < num_flip; i++) {
        vb[i] = create_vertex_buffer(_size, buf);
        if (!vb[i]) {
            destroy();
            return false;
        }
    }
    return true;
}

#if SHARED_OBJECT_BUFFER
// Added
void VertexBufferDivaGL::create(GLuint in_vb, uint32_t size, uint32_t offset) {
    destroy_shared();

    if (size) {
        num_flip_chain = 1;
        flip_index = 0;
        vb[0] = in_vb;
        vb_size = size;
        vb_offset = offset;

        bufobj_mgr.vb_all_size += size;
        bufobj_mgr.vb_peak_size = max_def(bufobj_mgr.vb_peak_size, bufobj_mgr.vb_all_size);
    }
}
#endif

// 0x140461870
void VertexBufferDivaGL::destroy() {
    for (uint32_t i = 0; i < num_flip_chain; i++) {
        free_vertex_buffer(vb[i]);
        vb[i] = 0;
    }

    num_flip_chain = 0;
    flip_index = 0;
#if SHARED_OBJECT_BUFFER
    vb_size = 0;
    vb_offset = 0;
#endif
}

#if SHARED_OBJECT_BUFFER
// Added
void VertexBufferDivaGL::destroy_shared() {
    for (uint32_t i = 0; i < num_flip_chain; i++)
        vb[i] = 0;

    bufobj_mgr.vb_all_size -= vb_size;

    num_flip_chain = 0;
    flip_index = 0;
    vb_size = 0;
    vb_offset = 0;
}
#endif

uint32_t VertexBufferDivaGL::get_glvb_offset() const {
#if SHARED_OBJECT_BUFFER
    if (vb[0])
        return vb_offset;
#endif
    return 0;
}

uint32_t VertexBufferDivaGL::get_size() const {
#if SHARED_OBJECT_BUFFER
    if (vb[0])
        return vb_size;
    return 0;
#else
    return VertexBuffer::get_size();
#endif
}
