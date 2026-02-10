#version 430 core
// exposure_minify.vert

#include "common_quad.glsl"

#define result_position (gl_Position)

layout(location = 0) out vec2 result_texcoord0;
layout(location = 1) out vec2 result_texcoord1;
layout(location = 2) out vec2 result_texcoord2;
layout(location = 3) out vec2 result_texcoord3;
layout(location = 4) out vec2 result_texcoord4;
layout(location = 5) out vec2 result_texcoord5;
layout(location = 6) out vec2 result_texcoord6;
layout(location = 7) out vec2 result_texcoord7;

void main() {
    vec2 pos;
    pos.x = -1.0 + float(gl_VertexID / 2 % 2) * 2.0;
    pos.y = 1.0 - float(gl_VertexID % 2) * 2.0;
    result_position = vec4(pos, 0.0, 1.0);
    
    vec2 tex = pos * g_texcoord_modifier.xy + g_texcoord_modifier.zw;
    result_texcoord0 = tex + vec2(-1.5, -0.6) * g_texel_size.xy;
    result_texcoord1 = tex + vec2(-0.5, -0.6) * g_texel_size.xy;
    result_texcoord2 = tex + vec2( 0.5, -0.6) * g_texel_size.xy;
    result_texcoord3 = tex + vec2( 1.5, -0.6) * g_texel_size.xy;
    result_texcoord4 = tex + vec2(-1.5,  0.6) * g_texel_size.xy;
    result_texcoord5 = tex + vec2(-0.5,  0.6) * g_texel_size.xy;
    result_texcoord6 = tex + vec2( 0.5,  0.6) * g_texel_size.xy;
    result_texcoord7 = tex + vec2( 1.5,  0.6) * g_texel_size.xy;
}
