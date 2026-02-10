#version 430 core
// silhouette.vert
//DEF
// 0 - Skinning
// 1 - Morph
// 2 - Alpha Test
// 3 - Depth

#define   SKINNING_DEF (_0 == 1)
#define      MORPH_DEF (_1 == 1)
#define ALPHA_TEST_DEF (_2 == 1)
#define      DEPTH_DEF (_3 == 1)

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#if SKINNING_DEF
#include "common_skinning.glsl"
#endif

#if MORPH_DEF
#include "common_morph.glsl"
#endif

#define result_position (gl_Position)

layout(location = 0) out vec4 result_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 1) out vec2 result_linear_depth; //x=, y=

layout(location = 0) in vec3 a_position;
layout(location = 8) in vec2 a_texcoords[2];

#if MORPH_DEF
layout(location = 10) in vec3 a_morph_position;
layout(location = 13) in vec2 a_morph_texcoords[2];
#endif

void main() {
    vec4 pos_m;
    #if SKINNING_DEF
        ivec4 mtxidx;
        vec4 weight = get_skinning_data(mtxidx);

        pos_m = apply_skinning(vec4(a_position, 1.0), mtxidx, weight);
    #elif MORPH_DEF
        pos_m = vec4(apply_morph(a_position, a_morph_position), 1.0);
    #else
        pos_m = vec4(a_position, 1.0);
    #endif

    vec4 pos_c = pos_m * g_transforms;
    result_position = pos_c;

    result_linear_depth = pos_c.zw * vec2(0.5, 1.0) + vec2(0.5, 0.0);

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
}
