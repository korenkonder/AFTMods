#version 430 core
// sprite.frag
//DEF
// 0 - Tex 0 Type
// 1 - Tex 1 Type
// 2 - Combiner

#define TEX_0_TYPE (_0)
#define TEX_1_TYPE (_1)
#define   COMBINER (_2)

const float cbcr_scale = 256.0 / 255.0;
const float cbcr_offset = 128.0 / 255.0 * cbcr_scale;

layout(set = 1, binding = 0) uniform Scene {
    mat4 g_transform;
    vec4 g_framebuffer_size;
};

layout(set = 0, binding = 0) uniform sampler2D g_texture0;
layout(set = 0, binding = 1) uniform sampler2D g_texture1;
layout(set = 0, binding = 7) uniform sampler2D g_overlay_dest_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_color;
layout(location = 1) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1

// ITU-R BT.709
void to_rgb_709(out vec3 rgb, in vec3 ybr) {
    vec3 _red_coef_709 = vec3( 1.5748, 1.0,     0.0);
    vec3 _grn_coef_709 = vec3(-0.4681, 1.0, -0.1873);
    vec3 _blu_coef_709 = vec3(    0.0, 1.0,  1.8556);
    rgb.r = clamp(dot(ybr, _red_coef_709), 0.0, 1.0);
    rgb.g = clamp(dot(ybr, _grn_coef_709), 0.0, 1.0);
    rgb.b = clamp(dot(ybr, _blu_coef_709), 0.0, 1.0);
}

vec4 sample_tex(in const int tex_type, sampler2D tex, in const vec2 texcoord) {
    vec4 col;
    if (tex_type == 1)
        col = texture(tex, texcoord);
    else if (tex_type == 2) {
        vec4 ybr;
        ybr.yw = textureLod(tex, texcoord, 0.0).rg;
        ybr.xz = textureLod(tex, texcoord, 1.0).gr;
        ybr.xz = ybr.xz * cbcr_scale - cbcr_offset;
        to_rgb_709(col.rgb, ybr.xyz);
        col.a = ybr.w;
    }
    else if (tex_type == 3) {
        vec3 ybr;
        ybr.y = textureLod(tex, texcoord, 0.0).r;
        ybr.x = textureLod(tex, texcoord, 1.0).r;
        ybr.z = textureLod(tex, texcoord, 2.0).r;
        ybr.xz = ybr.xz * cbcr_scale - cbcr_offset;
        to_rgb_709(col.rgb, ybr.xyz);
        col.a = 1.0;
    }
    else
        col = vec4(1.0);
    return col;
}

vec4 combine(in const int combiner, in vec4 col, in const vec2 position) {
    if (combiner == 1) {
        col.rgb = (col.rgb - 1.0) * col.a + 1.0;
    }
    else if (combiner == 2) {
        vec3 col3 = textureLod(g_overlay_dest_texture, position * g_framebuffer_size.xy, 0.0).rgb;
        vec3 col1 = 2.0 * (col3 * col.rgb);
        vec3 col2 = 2.0 * (col3 + col.rgb) - col1 - 1.0;
        col.rgb = mix(col2, col1, lessThan(col3, vec3(0.5)));
    }
    return col;
}

void main() {
    vec4 col0 = vec4(1.0);
    if (TEX_0_TYPE != 0) {
        col0 = sample_tex(TEX_0_TYPE, g_texture0, frg_texcoord.xy);

        if (TEX_1_TYPE != 0) {
            vec4 col1 = sample_tex(TEX_1_TYPE, g_texture1, frg_texcoord.zw);
            col0.rgb = col1.rgb;
            col0.a *= col1.a;
        }
    }

    result = combine(COMBINER, col0 * frg_color, gl_FragCoord.xy);
}
