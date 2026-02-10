#version 430 core
// ghost.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec3 frg_texcoord; //xy=texcoord, z=opacity

void main() {
    result = texture(g_texture, frg_texcoord.xy) * frg_texcoord.z;
}
