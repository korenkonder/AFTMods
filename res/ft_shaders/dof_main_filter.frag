#version 430 core
// dof_main_filter.frag
//DEF
// 0 - Use F2 CoC

#define USE_F2_COC (_0)

#include "dof_common.glsl"
layout(set = 0, binding = 0) uniform sampler2D g_presort; //r=coc[sample], g=background_weight(=depth_cmp*sample_alpha), b=foreground_weight(=depth_cmp*sample_alpha)
layout(set = 0, binding = 1) uniform sampler2D g_color;
layout(set = 0, binding = 2) uniform sampler2D g_tile; //r=min_depth_m, g=max_coc_pixel

layout(std140, set = 1, binding = 1) uniform Texcoords {
    vec2 g_offsets[SAMPLE_MAX_COUNT];
};

layout(location = 0) out vec3 result_color;
layout(location = 1) out float result_alpha;

layout(location = 0) in vec2 frg_texcoord;

#define DOF_SPREAD_TOW_POWER (4.0)
void main() {
    vec4 background = vec4(0.0);
    vec4 foreground = vec4(0.0);
    float v = 0.0;
    const vec2 tile = textureLod(g_tile, frg_texcoord, 0.0).rg;
    const float tile_max_coc_pixel = tile.g;
    const float tile_min_depth = tile.r;
    float coc_pixel_sum = 0.0;
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        vec2 offset_coc_pixel = g_offsets[i].xy; //[pixel]
        float offset_max_radius_pixel = ((SAMPLE_MAX_DIVISION - 1) * 0.5) * SCALE_FROM_SAMPLE_TO_PIXEL;
        offset_coc_pixel /= offset_max_radius_pixel; //Normalization
        offset_coc_pixel *= clamp_coc_pixel(tile_max_coc_pixel);
        vec2 uv_offset = offset_coc_pixel * (1.0 / vec2(1280.0, 720.0));
        vec2 uv = frg_texcoord + uv_offset;
        const vec3 color = textureLod(g_color, uv, 0.0).rgb;
        const vec3 presort = textureLod(g_presort, uv, 0.0).rgb;
        const float sample_coc_sample = clamp_coc_pixel(presort.r * SCALE_FROM_SAMPLE_TO_PIXEL) * SCALE_FROM_PIXEL_TO_SAMPLE;
        const float offset_coc_sample = length(offset_coc_pixel * SCALE_FROM_PIXEL_TO_SAMPLE);
        const float spread_cmp = clamp(sample_coc_sample - offset_coc_sample + 1.0, 0.0, 1.0);
        const float spread_toe = offset_coc_sample <= 1.0 ? pow(spread_cmp, DOF_SPREAD_TOW_POWER) : spread_cmp; //toe can be applied only to the first sample (=center tap)
        const float sample_back_weight = spread_toe * presort.g;
        const float sample_fore_weight = spread_toe * presort.b;
        background.rgb += color * sample_back_weight;
        background.a += sample_back_weight;
        foreground.rgb += color * sample_fore_weight;
        foreground.a += sample_fore_weight;
        coc_pixel_sum += presort.r;
    }
    //In the slide, this is like in 1st line, but it should be divided by sample_alpha() obtained from tile_min_depth like in 2nd line
    const float alpha = clamp(2.0 * (1.0 / SAMPLE_COUNT) * (1.0 / calculate_sample_alpha(tile_max_coc_pixel)) * foreground.a, 0.0, 1.0);
    //const float alpha = clamp(2.0 * (1.0 / SAMPLE_COUNT) * (1.0 / calculate_sample_alpha(calculate_coc_pixel_from_depth(tile_min_depth))) * foreground.a, 0.0, 1.0);
    const float epsilon = 0.0001;
    result_color = mix(
        background.rgb / max(background.a, epsilon),
        foreground.rgb / max(foreground.a, epsilon),
        alpha);
    result_alpha = alpha;
    //result_alpha = coc_pixel_sum / SAMPLE_COUNT / tile_max_coc_pixel;
}
