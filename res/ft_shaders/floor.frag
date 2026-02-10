#version 430 core
// floor.frag
//DEF
// 0 - Morph
// 1 - Alpha Test

#define      MORPH_DEF (_0 == 1)
#define ALPHA_TEST_DEF (_1 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 1) uniform sampler2D g_mask;
layout(set = 0, binding = 2) uniform sampler2D g_normal;
layout(set = 0, binding = 3) uniform sampler2D g_specular;
layout(set = 0, binding = 6) uniform sampler2D g_shadow0;
layout(set = 0, binding = 7) uniform sampler2D g_shadow1;
layout(set = 0, binding = 15) uniform sampler2D g_reflect;
layout(set = 0, binding = 20) uniform sampler2D g_shadow_depth1;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#include "common_stage.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec3 frg_normal;
layout(location = 1) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 2) in vec4 frg_texcoord_shadow0; //xyz=texcoord_shadow0, w=fog
layout(location = 3) in vec4 frg_texcoord_shadow1; //xyz=texcoord_shadow1, w=
layout(location = 4) in vec4 frg_color;
layout(location = 5) in vec4 frg_spec_color;

void main() {
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

    vec4 diff = color_map;

    vec2 normal_w;
    if (SHADER_FLAGS_NORMAL == 1)
        normal_w = texture(g_normal, frg_texcoord.xy).xy * 2.0 - 1.0;
    else
        normal_w = frg_normal.xz;

    vec2 screen_uv = gl_FragCoord.xy * g_framebuffer_size.xy + normal_w * g_bump_depth.y;
    vec4 reflect_map = texture(g_reflect, screen_uv);
    vec4 spec_map = texture(g_specular, frg_texcoord.xy);
    vec4 spec = vec4(frg_spec_color.rgb, 0.0) * spec_map + reflect_map * frg_spec_color.w;

    if (SHADER_FLAGS_STAGE_SHADOW == 1)
        apply_stage_shadow(g_shadow0, g_shadow1, g_shadow_depth1,
            frg_texcoord_shadow0.xyz, frg_texcoord_shadow1.xyz, diff, spec);

    diff *= frg_color;

    #if ALPHA_TEST_DEF
        if (color_map.a <= g_max_alpha.z && color_map.a != 1.0)
            discard;
    #endif

    diff.rgb += spec.rgb * spec_map.w;

    result.rgb = apply_fog_stage_depth(diff.rgb, frg_texcoord_shadow0.w);
    result.a = color_map.a;
}
