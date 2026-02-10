#version 430 core
// cloth_aniso.frag
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

    vec3 normal = sample_normal_texture(g_normal, frg_texcoord.xy, frg_normal, frg_tangent, frg_binormal);
    vec3 eye = normalize(frg_eye);
    vec3 tangent = normalize(frg_tangent);

    vec3 org_normal = normal;
    vec3 org_eye = eye;
    vec3 org_tangent = tangent;

    normal = org_normal * mat3(g_normal_tangent_transforms);
    eye = org_eye * mat3(g_normal_tangent_transforms);
    tangent = org_tangent * mat3(g_normal_tangent_transforms);

    vec3 lc = get_light_coef_chara(g_shadow_depth0, org_normal, frg_texcoord_shadow0.xyz);

    lc.x = lc.x * 0.6 + 0.4;

    vec3 aniso_normal = normalize(tangent - dot(normal, tangent) * normal);
    if (SHADER_FLAGS_ANISO == 1)
        aniso_normal = mix(aniso_normal, normal, 0.1);
    else if (SHADER_FLAGS_ANISO == 3)
        aniso_normal = mix(aniso_normal, normal, 0.9);
    else if (SHADER_FLAGS_ANISO == 2)
        aniso_normal = mix(aniso_normal, normal, 0.5);
    aniso_normal = normalize(aniso_normal);

    float cos_theta = dot(aniso_normal, eye);

    vec3 reflect_vec = eye - 2.0 * cos_theta * aniso_normal;
    vec2 tmp;
    tmp.y = sqrt(1.00001 - cos_theta * cos_theta);

    float fres = dot(aniso_normal, -eye) * 0.9 + 0.1;
    fres *= fres;
    fres *= fres;

    vec4 spec_ratio = get_fresnel_coefficient(fres, 2.0);
    spec_ratio *= g_material_state_specular;

    tmp.x = clamp(dot(normal, eye), 0.0, 1.0);
    tmp.x = pow(1.0 + tmp.x * -tmp.x, 4.0) * lc.x;
    tmp.x *= g_fresnel_coefficients.z;
    tmp.x *= tmp.y;

    vec3 luce = textureLod(g_ibl_diffuse, -eye, 0.0).rgb * tmp.x;

    vec3 env;
    if (SHADER_FLAGS_ENV_MAP != 0)
        env = texture(g_envmap, reflect_vec).rgb;
    else
        env = vec3(0.0);

    vec3 diff = get_ibl_diffuse(g_ibl_diffuse, normal, lc.y);

    diff *= g_light_env_chara_diffuse.rgb;
    diff += frg_face_offset.w;
    diff += g_light_env_chara_ambient.rgb;

    diff += luce * 0.5;

    if (SHADER_FLAGS_TONE_CURVE == 1)
        diff += get_tone_curve(org_normal);

    if (SHADER_FLAGS_ANISO == 1)
        tmp.y = tmp.y * 0.6 + 0.4;
    else if (SHADER_FLAGS_ANISO == 2)
        tmp.y = tmp.y * 0.7 + 0.3;
    else if (SHADER_FLAGS_ANISO == 3)
        tmp.y = tmp.y * 0.8 + 0.2;

    diff *= mix(g_material_state_ambient.rgb, col0.rgb, tmp.y);

    vec3 ibl_spec = get_ibl_specular(g_ibl_specular,
        g_ibl_specular_rough, reflect_vec, g_material_state_shininess.x).rgb;
    vec3 ibl_spec_shad = get_ibl_specular(g_ibl_specular_shadowed,
        g_ibl_specular_shadowed_rough, reflect_vec, g_material_state_shininess.x).rgb;

    ibl_spec = mix(ibl_spec_shad, ibl_spec, lc.z);
    ibl_spec *= g_light_env_chara_specular.rgb;

    if (SHADER_FLAGS_SPECULAR != 0)
        spec_ratio *= texture(g_specular, frg_texcoord.xy);

    spec_ratio.rgb += g_texture_color_coefficients.w;

    #if ALPHA_TEST_DEF
        if (col0.a <= g_max_alpha.z && col0.a != 1.0)
            discard;
    #endif

    diff *= 0.96;
    diff += ibl_spec * spec_ratio.rgb;

    if (SHADER_FLAGS_ENV_MAP != 0) {
        env *= lc.z * 0.5 + 0.5;
        diff += env * spec_ratio.w;
    }

    diff += luce * 0.5;

    result.rgb = apply_fog_chara(diff, frg_fog_color.rgb, frg_texcoord_shadow0.w);
    result.a = col0.a;
}
