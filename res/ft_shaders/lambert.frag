#version 430 core
// lambert.frag
//DEF
// 0 - Skinning
// 1 - Morph
// 2 - Alpha Test

#define   SKINNING_DEF (_0 == 1)
#define      MORPH_DEF (_1 == 1)
#define ALPHA_TEST_DEF (_2 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 1) uniform sampler2D g_mask;
layout(set = 0, binding = 6) uniform sampler2D g_shadow0;
layout(set = 0, binding = 7) uniform sampler2D g_shadow1;
layout(set = 0, binding = 20) uniform sampler2D g_shadow_depth1;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#include "common_stage.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 1) in vec4 frg_color;
layout(location = 2) in vec4 frg_texcoord_shadow0; //xyz=texcoord_shadow0, w=fog
layout(location = 3) in vec4 frg_texcoord_shadow1; //xyz=texcoord_shadow1, w=

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

    vec4 diff = frg_color;
    vec4 spec = vec4(1.0);

    if (SHADER_FLAGS_STAGE_SHADOW != 0)
        apply_stage_shadow(g_shadow0, g_shadow1, g_shadow_depth1,
            frg_texcoord_shadow0.xyz, frg_texcoord_shadow1.xyz, diff, spec);

    diff *= tex_col;

    result.rgb = apply_fog_stage(diff.rgb, frg_texcoord_shadow0.w);
    result.a = diff.a;

    #if ALPHA_TEST_DEF
        if (result.a <= g_max_alpha.z && result.a != 1.0)
            discard;
    #endif
}
