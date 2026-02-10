#version 430 core
// reduce_tex_reduce_composite_2.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture0;
layout(set = 0, binding = 1) uniform sampler2D g_texture1;

#include "common_quad.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord;

void main() {
    vec4 sum = texture(g_texture0, frg_texcoord);
    sum.rgb *= sum.rgb;
    vec4 col = texture(g_texture1, frg_texcoord);
    col.rgb *= col.rgb;
    sum = mix(col, sum, g_color.a);

    result.rgb = sum.rgb * (1.0 / sqrt(sum.rgb));
    result.a = sum.a;
}
