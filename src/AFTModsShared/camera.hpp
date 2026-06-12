/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../KKdLib/default.hpp"
#include "../KKdLib/mat.hpp"
#include "../KKdLib/vec.hpp"

struct CameraData {
    vec3 pos;
    vec3 intr;
    float_t rot_z;
    float_t pers;
    float_t pers_2d;
    double_t aspect;
    float_t clip_near;
    float_t clip_far;
    float_t frustum_left_offset;
    float_t frustum_right_offset;
    float_t frustum_bottom_offset;
    float_t frustum_top_offset;
    bool use_up;
    vec3 up;
    bool ignore_pers;
    bool ignore_near_clip;
    mat4 cmat;
    mat4 imat;
    mat4 pmat;
    mat4 vpmat;
    mat4 vpmat_2d;
    mat4 vpmat_pre2d;
    float_t fv;
    float_t fv_2d;
    vec3 fpn_left;
    vec3 fpn_right;
    vec3 fpn_bottom;
    vec3 fpn_top;
    float_t distance;
    vec3 rot;
    float_t pers_tan;
    bool portrait;
    bool discontinuity;
    bool discontinuity2;
    bool discontinuity3;
};

static_assert(sizeof(CameraData) == 0x230, "\"CameraData\" struct should have a size of 0x230");

struct CameraInfo {
    CameraData data;
    int32_t debug_flag;
    bool debug_active;
    CameraData debug_data;
    CameraData debug_data_org;
};

static_assert(sizeof(CameraInfo) == 0x698, "\"CameraInfo\" struct should have a size of 0x698");

extern CameraInfo& camera_info;

extern void(FASTCALL* calc_camera_matrix)(CameraData* data);
extern void(FASTCALL* calc_frustum_plane_normal)(CameraData* data);
extern vec2(FASTCALL* calc_screen_pos2d)(const vec3* pos, bool with_render_offset);
extern vec3(FASTCALL* calc_screen_pos3d)(const vec3* pos, bool with_render_offset);
extern float_t(FASTCALL* calc_screen_pos_r)(vec3* sc_pos, const vec3* pos, float_t r, bool with_render_offset);
extern bool(FASTCALL* check_camera_discontinuity_prev)();
extern bool(FASTCALL* check_camera_discontinuity)();
extern int32_t(FASTCALL* check_screen_pos)(const vec3* wpos);
extern int32_t(FASTCALL* check_screen_pos_r)(const vec3* wpos, float_t wr);
extern void(FASTCALL* ctrl_camera)();
extern void(FASTCALL* dest_camera)();
extern void(FASTCALL* enter_debug_camera)();
extern void(FASTCALL* exit_debug_camera)();
extern double_t(FASTCALL* get_camera_aspect)();
extern float_t(FASTCALL* get_camera_far_clip)();
extern float_t(FASTCALL* get_camera_fv_2d)();
extern void(FASTCALL* get_camera_imatrix)(mat4* imat);
extern vec3 (FASTCALL* get_camera_intr)();
extern void(FASTCALL* get_camera_matrix)(mat4* cmat, mat4* pmat, mat4* vpmat);
extern float_t(FASTCALL* get_camera_near_clip)();
extern float_t(FASTCALL* get_camera_pers)();
extern vec3 (FASTCALL* get_camera_pos)();
extern float_t(FASTCALL* get_camera_rot_y_deg)();
extern float_t(FASTCALL* get_camera_rot_z)();
extern vec3 (FASTCALL* get_camera_up)();
extern bool(FASTCALL* get_ignore_near_clip)();
extern bool(FASTCALL* get_ignore_pers)();
extern void(FASTCALL* init_camera)();
extern void(FASTCALL* init_projection_matrix)();
extern int32_t(FASTCALL* frustum_plane_check)(const vec4* plane, const vec4* vtx, int32_t count);
extern void(FASTCALL* project_screen_r)(vec2* pos2d, const vec3* pos3d, float_t r, bool with_render_offset);
extern void(FASTCALL* project_screen)(vec2* pos2d, const vec3* pos3d, bool with_render_offset);
extern void(FASTCALL* set_camera_aspect)(double_t aspect);
extern void(FASTCALL* set_camera_discontinuity2)();
extern void(FASTCALL* set_camera_discontinuity)();
extern void(FASTCALL* set_camera_frustum_offset)(float_t left_offset, float_t right_offset, float_t bottom_offset, float_t top_offset);
extern void(FASTCALL* set_camera_intr)(const vec3* in_intr);
extern void(FASTCALL* set_camera_near_clip)(float_t clip_near);
extern void(FASTCALL* set_camera_pers)(float_t pers);
extern void(FASTCALL* set_camera_portrait)(bool portrait);
extern void(FASTCALL* set_camera_pos)(const vec3* in_pos);
extern void(FASTCALL* set_camera_rot_z)(float_t rot_z);
extern void(FASTCALL* set_camera_up)(bool use_up, const vec3* in_up);
extern void(FASTCALL* set_debug_camera_aspect)(double_t aspect);
extern void(FASTCALL* set_debug_camera_distance)(float_t distance);
extern void(FASTCALL* set_debug_camera_intr)(const vec3* in_intr);
extern void(FASTCALL* set_debug_camera_near)(float_t in_clip_near);
extern void(FASTCALL* set_debug_camera_pers)(float_t pers);
extern void(FASTCALL* set_debug_camera_pos)(const vec3* in_pos);
extern void(FASTCALL* set_debug_camera_rot)(const vec3* in_rot);
extern void(FASTCALL* set_debug_camera_rot_z)(float_t rot);
extern void(FASTCALL* set_ignore_near_clip_camera)(bool ignore_clip_near);
extern void(FASTCALL* set_ignore_pers_camera)(bool ignore_pers);
