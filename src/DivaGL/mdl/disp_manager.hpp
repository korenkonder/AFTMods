/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../../KKdLib/default.hpp"
#include "../../KKdLib/mat.hpp"
#include "../../KKdLib/vec.hpp"
#include "../../AFTModsShared/mdl/disp_manager.hpp"
#include "../../AFTModsShared/color.hpp"
#include "../../AFTModsShared/shadow.hpp"
#include "../GL/array_buffer.hpp"
#include "../GL/element_array_buffer.hpp"
#include "../object.hpp"

#define MATERIAL_LIST_COUNT 24
#define TEXTURE_PATTERN_COUNT 24
#define TEXTURE_TRANSFORM_COUNT 24

struct cam_data;
struct render_data_context;

namespace mdl {
    enum EtcObjType {
        ETC_OBJ_TEAPOT = 0,
        ETC_OBJ_GRID,
        ETC_OBJ_CUBE,
        ETC_OBJ_SPHERE,
        ETC_OBJ_PLANE,
        ETC_OBJ_CONE,
        ETC_OBJ_LINE,
        ETC_OBJ_CROSS,
        ETC_OBJ_CAPSULE,  // Added
        ETC_OBJ_CYLINDER, // Added
        ETC_OBJ_MAX,
    };

    enum ObjKind {
        OBJ_KIND_NORMAL = 0,
        OBJ_KIND_ETC,
        OBJ_KIND_USER,
        OBJ_KIND_TRANSLUCENT,
        OBJ_KIND_MAX,
    };

    enum ObjType {
        OBJ_TYPE_OPAQUE = 0,
        OBJ_TYPE_TRANSLUCENT,
        OBJ_TYPE_TRANSLUCENT_SORT_BY_RADIUS,
        OBJ_TYPE_TRANSPARENT,
        OBJ_TYPE_SHADOW_CHARA,
        OBJ_TYPE_SHADOW_STAGE,
        OBJ_TYPE_TYPE_6,
        OBJ_TYPE_TYPE_7,
        OBJ_TYPE_SHADOW_OBJECT_CHARA,
        OBJ_TYPE_SHADOW_OBJECT_STAGE,
        OBJ_TYPE_REFLECT_CHARA_OPAQUE,
        OBJ_TYPE_REFLECT_CHARA_TRANSLUCENT,
        OBJ_TYPE_REFLECT_CHARA_TRANSPARENT,
        OBJ_TYPE_REFLECT_OPAQUE,
        OBJ_TYPE_REFLECT_TRANSLUCENT,
        OBJ_TYPE_REFLECT_TRANSPARENT,
        OBJ_TYPE_REFRACT_OPAQUE,
        OBJ_TYPE_REFRACT_TRANSLUCENT,
        OBJ_TYPE_REFRACT_TRANSPARENT,
        OBJ_TYPE_SSS,
        OBJ_TYPE_OPAQUE_ALPHA_ORDER_POST_GLITTER,
        OBJ_TYPE_TRANSPARENT_ALPHA_ORDER_POST_GLITTER,
        OBJ_TYPE_TRANSLUCENT_ALPHA_ORDER_POST_GLITTER,
        OBJ_TYPE_OPAQUE_ALPHA_ORDER_POST_TRANSLUCENT,
        OBJ_TYPE_TRANSPARENT_ALPHA_ORDER_POST_TRANSLUCENT,
        OBJ_TYPE_TRANSLUCENT_ALPHA_ORDER_POST_TRANSLUCENT,
        OBJ_TYPE_OPAQUE_ALPHA_ORDER_POST_OPAQUE,
        OBJ_TYPE_TRANSPARENT_ALPHA_ORDER_POST_OPAQUE,
        OBJ_TYPE_TRANSLUCENT_ALPHA_ORDER_POST_OPAQUE,
        OBJ_TYPE_USER,
        OBJ_TYPE_MAX,
    };

    enum ObjTypeScreen {
        OBJ_TYPE_SCREEN_OPAQUE = 0,
        OBJ_TYPE_SCREEN_TRANSLUCENT,
        OBJ_TYPE_SCREEN_TRANSPARENT,
        OBJ_TYPE_SCREEN_OPAQUE_ALPHA_ORDER_POST_TRANSLUCENT,
        OBJ_TYPE_SCREEN_TRANSPARENT_ALPHA_ORDER_POST_TRANSLUCENT,
        OBJ_TYPE_SCREEN_TRANSLUCENT_ALPHA_ORDER_POST_TRANSLUCENT,
        OBJ_TYPE_SCREEN_MAX
    };

