#version 430 core
#extension GL_EXT_control_flow_attributes : require
// exposure_measure.frag

const vec3 p_center_coef = vec3(0.8, 1.0, 1.2);

layout(set = 0, binding = 0) uniform sampler2D g_texture0;
layout(set = 0, binding = 1) uniform sampler2D g_texture1;

layout(location = 0) out vec4 result;

layout(set = 1, binding = 1) uniform ExposureMeasure {
    vec4 g_spot_weight;
    vec4 g_spot_coefficients[32];
};

void main() {
    vec2 sum = vec2(0.0, 0.000000001);
    sum.x += texture(g_texture0, vec2(0.125, 0.125)).w * p_center_coef.x;
    sum.y += p_center_coef.x;
    sum.x += texture(g_texture0, vec2(0.375, 0.125)).w * p_center_coef.y;
    sum.y += p_center_coef.y;
    sum.x += texture(g_texture0, vec2(0.625, 0.125)).w * p_center_coef.y;
    sum.y += p_center_coef.y;
    sum.x += texture(g_texture0, vec2(0.875, 0.125)).w * p_center_coef.x;
    sum.y += p_center_coef.x;
    sum.x += texture(g_texture0, vec2(0.125, 0.375)).w * p_center_coef.y;
    sum.y += p_center_coef.y;
    sum.x += texture(g_texture0, vec2(0.375, 0.375)).w * p_center_coef.z;
    sum.y += p_center_coef.z;
    sum.x += texture(g_texture0, vec2(0.625, 0.375)).w * p_center_coef.z;
    sum.y += p_center_coef.z;
    sum.x += texture(g_texture0, vec2(0.875, 0.375)).w * p_center_coef.y;
    sum.y += p_center_coef.y;
    sum.x += texture(g_texture0, vec2(0.125, 0.625)).w * p_center_coef.y;
    sum.y += p_center_coef.y;
    sum.x += texture(g_texture0, vec2(0.375, 0.625)).w * p_center_coef.z;
    sum.y += p_center_coef.z;
    sum.x += texture(g_texture0, vec2(0.625, 0.625)).w * p_center_coef.z;
    sum.y += p_center_coef.z;
    sum.x += texture(g_texture0, vec2(0.875, 0.625)).w * p_center_coef.y;
    sum.y += p_center_coef.y;
    sum.x += texture(g_texture0, vec2(0.125, 0.875)).w * p_center_coef.x;
    sum.y += p_center_coef.x;
    sum.x += texture(g_texture0, vec2(0.375, 0.875)).w * p_center_coef.y;
    sum.y += p_center_coef.y;
    sum.x += texture(g_texture0, vec2(0.625, 0.875)).w * p_center_coef.y;
    sum.y += p_center_coef.y;
    sum.x += texture(g_texture0, vec2(0.875, 0.875)).w * p_center_coef.x;
    sum.y += p_center_coef.x;
    float center = sum.x * (1.0 / sum.y);

    vec4 spot;
    [[unroll]] for (uint i = 0; i < 4; i++) {
        sum = vec2(0.0, 0.000000001);
        [[unroll]]  for (uint j = 8 * i; j < 8 * (i + 1); j++) {
            sum.x += texture(g_texture1, g_spot_coefficients[j].xy).w * g_spot_coefficients[j].w;
            sum.y += g_spot_coefficients[j].w;
        }
        spot[i] = sum.x * (1.0 / (sum.y * 1.1));
    }

    sum.x = center;
    sum.y = 1.0;
    [[unroll]] for (uint i = 0; i < 4; i++) {
        sum.x += spot[i] * g_spot_weight[i];
        sum.y += g_spot_weight[i];
    }
    result = vec4(sum.x * (1.0 / sum.y));
}
