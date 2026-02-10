#version 430 core
// glitter_particle.frag
//DEF

layout(set = 1, binding = 3) uniform GlitterBatch {
    mat4 g_mvp;
    mat3x4 g_wv;
    vec4 g_fz_proj_row2;
    vec4 g_glitter_blend_color;
    vec4 g_state_material_diffuse;
    vec4 g_state_material_emission;
};

layout(set = 0, binding = 0) uniform sampler2D g_color;
layout(set = 0, binding = 1) uniform sampler2D g_mask;

#include "common_shader.glsl"
#include "common_scene.glsl"

#define COMMON_BATCH
#define g_worldview g_wv
#define g_forward_z_projection_row2 g_fz_proj_row2
#define g_material_state_shininess vec4(0.0)

#include "common_stage.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_color;
layout(location = 1) in vec4 frg_texcoord0; //xy=texcoord0, z=unused, w=position.z
layout(location = 2) in vec4 frg_texcoord1; //xy=texcoord1, z=unused, w=fog

vec4 texture_blend_apply_glitter(in const uint blend, in const vec4 col0, in const vec4 col1) {
    vec4 col;
    if (blend == 0) {
        col.rgb = mix(col0.rgb, col1.rgb, col1.a);
        col.a = col0.a;
    } else if (blend == 1) {
        col = col0 * col1;
    } else if (blend == 2) {
        col.rgb = col0.rgb + col1.rgb;
        col.a = col0.a * col1.a;
    } else if (blend == 3) {
        col.rgb = col0.rgb * col1.rgb;
        col.a = col0.a;
    } else {
        col = col0;
    }
    return col;
}

void main() {
    vec4 col;
    if (SHADER_FLAGS_TEXTURE_COUNT == 1)
        col = texture(g_color, frg_texcoord0.xy);
    else if (SHADER_FLAGS_TEXTURE_COUNT == 2)
        col = texture_blend_apply_glitter(SHADER_FLAGS_TEXTURE_BLEND,
            texture(g_color, frg_texcoord0.xy), texture(g_mask, frg_texcoord1.xy));
    else
        col = g_state_material_diffuse;

    vec4 diff;
    if (SHADER_FLAGS_ALPHA_BLEND == 3) {
        diff.a = col.a * frg_color.a;
        if (diff.a < 0.5)
            discard;
    }
    else if (SHADER_FLAGS_ALPHA_BLEND == 2)
        diff.a = col.a * frg_color.a;
    else if (SHADER_FLAGS_ALPHA_BLEND == 1) {
        diff.a = col.a * frg_color.a;
        if (diff.a < 0.5)
            discard;

        diff.a = 1.0;
    }
    else if (SHADER_FLAGS_ALPHA_BLEND == 0)
        diff.a = 1.0;
    else
        diff.a = 0.0;

    diff.rgb = col.rgb * frg_color.rgb * g_state_material_emission.rgb;

    result.rgb = apply_fog_stage_depth(diff.rgb, frg_texcoord1.w);
    result.a = diff.a;
}
