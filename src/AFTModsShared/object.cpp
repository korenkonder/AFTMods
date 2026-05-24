/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "object.hpp"
#include "ogl_buffer_object.hpp"

struct IndexBuffer;
struct VertexBuffer;

bool (FASTCALL* create_mesh_index_buffer)(IndexBuffer* ibhn, const obj_mesh* mesh)
    = (bool (FASTCALL*)(IndexBuffer * ibhn, const obj_mesh * mesh))0x0000000140458040;
bool (FASTCALL* create_mesh_vertex_buffer)(VertexBuffer* vbhn, const obj_mesh* mesh)
    = (bool (FASTCALL*)(VertexBuffer * vbhn, const obj_mesh * mesh))0x0000000140458280;
void (FASTCALL* free_objset)(int32_t objset_index)
    = (void (FASTCALL*)(int32_t objset_index))0x00000001404599B0;
obj_mesh* (FASTCALL* get_mesh)(uint32_t obj_id, int32_t mesh_index)
    = (obj_mesh * (FASTCALL*)(uint32_t obj_id, int32_t mesh_index))0x0000000140459D40;
int32_t(FASTCALL* get_mesh_index)(uint32_t obj_id, const char* mesh_name)
    = (int32_t(FASTCALL*)(uint32_t obj_id, const char* mesh_name))0x0000000140459DE0;
const char* (FASTCALL* get_objdb_object_name)(uint32_t obj_id)
    = (const char* (FASTCALL*)(uint32_t obj_id))0x0000000140459F20;
uint32_t(FASTCALL* get_objdb_object_uid)(const char* name)
    = (uint32_t(FASTCALL*)(const char* name))0x0000000140459F80;
obj* (FASTCALL* get_object_header)(uint32_t obj_id)
    = (obj * (FASTCALL*)(uint32_t obj_id))0x000000014045A140;
obj_skin* (FASTCALL* get_object_skin)(uint32_t obj_id)
    = (obj_skin * (FASTCALL*)(uint32_t obj_id))0x000000014045A3E0;
int32_t(FASTCALL* get_objnum_idx2uid)(int32_t objset_index, int32_t obj_index)
    = (int32_t(FASTCALL*)(int32_t objset_index, int32_t obj_index))0x000000014045A750;
int32_t(FASTCALL* get_objset_idx2uid)(int32_t objset_index)
    = (int32_t(FASTCALL*)(int32_t objset_index))0x000000014045AA10;
int32_t(FASTCALL* get_objset_idx_name)(const char* name)
    = (int32_t(FASTCALL*)(const char* name))0x000000014045AA60;
const char* (FASTCALL* get_objset_name)(int32_t objset_index)
    = (const char* (FASTCALL*)(int32_t objset_index))0x000000014045AC80;
int32_t(FASTCALL* get_objset_num_textures)(int32_t objset_index)
    = (int32_t(FASTCALL*)(int32_t objset_index))0x000000014045ADE0;
texture** (FASTCALL* get_objset_textures)(int32_t objset_index)
    = (texture * *(FASTCALL*)(int32_t objset_index))0x000000014045AE20;
int32_t(FASTCALL* request_objset)(int32_t objset_index)
    = (int32_t(FASTCALL*)(int32_t objset_index))0x000000014045C6A0;
bool (FASTCALL* wait_objset)(int32_t objset_index)
    = (bool(FASTCALL*)(int32_t objset_index))0x000000014045DA60;

obj_material_shader_lighting_type obj_material_shader_attrib::get_lighting_type() const {
    if (!m.is_lgt_diffuse && !m.is_lgt_specular)
        return OBJ_MATERIAL_SHADER_LIGHTING_CONSTANT;
    else if (!m.is_lgt_specular)
        return OBJ_MATERIAL_SHADER_LIGHTING_LAMBERT;
    else
        return OBJ_MATERIAL_SHADER_LIGHTING_PHONG;
}

int32_t obj_texture_attrib::get_blend() const {
    switch (m.blend) {
    case 4:
        return 2;
    case 6:
        return 1;
    case 16:
        return 3;
    default:
        return 0;
    }
}

inline int32_t obj_material_texture_type_get_texcoord_index(
    obj_material_texture_type type, int32_t index) {
    switch (type) {
    case OBJ_MATERIAL_TEXTURE_COLOR:
        if (index < 2)
            return index;
    case OBJ_MATERIAL_TEXTURE_NORMAL:
    case OBJ_MATERIAL_TEXTURE_SPECULAR:
        return 0;
    case OBJ_MATERIAL_TEXTURE_TRANSLUCENCY:
    case OBJ_MATERIAL_TEXTURE_TRANSPARENCY:
        return 1;
    }
    return -1;
}

inline int32_t obj_material_texture_type_get_texture_index(
    obj_material_texture_type type, int32_t base_index) {
    switch (type) {
    case OBJ_MATERIAL_TEXTURE_COLOR:
        if (base_index < 2)
            return base_index;
    case OBJ_MATERIAL_TEXTURE_NORMAL:
        return 2;
    case OBJ_MATERIAL_TEXTURE_SPECULAR:
        return 3;
    case OBJ_MATERIAL_TEXTURE_TRANSLUCENCY:
        return 1;
    case OBJ_MATERIAL_TEXTURE_TRANSPARENCY:
        return 4;
    case OBJ_MATERIAL_TEXTURE_ENVIRONMENT_SPHERE: // AFT
    case OBJ_MATERIAL_TEXTURE_ENVIRONMENT_CUBE:
        return 5;
    }
    return -1;
}

// 0x1405E9250
void skin_calc_matrix_palette(const obj_skin* skin_data, const mat4* node_mtx,
    const mat4* subnode_mtx, mat4* mtx_pal, const mat4* mtx, const mat4& global_mat) {
    if (!skin_data->num_bone)
        return;

    const int32_t* matrix_id = skin_data->matrix_id;
    const mat4* trans_matrix = skin_data->trans_matrix;
    if (mtx)
        for (int32_t i = 0; i < skin_data->num_bone; i++, matrix_id++, trans_matrix++, mtx_pal++) {
            mat4 temp;
            if (*matrix_id & 0x8000)
                mat4_mul(&subnode_mtx[*matrix_id & 0x7FFF], mtx, &temp);
            else
                mat4_mul(&node_mtx[*matrix_id], mtx, &temp);

            mat4_mul(&global_mat, &temp, &temp);
            mat4_mul(&temp, trans_matrix, mtx_pal);
        }
    else
        for (int32_t i = 0; i < skin_data->num_bone; i++, matrix_id++, trans_matrix++, mtx_pal++) {
            mat4 temp;
            if (*matrix_id & 0x8000)
                temp = subnode_mtx[*matrix_id & 0x7FFF];
            else
                temp = node_mtx[*matrix_id];

            mat4_mul(&global_mat, &temp, &temp);
            mat4_mul(&temp, trans_matrix, mtx_pal);
        }
}
