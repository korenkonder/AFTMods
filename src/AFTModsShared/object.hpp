/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../KKdLib/default.hpp"
#include "../KKdLib/mat.hpp"
#include "../KKdLib/vec.hpp"
#include "texture.hpp"
#include "types.hpp"

enum obj_index_format : uint32_t {
    OBJ_INDEX_U8  = 0x00,
    OBJ_INDEX_U16 = 0x01,
    OBJ_INDEX_U32 = 0x02,
};

enum obj_material_aniso_direction : uint32_t {
    OBJ_MATERIAL_ANISO_DIRECTION_NORMAL = 0,
    OBJ_MATERIAL_ANISO_DIRECTION_U      = 1,
    OBJ_MATERIAL_ANISO_DIRECTION_V      = 2,
    OBJ_MATERIAL_ANISO_DIRECTION_RADIAL = 3,
};

enum obj_material_blend_factor : uint32_t {
    OBJ_MATERIAL_BLEND_ZERO              = 0,
    OBJ_MATERIAL_BLEND_ONE               = 1,
    OBJ_MATERIAL_BLEND_SRC_COLOR         = 2,
    OBJ_MATERIAL_BLEND_INVERSE_SRC_COLOR = 3,
    OBJ_MATERIAL_BLEND_SRC_ALPHA         = 4,
    OBJ_MATERIAL_BLEND_INVERSE_SRC_ALPHA = 5,
    OBJ_MATERIAL_BLEND_DST_ALPHA         = 6,
    OBJ_MATERIAL_BLEND_INVERSE_DST_ALPHA = 7,
    OBJ_MATERIAL_BLEND_DST_COLOR         = 8,
    OBJ_MATERIAL_BLEND_INVERSE_DST_COLOR = 9,
    OBJ_MATERIAL_BLEND_ALPHA_SATURATE = 10,
};

enum obj_material_bump_map_type : uint32_t {
    OBJ_MATERIAL_BUMP_MAP_NONE = 0,
    OBJ_MATERIAL_BUMP_MAP_DOT  = 1,
    OBJ_MATERIAL_BUMP_MAP_ENV  = 2,
};

enum obj_material_color_source_type : uint32_t {
    OBJ_MATERIAL_COLOR_SOURCE_MATERIAL_COLOR = 0,
    OBJ_MATERIAL_COLOR_SOURCE_VERTEX_COLOR   = 1,
    OBJ_MATERIAL_COLOR_SOURCE_VERTEX_MORPH   = 2,
};

enum obj_material_shader_lighting_type : uint32_t {
    OBJ_MATERIAL_SHADER_LIGHTING_LAMBERT  = 0x00,
    OBJ_MATERIAL_SHADER_LIGHTING_CONSTANT = 0x01,
    OBJ_MATERIAL_SHADER_LIGHTING_PHONG    = 0x02,
};

enum obj_material_specular_quality : uint32_t {
    OBJ_MATERIAL_SPECULAR_QUALITY_LOW  = 0,
    OBJ_MATERIAL_SPECULAR_QUALITY_HIGH = 1,
};

enum obj_material_texture_type : uint32_t {
    OBJ_MATERIAL_TEXTURE_NONE               = 0x00,
    OBJ_MATERIAL_TEXTURE_COLOR              = 0x01,
    OBJ_MATERIAL_TEXTURE_NORMAL             = 0x02,
    OBJ_MATERIAL_TEXTURE_SPECULAR           = 0x03,
    OBJ_MATERIAL_TEXTURE_HEIGHT             = 0x04,
    OBJ_MATERIAL_TEXTURE_REFLECTION         = 0x05,
    OBJ_MATERIAL_TEXTURE_TRANSLUCENCY       = 0x06,
    OBJ_MATERIAL_TEXTURE_TRANSPARENCY       = 0x07,
    OBJ_MATERIAL_TEXTURE_ENVIRONMENT_SPHERE = 0x08,
    OBJ_MATERIAL_TEXTURE_ENVIRONMENT_CUBE   = 0x09,
};

