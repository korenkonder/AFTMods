#version 430 core
// hair_npr1.frag
//DEF
// 0 - Skinning
// 1 - Alpha Test

#define   SKINNING_DEF (_0 == 1)
#define ALPHA_TEST_DEF (_1 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 2) uniform sampler2D g_normal;
layout(set = 0, binding = 4) uniform sampler2D g_transparency;
layout(set = 0, binding = 19) uniform sampler2D g_shadow_depth0;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#include "common_chara.glsl"
#include "common_npr_param.glsl"

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
    vec2 normal_t = texture(g_normal, frg_texcoord.xy).wy * 2.0 - 1.0;

    vec3 normal = frg_normal;
    normal += frg_tangent * normal_t.x;
    normal += frg_binormal * normal_t.y;
    normal = normalize(normal);

    vec3 eye = normalize(frg_eye);

    vec3 lc = get_light_coef_chara(g_shadow_depth0, normal, frg_texcoord_shadow0.xyz);

    vec4 col0 = texture(g_diffuse, frg_texcoord.xy);
    col0.a = max(col0.a, g_max_alpha.w);

    if (SHADER_FLAGS_TRANSPARENCY == 1) {
        col0.a = texture(g_transparency, frg_texcoord.zw).r;
        col0.a = max(col0.a, g_max_alpha.w);
    }

    #if ALPHA_TEST_DEF
        if (col0.a <= g_max_alpha.z && col0.a != 1.0)
            discard;
    #endif

    col0.rgb = textureLod(g_diffuse, frg_texcoord.xy, 3.0).rgb;

    vec3 ybr;
    to_ycbcr_601(ybr, col0.rgb);

    vec3 ybr_edge;
    ybr_edge.xz = clamp(ybr.xz * vec2(25.0, -25.0) +  vec2(-0.5, 1.5), vec2(0.0), vec2(1.0));
    ybr_edge.y = ybr_edge.x * ybr_edge.z;
    ybr_edge.z = clamp(ybr.z * 10.0 + 1.5, 0.0, 1.0);

    vec3 col_edge = mix(vec3(0.1, 0.05, 0.05), vec3(0.15, 0.0, 0.08), ybr_edge.z) * ybr_edge.y;

    vec3 ybr_dark = ybr * vec3(0.8, 0.4, 0.8);
    vec3 col_dark;
    to_rgb_601(col_dark, ybr_dark);

    vec3 ybr_light = ybr * vec3(1.3, 1.0, 1.3);
    vec3 col_light;
    to_rgb_601(col_light, ybr_light);

    col_dark += col_edge;
    col_light += col_edge;

    float col_mix = pow(clamp(dot(normal, normalize(vec3(0.6, 1.0, 0.3))), 0.0, 1.0), 0.3) * lc.y;
    vec3 col = mix(col_dark, col_light, col_mix);

    vec3 diff = g_light_env_chara_diffuse.rgb;
    diff += frg_face_offset.w;

    col *= diff;
    col += g_light_env_chara_ambient.rgb;

    if (SHADER_FLAGS_ANISO != 0) {
        vec3 aniso_tangent = normalize(frg_aniso_tangent);
        float aniso_mix = clamp(1.05 - abs(dot(normalize(eye + g_light_chara_dir.xyz), aniso_tangent)), 0.0, 1.0);
        aniso_mix = pow(aniso_mix, 12.0) * (lc.z * 0.75 + 0.25);
        vec3 amb = vec3(1.0);
        float aniso_mix_coef = 0.7;
        col = mix(col, amb, aniso_mix * aniso_mix_coef);
    }

    result.rgb = col;
    result.a = col0.a;
}
