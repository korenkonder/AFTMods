#version 430 core
// mlaa_area.vert
//DEF
// 0 - Alpha Mask
// 1 - MLAA Search

#define  ALPHA_MASK_DEF (_0 == 1)
#define MLAA_SEARCH     (_1)

#include "common_quad.glsl"

#define result_position (gl_Position)

layout(location = 0) out vec2 result_texcoord;

void main() {
    vec2 pos;
    pos.x = -1.0 + float(gl_VertexID / 2 % 2) * 2.0;
    pos.y = 1.0 - float(gl_VertexID % 2) * 2.0;
    result_position = vec4(pos, 0.0, 1.0);
    result_texcoord = pos * g_texcoord_modifier.xy + g_texcoord_modifier.zw;
}
