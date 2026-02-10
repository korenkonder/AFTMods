#version 430 core
// snow_particle.frag

layout(set = 1, binding = 1) uniform Batch {
    vec4 g_pos_offset;
    vec4 g_color;
    ivec4 start_vertex_location;
};

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_texcoord; //xy=texcoord, z=alpha, w=pos_c.w

void main() {
    vec4 col = texture(g_texture, frg_texcoord.xy) * g_color;
    col.a *= frg_texcoord.z;

    result = col;
}