enum obj_material_texture_coordinate_translation_type : uint32_t {
    OBJ_MATERIAL_TEXTURE_COORDINATE_TRANSLATION_NONE   = 0x00,
    OBJ_MATERIAL_TEXTURE_COORDINATE_TRANSLATION_UV     = 0x01,
    OBJ_MATERIAL_TEXTURE_COORDINATE_TRANSLATION_SPHERE = 0x02,
    OBJ_MATERIAL_TEXTURE_COORDINATE_TRANSLATION_CUBE   = 0x03,
};

enum obj_material_vertex_translation_type : uint32_t {
    OBJ_MATERIAL_VERTEX_TRANSLATION_DEFAULT  = 0,
    OBJ_MATERIAL_VERTEX_TRANSLATION_ENVELOPE = 1,
    OBJ_MATERIAL_VERTEX_TRANSLATION_MORPHING = 2,
};

enum obj_primitive_type : uint32_t {
    OBJ_PRIMITIVE_POINTS         = 0x00,
    OBJ_PRIMITIVE_LINES          = 0x01,
    OBJ_PRIMITIVE_LINE_STRIP     = 0x02,
    OBJ_PRIMITIVE_LINE_LOOP      = 0x03,
    OBJ_PRIMITIVE_TRIANGLES      = 0x04,
    OBJ_PRIMITIVE_TRIANGLE_STRIP = 0x05,
    OBJ_PRIMITIVE_TRIANGLE_FAN   = 0x06,
    OBJ_PRIMITIVE_QUADS          = 0x07,
    OBJ_PRIMITIVE_QUAD_STRIP     = 0x08,
    OBJ_PRIMITIVE_POLYGON        = 0x09,
};

enum obj_vertex_format : uint32_t {
    OBJ_VERTEX_NONE        = 0x0000,
    OBJ_VERTEX_POSITION    = 0x0001,
    OBJ_VERTEX_NORMAL      = 0x0002,
    OBJ_VERTEX_TANGENT     = 0x0004,
    OBJ_VERTEX_BINORMAL    = 0x0008,
    OBJ_VERTEX_TEXCOORD0   = 0x0010,
    OBJ_VERTEX_TEXCOORD1   = 0x0020,
    OBJ_VERTEX_TEXCOORD2   = 0x0040,
    OBJ_VERTEX_TEXCOORD3   = 0x0080,
    OBJ_VERTEX_COLOR0      = 0x0100,
    OBJ_VERTEX_COLOR1      = 0x0200,
    OBJ_VERTEX_BONE_WEIGHT = 0x0400,
    OBJ_VERTEX_BONE_INDEX  = 0x0800,
    OBJ_VERTEX_BONE_DATA   = 0x0C00,
    OBJ_VERTEX_UNKNOWN     = 0x1000,
};

struct AABB {
    vec3 center;
    vec3 r;
};

struct BSphere {
    vec3 center;
    float_t radius;
};

struct obj_shader_compo_member {
    uint32_t color : 1;
    uint32_t color_a : 1;
    uint32_t color_l1 : 1;
    uint32_t color_l1_a : 1;
    uint32_t color_l2 : 1;
    uint32_t color_l2_a : 1;
    uint32_t transparency : 1;
    uint32_t specular : 1;
    uint32_t normal_01 : 1;
    uint32_t normal_02 : 1;
    uint32_t envmap : 1;
    uint32_t color_l3 : 1;
    uint32_t color_l3_a : 1;
    uint32_t translucency : 1;
    uint32_t env_sphere : 1;
    uint32_t env_cube : 1;
    uint32_t dummy : 16;
};

union obj_shader_compo {
    obj_shader_compo_member m;
    uint32_t w;
};

struct obj_material_shader_attrib_member {
    obj_material_vertex_translation_type vtx_trans_type : 2;
    obj_material_color_source_type col_src : 2;
    uint32_t is_lgt_diffuse : 1;
    uint32_t is_lgt_specular : 1;
    uint32_t is_lgt_per_pixel : 1;
    uint32_t is_lgt_double : 1;
    obj_material_bump_map_type bump_map_type : 2;
    uint32_t fresnel_type : 4;
    uint32_t line_light : 4;
    uint32_t recieve_shadow : 1;
    uint32_t cast_shadow : 1;
    obj_material_specular_quality specular_quality : 1;
    obj_material_aniso_direction aniso_direction : 2;
    uint32_t dummy : 9;
};

