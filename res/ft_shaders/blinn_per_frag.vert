#version 430 core
// blinn_per_frag.vert
//DEF
// 0 - Skinning
// 1 - Morph
// 2 - Alpha Test

#define   SKINNING_DEF (_0 == 1)
#define      MORPH_DEF (_1 == 1)
#define ALPHA_TEST_DEF (_2 == 1)

layout(set = 0, binding = 14) uniform sampler2D g_effect_texture;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#if SKINNING_DEF
#include "common_skinning.glsl"
#endif

#if MORPH_DEF
#include "common_morph.glsl"
#endif

#include "common_stage.glsl"

#define result_position (gl_Position)

layout(location = 0) out vec3 result_normal;
layout(location = 1) out vec3 result_tangent;
layout(location = 2) out vec3 result_binormal;
layout(location = 3) out vec4 result_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 4) out vec3 result_eye;
layout(location = 5) out vec4 result_texcoord_shadow0; //xyz=texcoord_shadow0, w=fog
layout(location = 6) out vec4 result_texcoord_shadow1; //xyz=texcoord_shadow1, w=
layout(location = 7) out vec4 result_color;
layout(location = 8) out vec4 result_offset_color;

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec4 a_color;
layout(location = 6) in vec4 a_tangent;
layout(location = 8) in vec2 a_texcoords[2];

#if MORPH_DEF
layout(location = 5) in vec4 a_morph_color;
layout(location = 10) in vec3 a_morph_position;
layout(location = 11) in vec3 a_morph_normal;
layout(location = 12) in vec4 a_morph_tangent;
layout(location = 13) in vec2 a_morph_texcoords[2];
#endif

void main() {
    vec4 pos_m;
    vec3 normal_w;
    vec3 tangent_w;
    #if SKINNING_DEF
        ivec4 mtxidx;
        vec4 weight = get_skinning_data(mtxidx);

        pos_m = apply_skinning(vec4(a_position, 1.0), mtxidx, weight);

        normal_w = apply_skinning(a_normal, mtxidx, weight);
        normal_w = normalize(normal_w);

        tangent_w = apply_skinning(a_tangent.xyz, mtxidx, weight);
        tangent_w = normalize(tangent_w);
    #else
        vec3 normal_m;
        vec3 tangent_m;
        #if MORPH_DEF
            pos_m = vec4(apply_morph(a_position, a_morph_position), 1.0);
            normal_m = apply_morph(a_normal, a_morph_normal);
            tangent_m = apply_morph(a_tangent.xyz, a_morph_tangent.xyz);
        #else
            pos_m = vec4(a_position, 1.0);
            normal_m = a_normal;
            tangent_m = a_tangent.xyz;
        #endif

        normal_w = normal_m * mat3(g_worlds);
        tangent_w = tangent_m * mat3(g_worlds);
    #endif

    vec3 pos_w = pos_m * g_worlds;

    vec4 pos_c = pos_m * g_transforms;
    result_position = pos_c;

    vec3 binormal_w = cross(normal_w, tangent_w) * a_tangent.w;

    vec4 tmp;
    tmp.x = binormal_w.x;
    tmp.y = tangent_w.y;
    tmp.z = normal_w.x;
    tmp.w = normal_w.y;
    normal_w.x = tangent_w.z;
    normal_w.y = binormal_w.z;
    tangent_w.y = tmp.x;
    tangent_w.z = tmp.z;
    binormal_w.x = tmp.y;
    binormal_w.z = tmp.w;

    result_normal = normal_w;
    result_tangent = tangent_w;
    result_binormal = binormal_w;

    result_texcoord_shadow0.w = get_fog_stage(g_effect_texture, pos_m, pos_w);
    result_texcoord_shadow1.w = 0.0;

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

    result_eye = normalize(g_view_position.xyz - pos_w);

    get_texcoord_shadow_stage(pos_w, result_texcoord_shadow0.xyz, result_texcoord_shadow1.xyz);

    vec4 diff = g_blend_color * vec4(0.5, 0.5, 0.5, 1.0);
    #if MORPH_DEF
        diff = apply_morph_color(diff, a_color, a_morph_color);
    #else
        diff *= a_color;
    #endif
    result_color = diff;

    result_offset_color = g_offset_color;
}
