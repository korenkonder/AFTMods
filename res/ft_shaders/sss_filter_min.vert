#version 430 core
// sss_filter_min.vert

#include "common_quad.glsl"

#define result_position (gl_Position)

layout(location = 0) out vec2 result_texcoord0; //xy=texcoord0
layout(location = 1) out vec4 result_texcoord1; //xy=texcoord1, zw=texcoord2
layout(location = 2) out vec4 result_texcoord2; //xy=texcoord3, zw=texcoord4

void main() {
    vec2 pos;
    pos.x = -1.0 + float(gl_VertexID / 2 % 2) * 2.0;
    pos.y = 1.0 - float(gl_VertexID % 2) * 2.0;
    result_position = vec4(pos, 0.0, 1.0);

    vec2 tex = pos * g_texcoord_modifier.xy + g_texcoord_modifier.zw;
    result_texcoord0 = tex;
    result_texcoord1 = tex.xyxy + vec4(-2.0,  0.0, 2.0, 0.0) * g_texel_size.xyxy;
    result_texcoord2 = tex.xyxy + vec4( 0.0, -2.0, 0.0, 2.0) * g_texel_size.xyxy;
}
