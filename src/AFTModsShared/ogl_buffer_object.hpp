/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../KKdLib/default.hpp"
#include "types.hpp"

// Added
struct IndexBuffer {
    AFTGLuint ib;

    inline IndexBuffer() : ib() {

    }

    AFTGLuint get_glib() const;
};

static_assert(sizeof(IndexBuffer) == 0x04, "\"IndexBuffer\" struct should have a size of 0x04");

struct VertexBuffer {
    static const uint32_t NUM_FLIP_MAX = 3;

    uint32_t num_flip_chain;
    AFTGLuint vb[NUM_FLIP_MAX];
    uint32_t flip_index;
    AFTGLenum target;

    inline VertexBuffer() : num_flip_chain(), vb(), flip_index(), target(0x8892) { // GL_ARRAY_BUFFER

    }

    inline ~VertexBuffer() {

    }

    int32_t create(uint32_t size, const void* buf, uint32_t num_flip);
    void destroy();
    void flip();
    AFTGLuint get_glvb() const;
    AFTGLuint get_glvb_at(uint32_t index) const;
    uint32_t get_num_flip_chain(uint32_t index) const;
    uint32_t get_size() const;
    AFTGLenum get_target() const;
};

static_assert(sizeof(VertexBuffer) == 0x18, "\"VertexBuffer\" struct should have a size of 0x18");

struct BufObjMgr {
    int32_t vb_peak_size;
    int32_t vb_all_size;
    int32_t ib_peak_size;
    int32_t ib_all_size;
};

static_assert(sizeof(BufObjMgr) == 0x10, "\"BufObjMgr\" struct should have a size of 0x10");

extern BufObjMgr& bufobj_mgr;

extern AFTGLuint(FASTCALL* create_index_buffer)(uint32_t size, const void* buf);
extern AFTGLuint(FASTCALL* create_vertex_buffer)(uint32_t size, const void* buf);
extern void (FASTCALL* free_index_buffer)(AFTGLuint ib);
extern void (FASTCALL* free_vertex_buffer)(AFTGLuint vb);

extern uint32_t get_vertex_size(uint32_t vertex_format, uint32_t compression = 0);

// Inlined
inline AFTGLuint IndexBuffer::get_glib() const {
    return ib;
}