union obj_material_shader_attrib {
    obj_material_shader_attrib_member m;
    uint32_t w;

    obj_material_shader_lighting_type get_lighting_type() const;
};

struct obj_texture_attrib_member {
    uint32_t repeat_u : 1;
    uint32_t repeat_v : 1;
    uint32_t mirror_u : 1;
    uint32_t mirror_v : 1;
    uint32_t ignore_alpha : 1;
    uint32_t blend : 5;
    uint32_t alpha_blend : 5;
    uint32_t border : 1;
    uint32_t clamp2edge : 1;
    uint32_t filter : 3;
    uint32_t mipmap : 2;
    uint32_t mipmap_bias : 7;
    uint32_t ignore : 1;
    uint32_t aniso : 2;
};

union obj_texture_attrib {
    obj_texture_attrib_member m;
    uint32_t w;

    int32_t get_blend() const;
};

struct obj_texture_shader_attrib_member {
    obj_material_texture_type tex_type : 4;
    int32_t uv_idx : 4;
    obj_material_texture_coordinate_translation_type texcoord_trans : 3;
    uint32_t dummy : 21;
};

union obj_texture_shader_attrib {
    obj_texture_shader_attrib_member m;
    uint32_t w;
};

struct obj_material_texture_data {
    obj_texture_attrib attrib;
    uint32_t tex_index;
    obj_texture_shader_attrib shader_info;
    char ex_shader[8];
    float_t weight;
    mat4 tex_coord_mat;
    uint32_t reserved[8];
};

static_assert(sizeof(obj_material_texture_data) == 0x78, "\"obj_material_texture_data\" struct should have a size of 0x78");

struct obj_material_attrib_member {
    uint32_t alpha_tex : 1;
    uint32_t alpha_mat : 1;
    uint32_t punch_through : 1;
    uint32_t double_sided : 1;
    uint32_t normal_dir_light : 1;
    obj_material_blend_factor src_blend_factor : 4;
    obj_material_blend_factor dst_blend_factor : 4;
    uint32_t blend_operation : 3;
    uint32_t zbias : 4;
    uint32_t no_z_fog : 1;
    uint32_t alpha_prio : 6;
    uint32_t y_fog : 1;
    uint32_t ignore_alpha : 1;
    uint32_t y_fogmap : 1;
    uint32_t use_mat_center : 1;
    uint32_t dummy : 1;
};

union obj_material_attrib {
    obj_material_attrib_member m;
    uint32_t w;
};

struct obj_material_color {
    vec4 diffuse;
    vec4 ambient;
    vec4 specular;
    vec4 emission;
    float_t shininess;
    float_t intensity;
};

static_assert(sizeof(obj_material_color) == 0x48, "\"obj_material_color\" struct should have a size of 0x48");

struct obj_material {
    obj_shader_compo shader_compo;
    union {
        char name[8];
        int32_t index;
    } shader;
    obj_material_shader_attrib shader_info;
    obj_material_texture_data texdata[8];
    obj_material_attrib attrib;
    obj_material_color color;
    vec3 center;
    float_t radius;
    char name[64];
    float_t bump_depth;
    uint32_t reserved[15];
};

static_assert(sizeof(obj_material) == 0x4AC, "\"obj_material\" struct should have a size of 0x4AC");

struct obj_material_data {
    int32_t num_of_textures;
    obj_material material;
};

static_assert(sizeof(obj_material_data) == 0x4B0, "\"obj_material_data\" struct should have a size of 0x4B0");

struct obj_sub_mesh_attrib_member {
    uint32_t recieve_shadow : 1;
    uint32_t cast_shadow : 1;
    uint32_t vertex_alpha : 1;
    uint32_t hide : 1;
    uint32_t poly_offset : 3;
    uint32_t use_restart_index : 1;
    uint32_t no_reflect : 1; // Own stuff
    uint32_t reflect : 1; // Own stuff
    uint32_t reflect_cam_back : 1; // Own stuff
    uint32_t dummy : 21; // 24
};

