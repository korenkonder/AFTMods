#version 430 core
// constant.frag
//DEF
// 0 - Skinning
// 1 - Morph
// 2 - Alpha Test

#define   SKINNING_DEF (_0 == 1)
#define      MORPH_DEF (_1 == 1)
#define ALPHA_TEST_DEF (_2 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 1) uniform sampler2D g_mask;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#include "common_stage.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_color;
layout(location = 1) in vec4 frg_offset_color;
layout(location = 2) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 3) in float frg_fog;

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

    vec4 col = tex_col * frg_color;

    #if ALPHA_TEST_DEF
        if (col.a <= g_max_alpha.z && col.a != 1.0)
            discard;
    #endif

    col.rgb = apply_fog_stage(col.rgb, frg_fog);

    result = col;
}