    enum ObjTypeReflect {
        OBJ_TYPE_REFLECT_TRANSLUCENT_SORT_BY_RADIUS = 0,
        OBJ_TYPE_REFLECT_MAX,
    };
}

struct material_list_struct {
    uint64_t hash;
    vec4 blend_color;
    vec4u8 has_blend_color;
    vec4 emission;
    vec4u8 has_emission;

    material_list_struct();
    material_list_struct(uint64_t hash, vec4& blend_color,
        vec4u8& has_blend_color, vec4& emission, vec4u8& has_emission);
};

struct cam_data;
struct render_data_context;

namespace mdl {
    struct ObjSubMeshArgs;

    typedef void(FASTCALL* draw_func)(const ObjSubMeshArgs* args);

    struct ObjSubMeshArgs {
        const obj_sub_mesh* sub_mesh;
        const obj_mesh* mesh;
        const obj_material_data* material;
        const prj::vector<GLuint>* textures;
        int32_t mat_count;
        const mat4* mats;
        GLuint vertex_buffer;
        size_t vertex_buffer_offset;
        GLuint index_buffer;
        bool set_blend_color;
        bool chara_color;
        vec4 blend_color;
        vec4 emission;
        bool self_shadow;
        shadow_type_enum shadow;
        GLuint morph_vertex_buffer;
        size_t morph_vertex_buffer_offset;
        float_t morph_weight;
        int32_t texture_pattern_count;
        texture_pattern_struct texture_pattern_array[TEXTURE_PATTERN_COUNT];
        vec4 texture_color_coefficients;
        vec4 texture_color_offset;
        vec4 texture_specular_coefficients;
        vec4 texture_specular_offset;
        int32_t texture_transform_count;
        texture_transform_struct texture_transform_array[TEXTURE_TRANSFORM_COUNT];
        int32_t field_7C4;
        int32_t field_7C8;
        int32_t instances_count;
        const mat4* instances_mat;
        draw_func func;
        const ObjSubMeshArgs* func_data;

        ObjSubMeshArgs();
    };

    struct EtcObjTeapot {
        float_t size;

        EtcObjTeapot();
    };

    struct EtcObjGrid {
        int32_t w;
        int32_t h;
        int32_t ws;
        int32_t hs;

        EtcObjGrid();
    };

    struct EtcObjCube {
        vec3 size;
        bool wire;

        EtcObjCube();
    };

    struct EtcObjSphere {
        float_t radius;
        int32_t slices;
        int32_t stacks;
        bool wire;

        EtcObjSphere();
    };

    struct EtcObjPlane {
        int32_t w;
        int32_t h;

        EtcObjPlane();
    };

    struct EtcObjCone {
        float_t base;
        float_t height;
        int32_t slices;
        int32_t stacks;
        bool wire;

        EtcObjCone();
    };

    struct EtcObjLine {
        vec3 pos[2];

        EtcObjLine();
    };

    struct EtcObjCross {
        float_t size;

        EtcObjCross();
    };

    struct EtcObjCapsule { // Added
        float_t radius;
        int32_t slices;
        int32_t stacks;
        bool wire;
        vec3 pos[2];

        EtcObjCapsule();
    };

    struct EtcObjCylinder { // Added
        float_t base;
        float_t height;
        int32_t slices;
        int32_t stacks;
        bool wire;

        EtcObjCylinder();
    };

    struct EtcObj {
        union Data {
            EtcObjTeapot teapot;
            EtcObjGrid grid;
            EtcObjCube cube;
            EtcObjSphere sphere;
            EtcObjPlane plane;
            EtcObjCone cone;
            EtcObjLine line;
            EtcObjCross cross;
            EtcObjCapsule capsule; // Added
            EtcObjCylinder cylinder; // Added

            Data();
            Data(const EtcObjTeapot& other);
            Data(const EtcObjGrid& other);
            Data(const EtcObjCube& other);
            Data(const EtcObjSphere& other);
            Data(const EtcObjPlane& other);
            Data(const EtcObjCone& other);
            Data(const EtcObjLine& other);
            Data(const EtcObjCross& other);
            Data(const EtcObjCapsule& other); // Added
            Data(const EtcObjCylinder& other); // Added
        };

        EtcObjType type;
        color4u8_bgra color;
        bool constant;
        Data data;

        EtcObj(EtcObjType type);
        ~EtcObj();
    };

