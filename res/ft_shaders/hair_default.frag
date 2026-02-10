#version 430 core
// hair_aniso.frag
//DEF
// 0 - Skinning
// 1 - Alpha Test

#define   SKINNING_DEF (_0 == 1)
#define ALPHA_TEST_DEF (_1 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 1) uniform sampler2D g_translucency;
layout(set = 0, binding = 2) uniform sampler2D g_normal;
layout(set = 0, binding = 3) uniform sampler2D g_specular;
layout(set = 0, binding = 4) uniform sampler2D g_transparency;
layout(set = 0, binding = 9) uniform samplerCube g_ibl_diffuse;
layout(set = 0, binding = 19) uniform sampler2D g_shadow_depth0;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#include "common_chara.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec3 frg_normal;
layout(location = 1) in vec3 frg_tangent;
layout(location = 2) in vec3 frg_binormal;
layout(location = 3) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 4) in vec3 frg_eye;
layout(location = 5) in vec4 frg_texcoord_shadow0; //xyz=texcoord_shadow0, w=fog
layout(location = 6) in vec4 frg_face_offset; //xyz=unused, w=face_offset
layout(location = 7) in vec4 frg_fog_color; //xyz=fog_color, w=fresnel
layout(location = 8) in vec3 frg_aniso_tangent;

void main() {
    if (SHADER_FLAGS_ANISO == 0) {
        result = vec4(1.0, 0.0, 0.0, 1.0);
        return;
    }

    vec3 normal = sample_normal_texture(g_normal, frg_texcoord.xy, frg_normal, frg_tangent, frg_binormal);

    vec3 rot_normal = normal * mat3(g_normal_tangent_transforms);

    vec3 eye = normalize(frg_eye);

    vec3 lc = get_light_coef_chara(g_shadow_depth0, normal, frg_texcoord_shadow0.xyz);

    vec4 tmp;
    tmp.x = clamp(dot(normal, eye), 0.0, 1.0);
    tmp.x = pow(1.0 + tmp.x * -tmp.x, 8.0) * frg_fog_color.w;

    vec3 luce = g_light_chara_luce.rgb * tmp.x;

    if (SHADER_FLAGS_TRANSLUCENCY == 1)
        luce *= texture(g_translucency, frg_texcoord.zw).rgb;

    luce *= lc.z;

    vec3 diff = get_ibl_diffuse(g_ibl_diffuse, rot_normal, lc.y);

    vec4 col0 = texture(g_diffuse, frg_texcoord.xy);
    col0.rgb *= g_texture_color_coefficients.x;

    diff *= g_light_env_chara_diffuse.rgb;
    diff += frg_face_offset.w;
    diff += g_light_env_chara_ambient.rgb;

    if (SHADER_FLAGS_TONE_CURVE == 1)
        diff += get_tone_curve(normal);

    diff *= col0.rgb;

    vec3 aniso_tangent = normalize(frg_aniso_tangent);
    aniso_tangent = normalize(aniso_tangent - dot(aniso_tangent, normal) * normal);

    tmp.x = dot(aniso_tangent, g_light_chara_dir.xyz);
    tmp.y = dot(aniso_tangent, eye);
    tmp.z = -tmp.x;
    tmp = tmp.xyxz * tmp.xyyy + vec4(-1.01, -1.01, 0.0, 0.0);

    tmp.xy = sqrt(-tmp.xy);
    tmp.yz = clamp(tmp.xx * tmp.yy - tmp.zw, 0.0, 1.0);
    tmp.yz = pow(tmp.yz, g_shininess.xx);

    vec3 aniso_coef;
    aniso_coef.x = tmp.x * tmp.x;
    aniso_coef.yz = vec2(dot(normal, g_light_chara_dir.xyz)) * vec2(0.7, -0.7) + vec2(0.3, 0.3);
    aniso_coef.yz = tmp.yz * clamp(aniso_coef.yz, vec2(0.0), vec2(1.0));
    aniso_coef = aniso_coef * vec3(0.25, 0.18, 0.05) + vec3(0.75, 0.0, 0.0);

    vec3 spec = g_light_chara_spec.rgb * aniso_coef.y * lc.z + g_light_chara_back.rgb * aniso_coef.z;
    spec += g_texture_color_coefficients.w;
    if (SHADER_FLAGS_SPECULAR == 1)
        spec *= texture(g_specular, frg_texcoord.xy).rgb;

    diff *= aniso_coef.x;
    diff += luce * 0.5;

    diff += spec * g_material_state_specular.rgb;

    result.rgb = apply_fog_chara(diff, frg_fog_color.rgb, frg_texcoord_shadow0.w);

    result.a = max(col0.a, g_max_alpha.w);

    if (SHADER_FLAGS_TRANSPARENCY == 1) {
        col0.a = texture(g_transparency, frg_texcoord.zw).r;
        result.a = max(col0.a, g_max_alpha.w);
    }

    #if ALPHA_TEST_DEF
        if (result.a <= g_max_alpha.z && result.a != 1.0)
            discard;
    #endif
}
