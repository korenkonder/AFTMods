#version 430 core
// cloth_default.frag
//DEF
// 0 - Skinning
// 1 - Alpha Test

#define   SKINNING_DEF (_0 == 1)
#define ALPHA_TEST_DEF (_1 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 2) uniform sampler2D g_normal;
layout(set = 0, binding = 3) uniform sampler2D g_specular;
layout(set = 0, binding = 4) uniform sampler2D g_transparency;
layout(set = 0, binding = 5) uniform samplerCube g_envmap;
layout(set = 0, binding = 9) uniform samplerCube g_ibl_diffuse;
layout(set = 0, binding = 10) uniform samplerCube g_ibl_specular;
layout(set = 0, binding = 11) uniform samplerCube g_ibl_specular_rough;
layout(set = 0, binding = 12) uniform samplerCube g_ibl_specular_shadowed;
layout(set = 0, binding = 13) uniform samplerCube g_ibl_specular_shadowed_rough;
layout(set = 0, binding = 16) uniform sampler2D g_sss;
layout(set = 0, binding = 19) uniform sampler2D g_shadow_depth0;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#include "common_chara.glsl"
#include "common_ibl.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec3 frg_normal;
layout(location = 1) in vec3 frg_tangent;
layout(location = 2) in vec3 frg_binormal;
layout(location = 3) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 4) in vec3 frg_eye;
layout(location = 5) in vec4 frg_texcoord_shadow0; //xyz=texcoord_shadow0, w=fog
layout(location = 6) in vec4 frg_face_offset; //xyz=unused, w=face_offset
layout(location = 7) in vec4 frg_fog_color; //xyz=fog_color, w=fresnel

void main() {
    vec4 col0 = texture(g_diffuse, frg_texcoord.xy);
    col0.rgb *= g_texture_color_coefficients.x;

    if (SHADER_FLAGS_TRANSPARENCY == 1)
        col0.a = texture(g_transparency, frg_texcoord.zw).a;

    #if ALPHA_TEST_DEF
        if (col0.a < min(g_max_alpha.z, 0.5))
            discard;
    #endif

    col0.a = get_max_alpha(col0.a);

    vec3 normal;
    if (SHADER_FLAGS_NORMAL == 1)
        normal = sample_normal_texture(g_normal, frg_texcoord.xy, frg_normal, frg_tangent, frg_binormal);
    else
        normal = normalize(frg_normal);

    vec3 eye = normalize(frg_eye);
    vec3 org_normal = normal;
    vec3 org_eye = eye;

    normal = org_normal * mat3(g_normal_tangent_transforms);
    eye = org_eye * mat3(g_normal_tangent_transforms);

    vec3 reflect_vec = -reflect(org_eye, org_normal) * mat3(g_normal_tangent_transforms);

    vec3 lc = get_light_coef_chara(g_shadow_depth0, org_normal, frg_texcoord_shadow0.xyz);

    vec2 fres;
    fres.y = clamp(dot(normal, eye), 0.0, 1.0);
    fres.x = pow(1.0 - fres.y * fres.y, 4.0);
    fres.y = pow(1.0 - fres.y, 5.0); 

    vec4 luce;
    luce.rgb = g_light_chara_luce.rgb * (fres.x * frg_fog_color.w * lc.x * 0.75);
    luce.w = (dot(-org_eye, g_light_chara_dir.xyz) * 0.2 + 0.4) * fres.y * 0.5;

    vec4 spec_ratio = g_material_state_specular;

    if (SHADER_FLAGS_SPECULAR != 0)
        spec_ratio *= texture(g_specular, frg_texcoord.xy);

    luce *= clamp(1.3 - 3.0 * dot(spec_ratio.rgb, vec3(1.0)), 0.0, 1.0);
    fres.y *= lc.z * 0.7 + 0.3;

    spec_ratio *= get_fresnel_coefficient(fres.y, 10.0);
    spec_ratio += g_texture_color_coefficients.w;

    vec3 env;
    if (SHADER_FLAGS_ENV_MAP != 0)
        env = texture(g_envmap, reflect_vec).rgb;
    else
        env = vec3(0.0);

    vec3 diff = get_ibl_diffuse(g_ibl_diffuse, normal, lc.y);

    diff *= g_light_env_chara_diffuse.rgb;
    diff += frg_face_offset.w;
    diff += g_light_env_chara_ambient.rgb;

    diff += luce.rgb;

    if (SHADER_FLAGS_TONE_CURVE == 1)
        diff += get_tone_curve(org_normal);

    vec3 sss = texture(g_sss, gl_FragCoord.xy * g_framebuffer_size.xy).rgb;
    diff = mix(sss, diff, g_material_state_ambient.w);

    diff *= col0.rgb;
    diff *= 0.96;

    if (SHADER_FLAGS_SPECULAR_IBL != 0) {
        vec3 ibl_spec = get_ibl_specular(g_ibl_specular,
            g_ibl_specular_rough, reflect_vec, g_material_state_shininess.x).rgb;
        vec3 ibl_spec_shad = get_ibl_specular(g_ibl_specular_shadowed,
            g_ibl_specular_shadowed_rough, reflect_vec, g_material_state_shininess.x).rgb;

        ibl_spec = mix(ibl_spec_shad, ibl_spec, lc.z);
        ibl_spec *= g_light_env_chara_specular.rgb;

        diff += ibl_spec * spec_ratio.rgb;
    }

    #if ALPHA_TEST_DEF
        if (col0.a < min(g_max_alpha.z, 0.5))
            discard;
    #endif

    if (SHADER_FLAGS_ENV_MAP != 0) {
        env *= (lc.z * 0.5 + 0.5) * g_light_env_chara_specular.w;
        diff += env * spec_ratio.w;
    }

    diff += luce.w;

    result.rgb = apply_fog_chara(diff, frg_fog_color.rgb, frg_texcoord_shadow0.w);
    result.a = col0.a;
}
