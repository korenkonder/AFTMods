#version 430 core
// simple_refract.vert
//DEF
// 0 - Skinning

#define SKINNING_DEF (_0 == 1)

#include "common_shader.glsl"
#include "common_scene.glsl"
#include "common_batch.glsl"

#if SKINNING_DEF
#include "common_skinning.glsl"
#endif

#define result_position (gl_Position)

layout(location = 0) out vec4 result_color;
layout(location = 1) out float result_fog;
layout(location = 2) out vec2 result_texcoord;

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec3 a_normal;
layout(location = 8) in vec2 a_texcoords[2];

void main() {
    #if SKINNING_DEF
        ivec4 mtxidx;
        vec4 weight = get_skinning_data(mtxidx);

        vec4 pos_w = apply_skinning(vec4(a_position, 1.0), mtxidx, weight);

        vec3 normal_w = apply_skinning(a_normal, mtxidx, weight);
        normal_w = normalize(normal_w);

        vec4 pos_c = pos_w * g_transforms;
        result_position = pos_c;

        vec2 texcoord0 = a_texcoords[0];
        result_texcoord = vec4(texcoord0, 0.0, 1.0) * g_texcoord_transforms[0];

        vec3 diff = vec3(clamp(dot(normal_w, g_light_reflect_dir.xyz), 0.0, 1.0));
        vec3 amb = vec3(clamp(dot(normal_w, -g_light_reflect_dir.xyz), 0.0, 1.0));

        diff *= g_light_env_reflect_diffuse.rgb * g_material_state_diffuse.rgb;
        diff += g_light_env_reflect_ambient.rgb;
        amb *= g_light_env_reflect_ambient.rgb;

        result_color.rgb = diff + amb;
        result_color.a = 1.0;

        result_fog = clamp((-pos_w.y - g_fog_height_params.y)
            * g_fog_height_params.w, 0.0, 1.0) * g_fog_height_params.x;
    #else
        vec4 pos_m = vec4(a_position, 1.0);

        vec4 pos_c = pos_m * g_transforms;
        result_position = pos_c;

        vec2 texcoord0 = a_texcoords[0];
        result_texcoord = vec4(texcoord0, 0.0, 1.0) * g_texcoord_transforms[0];

        result_color.rgb = vec3(0.2);
        result_color.a = 1.0;

        result_fog = 0.49;
    #endif
}
