#version 430 core
// box4.frag

layout(set = 1, binding = 1) uniform Batch {
    vec4 g_texture_lod; //yzw=unused
    vec4 g_color_scale;
    vec4 g_color_offset;
};

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_texcoord0; //xy=texcoord0, zw=texcoord1
layout(location = 1) in vec4 frg_texcoord1; //xy=texcoord2, zw=texcoord3

void main() {
    vec4 sum;
    sum = textureLod(g_texture, frg_texcoord0.xy, g_texture_lod.x);
    sum += textureLod(g_texture, frg_texcoord0.zw, g_texture_lod.x);
    sum += textureLod(g_texture, frg_texcoord1.xy, g_texture_lod.x);
    sum += textureLod(g_texture, frg_texcoord1.zw, g_texture_lod.x);

    result = sum * g_color_scale + g_color_offset;
}
