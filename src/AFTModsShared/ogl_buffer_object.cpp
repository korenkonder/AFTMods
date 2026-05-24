/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "ogl_buffer_object.hpp"
#include "object.hpp"

BufObjMgr& bufobj_mgr = *(BufObjMgr*)0x00000001411A34D0;

AFTGLuint(FASTCALL* create_index_buffer)(uint32_t size, const void* buf)
    = (AFTGLuint(FASTCALL*)(uint32_t size, const void* buf))0x00000001404616F0;
AFTGLuint (FASTCALL* create_vertex_buffer)(uint32_t size, const void* buf)
    = (AFTGLuint(FASTCALL*)(uint32_t size, const void* buf))0x00000001404617B0;
void (FASTCALL* free_index_buffer)(AFTGLuint ib)
    = (void (FASTCALL*)(AFTGLuint ib))0x0000000140461900;
void (FASTCALL* free_vertex_buffer)(AFTGLuint vb)
    = (void (FASTCALL*)(AFTGLuint vb))0x0000000140461990;

// 0x140461650
int32_t VertexBuffer::create(uint32_t size, const void* buf, uint32_t num_flip) {
    if (!size || num_flip > VertexBuffer::NUM_FLIP_MAX)
        return -1;

    num_flip_chain = num_flip;
    flip_index = 0;

    for (uint32_t i = 0; i < num_flip; i++) {
        vb[i] = create_vertex_buffer(size, buf);
        if (!vb[i]) {
            destroy();
            return -1;
        }
    }
    return 0;
}

// 0x140461870
void VertexBuffer::destroy() {
    for (uint32_t i = 0; i < num_flip_chain; i++) {
        free_vertex_buffer(vb[i]);
        vb[i] = 0;
    }

    num_flip_chain = 0;
    flip_index = 0;
}

// 0x1404618E0
void VertexBuffer::flip() {
    if (++flip_index >= num_flip_chain)
        flip_index = 0;
}

// 0x140461A20
AFTGLuint VertexBuffer::get_glvb() const {
    if (flip_index < num_flip_chain)
        return vb[flip_index];
    return 0;
}

// Missing
AFTGLuint VertexBuffer::get_glvb_at(uint32_t index) const {
    if (index < num_flip_chain)
        return vb[index];
    return 0;
}

// 0x140461A40
uint32_t VertexBuffer::get_num_flip_chain(uint32_t index) const {
    return num_flip_chain;
}

// 0x140461A50
uint32_t VertexBuffer::get_size() const {
    uint32_t(FASTCALL * VertexBuffer__get_size)(const VertexBuffer * This)
        = (uint32_t(FASTCALL*)(const VertexBuffer * This))0x0000000140461A50;
    return VertexBuffer__get_size(this);
}

// 0x140461AE0
AFTGLenum VertexBuffer::get_target() const {
    return target;
}

// 0x140469640
uint32_t get_vertex_size(uint32_t format, uint32_t compression) {
    uint32_t size = 0;
    switch (compression) {
    case 0:
    default:
        if (format & OBJ_VERTEX_POSITION)
            size += 12;
        if (format & OBJ_VERTEX_NORMAL)
            size += 12;
        if (format & OBJ_VERTEX_TANGENT)
            size += 16;
        if (format & OBJ_VERTEX_BINORMAL)
            size += 12;
        if (format & OBJ_VERTEX_TEXCOORD0)
            size += 8;
        if (format & OBJ_VERTEX_TEXCOORD1)
            size += 8;
        if (format & OBJ_VERTEX_TEXCOORD2)
            size += 8;
        if (format & OBJ_VERTEX_TEXCOORD3)
            size += 8;
        if (format & OBJ_VERTEX_COLOR0)
            size += 16;
        if (format & OBJ_VERTEX_COLOR1)
            size += 16;
        if ((format & OBJ_VERTEX_BONE_DATA) == OBJ_VERTEX_BONE_DATA)
            size += 24;
        if (format & OBJ_VERTEX_UNKNOWN)
            size += 16;
        break;
    case 1: // Added
        if (format & OBJ_VERTEX_POSITION)
            size += 12;
        if (format & OBJ_VERTEX_NORMAL)
            size += 8;
        if (format & OBJ_VERTEX_TANGENT)
            size += 8;
        if (format & OBJ_VERTEX_TEXCOORD0)
            size += 4;
        if (format & OBJ_VERTEX_TEXCOORD1)
            size += 4;
        if (format & OBJ_VERTEX_TEXCOORD2)
            size += 4;
        if (format & OBJ_VERTEX_TEXCOORD3)
            size += 4;
        if (format & OBJ_VERTEX_COLOR0)
            size += 8;
        if ((format & OBJ_VERTEX_BONE_DATA) == OBJ_VERTEX_BONE_DATA)
            size += 16;
        break;
    case 2: // Added
        if (format & OBJ_VERTEX_POSITION)
            size += 12;
        if (format & OBJ_VERTEX_NORMAL)
            size += 4;
        if (format & OBJ_VERTEX_TANGENT)
            size += 4;
        if (format & OBJ_VERTEX_TEXCOORD0)
            size += 4;
        if (format & OBJ_VERTEX_TEXCOORD1)
            size += 4;
        if (format & OBJ_VERTEX_TEXCOORD2)
            size += 4;
        if (format & OBJ_VERTEX_TEXCOORD3)
            size += 4;
        if (format & OBJ_VERTEX_COLOR0)
            size += 8;
        if ((format & OBJ_VERTEX_BONE_DATA) == OBJ_VERTEX_BONE_DATA)
            size += 8;
        break;
    }
    return size;
}
