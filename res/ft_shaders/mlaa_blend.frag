#version 430 core
// mlaa_blend.frag
//DEF
// 0 - Alpha Mask
// 1 - MLAA Search

#define  ALPHA_MASK_DEF (_0 == 1)
#define MLAA_SEARCH     (_1)

layout(set = 0, binding = 0) uniform sampler2D g_texture;
layout(set = 0, binding = 1) uniform sampler2D g_mlaa_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord0;
layout(location = 1) in vec2 frg_texcoord1;
layout(location = 2) in vec2 frg_texcoord2;
layout(location = 3) in vec2 frg_texcoord3;
layout(location = 4) in vec2 frg_texcoord4;

void main() {
    vec4 area;
    area.xz = texture(g_mlaa_texture, frg_texcoord0).xz;
    area.y = texture(g_mlaa_texture, frg_texcoord1).y;
    area.w = texture(g_mlaa_texture, frg_texcoord3).w;

    vec4 sum = texture(g_texture, frg_texcoord0);
    float alpha = dot(area, vec4(1.0));
    if (alpha == 0.0) {
        result = sum;
        return;
    }

    vec4 col0 = texture(g_texture, frg_texcoord1);
    vec4 col1 = texture(g_texture, frg_texcoord2);
    vec4 col2 = texture(g_texture, frg_texcoord3);
    vec4 col3 = texture(g_texture, frg_texcoord4);
    alpha = 1.0 - alpha;
    #if ALPHA_MASK_DEF
        alpha *= sum.a;
        sum.rgb *= alpha;
        sum.a = alpha + 0.000001;
        alpha = col0.a * area.y;
        sum.rgb += col0.rgb * alpha;
        sum.a += alpha;
        alpha = col1.a * area.x;
        sum.rgb += col1.rgb * alpha;
        sum.a += alpha;
        alpha = col2.a * area.w;
        sum.rgb += col2.rgb * alpha;
        sum.a += alpha;
        alpha = col3.a * area.z;
        sum.rgb += col3.rgb * alpha;
        sum.a += alpha;
        sum.rgb *= 1.0 / sum.a;
    #else
        sum *= alpha;
        sum += col0 * area.y;
        sum += col1 * area.x;
        sum += col2 * area.w;
        sum += col3 * area.z;
    #endif
    result = sum;
}
