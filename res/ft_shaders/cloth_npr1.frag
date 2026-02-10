#version 430 core
// cloth_npr1.frag
//DEF
// 0 - Skinning
// 1 - Alpha Test

#define   SKINNING_DEF (_0 == 1)
#define ALPHA_TEST_DEF (_1 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 2) uniform sampler2D g_normal;
layout(set = 0, binding = 3) uniform sampler2D g_specular;
layout(set = 0, binding = 4) uniform sampler2D g_transparency;
layout(set = 0, binding = 19) uniform sampler2D g_shadow_depth0;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#include "common_npr_param.glsl"

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

void main() {
    vec4 col0 = texture(g_diffuse, frg_texcoord.xy);

    if (SHADER_FLAGS_TRANSPARENCY == 1)
        col0.a = texture(g_transparency, frg_texcoord.zw).a;

    #if ALPHA_TEST_DEF
        if (col0.a < min(g_max_alpha.z, 0.5))
            discard;
    #endif

    col0.a = get_max_alpha(col0.a);

    vec3 normal;
    if (SHADER_FLAGS_NORMAL == 1) {
        vec2 normal_t = texture(g_normal, frg_texcoord.xy).wy * 2.0 - 1.0;

        normal = frg_normal;
        normal += frg_tangent * normal_t.x;
        normal += frg_binormal * normal_t.y;
        normal = normalize(normal);
    }
    else
        normal = normalize(frg_normal);

    vec3 eye = normalize(frg_eye);

    vec3 lc = get_light_coef_chara(g_shadow_depth0, normal, frg_texcoord_shadow0.xyz);

    vec3 ybr;
    to_ycbcr_601(ybr, col0.rgb);

    vec3 ybr_dark;
    ybr_dark.xy = ybr.xy;
    ybr_dark.z = ybr.z + clamp(0.12 - sqrt(dot(ybr.xz, ybr.xz) + 0.000001), 0.0, 1.0) * 0.5;
    ybr_dark = ybr_dark * vec3(1.2, 0.8, 1.2) + vec3(0.0, -0.15, 0.01);
    ybr_dark.y = max(ybr_dark.y, 0.1);
    ybr_dark.z = max(ybr_dark.z, ybr_dark.z * 0.4 + 0.04);

    vec3 col_dark;
    to_rgb_601(col_dark, ybr_dark);

    vec3 ybr_light;
    ybr_light.xz = sign(ybr.xz) * pow(abs(ybr.xz * 2.0), vec2(0.85)) * 0.5;
    ybr_light.y = 1.0 + -0.97 * pow(1.0 - ybr.y, 1.5);

    vec3 col_light;
    to_rgb_601(col_light, ybr_light);

    vec3 col = mix(col_dark, col_light, pow(clamp(dot(normal, g_light_chara_dir.xyz), 0.0, 1.0), 0.3) * lc.y);

    vec3 diff = g_light_env_chara_diffuse.rgb;
    diff += frg_face_offset.w;
    diff *= col;

    diff += g_light_env_chara_ambient.rgb;

    #if ALPHA_TEST_DEF
        if (col0.a <= g_max_alpha.z && col0.a != 1.0)
            discard;
    #endif

    if (SHADER_FLAGS_SPECULAR != 0) {
        vec3 dir = normalize(vec3(-1.0, 1.0, -0.5));

        vec4 spec = textureLod(g_specular, frg_texcoord.xy, 3.0);
        spec.x = clamp((max(max(spec.r, spec.g), spec.b) - 0.033) * 8.0, 0.0, 1.0);
        spec.x = clamp(pow(0.05 + abs(dot(normalize(eye + dir), normal)), 1000.0), 0.0, 1.0);
        spec.x *= max(lc.z * 1.2 - 0.5, 0.05);
        diff = mix(diff, g_npr_cloth_spec_color.rgb, spec.x * g_npr_cloth_spec_color.w);
    }

    result.rgb = diff;
    result.a = col0.a;
}
