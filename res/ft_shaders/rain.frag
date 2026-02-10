#version 430 core
// rain.frag

layout(set = 1, binding = 1) uniform Batch {
    vec4 g_pos_offset;
    vec4 g_tangent;
    vec4 g_color;
};

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord;

void main() {
    result = texture(g_texture, frg_texcoord) * g_color;
}
