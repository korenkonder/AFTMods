/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../KKdLib/default.hpp"
#include "../KKdLib/mat.hpp"
#include "../KKdLib/vec.hpp"
#include "../AFTModsShared/object.hpp"
#include "../AFTModsShared/ogl_buffer_object.hpp"
#include "../AFTModsShared/types.hpp"
#include "GL/buffer.hpp"
#include "ogl_buffer_object.hpp"
#include "texture.hpp"

struct ObjIB {
    int32_t num_ib;
    IndexBufferDivaGL* ibhn_array;
};

static_assert(sizeof(ObjIB) == 0x10, "\"ObjIB\" struct should have a size of 0x10");

struct ObjVB {
    int32_t num_vb;
    VertexBufferDivaGL* vbhn_array;
};

static_assert(sizeof(ObjVB) == 0x10, "\"ObjVB\" struct should have a size of 0x10");

extern IndexBuffer* (FASTCALL* get_object_index_buffer)(uint32_t obj_info, int32_t is_tangent);
extern VertexBuffer* (FASTCALL* get_object_vertex_buffer)(uint32_t obj_info, int32_t is_tangent);
extern GLuint(FASTCALL* get_objset_gen_textures_id)(int32_t objset_index, int32_t uid);
extern prj::vector<GLuint>* (FASTCALL* get_objset_gen_textures_vec)(int32_t objset_index);

extern void object_patch();
