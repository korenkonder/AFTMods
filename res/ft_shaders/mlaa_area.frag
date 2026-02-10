#version 430 core
#extension GL_EXT_control_flow_attributes : require
// mlaa_area.frag
//DEF
// 0 - Alpha Mask
// 1 - MLAA Search

#define  ALPHA_MASK_DEF (_0 == 1)
#define MLAA_SEARCH     (_1)

#define PIXEL_SIZE (g_texel_size.xy)

const vec2 area_tex_wh = vec2(2.0, 1.0) / (30.0 + float(MLAA_SEARCH * 20));

layout(set = 0, binding = 0) uniform sampler2D g_texture;
layout(set = 0, binding = 1) uniform sampler2D g_area_texture;

#include "common_quad.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord;

float search_x_left(in const vec2 texcoord) {
    float len = 0.0;
    float len_coef;
    uint i;
    vec2 tex;
    float e;
    [[unroll]] for (i = 0, len_coef = 1.0; i <= MLAA_SEARCH; i++) {
        tex = texcoord + vec2(-1.25 - float(i * 2), 0.0) * PIXEL_SIZE;
        e = texture(g_texture, tex).g;
        len += len_coef * clamp(e - 0.5, 0.0, 1.0) * 4.0;
        if (e < 0.9)
            len_coef = 0.0;
    }
    return len;
}

float search_x_right(in const vec2 texcoord) {
    float len = 0.0;
    float len_coef;
    uint i;
    vec2 tex;
    float e;
    [[unroll]] for (i = 0, len_coef = 1.0; i <= MLAA_SEARCH; i++) {
        tex = texcoord + vec2(1.25 + float(i * 2), 0.0) * PIXEL_SIZE;
        e = texture(g_texture, tex).g;
        len += len_coef * clamp(e - 0.5, 0.0, 1.0) * 4.0;
        if (e < 0.9)
            len_coef = 0.0;
    }
    return len;
}

float search_y_up(in const vec2 texcoord) {
    float len = 0.0;
    float len_coef;
    uint i;
    vec2 tex;
    float e;
    [[unroll]] for (i = 0, len_coef = 1.0; i <= MLAA_SEARCH; i++) {
        tex = texcoord + vec2(0.0, 1.25 + float(i * 2)) * PIXEL_SIZE;
        e = texture(g_texture, tex).r;
        len += len_coef * clamp(e - 0.5, 0.0, 1.0) * 4.0;
        if (e < 0.9)
            len_coef = 0.0;
    }
    return len;
}

float search_y_down(in const vec2 texcoord) {
    float len = 0.0;
    float len_coef;
    uint i;
    vec2 tex;
    float e;
    [[unroll]] for (i = 0, len_coef = 1.0; i <= MLAA_SEARCH; i++) {
        tex = texcoord + vec2(0.0, -1.25 - float(i * 2)) * PIXEL_SIZE;
        e = texture(g_texture, tex).r;
        len += len_coef * clamp(e - 0.5, 0.0, 1.0) * 4.0;
        if (e < 0.9)
            len_coef = 0.0;
    }
    return len;
}

void main() {
    vec4 col0 = texture(g_texture, frg_texcoord);
    if (dot(col0.rg, vec2(1.0)) == 0.0) {
        result = vec4(0.0);
        return;
    }

    vec4 len = vec4(0.0);
    float len_coef;
    if (col0.g > 0.0) {
        len.x = search_x_left(frg_texcoord);
        len.y = search_x_right(frg_texcoord);
    }

    if (col0.r > 0.0) {
        len.z = search_y_up(frg_texcoord);
        len.w = search_y_down(frg_texcoord);
    }

    vec2 tmp = len.xz + len.yw;
    tmp.x -= tmp.y;
    if (tmp.x == 0.0) {
        result = vec4(0.0);
        return;
    }

    bvec2 cc = bvec2(tmp.x > 0.0, tmp.x < 0.0);
    vec4 texc1 = len.xxyy * vec4(-1.0, 0.0, 1.0,  0.0) + vec4( 0.0 , -0.25,   1.0, -0.25);
    vec4 texc2 = len.zzww * vec4( 0.0, 1.0, 0.0, -1.0) + vec4(-0.25,  1.0 , -0.25,  0.0 );
    vec4 texc = (cc.y ? texc2 : texc1) * g_texel_size.xyxy + frg_texcoord.xyxy;
    vec4 edge;
    edge.xy = texture(g_texture, texc.xy).xy;
    edge.zw = texture(g_texture, texc.zw).xy;
    edge = len * area_tex_wh.x + area_tex_wh.y + edge.xzyw * 0.8;

    vec2 area = texture(g_area_texture, cc.y ? edge.zw : edge.xy).xy;
    result = mix(vec4(0.0), area.xyxy, cc.xxyy);
}
