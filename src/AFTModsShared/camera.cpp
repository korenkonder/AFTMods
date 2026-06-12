/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "camera.hpp"
#include <Helpers.h>

CameraInfo& camera_info = *(CameraInfo*)0x0000000140FBC2C0;

FUNCTION_PTR(void, FASTCALL, calc_camera_matrix, 0x00000001401F7690, CameraData* data);
FUNCTION_PTR(void, FASTCALL, calc_frustum_plane_normal, 0x00000001401F7B20, CameraData* data);
FUNCTION_PTR(vec2, FASTCALL, calc_screen_pos2d, 0x00000001401F7D60, const vec3* pos, bool with_render_offset);
FUNCTION_PTR(vec3, FASTCALL, calc_screen_pos3d, 0x00000001401F7EB0, const vec3* pos, bool with_render_offset);
FUNCTION_PTR(float_t, FASTCALL, calc_screen_pos_r, 0x00000001401F7EE0, vec3* sc_pos, const vec3* pos, float_t r, bool with_render_offset);
FUNCTION_PTR(bool, FASTCALL, check_camera_discontinuity_prev, 0x00000001401F80E0);
FUNCTION_PTR(bool, FASTCALL, check_camera_discontinuity, 0x00000001401F8100);
FUNCTION_PTR(int32_t, FASTCALL, check_screen_pos, 0x00000001401F8700, const vec3* wpos);
FUNCTION_PTR(int32_t, FASTCALL, check_screen_pos_r, 0x00000001401F8710, const vec3* wpos, float_t wr);
FUNCTION_PTR(void, FASTCALL, ctrl_camera, 0x00000001401F8970);
FUNCTION_PTR(void, FASTCALL, dest_camera, 0x00000001401F89D0);
FUNCTION_PTR(void, FASTCALL, enter_debug_camera, 0x00000001401F89E0);
FUNCTION_PTR(void, FASTCALL, exit_debug_camera, 0x00000001401F8A00);
FUNCTION_PTR(double_t, FASTCALL, get_camera_aspect, 0x00000001401F8A20);
FUNCTION_PTR(float_t, FASTCALL, get_camera_far_clip, 0x00000001401F8A30);
FUNCTION_PTR(float_t, FASTCALL, get_camera_fv_2d, 0x00000001401F8A40);
FUNCTION_PTR(void, FASTCALL, get_camera_imatrix, 0x00000001401F8A50, mat4* imat);
FUNCTION_PTR(vec3, FASTCALL, get_camera_intr, 0x00000001401F8A70);
FUNCTION_PTR(void, FASTCALL, get_camera_matrix, 0x00000001401F8AA0, mat4* cmat, mat4* pmat, mat4* vpmat);
FUNCTION_PTR(float_t, FASTCALL, get_camera_near_clip, 0x00000001401F8B00);
FUNCTION_PTR(float_t, FASTCALL, get_camera_pers, 0x00000001401F8B10);
FUNCTION_PTR(vec3, FASTCALL, get_camera_pos, 0x00000001401F8B20);
FUNCTION_PTR(float_t, FASTCALL, get_camera_rot_y_deg, 0x00000001401F8B50);
FUNCTION_PTR(float_t, FASTCALL, get_camera_rot_z, 0x00000001401F8B70);
FUNCTION_PTR(vec3, FASTCALL, get_camera_up, 0x00000001401F8B80);
FUNCTION_PTR(bool, FASTCALL, get_ignore_near_clip, 0x00000001401F8C10);
FUNCTION_PTR(bool, FASTCALL, get_ignore_pers, 0x00000001401F8C20);
FUNCTION_PTR(void, FASTCALL, init_camera, 0x00000001401F8C70);
FUNCTION_PTR(void, FASTCALL, init_projection_matrix, 0x00000001401F8E90);
FUNCTION_PTR(int32_t, FASTCALL, frustum_plane_check, 0x00000001401F9220, const vec4* plane, const vec4* vtx, int32_t count);
FUNCTION_PTR(void, FASTCALL, project_screen_r, 0x00000001401F92E0, vec2* pos2d, const vec3* pos3d, float_t r, bool with_render_offset);
FUNCTION_PTR(void, FASTCALL, project_screen, 0x00000001401F9340, vec2* pos2d, const vec3* pos3d, bool with_render_offset);
FUNCTION_PTR(void, FASTCALL, set_camera_aspect, 0x00000001401F9390, double_t aspect);
FUNCTION_PTR(void, FASTCALL, set_camera_discontinuity2, 0x00000001401F93A0);
FUNCTION_PTR(void, FASTCALL, set_camera_discontinuity, 0x00000001401F93B0);
FUNCTION_PTR(void, FASTCALL, set_camera_frustum_offset, 0x00000001401F93C0, float_t left_offset, float_t right_offset, float_t bottom_offset, float_t top_offset);
FUNCTION_PTR(void, FASTCALL, set_camera_intr, 0x00000001401F93F0, const vec3* in_intr);
FUNCTION_PTR(void, FASTCALL, set_camera_near_clip, 0x00000001401F9410, float_t clip_near);
FUNCTION_PTR(void, FASTCALL, set_camera_pers, 0x00000001401F9430, float_t pers);
FUNCTION_PTR(void, FASTCALL, set_camera_portrait, 0x00000001401F9450, bool portrait);
FUNCTION_PTR(void, FASTCALL, set_camera_pos, 0x00000001401F9460, const vec3* in_pos);
FUNCTION_PTR(void, FASTCALL, set_camera_rot_z, 0x00000001401F9480, float_t rot_z);
FUNCTION_PTR(void, FASTCALL, set_camera_up, 0x00000001401F9490, bool use_up, const vec3* in_up);
FUNCTION_PTR(void, FASTCALL, set_debug_camera_aspect, 0x00000001401F94C0, double_t aspect);
FUNCTION_PTR(void, FASTCALL, set_debug_camera_distance, 0x00000001401F94D0, float_t distance);
FUNCTION_PTR(void, FASTCALL, set_debug_camera_intr, 0x00000001401F94E0, const vec3* in_intr);
FUNCTION_PTR(void, FASTCALL, set_debug_camera_near, 0x00000001401F9500, float_t in_clip_near);
FUNCTION_PTR(void, FASTCALL, set_debug_camera_pers, 0x00000001401F9510, float_t pers);
FUNCTION_PTR(void, FASTCALL, set_debug_camera_pos, 0x00000001401F9520, const vec3* in_pos);
FUNCTION_PTR(void, FASTCALL, set_debug_camera_rot, 0x00000001401F9540, const vec3* in_rot);
FUNCTION_PTR(void, FASTCALL, set_debug_camera_rot_z, 0x00000001401F9560, float_t rot);
FUNCTION_PTR(void, FASTCALL, set_ignore_near_clip_camera, 0x00000001401F9570, bool ignore_clip_near);
FUNCTION_PTR(void, FASTCALL, set_ignore_pers_camera, 0x00000001401F9580, bool ignore_pers);
