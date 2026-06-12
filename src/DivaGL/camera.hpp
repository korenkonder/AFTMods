/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../KKdLib/default.hpp"
#include "../AFTModsShared/camera.hpp"

extern void camera_patch();

extern int32_t check_screen_aabb(const struct AABB* aabb, const mat4* mat);
extern const mat4& set_projection_matrix_2d(bool is_pre2d);
