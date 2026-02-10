#version 430 core
// dof_render_tile.frag
//DEF
// 0 - Use F2 CoC

#define USE_F2_COC (_0)

#include "dof_common.glsl"
layout(set = 0, binding = 0) uniform sampler2D g_depth;

layout(location = 0) out vec2 result; //r=min_depth_m, g=max_coc_pixel

layout(location = 0) in vec2 frg_texcoord;

void main() {
    //Tiling. r=min depth, g=max CoC
#define N (TILE_SIZE)
    ivec2 texture_size = textureSize(g_depth, 0);
    const vec2 step = 1.0 / vec2(texture_size);
    vec2 lt_uv = frg_texcoord + (-N * 0.5 + 0.5) * step;
    vec2 uv = lt_uv;
    float min_z = 1.0;
    float max_coc = 0.0;
    for(int i = 0; i < N; i++) {
        uv.x = lt_uv.x;
        for(int j = 0; j < N; j++) { //@todo Try reducing number of loops with textureGatherOffsets
            float z = textureLod(g_depth, uv, 0.0).r;
            min_z = min(min_z, z);
            float coc = calculate_coc_pixel_from_value_in_zbuffer(z);
            max_coc = max(max_coc, coc);
            uv.x += step.x;
        }
        uv.y += step.y;
    }
    result.r = calculate_depth_m_from_value_in_zbuffer(min_z); //Linearization
    result.g = max_coc;
    //result.g = 8.0 <= max_coc ? 1.0 : 0.0;
}
