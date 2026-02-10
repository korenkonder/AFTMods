#version 430 core
// reduce_tex_reduce_composite_4.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture0;
layout(set = 0, binding = 1) uniform sampler2D g_texture1;
layout(set = 0, binding = 2) uniform sampler2D g_texture2;
layout(set = 0, binding = 3) uniform sampler2D g_texture3;

#include "common_quad.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_texcoord0; //xy=texcoord0, zw=texcoord1
layout(location = 1) in vec4 frg_texcoord1; //xy=texcoord2, zw=texcoord3
layout(location = 2) in vec2 frg_texcoord2; //xy=texcoord4

void main() {
    vec4 col0 = texture(g_texture0, frg_texcoord2.xy);
    vec4 col1 = texture(g_texture1, frg_texcoord2.xy);
    vec4 col2 = texture(g_texture2, frg_texcoord2.xy);
    vec3 sum = texture(g_texture3, frg_texcoord0.xy).rgb;
    sum += texture(g_texture3, frg_texcoord0.zw).rgb;
    sum += texture(g_texture3, frg_texcoord1.xy).rgb;
    sum += texture(g_texture3, frg_texcoord1.zw).rgb;
    sum *= g_color.w;
    sum *= 0.25;
    sum += col0.rgb * g_color.x;
    sum += col1.rgb * g_color.y;
    sum += col2.rgb * g_color.z;

    result.rgb = sum;
    result.a = col0.a;
}
