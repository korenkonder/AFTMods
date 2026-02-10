#version 430 core
// simple_refract.frag
//DEF
// 0 - Skinning

#define SKINNING_DEF (_0 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 4) uniform sampler2D g_transparency;

#include "common_shader.glsl"
#include "common_scene.glsl"
#include "common_batch.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_color;
layout(location = 1) in float frg_fog;
layout(location = 2) in vec2 frg_texcoord;

void main() {
    vec4 color_map = texture(g_diffuse, frg_texcoord);
    if (SHADER_FLAGS_TRANSPARENCY == 1)
        color_map.a = texture(g_transparency, frg_texcoord).r;

    if (color_map.a < 0.5)
        discard;

    result.rgb = mix(color_map.rgb * frg_color.rgb, g_fog_height_color.rgb, frg_fog);
    result.a = 1.0 - frg_fog;
}
