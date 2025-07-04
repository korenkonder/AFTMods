/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "static_var.hpp"

int32_t sv_max_texture_size = 2048;
int32_t sv_max_texture_max_anisotropy = 1;
int32_t sv_max_uniform_buffer_size = 0x10000;
int32_t sv_max_storage_buffer_size = 0x8000000;
int32_t sv_min_uniform_buffer_alignment = 0x100;
int32_t sv_min_storage_buffer_alignment = 0x100;

bool sv_reflect_full = true;
int32_t sv_reflect_res_scale = 100;

bool sv_shared_storage_uniform_buffer = false;

bool sv_task_movie_player_no_interop = false;

bool sv_texture_skinning_buffer = false;
