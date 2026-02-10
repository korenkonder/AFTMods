#version 430 core
// dof_downsample.frag
//DEF
// 0 - Use F2 CoC

#define USE_F2_COC (_0)

#include "dof_common.glsl"
layout(set = 0, binding = 0) uniform sampler2D g_depth_point_sampler;
layout(set = 0, binding = 1) uniform sampler2D g_color_linear_sampler;
layout(set = 0, binding = 2) uniform sampler2D g_tile_sampler;

layout(location = 0) out vec3 result_prefilter;
layout(location = 1) out vec3 result_presort;

layout(location = 0) in vec2 frg_texcoord;

float fetch_max_depth(in const vec2 texcoord) {
    vec4 z = textureGather(g_depth_point_sampler, texcoord); //4 samples with bilinear footprint
    return max(max(z.x, z.y), max(z.z, z.w)); //Select farthest depth
}

float calculate_min_bilateral_weight(
    in const vec2 texcoord,
    in const float depth_center,
    in const float side_center) { //If depth_center is foreground, use only foreground samples. If depth_center is background, use only background samples
    const float depth_scale = 1.0;
#if 1
    vec4 z = calculate_depth_m_from_value_in_zbuffer(textureGather(g_depth_point_sampler, texcoord)); //It might be better to keep it non-linear and choose one with largest difference
    z -= vec4(depth_center);
    z = abs(z);
    float d = max(max(z.x, z.y), max(z.z, z.w)); //Select farthest depth
    return 1.0 / (d * depth_scale + 1.0);
#elif 0//Think!
    vec4 z = textureGather(g_depth_point_sampler, texcoord);
    float max_z = calculate_depth_m_from_value_in_zbuffer(max(max(z.x, z.y), max(z.z, z.w))); //Select farthest depth
    if (0.0 < side_center * (max_z - g_depth_params2.x)) { //On same side (foreground, background) as center tap
        z = calculate_depth_m_from_value_in_zbuffer(z);
        z -= vec4(depth_center);
        z = abs(z);
        float d = max(max(z.x, z.y), max(z.z, z.w)); //Select farthest depth
        return 1.0 / (d * depth_scale + 1.0);
    }
    else
        return 0.0;
#else//Think!
    vec4 z = calculate_depth_m_from_value_in_zbuffer(textureGather(g_depth_point_sampler, texcoord));
    vec4 d = z - vec4(depth_center);
    d = abs(d); //Choose largest component
    float rz, rd;
    if (d.x < d.y) { //y, z, w
        if (d.y < d.z) { //z, w
            if (d.z < d.w) { //w
                rz = z.w;
                rd = d.w;
            }
            else { //z
                rz = z.z;
                rd = d.z;
            }
        }
        else if (d.y < d.w) { //w
            rz = z.w;
            rd = d.w;
        }
        else { //y
            rz = z.y;
            rd = d.y;
        }
    }
    else if (d.x < d.z) { //z, w
        if (d.z < d.w) { //w
            rz = z.w;
            rd = d.w;
        }
        else { //z
            rz = z.z;
            rd = d.z;
        }
    }
    else if (d.x < d.w) { //w
        rz = z.w;
        rd = d.w;
    }
    else { //x
        rz = z.x;
        rd = d.x;
    }
    return (0.0 <= (rz - g_depth_params2.x) * side_center) ? (1.0 / (rd * depth_scale + 1.0)) : 0.0; //Weight 0 if center tap and side (foreground, background) are different
#endif
}

float luminace_from_rgb(in const vec3 rgb) {
    return dot(vec3(0.3, 0.59, 0.11), rgb);
}

vec3 calculate_karis_average(in const vec3 color, const float sharpness) {
    return color * (1.0 / (1.0 + (1.0 - sharpness) * luminace_from_rgb(color)));
}

