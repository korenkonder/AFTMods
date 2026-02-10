#version 430 core
// sky_default.vert
//DEF
// 0 - Morph

#define MORPH_DEF (_0 == 1)

layout(set = 0, binding = 14) uniform sampler2D g_effect_texture;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#if MORPH_DEF
#include "common_morph.glsl"
#endif

#include "common_stage.glsl"

#define result_position (gl_Position)

layout(location = 0) out vec4 result_color;
layout(location = 1) out vec4 result_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 2) out float result_fog;

layout(location = 0) in vec3 a_position;
layout(location = 3) in vec4 a_color;
layout(location = 8) in vec2 a_texcoords[2];

#if MORPH_DEF
layout(location = 5) in vec4 a_morph_color;
layout(location = 10) in vec3 a_morph_position;
layout(location = 13) in vec2 a_morph_texcoords[2];
#endif

void main() {
    vec4 pos_m;
    #if MORPH_DEF
        pos_m = vec4(apply_morph(a_position, a_morph_position), 1.0);
    #else
        pos_m = vec4(a_position, 1.0);
    #endif

    vec3 pos_w = pos_m * g_worlds;

    vec4 pos_c = pos_m * g_transforms;
    result_position = pos_c;

    vec2 texcoord0;
    #if MORPH_DEF
        texcoord0 = apply_morph(a_texcoords[0], a_morph_texcoords[0]);
    #else
        texcoord0 = a_texcoords[0];
    #endif
    result_texcoord.xy = vec4(texcoord0, 0.0, 1.0) * g_texcoord_transforms[0];

    vec2 texcoord1;
    #if MORPH_DEF
        texcoord1 = apply_morph(a_texcoords[1], a_morph_texcoords[1]);
    #else
        texcoord1 = a_texcoords[1];
    #endif
    result_texcoord.zw = vec4(texcoord1, 0.0, 1.0) * g_texcoord_transforms[1];

    vec4 diff;
    #if MORPH_DEF
        diff = apply_morph_color(diff, a_color, a_morph_color);
    #else
        diff = a_color;
    #endif
    result_color = diff * g_blend_color;

    result_fog = get_fog_stage(g_effect_texture, pos_m, pos_w);
}