    struct EtcObjData {
        color4u8_bgra color;
        bool constant;
        int32_t index;
        int32_t count;
    };

    typedef void(*UserArgsFunc)(render_data_context& rend_data_ctx, void* data, const cam_data& cam, mat4* mat);

    struct UserArgs {
        UserArgsFunc func;
        void* data;

        UserArgs();
    };

    struct ObjTranslucentArgs {
        int32_t count;
        ObjSubMeshArgs* sub_mesh[40];

        ObjTranslucentArgs();
    };

    struct ObjData {
        union Args {
            ObjSubMeshArgs sub_mesh;
            EtcObjData etc;
            UserArgs user;
            ObjTranslucentArgs translucent;

            Args();
            ~Args();
        };

        ObjKind kind;
        mat4 mat;
        float_t view_z;
        float_t radius;
        Args args;

        ObjData();
        ~ObjData();

        void init_etc(const mat4& mat, int32_t index, int32_t count, const mdl::EtcObj& etc);
        void init_sub_mesh(const mat4& mat, float_t radius, const obj_sub_mesh* sub_mesh,
            const obj_mesh* mesh, const obj_material_data* material, const prj::vector<GLuint>* textures,
            int32_t mat_count, const mat4* mats, GLuint vertex_buffer, size_t vertex_buffer_offset,
            GLuint index_buffer, const vec4& blend_color, const vec4& emission, GLuint morph_vertex_buffer,
            size_t morph_vertex_buffer_offset,
            int32_t instances_count, const mat4* instances_mat, draw_func func, const ObjSubMeshArgs* func_data);
        void init_translucent(const mat4& mat, const ObjTranslucentArgs& translucent);
        void init_user(const mat4& mat, UserArgsFunc func, void* data);
    };

    typedef prj::list<mdl::ObjData*> ObjList;

    struct CullingCheck {
        struct Info {
            int32_t objects;
            int32_t meshes;
            int32_t sub_meshes;
            int pad;
        };

        Info passed;
        Info culled;
        Info passed_prev;
        Info culled_prev;
    };

    static_assert(sizeof(mdl::CullingCheck) == 0x40, "\"mdl::CullingCheck\" struct should have a size of 0x40");

    struct etc_obj_draw_param_attrib_member {
        uint32_t primitive : 4;
    };

    union etc_obj_draw_param_attrib {
        etc_obj_draw_param_attrib_member m;
        uint32_t w;
    };

    struct etc_obj_draw_param {
        union {
            GLint first;
            struct {
                GLuint start;
                GLuint end;
            };
        };
        GLsizei count;
        GLintptr offset;
        etc_obj_draw_param_attrib attrib;
    };

    struct etc_obj_vertex_data {
        vec3 position;
        vec3 normal;

        inline etc_obj_vertex_data(const vec3 position = vec3(0.0f), const vec3 normal = vec3(0.0f, 1.0f, 0.0f))
            : position(position), normal(normal) {

        }
    };

    struct EtcObjManager {
        std::vector<etc_obj_draw_param> draw_param_buffer;
        std::vector<uint8_t> vertex_buffer;
        std::vector<uint32_t> index_buffer;
        prj::vector_pair<std::pair<EtcObjType, int32_t>, EtcObj::Data> etc_obj_buffer;

        GLuint vao;
        GL::ArrayBuffer vbo;
        size_t vbo_vertex_count;
        GL::ElementArrayBuffer ebo;
        size_t ebo_index_count;

        EtcObjManager();
        ~EtcObjManager();

        bool add_capsule(int32_t& index, int32_t& count, const EtcObjCapsule& capsule); // Added
        bool add_cone(int32_t& index, int32_t& count, const EtcObjCone& cone);
        bool add_cross(int32_t& index, int32_t& count, const EtcObjCross& cross);
        bool add_cube(int32_t& index, int32_t& count, const EtcObjCube& cube);
        bool add_cylinder(int32_t& index, int32_t& count, const EtcObjCylinder& cylinder); // Added
        template <typename T>
        size_t add_data(T*& data, size_t num_vertex);
        template <typename T>
        bool add_data(int32_t& index, T*& data, size_t num_vertex, GLenum primitive);
        bool add_grid(int32_t& index, int32_t& count, const EtcObjGrid& grid);
        bool add_line(int32_t& index, int32_t& count, const EtcObjLine& line);
        bool add_obj(int32_t& index, int32_t& count, const EtcObj& etc);
        bool add_plane(int32_t& index, int32_t& count, const EtcObjPlane& plane);
        bool add_sphere(int32_t& index, int32_t& count, const EtcObjSphere& sphere);
        void clear();
        void pre_draw();
        void post_draw();
        void update();
    };

