#version 430 core
// sss_filter_gauss_2d.frag

layout(set = 1, binding = 1) uniform GaussianCoef {
    vec4 g_param;
    vec4 g_coef[64];
};

layout(set = 0, binding = 0) uniform sampler2D g_texture;

#include "common_quad.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord;

void main() {
    vec4 col = texture(g_texture, frg_texcoord);
    if (col.a < 0.5) {
        result = col;
        return;
    }

    const vec2 step = g_param.zw * g_texel_size.xy;
    const vec2 step_x = vec2(step.x, 0.0);
    const vec2 step_y = vec2(0.0, step.y);

    vec3 sum = vec3(0.00001);
    vec3 sum_coef = vec3(0.00001);

    uint idx = 0;
    sum += col.rgb * g_coef[idx].rgb;
    sum_coef += g_coef[idx].rgb;
    idx++;

    vec3 coeff;
    vec4 stex = frg_texcoord.xyxy;
    const int count = int(floor(g_param.x));
    for (int i = 0; i < count; i++) {
        stex.xy += step_x;
        stex.zw -= step_x;

        col = texture(g_texture, stex.xy);
        coeff = g_coef[idx].rgb * col.a;
        sum += col.rgb * coeff;
        sum_coef += coeff;

        col = texture(g_texture, stex.zw);
        coeff = g_coef[idx].rgb * col.a;
        sum += col.rgb * coeff;
        sum_coef += coeff;
        idx++;
    }

    vec4 ttex = frg_texcoord.xyxy;
    for (int i = 0; i < count; i++) {
        ttex.xy += step_y;
        ttex.zw -= step_y;

        col = texture(g_texture, ttex.xy);
        coeff = g_coef[idx].rgb * col.a;
        sum += col.rgb * coeff;
        sum_coef += coeff;

        col = texture(g_texture, ttex.zw);
        coeff = g_coef[idx].rgb * col.a;
        sum += col.rgb * coeff;
        sum_coef += coeff;
        idx++;

        vec4 stex0 = ttex.xyxy;
        vec4 stex2 = ttex.zwzw;

        for (int j = 0; j < count; j++) {
            stex0.xy += step_x;
            stex0.zw -= step_x;
            stex2.xy += step_x;
            stex2.zw -= step_x;

            col = texture(g_texture, stex0.xy);
            coeff = g_coef[idx].rgb * col.a;
            sum += col.rgb * coeff;
            sum_coef += coeff;

            col = texture(g_texture, stex0.zw);
            coeff = g_coef[idx].rgb * col.a;
            sum += col.rgb * coeff;
            sum_coef += coeff;

            col = texture(g_texture, stex2.xy);
            coeff = g_coef[idx].rgb * col.a;
            sum += col.rgb * coeff;
            sum_coef += coeff;

            col = texture(g_texture, stex2.zw);
            coeff = g_coef[idx].rgb * col.a;
            sum += col.rgb * coeff;
            sum_coef += coeff;
            idx++;
        }
    }

    result.rgb = sum * (1.0 / sum_coef) * g_color.rgb;
    result.a = 1.0;
}
