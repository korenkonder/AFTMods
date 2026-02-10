#version 430 core
// tone_map.vert
//DEF
// 0 - Tone Map
// 1 - Composite Back

#define   YCC_EXPONENT_DEF (_0 == 0)
#define     RGB_LINEAR_DEF (_0 == 1)
#define    RGB_LINEAR2_DEF (_0 == 2)
#define COMPOSITE_BACK_DEF (_1 == 1)

layout(set = 1, binding = 1) uniform ToneMap {
    vec4 g_exposure;
    vec4 g_fade_color;
    vec4 g_tone_scale; //xyz=tone_scale, w=fade_func
    vec4 g_tone_offset; //xyz=tone_offset, w=inv_tone
    //[0].xyz=texcoord_transforms[0].xyw, [0].w=lens_flare_coef
    //[1].xyz=texcoord_transforms[1].xyw, [1].w=litproj_quality
    //[2].xyz=texcoord_transforms[2].xyw, [2].w=lens_shaft_coef
    //[3].xyz=texcoord_transforms[3].xyw, [3].w=litproj_enable
    vec4 g_texcoord_transforms[4];
};

layout(set = 0, binding = 3) uniform sampler2D g_exposure_tex;

#include "common_quad.glsl"

#define g_fade_func (g_tone_scale.w)
#define g_inv_tone (g_tone_offset.w)
#define result_position (gl_Position)

layout(location = 0) out vec4 result_texcoord0; //xy=texcoord0, zw=texcoord1
layout(location = 1) out vec4 result_texcoord1; //xy=texcoord2, zw=texcoord3
layout(location = 2) out vec4 result_exposure;
layout(location = 3) out vec4 result_texcoord2; //xy=texcoord4, z=litproj_enable, w=unused

void main() {
    vec2 pos;
    pos.x = -1.0 + float(gl_VertexID / 2 % 2) * 2.0;
    pos.y = 1.0 - float(gl_VertexID % 2) * 2.0;
    result_position = vec4(pos, 0.0, 1.0);

    vec2 texcoord = pos * 0.5 + 0.5;
    result_texcoord0.xy = texcoord;
    result_texcoord0.zw = texcoord;

    result_texcoord1.x = dot(g_texcoord_transforms[0].xy, pos) + g_texcoord_transforms[0].z;
    result_texcoord1.y = dot(g_texcoord_transforms[1].xy, pos) + g_texcoord_transforms[1].z;
    result_texcoord1.z = dot(g_texcoord_transforms[2].xy, pos) + g_texcoord_transforms[2].z;
    result_texcoord1.w = dot(g_texcoord_transforms[3].xy, pos) + g_texcoord_transforms[3].z;

    result_texcoord2.xy = (pos * 0.5 + 0.5) * g_texcoord_transforms[1].w;
    result_texcoord2.z = g_texcoord_transforms[3].w;

    float exposure = texture(g_exposure_tex, vec2(0.0)).x;
    exposure = (exp2(-(exposure * 1.8)) * 2.9 + 0.4) * g_exposure.z;

    vec4 ex_col;
    ex_col.x = g_exposure.w > 0.0 ? exposure : g_exposure.x;
    #if COMPOSITE_BACK_DEF
        ex_col.x = max(ex_col.x, 0.0001);
    #endif

    ex_col.y = ex_col.x * g_exposure.y;
    ex_col.z = 1.0;

    #if COMPOSITE_BACK_DEF
        ex_col.w = 1.0 / (ex_col.x * -1.442695);
    #else
        ex_col.w = g_exposure.w;
    #endif

    result_exposure = ex_col;
}
