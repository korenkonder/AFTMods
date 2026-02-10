#version 430 core
// exposure_minify.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord0;
layout(location = 1) in vec2 frg_texcoord1;
layout(location = 2) in vec2 frg_texcoord2;
layout(location = 3) in vec2 frg_texcoord3;
layout(location = 4) in vec2 frg_texcoord4;
layout(location = 5) in vec2 frg_texcoord5;
layout(location = 6) in vec2 frg_texcoord6;
layout(location = 7) in vec2 frg_texcoord7;

void main() {
    vec4 sum;
    sum = texture(g_texture, frg_texcoord0);
    sum += texture(g_texture, frg_texcoord1);
    sum += texture(g_texture, frg_texcoord2);
    sum += texture(g_texture, frg_texcoord3);
    sum += texture(g_texture, frg_texcoord4);
    sum += texture(g_texture, frg_texcoord5);
    sum += texture(g_texture, frg_texcoord6);
    sum += texture(g_texture, frg_texcoord7);
    result = sum * 0.125;
}