union obj_sub_mesh_attrib {
    obj_sub_mesh_attrib_member m;
    uint32_t w;
};

struct obj_sub_mesh {
    uint32_t flags;
    BSphere bsphere;
    uint32_t material_index;
    uint8_t uv_index[8];
    int32_t num_bone_index;
    uint16_t* bone_index_array;
    uint32_t bones_per_vertex;
    obj_primitive_type primitive_type;
    obj_index_format index_format;
    int32_t num_index;
    void* index_array;
    obj_sub_mesh_attrib attrib;
    uint32_t reserved[4];
    AABB* aabb;
    uint16_t min_index;
    uint16_t max_index;
    uint32_t index_offset;
};

static_assert(sizeof(obj_sub_mesh) == 0x70, "\"obj_sub_mesh\" struct should have a size of 0x70");

struct obj_mesh_attrib_member {
    uint32_t soft_body : 1;
    uint32_t billboard : 1;
    uint32_t around_obj : 1;
    uint32_t billboard_view : 1;
    uint32_t no_reflect : 1; // Own stuff
    uint32_t reflect : 1; // Own stuff
    uint32_t reflect_cam_back : 1; // Own stuff
    uint32_t disable_aabb_culling : 1; // Own stuff
    uint32_t dummy : 22; // 28
    uint32_t compression : 2; // Own stuff
};

union obj_mesh_attrib {
    obj_mesh_attrib_member m;
    uint32_t w;
};

struct obj_mesh_vertex_array {
    vec3* position;
    vec3* normal;
    vec4* tangent;
    vec3* binormal;
    vec2* texcoord0;
    vec2* texcoord1;
    vec2* texcoord2;
    vec2* texcoord3;
    vec4* color0;
    vec4* color1;
    vec4* bone_weight;
    vec4* bone_index;
    vec4* unknown;
    void* field_68;
    void* field_70;
    void* field_78;
    void* field_80;
    void* field_88;
    void* field_90;
    void* field_98;
};

static_assert(sizeof(obj_mesh_vertex_array) == 0xA0, "\"obj_mesh_vertex_array\" struct should have a size of 0xA0");

struct obj_mesh {
    uint32_t flags;
    BSphere bsphere;
    int32_t num_submesh;
    obj_sub_mesh* submesh_array;
    obj_vertex_format vertex_format;
    uint32_t size_vertex;
    int32_t num_vertex;
    union {
        obj_mesh_vertex_array vertex_array;
        void* vertex_array_ptr[20];
    };
    obj_mesh_attrib attrib;
    uint32_t reserved[7];
    char name[0x40];
};

static_assert(sizeof(obj_mesh) == 0x130, "\"obj_mesh\" struct should have a size of 0x130");

struct obj {
    uint32_t version;
    uint32_t flags;
    BSphere bsphere;
    int32_t num_mesh;
    obj_mesh* mesh_array;
    int32_t num_material;
    obj_material_data* material_array;
    uint32_t reserved[10];
};

static_assert(sizeof(obj) == 0x60, "\"obj\" struct should have a size of 0x60");

struct obj_skin_ex_data {
    int32_t nb_root;
    int32_t nb_jointX;
    const char** osage_root;
    struct ObjOsageJoint* osage_joint;
    const char** root_name;
    struct ObjExNode* ex_node_table;
    uint32_t nb_node_name;
    const char** ex_node_name;
    struct ObjOsageConstraintInfo* osage_constraint_tbl;
    int32_t nb_cloth;
    uint32_t dummy[7];
};

static_assert(sizeof(obj_skin_ex_data) == 0x60, "\"obj_skin_ex_data\" struct should have a size of 0x60");

struct obj_skin {
    int32_t* matrix_id;
    mat4* trans_matrix;
    const char** bone_name;
    obj_skin_ex_data* osage_header;
    int32_t num_bone;
    uint32_t dummy[4];
};

static_assert(sizeof(obj_skin) == 0x38, "\"obj_skin\" struct should have a size of 0x38");

