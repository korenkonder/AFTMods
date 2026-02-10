#version 430 core
// reduce_tex_reduce_4_extract.frag

const vec3 to_ybr = vec3(0.35, 0.45, 0.2);

layout(set = 0, binding = 0) uniform sampler2D g_texture;

#include "common_quad.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_texcoord0; //xy=texcoord0, zw=texcoord1
layout(location = 1) in vec4 frg_texcoord1; //xy=texcoord2, zw=texcoord3

void main() {
    vec3 col0 = texture(g_texture, frg_texcoord0.xy).rgb;
    vec3 col1 = texture(g_texture, frg_texcoord0.zw).rgb;
    vec3 col2 = texture(g_texture, frg_texcoord1.xy).rgb;
    vec3 col3 = texture(g_texture, frg_texcoord1.zw).rgb;
    vec3 sum = col0 + col1 + col2 + col3;
    sum *= 0.25;

    float luma = dot(sum, to_ybr);
    vec3 col = max(max(max(col0, col1), col2), col3);

    result.rgb = max(col - g_color.rgb, vec3(0.0));
    result.a = luma;
}
