#version 430 core
// blinn_per_frag.frag
//DEF
// 0 - Skinning
// 1 - Morph
// 2 - Alpha Test

#define   SKINNING_DEF (_0 == 1)
#define      MORPH_DEF (_1 == 1)
#define ALPHA_TEST_DEF (_2 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 1) uniform sampler2D g_mask;
layout(set = 0, binding = 2) uniform sampler2D g_normal;
layout(set = 0, binding = 3) uniform sampler2D g_specular;
layout(set = 0, binding = 5) uniform samplerCube g_envmap;
layout(set = 0, binding = 6) uniform sampler2D g_shadow0;
layout(set = 0, binding = 7) uniform sampler2D g_shadow1;
layout(set = 0, binding = 9) uniform samplerCube g_ibl_diffuse;
layout(set = 0, binding = 10) uniform samplerCube g_ibl_specular;
layout(set = 0, binding = 11) uniform samplerCube g_ibl_specular_rough;
layout(set = 0, binding = 20) uniform sampler2D g_shadow_depth1;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#include "common_ibl.glsl"
#include "common_stage.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec3 frg_normal;
layout(location = 1) in vec3 frg_tangent;
layout(location = 2) in vec3 frg_binormal;
layout(location = 3) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 4) in vec3 frg_eye;
layout(location = 5) in vec4 frg_texcoord_shadow0; //xyz=texcoord_shadow0, w=fog
layout(location = 6) in vec4 frg_texcoord_shadow1; //xyz=texcoord_shadow1, w=
layout(location = 7) in vec4 frg_color;
layout(location = 8) in vec4 frg_offset_color;

vec4 apply_fog_stage(in const vec4 color, in const vec4 color_height, in const float fog) {
    vec4 col;
    if (SHADER_FLAGS_FOG_STAGE == 1) {
        col.rgb = mix(color.rgb, g_fog_depth_color.rgb, fog);
        col.a = color.a;
    } else if (SHADER_FLAGS_FOG_STAGE == 2 || SHADER_FLAGS_FOG_STAGE == 3) {
        col.rgb = mix(color_height.rgb, g_fog_height_color.rgb, fog);
        col.a = color_height.a;
    } else {
        col.rgb = color.rgb;
        col.a = color.a;
    }
    return col;
}

vec4 get_specular_reflection(in const vec3 reflect_vec, in const vec3 spec_map) {
    vec4 spec;
    if (SHADER_FLAGS_ENV_MAP == 1) {
        spec = texture(g_envmap, reflect_vec);
        spec.a = g_material_state_specular.w * g_light_env_stage_specular.w;
        spec.rgb *= spec.a;
        spec.rgb *= spec_map;
    }
    else {
        spec = get_ibl_specular(g_ibl_specular,
            g_ibl_specular_rough, reflect_vec, 1.0 - g_material_state_shininess.x);
        spec.rgb *= spec_map;
    }
    return spec;
}

vec4 get_specular(in const vec2 texcoord, in const vec3 reflect_vec) {
    vec4 spec;
    if (SHADER_FLAGS_SPECULAR == 1)
        spec = get_specular_reflection(reflect_vec, texture(g_specular, texcoord).rgb);
    else
        spec = get_specular_reflection(reflect_vec, vec3(1.0));
    return spec;
}

void main() {
    vec4 tex_col;
    if (SHADER_FLAGS_TEXTURE_COUNT == 1)
        tex_col = texture(g_diffuse, frg_texcoord.xy);
    else if (SHADER_FLAGS_TEXTURE_COUNT == 2)
        tex_col = texture_blend_apply(SHADER_FLAGS_TEXTURE_BLEND,
            texture(g_diffuse, frg_texcoord.xy), texture(g_mask, frg_texcoord.zw));
    else if (SHADER_FLAGS_TEXTURE_COUNT == 0)
        tex_col = g_material_state_diffuse;
    else
        tex_col = vec4(1.0, 0.0, 0.0, 1.0);

    vec3 org_normal;
    if (SHADER_FLAGS_NORMAL == 1) {
        org_normal.xy = texture(g_normal, frg_texcoord.xy).wy * 2.0 - 1.0;
        org_normal.z = 0.8;
    }
    else
        org_normal = vec3(0.0, 0.0, 1.0);

    org_normal = (frg_color.a * 2.0 - 1.0) * org_normal;

    vec3 normal;
    normal.x = dot(frg_tangent, org_normal);
    normal.y = dot(frg_binormal, org_normal);
    normal.z = dot(frg_normal, org_normal);

    vec4 diff = textureLod(g_ibl_diffuse, normal, 0.0);

    vec3 reflect_vec = -reflect(frg_eye, normal);

    vec4 spec = get_specular(frg_texcoord.xy, reflect_vec);
    spec.rgb *= g_light_env_stage_specular.rgb * g_material_state_specular.rgb;

    if (SHADER_FLAGS_STAGE_SHADOW != 0)
        apply_stage_shadow(g_shadow0, g_shadow1, g_shadow_depth1,
            frg_texcoord_shadow0.xyz, frg_texcoord_shadow1.xyz, diff, spec);

    diff *= g_light_env_stage_diffuse;
    diff += frg_color;

    diff *= tex_col;

    result = apply_fog_stage(diff, spec, frg_texcoord_shadow0.w);

    #if ALPHA_TEST_DEF
        if (result.a <= g_max_alpha.z && result.a != 1.0)
            discard;
    #endif
}