struct obj_set {
    uint32_t version;
    int32_t obj_num;
    uint32_t last_obj_id;
    obj** obj_data;
    obj_skin** obj_skin_data;
    const char** obj_name_data;
    uint32_t* obj_id_data;
    uint32_t* tex_id_data;
    int32_t tex_num;
    uint32_t reserved[2];
};

static_assert(sizeof(obj_set) == 0x48, "\"obj_set\" struct should have a size of 0x48");

struct object_info {
    uint16_t id;
    uint16_t set_id;

    inline object_info() {
        this->id = (uint16_t)-1;
        this->set_id = (uint16_t)-1;
    }

    inline object_info(uint16_t id, uint16_t set_id) {
        this->id = id;
        this->set_id = set_id;
    }

    inline object_info(uint32_t data) {
        this->id = (uint16_t)data;
        this->set_id = (uint16_t)(data >> 16);
    }

    inline bool is_null() const {
        return id == (uint16_t)-1 && set_id == (uint16_t)-1;
    }

    inline bool not_null() const {
        return id != (uint16_t)-1 || set_id != (uint16_t)-1;
    }

    inline operator uint32_t() {
        return ((uint32_t)set_id << 16) | id;
    }
};

static_assert(sizeof(object_info) == 0x04, "\"object_info\" struct should have a size of 0x04");

inline bool operator >(const object_info& left, const object_info& right) {
    return *(uint32_t*)&left > *(uint32_t*)&right;
}

inline bool operator <(const object_info& left, const object_info& right) {
    return *(uint32_t*)&left < *(uint32_t*)&right;
}

inline bool operator >=(const object_info& left, const object_info& right) {
    return *(uint32_t*)&left >= *(uint32_t*)&right;
}

inline bool operator <=(const object_info& left, const object_info& right) {
    return *(uint32_t*)&left <= *(uint32_t*)&right;
}

inline bool operator ==(const object_info& left, const object_info& right) {
    return *(uint32_t*)&left == *(uint32_t*)&right;
}

inline bool operator !=(const object_info& left, const object_info& right) {
    return *(uint32_t*)&left != *(uint32_t*)&right;
}

extern bool (FASTCALL* create_mesh_index_buffer)(struct IndexBuffer* ibhn, const obj_mesh* mesh);
extern bool (FASTCALL* create_mesh_vertex_buffer)(struct VertexBuffer* vbhn, const obj_mesh* mesh);
extern void (FASTCALL* free_objset)(int32_t objset_index);
extern obj_mesh* (FASTCALL* get_mesh)(uint32_t obj_id, int32_t mesh_index);
extern int32_t(FASTCALL* get_mesh_index)(uint32_t obj_id, const char* mesh_name);
extern const char* (FASTCALL* get_objdb_object_name)(uint32_t obj_id);
extern uint32_t(FASTCALL* get_objdb_object_uid)(const char* name);
extern obj* (FASTCALL* get_object_header)(uint32_t obj_id);
extern obj_skin* (FASTCALL* get_object_skin)(uint32_t obj_id);
extern int32_t(FASTCALL* get_objnum_idx2uid)(int32_t objset_index, int32_t obj_index);
extern int32_t(FASTCALL* get_objset_idx2uid)(int32_t objset_index);
extern int32_t(FASTCALL* get_objset_idx_name)(const char* name);
extern const char* (FASTCALL* get_objset_name)(int32_t objset_index);
extern int32_t(FASTCALL* get_objset_num_textures)(int32_t objset_index);
extern texture** (FASTCALL* get_objset_textures)(int32_t objset_index);
extern int32_t(FASTCALL* request_objset)(int32_t objset_index);
extern bool (FASTCALL* wait_objset)(int32_t objset_index);

extern int32_t obj_material_texture_type_get_texcoord_index(
    obj_material_texture_type type, int32_t index);
extern int32_t obj_material_texture_type_get_texture_index(
    obj_material_texture_type type, int32_t base_index);

extern void skin_calc_matrix_palette(const obj_skin* skin_data, const mat4* node_mtx,
    const mat4* subnode_mtx, mat4* mtx_pal, const mat4* mtx, const mat4& global_mat);
