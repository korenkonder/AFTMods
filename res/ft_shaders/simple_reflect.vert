#version 430 core
// simple_reflect.vert
//DEF
// 0 - Skinning
// 1 - Morph
// 2 - Alpha Test
// 3 - Clip Plane

#define   SKINNING_DEF (_0 == 1)
#define      MORPH_DEF (_1 == 1)
#define ALPHA_TEST_DEF (_2 == 1)
#define CLIP_PLANE_DEF (_3 == 1)

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

layout(location = 0) out vec3 result_normal;
layout(location = 1) out vec4 result_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 2) out vec4 result_clip_position;
layout(location = 3) out vec4 result_color;

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec4 a_color;
layout(location = 8) in vec2 a_texcoords[2];

#if MORPH_DEF
layout(location = 5) in vec4 a_morph_color;
layout(location = 13) in vec2 a_morph_texcoords[2];
#endif

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
        pos_m = vec4(vec4(a_position, 1.0) * g_worlds, 1.0);
        vec3 normal_m = a_normal;

        normal_w = normal_m * mat3(g_worlds);
    #endif

    if (SHADER_FLAGS_REFLECT == 0 || SHADER_FLAGS_REFLECT == 1)
        pos_m.xyz += g_clip_plane.xyz * (dot(vec4(pos_m.xyz, 1.0), -g_clip_plane) * 2.0);

    result_clip_position = pos_m;

    vec4 pos_c = pos_m * g_projection_view;
    result_position = pos_c;

    if (SHADER_FLAGS_REFLECT == 0 || SHADER_FLAGS_REFLECT == 1) {
        vec3 diff = vec3(clamp(dot(normal_w, g_light_reflect_dir.xyz), 0.0, 1.0));
        vec3 amb = vec3(clamp(dot(normal_w, -g_light_reflect_dir.xyz), 0.0, 1.0));

        diff *= g_light_env_reflect_diffuse.rgb * g_material_state_diffuse.rgb;
        diff += g_light_env_reflect_ambient.rgb;
        amb *= g_light_env_reflect_ambient.rgb;

        result_color.rgb = diff + amb;
        result_color.a = 1.0;

        vec2 texcoord0 = a_texcoords[0];
        result_texcoord.xy = vec4(texcoord0, 0.0, 1.0) * g_texcoord_transforms[0];
        result_texcoord.zw = vec2(0.0);

        result_normal = normal_w;
    }
    else {
        vec4 diff;
        diff.rgb = irradiance_transforms_get_color(vec3(normal_w.x, -normal_w.y , normal_w.z));
        diff.rgb *= g_light_env_stage_diffuse.rgb * g_material_state_diffuse.rgb;
        diff.rgb += g_material_state_ambient.rgb;
        diff.a = g_material_state_diffuse.a;

        #if MORPH_DEF
            diff = apply_morph_color(diff, a_color, a_morph_color);
        #else
            diff *= a_color;
        #endif
        result_color = diff;

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

        result_normal = vec3(0.0);
    }
}
