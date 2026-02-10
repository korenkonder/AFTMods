#version 430 core
// simple_reflect.frag
//DEF
// 0 - Skinning
// 1 - Morph
// 2 - Alpha Test
// 3 - Clip Plane

#define   SKINNING_DEF (_0 == 1)
#define      MORPH_DEF (_1 == 1)
#define ALPHA_TEST_DEF (_2 == 1)
#define CLIP_PLANE_DEF (_3 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 1) uniform sampler2D g_mask;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#include "common_chara.glsl"
#include "common_stage.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec3 frg_normal;
layout(location = 1) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 2) in vec4 frg_clip_position;
layout(location = 3) in vec4 frg_color;

void main() {
    #if CLIP_PLANE_DEF
        if (dot(frg_clip_position, g_clip_plane) < 0.0)
            discard;
    #endif

    vec4 color_map;
    if (SHADER_FLAGS_TEXTURE_COUNT == 1)
        color_map = texture(g_diffuse, frg_texcoord.xy);
    else if (SHADER_FLAGS_TEXTURE_COUNT == 2)
        color_map = texture_blend_apply(SHADER_FLAGS_TEXTURE_BLEND,
            texture(g_diffuse, frg_texcoord.xy), texture(g_mask, frg_texcoord.zw));
    else if (SHADER_FLAGS_TEXTURE_COUNT == 0)
        color_map = g_material_state_diffuse;
    else
        color_map = vec4(1.0, 0.0, 0.0, 1.0);

    result.a = color_map.a;

    vec3 diff;
    if (SHADER_FLAGS_REFLECT == 0 || SHADER_FLAGS_REFLECT == 1) {
        if (color_map.a < 0.3)
            discard;

        diff = frg_color.rgb;
        diff += g_material_state_emission.rgb;

        if (SHADER_FLAGS_REFLECT == 1) {
            vec3 normal = frg_normal * mat3(g_normal_tangent_transforms);
            if (SHADER_FLAGS_TONE_CURVE == 1)
                diff += get_tone_curve(normal);
        }

        diff *= color_map.rgb;
    }
    else if (SHADER_FLAGS_REFLECT == 2) {
        #if ALPHA_TEST_DEF
            if (color_map.a < min(g_max_alpha.z, 0.5))
                discard;
        #endif

        diff = frg_color.rgb;
        diff *= color_map.rgb;
    }

    #if ALPHA_TEST_DEF
        if (result.a <= g_max_alpha.z && result.a != 1.0)
            discard;
    #endif

    if (SHADER_FLAGS_REFLECT == 1) {
        if (SHADER_FLAGS_CHARA_COLOR == 1)
            diff = apply_chara_color(diff);

        diff *= g_intensity.y;
    }
    else
        diff *= g_intensity.y;

    result.rgb = diff;
}
