#ifndef DOF_COMMON
#define DOF_COMMON

#define SCALE_FROM_METER_TO_PIXEL (g_spread_scale.x)
#define SCALE_FROM_METER_TO_SAMPLE (g_spread_scale.y)
#define SCALE_FROM_PIXEL_TO_SAMPLE (g_spread_scale.z)
#define SCALE_FROM_SAMPLE_TO_PIXEL (g_spread_scale.w)
#define TILE_SIZE (g_dof_param.x)
#define PREFILTER_TAP_NUM (g_dof_param.y)
#define SAMPLE_DIVISION (g_dof_param.z)
#define UPSAMPLE_TAP_NUM (g_dof_param.w)
#define SAMPLE_COUNT (SAMPLE_DIVISION * SAMPLE_DIVISION)
#define SAMPLE_MAX_DIVISION (7)
#define SAMPLE_MAX_COUNT (SAMPLE_MAX_DIVISION * SAMPLE_MAX_DIVISION)
#define PI 3.1415926535897932
#define DOF_SINGLE_PIXEL_RADIUS (0.5 * 1.4142135623730950)
#define DOF_DEPTH_SCALE_FOREGROUND 0.0 //Give up on front bokeh at 0 //0.05f //Smaller, more foreground
#define MAX_COC_RADIUS_PIXEL (8)

layout(set = 1, binding = 0) uniform Common {
    uniform vec4 g_depth_params; //x=(n-f)/(nf), y=1/n, z=coc_from_z_scale, w=coc_from_z_offset
    uniform vec4 g_spread_scale; //x=scale_from_meter_to_pixel, y=scale_from_meter_to_sample, z=scale_from_pixel_to_sample, w=scale_from_sample_to_pixel
    uniform vec4 g_depth_params2; //x=distance_to_focus_m, y=focus_range, z=k/(fuzzing_range*fuzzing_range), w=max_coc_radius_in_pixel   //yzw=for_f2
    uniform ivec4 g_dof_param; //x=tile_size, y=prefilter_tap_num, z=sample_division, w=upsample_tap_num
};

float calculate_depth_m_from_value_in_zbuffer(const float value_in_zbuffer) {
    return 1.0 / (value_in_zbuffer * g_depth_params.x + g_depth_params.y); //Linearization
}

vec4 calculate_depth_m_from_value_in_zbuffer(const vec4 value_in_zbuffer) {
    return vec4(1.0) / (value_in_zbuffer * g_depth_params.x + g_depth_params.y);
}

float clamp_coc_pixel(const float radius_pixel) {
    return min(radius_pixel, MAX_COC_RADIUS_PIXEL);
    //return clamp(radius_pixel, -MAX_COC_RADIUS_PIXEL, MAX_COC_RADIUS_PIXEL);
}

#if USE_F2_COC
float calculate_coc_pixel_from_depth(const float linear_depth) {
    float depth_dist = max(abs(g_depth_params2.x - linear_depth) - g_depth_params2.y, 0.0);
    float dof_ratio = 1.0 - exp(depth_dist * depth_dist * g_depth_params2.z);
    return dof_ratio * g_depth_params2.w;
}

float calculate_coc_pixel_from_value_in_zbuffer(const float value_in_zbuffer) {
    float d = calculate_depth_m_from_value_in_zbuffer(value_in_zbuffer);
    return calculate_coc_pixel_from_depth(d);
}
#else
const float TEST_SCALE = 10.0;
float calculate_coc_pixel_from_value_in_zbuffer(const float value_in_zbuffer) {
    return clamp_coc_pixel(abs(value_in_zbuffer * g_depth_params.z
     + g_depth_params.w) * 1000.0 * TEST_SCALE); //Appropriate; converted to 1[m]=100[pixel]. @todo Appropriate
}

float calculate_coc_pixel_from_depth(const float linear_depth) {
    float z = 1.0 / ((linear_depth - g_depth_params.y) * g_depth_params.x); //It's possible to divide by zero. @todo Summarize calculations in advance
    return calculate_coc_pixel_from_value_in_zbuffer(z);
}
#endif

float calculate_sample_alpha(const float sample_coc_in_pixel) {
    const float t = DOF_SINGLE_PIXEL_RADIUS * DOF_SINGLE_PIXEL_RADIUS;
    float coc = sample_coc_in_pixel * sample_coc_in_pixel;
    return 1.0 / (PI * max(t, coc)); //Reciprocal of area of CoC. Energy is conserved by dividing by area
}

float calculate_background_depth_weight(const float depth, const float tile_min_depth) { //1 for background. 0 for foreground
    float d = DOF_DEPTH_SCALE_FOREGROUND * (depth - tile_min_depth);
    return smoothstep(0.0, 1.0, d);
}
#endif  // DOF_COMMON
