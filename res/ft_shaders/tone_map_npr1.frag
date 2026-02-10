#version 430 core
// tone_map_npr1.frag
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

layout(set = 0, binding = 0) uniform sampler2D g_texture;
layout(set = 0, binding = 1) uniform sampler2D g_bloom;

#if COMPOSITE_BACK_DEF
layout(set = 0, binding = 6) uniform sampler2D g_back;
layout(set = 0, binding = 14) uniform sampler2D g_scene_depth_texture;
#endif

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_texcoord0; //xy=texcoord0, zw=texcoord1
layout(location = 1) in vec4 frg_texcoord1; //xy=texcoord2, zw=texcoord3
layout(location = 2) in vec4 frg_exposure;
layout(location = 3) in vec4 frg_texcoord2; //xy=texcoord4, z=litproj_enable

void main() {
    vec4 sum = texture(g_texture, frg_texcoord0.xy);
    result.a = sum.a;

    vec3 res;
    res = clamp(sum.rgb * frg_exposure.x * 0.48, vec3(0.0), vec3(1.0));
    #if COMPOSITE_BACK_DEF
        if (texture(g_scene_depth_texture, frg_texcoord0.xy).x - 1.0 >= 0.0) {
            vec3 back = texture(g_back, frg_texcoord0.xy).rgb;
            sum.a = min(sum.a, 1.0);
            if (sum.a >= 0.0)
                res += back * (1.0 - sum.a);
        }
    #endif

    vec3 col = texture(g_bloom, frg_texcoord0.zw).rgb;
    if (frg_exposure.z > 0.0)
        res += col * frg_exposure.x * 0.48;
    res = min(res, vec3(0.96));
    res = clamp(res * g_tone_scale.rgb + g_tone_offset.rgb, vec3(0.0), vec3(1.0));

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
    result.rgb = res;
}
