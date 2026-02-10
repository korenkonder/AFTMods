#version 430 core
// font.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_color;
layout(location = 1) in vec2 frg_texcoord;

void main() {
    float tmp = texture(g_texture, frg_texcoord).a;

    vec3 col = frg_color.rgb * frg_color.a * tmp;
    vec4 alpha = vec4(0.000000001);
    alpha.w = max(alpha.w, tmp);

    alpha.x = max(alpha.x, textureOffset(g_texture, frg_texcoord, ivec2(-1,  0)).a);
    alpha.x = max(alpha.x, textureOffset(g_texture, frg_texcoord, ivec2( 1,  0)).a);
    alpha.x = max(alpha.x, textureOffset(g_texture, frg_texcoord, ivec2( 0, -1)).a);
    alpha.x = max(alpha.x, textureOffset(g_texture, frg_texcoord, ivec2( 0,  1)).a);
    alpha.y = max(alpha.y, textureOffset(g_texture, frg_texcoord, ivec2(-2,  0)).a);
    alpha.y = max(alpha.y, textureOffset(g_texture, frg_texcoord, ivec2( 2,  0)).a);
    alpha.y = max(alpha.y, textureOffset(g_texture, frg_texcoord, ivec2( 0, -2)).a);
    alpha.y = max(alpha.y, textureOffset(g_texture, frg_texcoord, ivec2( 0,  2)).a);
    alpha.z = max(alpha.z, textureOffset(g_texture, frg_texcoord, ivec2(-1, -1)).a);
    alpha.z = max(alpha.z, textureOffset(g_texture, frg_texcoord, ivec2( 1, -1)).a);
    alpha.z = max(alpha.z, textureOffset(g_texture, frg_texcoord, ivec2(-1,  1)).a);
    alpha.z = max(alpha.z, textureOffset(g_texture, frg_texcoord, ivec2( 1,  1)).a);

    alpha *= vec4(0.9, 0.6, 0.8, 1.0);
    alpha.w = max(max(max(alpha.w, alpha.x), alpha.y), alpha.z);

    result.rgb = col * (1.0 / alpha.w);
    result.a = alpha.w * frg_color.a;
}
