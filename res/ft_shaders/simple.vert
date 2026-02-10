#version 430 core
// simple.vert
//DEF
// 0 - Skinning
// 1 - Alpha Test

#define SKINNING_DEF (_0 == 1)
#define ALPHA_TEST_DEF (_1 == 1)

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#if SKINNING_DEF
#include "common_skinning.glsl"
#endif

#define result_position (gl_Position)

layout(location = 0) out vec2 result_texcoord;
layout(location = 1) out vec4 result_color;
layout(location = 2) out vec4 result_offset_color;

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec3 a_normal;
layout(location = 8) in vec2 a_texcoords[1];

void main() {
    vec4 pos_m;
    vec3 normal_v;
    #if SKINNING_DEF
        ivec4 mtxidx;
        vec4 weight = get_skinning_data(mtxidx);

        pos_m = apply_skinning(vec4(a_position, 1.0), mtxidx, weight);

        vec3 normal_w = apply_skinning(a_normal, mtxidx, weight);
        normal_w = normalize(normal_w);

        normal_v = normal_w * mat3(g_view);
    #else
        pos_m = vec4(a_position, 1.0);

        normal_v = a_normal * mat3(g_worldview);
    #endif

    vec4 pos_c = pos_m * g_transforms;
    result_position = pos_c;

    vec2 texcoord0 = a_texcoords[0];
    result_texcoord = vec4(texcoord0, 0.0, 1.0) * g_texcoord_transforms[0];

    float intensity = max(dot(normal_v, vec3(1.0)), 0.0) + 0.5;
    result_color.rgb = g_blend_color.rgb * intensity;
    result_color.a = g_blend_color.a;
    result_offset_color = g_offset_color;
}