    struct DispManager {
        struct vertex_array {
            GLuint vertex_buffer;
            size_t vertex_buffer_offset;
            GLuint morph_vertex_buffer;
            size_t morph_vertex_buffer_offset;
            GLuint index_buffer;
            GLuint vertex_array;
            obj_vertex_format vertex_format;
            GLsizei size_vertex;
            uint32_t compression;
            int32_t texcoord_array[2];
        };

        mdl::ObjFlags obj_flags;
        shadow_type_enum shadow_type;
        int32_t field_8;
        int32_t field_C;
        mdl::ObjList obj[mdl::OBJ_TYPE_MAX];
        mdl::CullingCheck culling;
        int32_t put_index;
        bool show_alpha_center;
        bool show_mat_center;
        bool object_culling;
        bool object_sort;
        bool chara_color;
        int32_t buff_offset;
        int32_t buff_max;
        int32_t buff_size;
        size_t buff;
        morph_struct morph;
        int32_t texture_pattern_count;
        texture_pattern_struct texture_pattern_array[TEXTURE_PATTERN_COUNT];
        vec4 texture_color_coefficients;
        vec4 texture_color_offset;
        vec4 texture_specular_coefficients;
        vec4 texture_specular_offset;
        float_t wet_param;
        int32_t texture_transform_count;
        texture_transform_struct texture_transform_array[TEXTURE_TRANSFORM_COUNT];
        bool(FASTCALL* culling_func)(const obj_bounding_sphere*);

