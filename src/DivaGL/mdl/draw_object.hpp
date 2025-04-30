/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../../KKdLib/default.hpp"
#include "../../KKdLib/mat.hpp"
#include "../../KKdLib/vec.hpp"
#include "../object.hpp"
#include "../render_context.hpp"

namespace mdl {
    extern void draw(
        render_data_context& rend_data_ctx, obj_primitive_type primitive_type, uint32_t count,
        uint16_t start, uint16_t end, obj_index_format index_format, size_t indices);
    extern void draw_etc_obj(
        render_data_context& rend_data_ctx, const mdl::EtcObj* etc, const mat4* mat);
    extern void draw_sub_mesh(render_data_context& rend_data_ctx, const ObjSubMeshArgs* args,
        const mat4* mat, void(*func)(render_data_context& rend_data_ctx,
            const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat), const cam_data& cam);
    extern void draw_sub_mesh_cheap(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat);
    extern void draw_sub_mesh_cheap_reflect_map(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat);
    extern void draw_sub_mesh_default(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat);
    extern void draw_sub_mesh_default_instanced(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat);
    extern void draw_sub_mesh_no_mat(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat);
    extern void draw_sub_mesh_shadow(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat);
    extern void draw_sub_mesh_sss(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat);
};

extern void model_mat_face_camera_position(const cam_data& cam, const mat4* src, mat4* dst);
extern void model_mat_face_camera_view(const cam_data& cam, const mat4* src, mat4* dst);
