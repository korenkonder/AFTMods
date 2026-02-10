#version 430 core
// sss_skin.vert
//DEF
// 0 - Skinning
// 1 - Alpha Test

#define   SKINNING_DEF (_0 == 1)
#define ALPHA_TEST_DEF (_1 == 1)

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#if SKINNING_DEF
#include "common_skinning.glsl"
#endif

#include "common_chara.glsl"

#define result_position (gl_Position)

layout(location = 0) out vec3 result_normal;
layout(location = 3) out vec4 result_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 4) out vec3 result_eye;
layout(location = 5) out vec4 result_texcoord_shadow0; //xyz=texcoord_shadow0, w=
layout(location = 6) out vec4 result_face_offset; //xyz=unused, w=face_offset
layout(location = 7) out vec4 result_fog_color; //xyz=fog_color, w=fresnel(unused)

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec3 a_normal;
layout(location = 8) in vec2 a_texcoords[2];

void main() {
    vec4 pos_m;
    vec3 normal_w;
    #if SKINNING_DEF
        ivec4 mtxidx;
        vec4 weight = get_skinning_data(mtxidx);

        pos_m = apply_skinning(vec4(a_position, 1.0), mtxidx, weight);

        normal_w = apply_skinning(a_normal, mtxidx, weight);
        normal_w = normalize(normal_w);
    #else
        pos_m = vec4(a_position, 1.0);
        vec3 normal_m = a_normal;

        normal_w = normal_m * mat3(g_worlds);
    #endif

    vec3 pos_w = pos_m * g_worlds;

    vec3 normal_v = normal_w * mat3(g_view);

    vec4 pos_c = pos_m * g_transforms;
    result_position = pos_c;

    vec2 texcoord0 = a_texcoords[0];
    result_texcoord.xy = vec4(texcoord0, 0.0, 1.0) * g_texcoord_transforms[0];

    vec2 texcoord1 = a_texcoords[1];
    result_texcoord.zw = vec4(texcoord1, 0.0, 1.0) * g_texcoord_transforms[1];

    result_texcoord_shadow0.xyz = get_texcoord_shadow_chara(pos_w);
    result_texcoord_shadow0.w = 0.3;

    result_normal = normal_w;

    vec3 eye_w = g_view_position.xyz - pos_w;
    result_eye = eye_w;

    eye_w = normalize(eye_w);

    result_normal = get_normal_chara(normal_w, eye_w);

    result_fog_color.rgb = vec3(0.0);
    result_fog_color.w = get_fresnel(normal_w, eye_w, 4.0, 0.3);

    result_face_offset.rgb = vec3(0.0);
    result_face_offset.w = get_face_offset(normal_v, eye_w);
}
