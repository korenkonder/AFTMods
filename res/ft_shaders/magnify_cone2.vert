#version 430 core
// magnify_cone2.vert

#include "common_quad.glsl"

#define result_position (gl_Position)

layout(location = 0) out vec4 result_texcoord;  //xy=texcoord0, zw=texcoord1

void main() {
    vec2 pos;
    pos.x = -1.0 + float(gl_VertexID / 2 % 2) * 2.0;
    pos.y = 1.0 - float(gl_VertexID % 2) * 2.0;
    result_position = vec4(pos, 0.0, 1.0);

    vec2 tex = pos * g_texcoord_modifier.xy + g_texcoord_modifier.zw;
    result_texcoord.xy = tex + vec2(-0.3, -0.4) * g_texel_size.xy;
    result_texcoord.zw = tex + vec2( 0.3,  0.4) * g_texel_size.xy;
}
