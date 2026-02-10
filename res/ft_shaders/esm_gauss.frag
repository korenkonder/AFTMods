#version 430 core
#extension GL_EXT_control_flow_attributes : require
// esm_gauss.frag
//DEF
// 0 - Light Proj

#define LIGHT_PROJ_DEF (_0 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_texture;

#if LIGHT_PROJ_DEF
#define MIN_DEPTH   (0.0)
#define MIN_COEF    (0.00001)
#define MAX_DEPTH   (11.0)
#define KERNEL_SIZE (4)
#else
#define MIN_DEPTH   (0.000011)
#define MIN_COEF    (0.00001)
#define MAX_DEPTH   (0.999)
#define KERNEL_SIZE (8)
#endif

layout(location = 0) out float result;

layout(location = 0) in vec2 frg_texcoord;

layout(set = 1, binding = 1) uniform Batch {
    vec4 g_params;
    vec4 g_gauss[2];
};

float sample_depth(in const vec2 tex) {
    float depth = texture(g_texture, tex).x;
    return depth;
}

void main() {
    float dep0;
    float dep1;
    dep0 = sample_depth(frg_texcoord);

    vec4 sum = vec4(MIN_DEPTH, MIN_COEF, 0.0, 1.0);

    sum.w = MAX_DEPTH;
    sum.z = dep0 + g_params.w;

    if (dep0 > sum.w) {
        dep0 = sample_depth(frg_texcoord + g_params.xy);
        dep1 = sample_depth(frg_texcoord - g_params.xy);
        if (dep0 < sum.w)
            sum.xy += vec2(dep0, 1.0);
        if (dep1 < sum.w)
            sum.xy += vec2(dep1, 1.0);

        result = sum.x * (1.0 / sum.y) + g_params.z;
    }
    else {
        sum.y += g_gauss[0][0];
        sum.x += dep0 * g_gauss[0][0];

        vec2 stex0 = frg_texcoord.xy + g_params.xy;
        vec2 stex1 = frg_texcoord.xy - g_params.xy;
        [[unroll]] for (uint i = 1; i < KERNEL_SIZE; i++, stex0 += g_params.xy, stex1 -= g_params.xy) {
            const float coef = g_gauss[i / 4][i % 4];

            sum.y += coef;
            float dep0 = sample_depth(stex0);
            if (dep0 > sum.w) dep0 = sum.z;
            sum.x += dep0 * coef;

            sum.y += coef;
            float dep1 = sample_depth(stex1);
            if (dep1 > sum.w) dep1 = sum.z;
            sum.x += dep1 * coef;
        }

        result = sum.x * (1.0 / sum.y);
    }
}
