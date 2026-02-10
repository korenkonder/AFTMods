#version 430 core
// magnify_cone2.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1

void main() {
    vec4 sum;
    sum = texture(g_texture, frg_texcoord.xy);
    sum += texture(g_texture, frg_texcoord.zw);
    result = sum * 0.5;
}
