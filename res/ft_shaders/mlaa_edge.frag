#version 430 core
// mlaa_edge.frag
//DEF
// 0 - Alpha Mask
// 1 - MLAA Search

#define  ALPHA_MASK_DEF (_0 == 1)
#define MLAA_SEARCH     (_1)

layout(set = 0, binding = 0) uniform sampler2D g_texture;

#define MLAA_THRESHOLD 0.15

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord0;
layout(location = 1) in vec2 frg_texcoord1;
layout(location = 2) in vec2 frg_texcoord2;

void main() {
    vec4 col = texture(g_texture, frg_texcoord0);
    vec4 col_left = texture(g_texture, frg_texcoord1);
    vec4 col_top = texture(g_texture, frg_texcoord2);
    vec4 delta_left = abs(col_left - col);
    vec4 delta_top = abs(col_top - col);
    vec2 edge;
    #if ALPHA_MASK_DEF
        edge.x = float(max(max(delta_left.r, delta_left.g), max(delta_left.b, delta_left.a)) > MLAA_THRESHOLD);
        edge.y = float(max(max(delta_top.r, delta_top.g), max(delta_top.b, delta_top.a)) > MLAA_THRESHOLD);
    #else
        edge.x = float(max(max(delta_left.r, delta_left.g), delta_left.b) > MLAA_THRESHOLD);
        edge.y = float(max(max(delta_top.r, delta_top.g), delta_top.b) > MLAA_THRESHOLD);
    #endif

    result = vec4(edge, 0.0, 0.0);
}
