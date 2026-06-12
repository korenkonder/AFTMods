/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "camera.hpp"
#include "../AFTModsShared/resolution_mode.hpp"
#include "object.hpp"
#include "render.hpp"
#include "render_context.hpp"
#include <Helpers.h>

HOOK(void, FASTCALL, init_projection_matrix, 0x00000001401F8E90) {
    const resolution_struct* res_wind = res_window_get();
    const resolution_struct* res_wind_int = res_window_internal_get();

    const float_t half_width = (float_t)res_wind->width * 0.5f;
    const float_t half_height = (float_t)res_wind->height * 0.5f;
    const float_t render_half_width = (float_t)res_wind_int->width * 0.5f;
    const float_t render_half_height = (float_t)res_wind_int->height * 0.5f;

    const float_t fv_2d = camera_info.data.fv_2d;

    const float_t clip_near_2d = camera_info.data.clip_near;
    const float_t clip_far_2d = 3000.0f;

    const float_t range_2d = clip_near_2d / fv_2d;
    const float_t range_x_2d = range_2d * half_width;
    const float_t range_y_2d = range_2d * half_height;

    mat4 pmat_2d;
    mat4_frustum(-range_x_2d, range_x_2d, range_y_2d, -range_y_2d,
        clip_near_2d, clip_far_2d, &pmat_2d);

    const vec3 pos_2d(half_width, half_height, fv_2d);
    const vec3 intr_2d(half_width, half_height, 0.0f);
    const vec3 up_2d(0.0f, 1.0f, 0.0f);
    mat4 vmat_2d;
    mat4_look_at(&pos_2d, &intr_2d, &up_2d, &vmat_2d);

    mat4_mul(&vmat_2d, &pmat_2d, &pmat_2d);
    mat4_transpose(&pmat_2d, &camera_info.data.vpmat_2d);

    const float_t fv_pre2d = render_half_height / tanf(camera_info.data.pers_2d * 0.5f * DEG_TO_RAD_FLOAT);

    const float_t range_pre2d = clip_near_2d / fv_pre2d;
    const float_t range_x_pre2d = range_pre2d * render_half_width;
    const float_t range_y_pre2d = range_pre2d * render_half_height;

    mat4 pmat_pre2d;
    mat4_frustum(-range_x_pre2d, range_x_pre2d, range_y_pre2d, -range_y_pre2d,
        clip_near_2d, clip_far_2d, &pmat_pre2d);

    const vec3 pos_pre2d(render_half_width, render_half_height, fv_pre2d);
    const vec3 intr_pre2d(render_half_width, render_half_height, 0.0f);
    const vec3 up_pre2d(0.0f, 1.0f, 0.0f);
    mat4 vmat_pre2d;
    mat4_look_at(&pos_pre2d, &intr_pre2d, &up_pre2d, &vmat_pre2d);

    mat4_mul(&vmat_pre2d, &pmat_pre2d, &pmat_pre2d);
    mat4_transpose(&pmat_pre2d, &camera_info.data.vpmat_pre2d);

    vec2 persp_scale = 1.0f;
    vec2 persp_offset = render_get()->get_taa_offset();
    mat4 proj;
    mat4_persp_offset(camera_info.data.pers * DEG_TO_RAD_FLOAT, (float_t)camera_info.data.aspect,
        camera_info.data.clip_near, camera_info.data.clip_far, &persp_scale, &persp_offset, &proj);
    mat4_transpose(&proj, &camera_info.data.pmat);

    camera_info.data.pers_tan = tanf(camera_info.data.pers * 0.5f * DEG_TO_RAD_FLOAT);
}

HOOK(void, FASTCALL, ctrl_camera, 0x00000001401F8970) {
    implOfinit_projection_matrix();
    calc_camera_matrix(&camera_info.data);

    camera_info.data.discontinuity3 = camera_info.data.discontinuity2;
    camera_info.data.discontinuity2 = camera_info.data.discontinuity;
    camera_info.data.discontinuity = false;

    extern render_context* rctx;
    rctx->render_manager_cam.get();
}

void camera_patch() {
    INSTALL_HOOK(init_projection_matrix);
    INSTALL_HOOK(ctrl_camera);
}

// 0x1401F8130
int32_t check_screen_aabb(const AABB* aabb, const mat4* mat) {
    vec3 points[8];
    points[0] = aabb->center + (aabb->r ^ vec3( 0.0f,  0.0f,  0.0f));
    points[1] = aabb->center + (aabb->r ^ vec3(-0.0f, -0.0f, -0.0f));
    points[2] = aabb->center + (aabb->r ^ vec3(-0.0f,  0.0f,  0.0f));
    points[3] = aabb->center + (aabb->r ^ vec3( 0.0f, -0.0f, -0.0f));
    points[4] = aabb->center + (aabb->r ^ vec3( 0.0f, -0.0f,  0.0f));
    points[5] = aabb->center + (aabb->r ^ vec3(-0.0f,  0.0f, -0.0f));
    points[6] = aabb->center + (aabb->r ^ vec3( 0.0f,  0.0f, -0.0f));
    points[7] = aabb->center + (aabb->r ^ vec3(-0.0f, -0.0f,  0.0f));

    mat4 view_mat;
    mat4_mul(&camera_info.data.cmat, mat, &view_mat);
    mat4_transpose(&view_mat, &view_mat);

    vec4 vtx[8];
    for (int32_t i = 0; i < 8; i++) {
        mat4_transform_point(&view_mat, &points[i], (vec3*)&vtx[i]);
        vtx[i].w = 1.0f;
    }

    vec4 plane[6];
    *(vec3*)&plane[0] = { 0.0f, 0.0f, -1.0f };
    plane[0].w = -camera_info.data.clip_near;
    *(vec3*)&plane[1] = camera_info.data.fpn_left;
    plane[1].w = 0.0f;
    *(vec3*)&plane[2] = camera_info.data.fpn_right;
    plane[2].w = 0.0f;
    *(vec3*)&plane[3] = camera_info.data.fpn_bottom;
    plane[3].w = 0.0f;
    *(vec3*)&plane[4] = camera_info.data.fpn_top;
    plane[4].w = 0.0f;
    *(vec3*)&plane[5] = { 0.0f, 0.0f, 1.0f };
    plane[5].w = camera_info.data.clip_far;

    for (int32_t i = 0; i < 6; i++)
        if (!frustum_plane_check(&plane[i], vtx, 8))
            return 0;
    return 1;
}

// 0x1401F9590
const mat4& set_projection_matrix_2d(bool is_pre2d) {
    if (is_pre2d)
        return camera_info.data.vpmat_pre2d;
    return camera_info.data.vpmat_2d;
}
