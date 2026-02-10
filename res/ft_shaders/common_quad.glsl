#ifndef COMMON_QUAD
#define COMMON_QUAD

layout(set = 1, binding = 0) uniform Quad {
    vec4 g_texcoord_modifier;
    vec4 g_texel_size;
    vec4 g_color;
    vec4 g_texture_lod; //yzw=unused
};
#endif  // COMMON_QUAD
