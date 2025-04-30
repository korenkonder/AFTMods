/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../KKdLib/default.hpp"
#include "../AFTModsShared/camera.hpp"

struct cam_data {
    vec3 view_point;
    vec3 interest;
    vec3 up;
    float_t fov;
    float_t aspect;
    float_t min_distance;
    float_t max_distance;
    mat4 view_mat;
    mat4 proj_mat;
    mat4 view_proj_mat;
    vec2 persp_scale;
    vec2 persp_offset;

    cam_data();

    void calc_ortho_proj_mat(float_t left, float_t right,
        float_t bottom, float_t top, const vec2& scale, const vec2& offset);
    void calc_persp_proj_mat();
    void calc_persp_proj_mat_offset(const vec2& persp_scale, const vec2& persp_offset);
    void calc_view_mat();
    void calc_view_proj_mat();
    void get();
    float_t get_aspect() const;
    float_t get_fov() const;
    const vec3& get_interest() const;
    float_t get_min_distance() const;
    float_t get_max_distance() const;
    const mat4& get_proj_mat() const;
    const mat4& get_view_mat() const;
    const vec3& get_view_point() const;
    const mat4& get_view_proj_mat() const;
    void set_aspect(float_t value);
    void set_fov(float_t value);
    void set_interest(const vec3& value);
    void set_min_distance(float_t value);
    void set_max_distance(float_t value);
    void set_up(const vec3& value);
    void set_view_point(const vec3& value);
};

extern void camera_patch();
