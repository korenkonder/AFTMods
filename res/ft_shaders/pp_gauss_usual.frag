#version 430 core
#extension GL_EXT_control_flow_attributes : require
// pp_gauss_usual.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(set = 1, binding = 1) uniform GaussianCoef {
    vec4 g_coef[8];
};

#include "common_quad.glsl"

#define KERNEL_SIZE (7)

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord;

void main() {
    vec4 sum = texture(g_texture, frg_texcoord);
    sum.rgb *= g_coef[0].rgb;

    vec2 stex0 = frg_texcoord + g_texel_size.xy * g_color.xy;
    vec2 stex1 = frg_texcoord + g_texel_size.xy * -g_color.xy;
    [[unroll]] for (uint i = 1; i < KERNEL_SIZE; i++) {
        sum.rgb += texture(g_texture, stex0).rgb * g_coef[i].rgb;
        stex0 += g_texel_size.xy * g_color.zw;

        sum.rgb += texture(g_texture, stex1).rgb * g_coef[i].rgb;
        stex1 -= g_texel_size.xy * g_color.zw;
    }
    result = sum;
}
