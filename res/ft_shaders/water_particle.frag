#version 430 core
// water_particle.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_color;
layout(location = 1) in vec2 frg_texcoord;

void main() {
    result = texture(g_texture, frg_texcoord) * frg_color;
}
