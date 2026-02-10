#version 430 core
// sky_default.frag
//DEF
// 0 - Morph

#define MORPH_DEF (_0 == 1)

const float cbcr_scale = 256.0001 / 255.0;
const float cbcr_offset = 127.99989 / 255.0 * cbcr_scale;

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 1) uniform sampler2D g_mask;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#include "common_stage.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_color;
layout(location = 1) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 2) in float frg_fog;

// ITU-R BT.709
void to_rgb_709(out vec3 rgb, in vec3 ybr) {
    vec3 _red_coef_709 = vec3( 1.5748, 1.0,     0.0);
    vec3 _grn_coef_709 = vec3(-0.4681, 1.0, -0.1873);
    vec3 _blu_coef_709 = vec3(    0.0, 1.0,  1.8556);
    rgb.r = dot(ybr, _red_coef_709);
    rgb.g = dot(ybr, _grn_coef_709);
    rgb.b = dot(ybr, _blu_coef_709);
}

vec4 sample_tex(in const uint tex_type, sampler2D tex, in const vec2 texcoord) {
    vec4 col;
    if (tex_type == 2) {
        vec4 ybr;
        ybr.yw = textureLod(tex, texcoord, 0.0).rg;
        ybr.xz = textureLod(tex, texcoord, 1.0).gr;
        ybr.xz = ybr.xz * cbcr_scale - cbcr_offset;
        to_rgb_709(col.rgb, ybr.xyz);
        col.a = ybr.w;
    } else if (tex_type == 3) {
        vec3 ybr;
        ybr.y = textureLod(tex, texcoord, 0.0).r;
        ybr.x = textureLod(tex, texcoord, 1.0).r;
        ybr.z = textureLod(tex, texcoord, 2.0).r;
        ybr.xz = ybr.xz * cbcr_scale - cbcr_offset;
        to_rgb_709(col.rgb, ybr.xyz);
        col.a = 1.0;
    } else {
        col = texture(tex, texcoord);
    }
    return col;
}

void main() {
    vec4 tex_col;
    if (SHADER_FLAGS_TEXTURE_COUNT == 0)
        tex_col = g_material_state_diffuse;
    else if (SHADER_FLAGS_TEXTURE_COUNT == 1 || SHADER_FLAGS_TEXTURE_COUNT == 2) {
        vec4 col0 = sample_tex(SHADER_FLAGS_TEX_0_TYPE, g_diffuse, frg_texcoord.xy);

        if (SHADER_FLAGS_TEXTURE_COUNT == 2) {
            vec4 col1 = sample_tex(SHADER_FLAGS_TEX_1_TYPE, g_mask, frg_texcoord.zw);

            tex_col = texture_blend_apply(SHADER_FLAGS_TEXTURE_BLEND, col0, col1);
        }
        else
            tex_col = col0;
    }
    else
        tex_col = vec4(0.0, 0.0, 0.0, 0.0);

    vec3 col = tex_col.rgb * frg_color.rgb;
    col *= g_material_state_emission.rgb;

    result.rgb = apply_fog_stage_depth(col, frg_fog);
    result.a = max(tex_col.a * frg_color.a, g_max_alpha.w);
}
