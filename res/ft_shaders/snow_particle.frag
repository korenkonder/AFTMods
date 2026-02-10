#version 430 core
// snow_particle.frag

layout(set = 1, binding = 0) uniform Scene {
    mat4 g_transform;
    vec4 g_view_world_row2;
    vec4 g_size_in_projection;
    vec4 g_state_point_attenuation;
    vec4 g_range_scale;
    vec4 g_range_offset;
    vec4 g_framebuffer_size;
    vec4 g_near_far;
};

layout(set = 1, binding = 1) uniform Batch {
    vec4 g_pos_offset;
    vec4 g_color;
    ivec4 start_vertex_location;
};

layout(set = 0, binding = 0) uniform sampler2D g_texture;
layout(set = 0, binding = 1) uniform sampler2D g_depth_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_texcoord; //xy=texcoord, z=alpha, w=pos_c.w

void main() {
    vec4 col = texture(g_texture, frg_texcoord.xy) * g_color;
    col.a *=  frg_texcoord.z;

    if (frg_texcoord.w > 20.0) {
        result = col;
        return;
    }

    float depth = texture(g_depth_texture, gl_FragCoord.xy * g_framebuffer_size.xy).x;
    depth = (1.0 / (depth - g_near_far.x)) * g_near_far.y;
    col.a *= clamp(abs(depth - frg_texcoord.w) * 0.4 - 0.05, 0.0, 1.0);

    result = col;
}
