#version 430 core
// magnify_diff.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_texcoord0; //xy=texcoord0, zw=texcoord1
layout(location = 1) in vec4 frg_texcoord1; //xy=texcoord2, zw=texcoord3
layout(location = 2) in vec2 frg_texcoord2; //xy=texcoord4

void main() {
    vec4 sum;
    sum = texture(g_texture, frg_texcoord0.xy) * 16.0;
    sum -= texture(g_texture, frg_texcoord0.zw);
    sum -= texture(g_texture, frg_texcoord1.xy);
    sum -= texture(g_texture, frg_texcoord1.zw);
    sum -= texture(g_texture, frg_texcoord2.xy);
    result = sum * (1.0 / 12.0);
}
