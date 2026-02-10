#version 430 core
// reduce_tex_reduce_composite_blur.frag

layout(set = 1, binding = 1) uniform CameraBlur {
    mat4 g_transform;
};

layout(set = 0, binding = 0) uniform sampler2D g_texture0;
layout(set = 0, binding = 2) uniform sampler2D g_texture2;

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1

void main() {
    vec4 pos;
    pos.xy = frg_texcoord.zw;
    pos.z = texture(g_texture2, frg_texcoord.xy).x * 2.0 - 1.0;
    pos.w = 1.0;

    vec4 prev_pos = pos * g_transform;
    prev_pos.xy = prev_pos.xy * (1.0 / prev_pos.w);

    prev_pos.xy = prev_pos.xy * 0.5 + 0.5;
    pos.xy = pos.xy * 0.5 + 0.5;

    vec4 sum = texture(g_texture0, frg_texcoord.xy);
    result.a = sum.a;

    vec3 col1 = sum.rgb;
    col1 += texture(g_texture0, mix(prev_pos.xy, pos.xy, 15.0 / 16.0)).rgb;
    col1 += texture(g_texture0, mix(prev_pos.xy, pos.xy, 14.0 / 16.0)).rgb;
    col1 += texture(g_texture0, mix(prev_pos.xy, pos.xy, 13.0 / 16.0)).rgb;
    col1 += texture(g_texture0, mix(prev_pos.xy, pos.xy, 12.0 / 16.0)).rgb;
    col1 += texture(g_texture0, mix(prev_pos.xy, pos.xy, 11.0 / 16.0)).rgb;
    col1 += texture(g_texture0, mix(prev_pos.xy, pos.xy, 10.0 / 16.0)).rgb;
    col1 += texture(g_texture0, mix(prev_pos.xy, pos.xy,  9.0 / 16.0)).rgb;
    result.rgb = col1 * 0.125;
}
