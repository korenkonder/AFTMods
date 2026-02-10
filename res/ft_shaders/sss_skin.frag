#version 430 core
// sss_skin.frag
//DEF
// 0 - Skinning
// 1 - Alpha Test

#define   SKINNING_DEF (_0 == 1)
#define ALPHA_TEST_DEF (_1 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 3) uniform sampler2D g_specular;
layout(set = 0, binding = 9) uniform samplerCube g_ibl_diffuse;
layout(set = 0, binding = 19) uniform sampler2D g_shadow_depth0;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#include "common_chara.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec3 frg_normal;
layout(location = 3) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 4) in vec3 frg_eye;
layout(location = 5) in vec4 frg_texcoord_shadow0; //xyz=texcoord_shadow0, w=
layout(location = 6) in vec4 frg_face_offset; //xyz=unused, w=face_offset
layout(location = 7) in vec4 frg_fog_color; //xyz=fog_color, w=fresnel(unused)

void main() {
    #if ALPHA_TEST_DEF
        vec4 col0 = texture(g_diffuse, frg_texcoord.xy);
        if (col0.a < g_sss_param.a)
            discard;
    #endif

    vec3 normal = normalize(frg_normal);

    vec3 org_normal = normal;
    normal = org_normal * mat3(g_normal_tangent_transforms);

    vec3 npr = vec3(0.0);
    if (SHADER_FLAGS_NPR == 1) {
        if (SHADER_FLAGS_NPR_NORMAL == 1) {
            vec3 _normal = org_normal * mat3(g_worldview) + 2.0;
            npr.z = _normal.y;
            npr.y = g_material_state_emission.w < 0.15 ? 100.0 : _normal.x;
        }
    }

    if (SHADER_FLAGS_SSS_CHARA == 0) {
        if (SHADER_FLAGS_NPR == 1)
            npr.r = g_sss_param.r;
        else
            npr.rgb = g_sss_param.rgb;

        result = vec4(npr, 0.01);
        return;
    }

    vec3 lc = get_light_coef_chara(g_shadow_depth0, org_normal, frg_texcoord_shadow0.xyz);

    float spec = texture(g_specular, frg_texcoord.xy).w;
    vec3 luce = g_light_chara_luce.rgb * ((lc.z * spec * 0.7 + 0.3) * frg_fog_color.w);

    vec3 diff;
    if (lc.y == 1.0)
        diff = textureLod(g_ibl_diffuse, normal, 0.0).rgb;
    else if (lc.y == 0.0)
        diff = textureLod(g_ibl_diffuse, normal, 1.0).rgb;
    else
        diff = get_ibl_diffuse(g_ibl_diffuse, normal, lc.y);

    if (SHADER_FLAGS_NPR != 1) {
        diff *= g_light_env_chara_diffuse.rgb;
        diff += g_light_env_chara_ambient.rgb;
    }

    diff += luce * vec3(1.0, 0.9, 1.0);
    diff += frg_face_offset.w;

    if (spec > 0.99) {
        vec3 tone_curve = vec3(0.0);
        // Missing!
        //if (SHADER_FLAGS_TONE_CURVE == 1)
        //    tone_curve = get_tone_curve(org_normal);
        diff += tone_curve;
    }

    if (SHADER_FLAGS_NPR == 1)
        npr.r = diff.r;
    else
        npr.rgb = diff;

    result = vec4(npr, 1.0);
}
