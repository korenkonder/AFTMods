#version 430 core
// reduce_tex_reduce_4_extract.vert

#include "common_quad.glsl"

#define result_position (gl_Position)

layout(location = 0) out vec4 result_texcoord0; //xy=texcoord0, zw=texcoord1
layout(location = 1) out vec4 result_texcoord1; //xy=texcoord2, zw=texcoord3

void main() {
    vec2 pos;
    pos.x = -1.0 + float(gl_VertexID / 2 % 2) * 2.0;
    pos.y = 1.0 - float(gl_VertexID % 2) * 2.0;
    result_position = vec4(pos, 0.0, 1.0);

    vec2 tex = pos * g_texcoord_modifier.xy + g_texcoord_modifier.zw;
    result_texcoord0.xy = tex + vec2(-1.0, -1.0) * g_texel_size.xy;
    result_texcoord0.zw = tex + vec2( 1.0, -1.0) * g_texel_size.xy;
    result_texcoord1.xy = tex + vec2(-1.0,  1.0) * g_texel_size.xy;
    result_texcoord1.zw = tex + vec2( 1.0,  1.0) * g_texel_size.xy;
}
