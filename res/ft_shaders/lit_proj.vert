#version 430 core
// lit_proj.vert
//DEF
// 0 - Skinning
// 1 - Alpha Test

#define   SKINNING_DEF (_0 == 1)
#define ALPHA_TEST_DEF (_1 == 1)

#include "common_shader.glsl"
#include "common_scene.glsl"
#include "common_batch.glsl"

#if SKINNING_DEF
#include "common_skinning.glsl"
#endif

#define result_position (gl_Position)

layout(location = 0) out vec3 result_normal;
layout(location = 1) out vec3 result_tangent;
layout(location = 2) out vec3 result_binormal;
layout(location = 3) out vec4 result_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 4) out vec3 result_eye;
layout(location = 5) out vec4 result_texcoord_litproj;
layout(location = 6) out vec3 result_lit;
layout(location = 7) out vec4 result_texcoord_litproj_depth;

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec3 a_normal;
layout(location = 6) in vec4 a_tangent;
layout(location = 8) in vec2 a_texcoords[2];

void main() {
    vec4 pos_m;
    vec3 normal_w;
    vec3 tangent_w;
    #if SKINNING_DEF
        ivec4 mtxidx;
        vec4 weight = get_skinning_data(mtxidx);

        pos_m = apply_skinning(vec4(a_position, 1.0), mtxidx, weight);

        normal_w = apply_skinning(a_normal, mtxidx, weight);
        tangent_w = apply_skinning(a_tangent.xyz, mtxidx, weight);

        normal_w = normalize(normal_w);
        tangent_w = normalize(tangent_w);
    #else
        pos_m = vec4(a_position, 1.0);
        vec3 normal_m = a_normal;
        vec3 tangent_m = a_tangent.xyz;

        normal_w = normal_m * mat3(g_worlds);
        tangent_w = tangent_m * mat3(g_worlds);
    #endif

    vec3 pos_w = pos_m * g_worlds;

    vec4 pos_c = pos_m * g_transforms;
    result_position = pos_c;

    vec3 binormal_w = cross(normal_w, tangent_w) * a_tangent.w;

    result_normal = normal_w;
    result_tangent = tangent_w;
    result_binormal = binormal_w;

    result_texcoord_litproj = vec4(pos_w, 1.0) * g_light_projection;
    result_texcoord_litproj_depth = vec4(pos_w, 1.0) * g_light_projection_depth;

    vec2 texcoord0 = a_texcoords[0];
    result_texcoord.xy = vec4(texcoord0, 0.0, 1.0) * g_texcoord_transforms[0];

    vec2 texcoord1 = a_texcoords[1];
    result_texcoord.zw = vec4(texcoord1, 0.0, 1.0) * g_texcoord_transforms[1];

    vec3 lit_w = normalize(g_light_env_proj_position.xyz - pos_w);
    result_lit = lit_w;

    vec3 eye_w = normalize(g_view_position.xyz - pos_w);
    result_eye = eye_w;
}
