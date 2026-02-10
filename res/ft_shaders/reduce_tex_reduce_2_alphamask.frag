#version 430 core
// reduce_tex_reduce_2_alphamask.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_texcoord0; //xy=texcoord0, zw=texcoord1
layout(location = 1) in vec4 frg_texcoord1; //xy=texcoord2, zw=texcoord3

void main() {
    vec4 col;
    vec4 sum;
    col = texture(g_texture, frg_texcoord0.xy);
    sum.rgb = col.rgb * col.a;
    sum.a = col.a;
    col = texture(g_texture, frg_texcoord0.zw);
    sum.rgb += col.rgb * col.a;
    sum.a += col.a;
    col = texture(g_texture, frg_texcoord1.xy);
    sum.rgb += col.rgb * col.a;
    sum.a += col.a;
    col = texture(g_texture, frg_texcoord1.zw);
    sum.rgb += col.rgb * col.a;
    sum.a += col.a;
    result.rgb = sum.rgb * (1.0 / sum.a);
    result.a = sum.a * 0.25;
}
