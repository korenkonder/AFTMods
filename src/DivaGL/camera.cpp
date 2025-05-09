/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "camera.hpp"
#include "../AFTModsShared/resolution_mode.hpp"
#include "render.hpp"
#include "render_context.hpp"
#include <Helpers.h>

cam_data::cam_data() : view_point(0.0f, 0.0f, 1.0f), interest(), up(0.0f, 1.0f, 0.0f),
fov(30.0f * DEG_TO_RAD_FLOAT), aspect(4.0f / 3.0f), min_distance(1.0f), max_distance(200.0f),
view_mat(), proj_mat(), view_proj_mat(), persp_scale(), persp_offset() {

}

void cam_data::calc_ortho_proj_mat(float_t left, float_t right,
    float_t bottom, float_t top, const vec2& scale, const vec2& offset) {
    mat4_ortho_offset(left, right, bottom, top, min_distance, max_distance, &scale, &offset, &proj_mat);
}

void cam_data::calc_persp_proj_mat() {
    mat4_persp(fov, aspect, min_distance, max_distance, &proj_mat);
    persp_scale = 1.0f;
    persp_offset = 0.0f;
}

void cam_data::calc_persp_proj_mat_offset(const vec2& persp_scale, const vec2& persp_offset) {
    mat4_persp_offset(fov, aspect, min_distance, max_distance, &persp_scale, &persp_offset, &proj_mat);
    this->persp_scale = persp_scale;
    this->persp_offset = persp_offset;
}

void cam_data::calc_view_mat() {
    mat4_look_at(&view_point, &interest, &up, &view_mat);
}

void cam_data::calc_view_proj_mat() {
    mat4_mul(&view_mat, &proj_mat, &view_proj_mat);
}

void cam_data::get() {
    view_point = camera_data.view_point;
    interest = camera_data.interest;
    up = camera_data.up;
    fov = camera_data.fov * DEG_TO_RAD_FLOAT;
    aspect = (float_t)camera_data.aspect;
    min_distance = camera_data.min_distance;
    max_distance = camera_data.max_distance;
    mat4_transpose(&camera_data.view, &view_mat);
    mat4_transpose(&camera_data.projection, &proj_mat);
    mat4_transpose(&camera_data.view_projection, &view_proj_mat);
    persp_scale = 1.0f;
    persp_offset = 0.0f;
}

float_t cam_data::get_aspect() const {
    return aspect;
}

float_t cam_data::get_fov() const {
    return fov;
}

const vec3& cam_data::get_interest() const {
    return interest;
}

float_t cam_data::get_min_distance() const {
    return min_distance;
}

float_t cam_data::get_max_distance() const {
    return max_distance;
}

const mat4& cam_data::get_proj_mat() const {
    return proj_mat;
}

const mat4& cam_data::get_view_mat() const {
    return view_mat;
}

const vec3& cam_data::get_view_point() const {
    return view_point;
}

const mat4& cam_data::get_view_proj_mat() const {
    return view_proj_mat;
}

void cam_data::set_aspect(float_t value) {
    aspect = value;
}

void cam_data::set_fov(float_t value) {
    fov = value;
}

void cam_data::set_interest(const vec3& value) {
    interest = value;
}

void cam_data::set_min_distance(float_t value) {
    min_distance = value;
}

void cam_data::set_max_distance(float_t value) {
    max_distance = value;
}

void cam_data::set_up(const vec3& value) {
    up = value;
}

void cam_data::set_view_point(const vec3& value) {
    view_point = value;
}

static void (FASTCALL* camera_struct__update_view)(camera_struct& cam)
    = (void (FASTCALL*)(camera_struct & cam))0x00000001401F7690;

HOOK(void, FASTCALL, camera_data_update_projection, 0x00000001401F8E90) {
    resolution_struct* res_wind = res_window_get();
    resolution_struct* res_wind_int = res_window_internal_get();

    float_t sprite_half_width = (float_t)res_wind->width * 0.5f;
    float_t sprite_half_height = (float_t)res_wind->height * 0.5f;
    float_t render_half_width = (float_t)res_wind_int->width * 0.5f;
    float_t render_half_height = (float_t)res_wind_int->height * 0.5f;

    float_t aet_depth = camera_data.aet_depth;

    float_t spr_2d_range = camera_data.min_distance / aet_depth;
    float_t spr_2d_range_x = spr_2d_range * sprite_half_width;
    float_t spr_2d_range_y = spr_2d_range * sprite_half_height;

    mat4 spr_2d_proj;
    mat4_frustrum(-spr_2d_range_x, spr_2d_range_x, spr_2d_range_y, -spr_2d_range_y,
        camera_data.min_distance, 3000.0f, &spr_2d_proj);

    vec3 spr_2d_viewpoint = { sprite_half_width, sprite_half_height, aet_depth };
    vec3 spr_2d_interest = { sprite_half_width, sprite_half_height, 0.0f };
    vec3 spr_2d_up = { 0.0f, 1.0f, 0.0f };
    mat4 spr_2d_view;
    mat4_look_at(&spr_2d_viewpoint, &spr_2d_interest, &spr_2d_up, &spr_2d_view);

    mat4_mul(&spr_2d_view, &spr_2d_proj, &spr_2d_proj);
    mat4_transpose(&spr_2d_proj, &camera_data.view_projection_aet_2d);

    float_t aet_3d_depth = render_half_height / tanf(camera_data.aet_fov * 0.5f * DEG_TO_RAD_FLOAT);

    float_t spr_3d_range = camera_data.min_distance / aet_3d_depth;
    float_t spr_3d_range_x = spr_3d_range * render_half_width;
    float_t spr_3d_range_y = spr_3d_range * render_half_height;

    mat4 spr_3d_proj;
    mat4_frustrum(-spr_3d_range_x, spr_3d_range_x, spr_3d_range_y, -spr_3d_range_y,
        camera_data.min_distance, 3000.0f, &spr_3d_proj);

    vec3 spr_3d_viewpoint = { render_half_width, render_half_height, aet_3d_depth };
    vec3 spr_3d_interest = { render_half_width, render_half_height, 0.0f };
    vec3 spr_3d_up = { 0.0f, 1.0f, 0.0f };
    mat4 spr_3d_view;
    mat4_look_at(&spr_3d_viewpoint, &spr_3d_interest, &spr_3d_up, &spr_3d_view);

    mat4_mul(&spr_3d_view, &spr_3d_proj, &spr_3d_proj);
    mat4_transpose(&spr_3d_proj, &camera_data.view_projection_aet_3d);

    vec2 persp_scale = 1.0f;
    vec2 persp_offset = render_get()->get_taa_offset();
    mat4 proj;
    mat4_persp_offset(camera_data.fov * DEG_TO_RAD_FLOAT, (float_t)camera_data.aspect,
        camera_data.min_distance, camera_data.max_distance, &persp_scale, &persp_offset, &proj);
    mat4_transpose(&proj, &camera_data.projection);

    camera_data.fov_horizontal_rad = tanf(camera_data.fov * 0.5f * DEG_TO_RAD_FLOAT);
}

HOOK(void, FASTCALL, camera_update, 0x00000001401F8970) {
    implOfcamera_data_update_projection();
    camera_struct__update_view(camera_data);
    camera_data.fast_change_hist1 = camera_data.fast_change_hist0;
    camera_data.fast_change_hist0 = camera_data.fast_change;
    camera_data.fast_change = false;

    extern render_context* rctx;
    rctx->render_manager_cam.get();
}

void camera_patch() {
    INSTALL_HOOK(camera_data_update_projection);
    INSTALL_HOOK(camera_update);
}
