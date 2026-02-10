#version 430 core
// copy.frag

layout(set = 1, binding = 1) uniform Batch {
    vec4 g_texture_lod; //yzw=unused
    vec4 g_color_scale;
    vec4 g_color_offset;
};

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord;

void main() {
    result = textureLod(g_texture, frg_texcoord, g_texture_lod.x) * g_color_scale;
}
