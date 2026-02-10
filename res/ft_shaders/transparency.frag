#version 430 core
// transparency.frag

layout(set = 1, binding = 0) uniform Batch {
    vec4 g_opacity; //x=opacity, yzw=unused
};

layout(set = 0, binding = 0) uniform sampler2D g_layerd_color;
layout(set = 0, binding = 1) uniform sampler2D g_base_color;

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord;

void main() {
    vec4 cl = textureLod(g_layerd_color, frg_texcoord, 0.0);
    vec4 cb = textureLod(g_base_color, frg_texcoord, 0.0);
    result = mix(cb, cl, g_opacity.x);
}
