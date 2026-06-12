/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "camera_render.hpp"
#include "camera.hpp"

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
    view_point = get_camera_pos();
    interest = get_camera_intr();
    up = get_camera_up();
    fov = get_camera_pers() * DEG_TO_RAD_FLOAT;
    aspect = (float_t)get_camera_aspect();
    min_distance = get_camera_near_clip();
    max_distance = get_camera_far_clip();
    get_camera_matrix(&view_mat, &proj_mat, &view_proj_mat);
    mat4_transpose(&view_mat, &view_mat);
    mat4_transpose(&proj_mat, &proj_mat);
    mat4_transpose(&view_proj_mat, &view_proj_mat);
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