        void add_vertex_array(const obj_mesh* mesh, const obj_sub_mesh* sub_mesh, const obj_material_data* material,
            GLuint vertex_buffer, size_t vertex_buffer_offset, GLuint index_buffer,
            GLuint morph_vertex_buffer, size_t morph_vertex_buffer_offset);
        void* alloc_data(int32_t size);
        ObjData* alloc_obj_data(ObjKind kind);
        mat4* alloc_mat4_array(int32_t count);
        void buffer_reset();
        void calc_obj_radius(const cam_data& cam, ObjType type);
        void calc_obj_radius(const cam_data& cam, ObjTypeScreen type);
        void calc_obj_radius(const cam_data& cam, ObjTypeReflect type);
        void draw(render_data_context& rend_data_ctx, ObjType type, const cam_data& cam,
            int32_t depth_mask = 0, bool reflect_texture_mask = true, int32_t alpha = -1);
        void draw(render_data_context& rend_data_ctx, ObjTypeScreen type, const cam_data& cam,
            int32_t depth_mask = 0, bool reflect_texture_mask = true, int32_t alpha = -1);
        void draw(render_data_context& rend_data_ctx, ObjTypeReflect type, const cam_data& cam,
            int32_t depth_mask = 0, bool reflect_texture_mask = true);
        void entry_list(ObjType type, ObjData* data);
        void entry_list(ObjTypeScreen type, ObjData* data);
        void entry_list(ObjTypeReflect type, ObjData* data);
        bool entry_obj(const ::obj* obj, const mat4& mat, obj_mesh_vertex_buffer_divagl* obj_vert_buf,
            obj_mesh_index_buffer* obj_index_buf, const prj::vector<GLuint>* textures, const vec4* blend_color,
            const mat4* bone_mat, const ::obj* obj_morph, obj_mesh_vertex_buffer_divagl* obj_morph_vert_buf,
            int32_t instances_count, const mat4* instances_mat,
            draw_func func, const ObjSubMeshArgs* func_data, bool enable_bone_mat);
        bool entry_obj_screen(const ::obj* obj, const mat4& mat, obj_mesh_vertex_buffer_divagl* obj_vert_buf,
            obj_mesh_index_buffer* obj_index_buf, const prj::vector<GLuint>* textures, const vec4* blend_color);
        void entry_obj_by_obj(const mat4& mat,
            const ::obj* obj, prj::vector<GLuint>* textures, obj_mesh_vertex_buffer* obj_vert_buf,
            obj_mesh_index_buffer* obj_index_buf, const mat4* bone_mat, float_t alpha);
        void entry_obj_by_obj(const mat4& mat,
            const ::obj* obj, prj::vector<GLuint>* textures, obj_mesh_vertex_buffer_divagl* obj_vert_buf,
            obj_mesh_index_buffer* obj_index_buf, const mat4* bone_mat, float_t alpha);
        bool entry_obj_by_object_info(const mat4& mat, object_info obj_info);
        bool entry_obj_by_object_info(const mat4& mat, object_info obj_info, const mat4* bone_mat);
        bool entry_obj_by_object_info(const mat4& mat, object_info obj_info,
            const vec4* blend_color, const mat4* bone_mat, int32_t instances_count, const mat4* instances_mat,
            void(*func)(const ObjSubMeshArgs*), const ObjSubMeshArgs* func_data, bool enable_bone_mat);
        bool entry_obj_by_object_info_screen(const mat4& mat, object_info obj_info, const vec4* blend_color);
        bool entry_obj_by_object_info(const mat4& mat, object_info obj_info, float_t alpha, const mat4* bone_mat = 0);
        bool entry_obj_by_object_info(const mat4& mat, object_info obj_info,
            float_t r, float_t g, float_t b, float_t a, const mat4* bone_mat = 0);
        bool entry_obj_by_object_info(const mat4& mat, object_info obj_info,
            const vec4* blend_color, const mat4* bone_mat = 0);
        void entry_obj_by_object_info_object_skin(object_info obj_info,
            prj::vector<texture_pattern_struct>* texture_pattern, texture_data_struct* texture_data, float_t alpha,
            const mat4* matrices, const mat4* ex_data_matrices, const mat4* mat, const mat4& global_mat);
        void entry_obj_etc(const mat4& mat, const EtcObj& etc);
        void entry_obj_user(const mat4& mat, UserArgsFunc func, void* data, ObjType type);
        GLuint get_vertex_array(const ObjSubMeshArgs* args);
        bool get_chara_color();
        ObjList& get_obj_list(ObjType type);
        ObjList& get_obj_list(ObjTypeScreen type);
        ObjList& get_obj_list(ObjTypeReflect type);
        void get_morph(object_info& object, float_t& weight);
        void get_obj_center(mat4& mat, const ObjSubMeshArgs* args, vec3& center);
        int32_t get_obj_count(ObjType type);
        int32_t get_obj_count(ObjTypeScreen type);
        int32_t get_obj_count(ObjTypeReflect type);
        ObjFlags get_obj_flags();
        shadow_type_enum get_shadow_type();
        void get_texture_color_coeff(vec4& value);
        void get_texture_color_offset(vec4& value);
        void get_texture_pattern(int32_t& count, texture_pattern_struct*& value);
        void get_texture_specular_coeff(vec4& value);
        void get_texture_specular_offset(vec4& value);
        void get_texture_transform(int32_t& count, texture_transform_struct*& value);
        float_t get_wet_param();
        void obj_sort(render_data_context& rend_data_ctx,
            ObjType type, int32_t compare_func, const cam_data& cam, bool a3 = false);
        void obj_sort(render_data_context& rend_data_ctx,
            ObjTypeScreen type, int32_t compare_func, const cam_data& cam);
        void obj_sort(render_data_context& rend_data_ctx,
            ObjTypeReflect type, int32_t compare_func, const cam_data& cam);
        void refresh();
        void remove_index_buffer(GLuint buffer);
        void remove_vertex_buffer(GLuint buffer);
        void set_chara_color(bool value = false);
        void set_culling_func(bool(FASTCALL* func)(const obj_bounding_sphere*) = 0);
        void set_obj_flags(ObjFlags flags = (ObjFlags)0);
        void set_material_list(int32_t count = 0, const material_list_struct* value = 0);
        void set_morph(object_info object = {}, float_t weight = 0.0f);
        void set_shadow_type(shadow_type_enum type = SHADOW_CHARA);
        void set_texture_color_coefficients(vec4& value);
        void set_texture_color_offset(vec4& value);
        void set_texture_pattern(int32_t count = 0, const texture_pattern_struct* value = 0);
        void set_texture_specular_coefficients(vec4& value);
        void set_texture_specular_offset(vec4& value);
        void set_texture_transform(int32_t count = 0, const texture_transform_struct* value = 0);
        void set_wet_param(float_t value = 0.0f);
    };

    static_assert(sizeof(mdl::DispManager) == 0x9D0, "\"mdl::DispManager\" struct should have a size of 0x9D0");

    extern mdl::EtcObjManager* etc_obj_manager;

    extern bool obj_reflect_enable;

    extern void disp_manager_patch();
}

extern mdl::DispManager* disp_manager;
