#version 430 core
// contour.frag

layout(set = 1, binding = 2) uniform ContourCoef {
    vec4 g_contour;
    vec4 g_near_far;
};

layout(set = 0, binding = 0) uniform sampler2D g_color_texture;
layout(set = 0, binding = 1) uniform sampler2D g_depth_texture;

#define SKIN_SUM_MIN (0.5)
#define SKIN_SUM_MAX (7.5)

#define result_depth (gl_FragDepth)

layout(location = 0) out vec4 result_color;

layout(location = 0) in vec2 frg_texcoord;

float get_inner_line(in const bool nrm_mask, in const float edge,
    in const float nrm_mask_flt, in const vec4 nrm1, in const vec4 nrm2, in const vec4 nrm3) {
    if (nrm_mask) {
        vec2 tmp = clamp(nrm1.xz - nrm1.yw, vec2(0.0), vec2(1.0));
        float tmp1 = tmp.y * 0.5 + tmp.x;
        tmp.x = dot(nrm2, vec4(0.7071,  0.7071, -0.7071, -0.7071));
        tmp.y = dot(nrm3, vec4(0.7071, -0.7071, -0.7071,  0.7071));
        tmp.xy = clamp(tmp.xy, vec2(0.0), vec2(1.0));
        tmp1 = clamp(max(tmp1, tmp.x + tmp.y) * 1.2 - 0.6, 0.0, 1.0);
        tmp1 = tmp1 * edge * nrm_mask_flt * 0.8;
        return tmp1;
    } else {
        return 0.0;
    }
}

void main() {
    vec4 col0 = texture(g_color_texture, frg_texcoord);
    if (col0.w == 0.0 || col0.y > 99.0) {
        result_color = vec4(0.0);
        result_depth = 1.0;
        return;
    }

    float skin_mask = float(col0.w > 0.5);

    float depth0 = texture(g_depth_texture, frg_texcoord).x;
    result_depth = depth0;

    depth0 = g_near_far.y * (1.0 / (depth0 - g_near_far.x));
    float edge = pow(clamp(1.0 / depth0 * g_contour.z + (1.0 / 64.0), 0.0, 1.0), 0.5);

    vec4 tmp1;
    vec4 tmp2;
    vec4 tmp3;
    vec4 tmp4;
    vec4 col1;
    vec4 col2;
    vec4 nrm1;
    vec4 nrm2;
    vec4 nrm3;
    tmp1 = textureOffset(g_color_texture, frg_texcoord, ivec2(-1,  0));
    tmp2 = textureOffset(g_color_texture, frg_texcoord, ivec2( 1,  0));
    tmp3 = textureOffset(g_color_texture, frg_texcoord, ivec2( 0, -1));
    tmp4 = textureOffset(g_color_texture, frg_texcoord, ivec2( 0,  1));
    col1 = vec4(tmp1.w, tmp2.w, tmp3.w, tmp4.w);
    nrm1 = vec4(tmp1.y, tmp2.y, tmp3.z, tmp4.z);

    tmp1 = textureOffset(g_color_texture, frg_texcoord, ivec2(-1, -1));
    tmp2 = textureOffset(g_color_texture, frg_texcoord, ivec2( 1,  1));
    tmp3 = textureOffset(g_color_texture, frg_texcoord, ivec2(-1,  1));
    tmp4 = textureOffset(g_color_texture, frg_texcoord, ivec2( 1, -1));
    col2 = vec4(tmp1.w, tmp2.w, tmp3.w, tmp4.w);
    nrm2 = vec4(tmp1.yz, tmp2.yz);
    nrm3 = vec4(tmp3.yz, tmp4.yz);

    bool nrm_mask = any(greaterThanEqual(nrm1 * nrm2 * nrm3, vec4(0.5)));

    vec4 nrm0 = col0.yzyz - 2.0;
    nrm1 = nrm1 - 2.0;
    nrm2 = nrm2 - 2.0;
    nrm3 = nrm3 - 2.0;

    vec4 depth_corn;
    depth_corn.x = textureOffset(g_depth_texture, frg_texcoord, ivec2(-1, -1)).x;
    depth_corn.y = textureOffset(g_depth_texture, frg_texcoord, ivec2( 1,  1)).x;
    depth_corn.z = textureOffset(g_depth_texture, frg_texcoord, ivec2(-1,  1)).x;
    depth_corn.w = textureOffset(g_depth_texture, frg_texcoord, ivec2( 1, -1)).x;

    depth_corn.x = g_near_far.y * (1.0 / (depth_corn.x - g_near_far.x));
    depth_corn.y = g_near_far.y * (1.0 / (depth_corn.y - g_near_far.x));
    depth_corn.z = g_near_far.y * (1.0 / (depth_corn.z - g_near_far.x));
    depth_corn.w = g_near_far.y * (1.0 / (depth_corn.w - g_near_far.x));

    float skin_sum = dot(col1, vec4(1.0)) + dot(col2, vec4(1.0));
    float skin_edge = edge * float((float(skin_sum > SKIN_SUM_MIN) * (1.0 - skin_mask) > 0.0) || ((float(skin_sum < SKIN_SUM_MAX) * skin_mask) > 0.0));

    result_color.y = skin_edge;
    result_color.w = skin_mask;

    vec2 depth_corn_diff = (depth_corn.xz + depth_corn.yw) * 0.5 - depth0;

    vec2 edge_corn = depth_corn_diff - (edge * -3.0 + 4.0) * (g_contour.w * skin_mask + g_contour.x);
    if (any(greaterThan(edge_corn, vec2(0.0)))) {
        result_color.x = clamp(max(edge_corn.x, edge_corn.y) * 300.0 + 0.25, 0.0, 1.0) * edge;
        result_color.z = 0.0;
        return;
    }

    if (any(lessThan(g_contour.y + depth_corn_diff, vec2(0.0)))) {
        result_color.x = 0.0;
        result_color.z = 0.0;
        return;
    }

    float inner_line = get_inner_line(nrm_mask, edge, float(nrm_mask), nrm1, nrm2, nrm3);

    vec2 tmp;
    tmp.x = textureOffset(g_color_texture, frg_texcoord, ivec2(-2, 0)).w;
    tmp.y = textureOffset(g_color_texture, frg_texcoord, ivec2( 2, 0)).w;

    if (tmp.x * tmp.y == 0.0) {
        result_color.x = edge * float(edge > 0.9);
        result_color.z = inner_line;
        return;
    }

    result_color.x = 0.0;
    result_color.z = inner_line;
}