//9 points are sampling and combining with bilateral filter using depth as a weight
vec3 prefilter(in const float coc_center_pixel, in const float depth_center) {
    const float side_center = depth_center - g_depth_params2.x; //foreground->side_center<0, background->0<side_center
    const float tw = 1280.0;
    const float th = 720.0;

    const float radius_in_pixel = coc_center_pixel * (1.0 / 3.0); //Reason for dividing by 3 is that coc is 49 taps wide and space between these taps is 1/3. Here, 9 taps are used to interpolate between taps
    //Center tap
    vec3 c_t = textureLod(g_color_linear_sampler, frg_texcoord, 0.0).rgb;
    float w_t = 1.0; //Center tap has a weight of 1 because depth difference is 0
    if (PREFILTER_TAP_NUM == 5) {
        //concentric_mapping
        const vec2 offsets[5] = vec2[5](
            vec2(        1.0 / tw,         0.0 / th),
            vec2( 0.30901699 / tw, -0.95105652 / th),
            vec2( 0.30901699 / tw,  0.95105652 / th),
            vec2(-0.80901699 / tw, -0.58778525 / th),
            vec2(-0.80901699 / tw,  0.58778525 / th)
        );
        //Neighborhood tap
        for (int i = 0; i < 5; i++) {
            const vec2 uv = frg_texcoord + offsets[i] * radius_in_pixel;
            float w = calculate_min_bilateral_weight(uv, depth_center, side_center); //Calculate depth, gather4, minimum bilateral weights
            //c_t += calculate_karis_average(textureLod(g_color_linear_sampler, uv, 0.0).rgb, 0.5) * w; //Accumulate colors with that as a weight
            c_t += textureLod(g_color_linear_sampler, uv, 0.0).rgb * w; //Accumulate colors with that as a weight
            w_t += w; //Accumulate weights
        }
    }
    else if (PREFILTER_TAP_NUM == 4) {
        //concentric_mapping
        const vec2 offsets[4] = vec2[4](
            vec2(        1.0 / tw,         0.0 / th),
            vec2(        0.0 / tw,        -1.0 / th),
            vec2(       -1.0 / tw,         0.0 / th),
            vec2(        0.0 / tw,         1.0 / th)
        );
        //Neighborhood tap
        for (int i = 0; i < 4; i++) {
            const vec2 uv = frg_texcoord + offsets[i] * radius_in_pixel;
            float w = calculate_min_bilateral_weight(uv, depth_center, side_center); //Calculate depth, gather4, minimum bilateral weights
            //c_t += calculate_karis_average(textureLod(g_color_linear_sampler, uv, 0.0).rgb, 0.5) * w; //Accumulate colors with that as a weight
            c_t += textureLod(g_color_linear_sampler, uv, 0.0).rgb * w; //Accumulate colors with that as a weight
            w_t += w; //Accumulate weights
        }
    }
    else if (PREFILTER_TAP_NUM == 3) {
        //concentric_mapping
        const vec2 offsets[3] = vec2[3](
            vec2(        1.0 / tw,         0.0 / th),
            vec2(-0.30901699 / tw, -0.86602540 / th),
            vec2(-0.30901699 / tw,  0.86602540 / th)
        );
        //Neighborhood tap
        for (int i = 0; i < 3; i++) {
            const vec2 uv = frg_texcoord + offsets[i] * radius_in_pixel;
            float w = calculate_min_bilateral_weight(uv, depth_center, side_center); //Calculate depth, gather4, minimum bilateral weights
            //c_t += calculate_karis_average(textureLod(g_color_linear_sampler, uv, 0.0).rgb, 0.5) * w; //Accumulate colors with that as a weight
            c_t += textureLod(g_color_linear_sampler, uv, 0.0).rgb * w; //Accumulate colors with that as a weight
            w_t += w; //Accumulate weights
        }
    }
    else {
        //concentric_mapping
        const vec2 offsets[8] = vec2[8](
            vec2(-0.70710678 / tw, -0.70710678 / th),
            vec2(        0.0 / tw,        -1.0 / th),
            vec2( 0.70710678 / tw, -0.70710678 / th),
            vec2(       -1.0 / tw,         0.0 / th),
            vec2(        1.0 / tw,         0.0 / th),
            vec2(-0.70710678 / tw,  0.70710678 / th),
            vec2(        0.0 / tw,         1.0 / th),
            vec2( 0.70710678 / tw,  0.70710678 / th)
        );
        //Neighborhood tap
        for (int i = 0; i < 8; i++) {
            const vec2 uv = frg_texcoord + offsets[i] * radius_in_pixel;
            float w = calculate_min_bilateral_weight(uv, depth_center, side_center); //Calculate depth, gather4, minimum bilateral weights
            //c_t += calculate_karis_average(textureLod(g_color_linear_sampler, uv, 0.0).rgb, 0.5) * w; //Accumulate colors with that as a weight
            c_t += textureLod(g_color_linear_sampler, uv, 0.0).rgb * w; //Accumulate colors with that as a weight
            w_t += w; //Accumulate weights
        }
    }
    c_t *= 1.0 / w_t;
    c_t = pow(c_t, vec3(2.2));
    return c_t;
}

vec3 presort(const float coc_center_pixel, const float depth_center) {
    const vec2 tile = textureLod(g_tile_sampler, frg_texcoord, 0.0).rg;
    const float tile_min_depth = tile.r;
    const float sample_alpha = calculate_sample_alpha(coc_center_pixel);
    const float background_depth_weight = calculate_background_depth_weight(depth_center, tile_min_depth);
    const float foreground_depth_weight = 1.0 - background_depth_weight;
    return vec3(
        coc_center_pixel * SCALE_FROM_PIXEL_TO_SAMPLE,
        sample_alpha * background_depth_weight,
        sample_alpha * foreground_depth_weight);
}

void main() {
    //Find the z of the center tap
    const float z_center = fetch_max_depth(frg_texcoord); //Select the farthest depth on the bilinear footprint //value_in_zbuffer
    const float depth_center = calculate_depth_m_from_value_in_zbuffer(z_center);
    const float coc_center_pixel = calculate_coc_pixel_from_value_in_zbuffer(z_center);
    //prefilter
    result_prefilter = prefilter(coc_center_pixel, depth_center);
    //presort
    result_presort = presort(coc_center_pixel, depth_center);
}
