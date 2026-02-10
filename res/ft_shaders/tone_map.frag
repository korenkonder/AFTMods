#version 430 core
// tone_map.frag
//DEF
// 0 - Tone Map
// 1 - Composite Back

#define   YCC_EXPONENT_DEF (_0 == 0)
#define     RGB_LINEAR_DEF (_0 == 1)
#define    RGB_LINEAR2_DEF (_0 == 2)
#define COMPOSITE_BACK_DEF (_1 == 1)

const vec3 to_ybr = vec3(0.3, 0.59, 0.11);
const vec3 to_rgb = vec3(-0.508475, 1.0, -0.186441);

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

layout(set = 0, binding = 0) uniform sampler2D g_texture;
layout(set = 0, binding = 1) uniform sampler2D g_bloom;
layout(set = 0, binding = 2) uniform sampler2D g_tone_map;
layout(set = 0, binding = 4) uniform sampler2D g_lens_flare;
layout(set = 0, binding = 5) uniform sampler2D g_lens_shaft;

#if COMPOSITE_BACK_DEF
layout(set = 0, binding = 6) uniform sampler2D g_back;
#endif

layout(set = 0, binding = 7) uniform sampler2D g_light_proj;

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_texcoord0; //xy=texcoord0, zw=texcoord1
layout(location = 1) in vec4 frg_texcoord1; //xy=texcoord2, zw=texcoord3
layout(location = 2) in vec4 frg_exposure;
layout(location = 3) in vec4 frg_texcoord2; //xy=texcoord4, z=litproj_enable

void main() {
    vec4 sum = texture(g_texture, frg_texcoord0.xy);
    vec4 col = texture(g_bloom, frg_texcoord0.zw);
    if (frg_exposure.z > 0.0)
        sum.rgb += col.rgb;

    if (g_texcoord_transforms[0].w  > 0.0) {
        vec3 col = texture(g_lens_flare, frg_texcoord1.xy).rgb;
        sum.rgb += col * col * g_texcoord_transforms[0].w;
    }

    if (g_texcoord_transforms[2].w > 0.0) {
        vec3 col = texture(g_lens_shaft, frg_texcoord1.zw).rgb;
        sum.rgb += col * col * g_texcoord_transforms[2].w;
    }

    if (frg_texcoord2.z > 0.0)
        sum.rgb += texture(g_light_proj, frg_texcoord2.xy).rgb;

    vec3 back;
    #if COMPOSITE_BACK_DEF
        back = texture(g_back, frg_texcoord0.xy).rgb * 0.96;
    #endif

    #if YCC_EXPONENT_DEF && COMPOSITE_BACK_DEF
        vec3 tmp;
        tmp.x = dot(back, to_ybr);
        tmp.y = 1.0 - pow(tmp.x, g_tone_offset.w);
        tmp.y = (tmp.y > 0.0 ? log2(tmp.y) : tmp.y) * frg_exposure.w;
        tmp.z = max(tmp.x * 2.0 - 1.0, 0.0);
        tmp.z *= tmp.z;
        tmp.z *= tmp.z;
        tmp.z *= tmp.z;
        tmp.z *= tmp.z;
        tmp.z = 1.0 - tmp.z;
        back -= tmp.x;
        tmp.x *= tmp.z;
        if (tmp.x != 0.0)
            tmp.x = 1.0 / tmp.x;
        back = (back * tmp.x + 1.0) * tmp.y;
        back.y = tmp.y;
        back.g = dot(back, vec3(-0.50847, 1.6949, -0.18644));

        sum.a = min(sum.a, 1.0);
        sum.rgb += back * (1.0 - sum.a);
    #endif

    vec4 res;
    #if RGB_LINEAR2_DEF
        res.rgb = min(sum.rgb * 0.25 * frg_exposure.x, 0.80);
    #elif RGB_LINEAR_DEF
        res.rgb = min(sum.rgb * 0.48 * frg_exposure.x, 0.96);
    #elif YCC_EXPONENT_DEF
        vec3 ybr;
        ybr.y = dot(sum.rgb, to_ybr);
        ybr.xz = sum.rb - ybr.y;
        col.yx = texture(g_tone_map, vec2(ybr.y * frg_exposure.y, 0.0)).yw;
        col.xz = col.x * frg_exposure.x * ybr.xz;
        res.rb = col.xz + col.y;
        res.g = dot(col.rgb, to_rgb);
    #else
        res.rgb = sum.rgb;
    #endif
    res.a = sum.a;

    #if (RGB_LINEAR_DEF || RGB_LINEAR2_DEF) && COMPOSITE_BACK_DEF
        res.a = min(res.a, 1.0);
        res.rgb += back * (1.0 - res.a);
    #endif

    res.rgb = clamp(res.rgb * g_tone_scale.rgb + g_tone_offset.rgb, vec3(0.0), vec3(1.0));

    if (g_fade_color.a > 0.0) {
        const float blend = g_tone_scale.w;
        if (blend == 0.0) {
            res.rgb = mix(res.rgb, g_fade_color.rgb, g_fade_color.a);
        } else if (blend == 2.0) {
            res.rgb += g_fade_color.rgb;
        } else {
            res.rgb *= g_fade_color.rgb;
        }
    }
    result = res;
}
