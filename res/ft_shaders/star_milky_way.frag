#version 430 core
// star_milky_way.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord;

//ib VertexData {

void main() {
    result = texture(g_texture, frg_texcoord);
}
