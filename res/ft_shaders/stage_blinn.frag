#version 430 core
// stage_blinn.frag
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
layout(set = 0, binding = 20) uniform sampler2D g_shadow_depth1;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

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
layout(location = 8) in vec4 frg_spec_color;

void main() {
    vec3 normal;
    if (SHADER_FLAGS_NORMAL == 1)
        normal = sample_normal_texture(g_normal, frg_texcoord.xy, frg_normal, frg_tangent, frg_binormal);
    else
        normal = normalize(frg_normal);

    vec3 eye = normalize(frg_eye);
    vec3 reflect_vec = -reflect(eye, normal);

    vec4 diff = vec4(1.0);
    vec4 spec = vec4(1.0);

    if (SHADER_FLAGS_STAGE_SHADOW != 0)
        apply_stage_shadow(g_shadow0, g_shadow1, g_shadow_depth1,
            frg_texcoord_shadow0.xyz, frg_texcoord_shadow1.xyz, diff, spec);

    vec4 lc;
    lc.y = diff.x;
    lc.z = spec.x;

    vec3 shadow_diff = vec3(0.0);
    if (SHADER_FLAGS_STAGE_AMBIENT != 0)
        shadow_diff = diff.rgb;

    lc.xw = get_light_coef_stage(normal, eye, g_light_stage_dir.xyz).yz;

    vec4 tmp;
    diff.rgb = irradiance_transforms_get_color(normal);
    diff.a = frg_color.a;

    diff.rgb += g_light_stage_diff.rgb * lc.x;
    diff.rgb *= frg_color.rgb;
    diff.rgb += g_material_state_emission.rgb;

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

    diff *= tex_col;

    if (SHADER_FLAGS_STAGE_AMBIENT != 0)
        diff.rgb *= shadow_diff;
    else
        diff.rgb *= lc.y;

    spec.rgb = g_light_stage_spec.rgb * lc.w * lc.z * g_light_env_stage_specular.rgb;

    vec4 spec_ratio = texture(g_specular, frg_texcoord.xy) * frg_spec_color;
    diff.rgb *= 0.96;
    diff.rgb += spec_ratio.rgb * spec.rgb;

    if (SHADER_FLAGS_ENV_MAP != 0) {
        vec3 env = texture(g_envmap, reflect_vec).rgb;
        diff.rgb += env * (g_light_env_stage_specular.w * lc.z) * spec_ratio.w;
    }

    result.rgb = apply_fog_stage_depth(diff.rgb, frg_texcoord_shadow0.w);

    result.a = max(tex_col.a * frg_color.a, g_max_alpha.w);

    #if ALPHA_TEST_DEF
        if (result.a < min(g_max_alpha.z, 0.5))
            discard;
    #endif
}
