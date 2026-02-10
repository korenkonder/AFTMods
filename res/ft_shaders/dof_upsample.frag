#version 430 core
// dof_upsample.frag
//DEF
// 0 - Use F2 CoC

#define USE_F2_COC (_0)

#include "dof_common.glsl"
layout(set = 0, binding = 0) uniform sampler2D g_filtered_rgb_sampler;
layout(set = 0, binding = 1) uniform sampler2D g_filtered_a_sampler;
layout(set = 0, binding = 2) uniform sampler2D g_tile_sampler;
layout(set = 0, binding = 3) uniform sampler2D g_full_res_color_sampler;
layout(set = 0, binding = 4) uniform sampler2D g_full_res_depth_sampler;

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord;

void sort3(
    out vec4 out_min,
    out vec4 out_mid,
    out vec4 out_max,
    const in vec4 p0,
    const in vec4 p1,
    const in vec4 p2) {
    vec4 a = min(p1, p2);
    vec4 b = max(p1, p2);
    vec4 c = max(p0, a);
    out_min = min(p0, a);
    out_mid = min(b, c);
    out_max = max(b, c);
}

vec4 median9(
    const vec4 p0,
    const vec4 p1,
    const vec4 p2,
    const vec4 p3,
    const vec4 p4,
    const vec4 p5,
    const vec4 p6,
    const vec4 p7,
    const vec4 p8) {
    vec4 min012, mid012, max012;
    sort3(min012, mid012, max012, p0, p1, p2);
    vec4 min345, mid345, max345;
    sort3(min345, mid345, max345, p3, p4, p5);
    vec4 min678, mid678, max678;
    sort3(min678, mid678, max678, p6, p7, p8);
    vec4 a = max(max(min012, min345), min678);
    vec4 c = min(min(max678, max345), max012);
    vec4 t0, b, t1;
    sort3(t0, b, t1, mid012, mid345, mid678);
    vec4 m;
    sort3(t0, m, t1, a, b, c);
    return m;
}

vec3 tone_map(in const vec3 color, in const float exposure) {
    return pow(color, vec3(1.0 / 2.2));
}

vec4 fetch_half(in const vec2 texcoord) {
    return vec4(
        textureLod(g_filtered_rgb_sampler, texcoord, 0.0).rgb,
        textureLod(g_filtered_a_sampler, texcoord, 0.0).r);
}

vec4 upsample() {
    //Apply 3x3 tap median filter
    vec2 offset = 1.0 / vec2(1280.0, 720.0);
    if (UPSAMPLE_TAP_NUM <= 3) {
        vec4 p0 = fetch_half(frg_texcoord + vec2(-offset.x, -offset.y));
        vec4 p2 = fetch_half(frg_texcoord + vec2( offset.x, -offset.y));
        vec4 p4 = fetch_half(frg_texcoord + vec2(      0.0,       0.0));
        vec4 p7 = fetch_half(frg_texcoord + vec2(      0.0,  offset.y));
        return median9(p0, p0, p2, p2, p4, p4, p4, p7, p7);
    }
    else if (UPSAMPLE_TAP_NUM <= 4) {
        vec4 p0 = fetch_half(frg_texcoord + vec2(-offset.x, -offset.y));
        vec4 p2 = fetch_half(frg_texcoord + vec2( offset.x, -offset.y));
        vec4 p4 = fetch_half(frg_texcoord + vec2(      0.0,       0.0));
        vec4 p6 = fetch_half(frg_texcoord + vec2(-offset.x,  offset.y));
        vec4 p8 = fetch_half(frg_texcoord + vec2( offset.x,  offset.y));
        return median9(p0, p0, p2, p2, p4, p6, p6, p8, p8);
    }
    else {
        vec4 p0 = fetch_half(frg_texcoord + vec2(-offset.x, -offset.y));
        vec4 p1 = fetch_half(frg_texcoord + vec2(      0.0, -offset.y));
        vec4 p2 = fetch_half(frg_texcoord + vec2( offset.x, -offset.y));
        vec4 p3 = fetch_half(frg_texcoord + vec2(-offset.x,       0.0));
        vec4 p4 = fetch_half(frg_texcoord + vec2(      0.0,       0.0));
        vec4 p5 = fetch_half(frg_texcoord + vec2( offset.x,       0.0));
        vec4 p6 = fetch_half(frg_texcoord + vec2(-offset.x,  offset.y));
        vec4 p7 = fetch_half(frg_texcoord + vec2(      0.0,  offset.y));
        vec4 p8 = fetch_half(frg_texcoord + vec2( offset.x,  offset.y));
        return median9(p0, p1, p2, p3, p4, p5, p6, p7, p8);
    }
}

void main() {
    vec4 full_res = textureLod(g_full_res_color_sampler, frg_texcoord, 0.0);
    full_res.rgb = pow(full_res.rgb, vec3(2.2));
    vec4 half_res = upsample();
    half_res.a = textureLod(g_filtered_a_sampler, frg_texcoord, 0.0).r; //test
    float full_z = textureLod(g_full_res_depth_sampler, frg_texcoord, 0.0).r;
    float full_depth = calculate_depth_m_from_value_in_zbuffer(full_z);
    float full_coc_pixel = calculate_coc_pixel_from_value_in_zbuffer(full_z);
    vec2 tile = textureLod(g_tile_sampler, frg_texcoord, 0.0).rg;
    float tile_min_depth = tile.r;
    float tile_max_coc = tile.g;
    float background_factor = calculate_sample_alpha(full_coc_pixel);
    float foreground_factor = calculate_sample_alpha(tile_max_coc);
    //float foreground_factor = calculate_sample_alpha(calculate_coc_pixel_from_depth(tile_min_depth));
    float combined_factor = mix(background_factor, foreground_factor, half_res.a);
    combined_factor += background_factor;
#if 1
    //Enhance
    combined_factor = 1.0 - combined_factor;
    combined_factor *= combined_factor;
    combined_factor = 1.0 - combined_factor;
    combined_factor *= 4.0; //Suitable
    combined_factor -= 0.2; //Discard the part where the half resolution is thinly combined with the actual resolution because it's not good
    combined_factor = clamp(combined_factor, 0.0, 1.0);
#endif
    result.rgb = mix(half_res.rgb, full_res.rgb, combined_factor);
    result.rgb = max(tone_map(result.rgb, 1.0), vec3(0.0));
#if 1 // Fix alpha
    result.a = full_res.a;
#else
    result.a = 1.0;
#endif
}
