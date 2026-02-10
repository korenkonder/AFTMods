#version 430 core
// snow_particle.vert
//DEF

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


#if USE_VERTEX_ATTRIB
    layout(location = 0) in vec3 a_position;
    layout(location = 1) in float a_size;
#else
    struct Vertex {
        float position[3];
        float size;
    };

    layout(std430, set = 2, binding = 0) readonly buffer VertexBuffer {
        Vertex g_vertices[];
    };
#endif

#define result_position (gl_Position)

layout(location = 0) out vec4 result_texcoord; //xy=texcoord, z=alpha, w=pos_c.w

void main() {
    const int vtx_id = gl_VertexID + start_vertex_location.x;

    vec2 texcoord;
    texcoord.x = float((vtx_id + 1) / 3 % 2);
    texcoord.y = 1.0 - float(vtx_id % 2);

    result_texcoord.xy = texcoord;

    vec2 pos = texcoord * 2.0 - 1.0;

    vec3 vtx_position;
    float vtx_size;
    #if USE_VERTEX_ATTRIB
        vtx_position = a_position;
        vtx_size = a_size;
    #else
        Vertex vtx = g_vertices[vtx_id / 6];

        vtx_position = vec3(vtx.position[0], vtx.position[1], vtx.position[2]);
        vtx_size = vtx.size;
    #endif

    vec4 pos_m = vec4(fract(vtx_position + g_pos_offset.xyz) * g_range_scale.xyz + g_range_offset.xyz, 1.0);

    float pos_v_z = dot(g_view_world_row2, pos_m);
    vec3 dist = vec3(1.0, -pos_v_z, pos_v_z * pos_v_z);
    float size = sqrt(1.0 / dot(g_state_point_attenuation.xyz, dist));

    result_texcoord.z = clamp(size * -0.2 + 0.9, 0.0, 1.0);

    size = clamp(size * vtx_size, g_size_in_projection.z, g_size_in_projection.w);

    vec4 pos_c = pos_m * g_transform;
    pos_c.xy += pos * (size * pos_c.w) * g_size_in_projection.xy;
    result_position = pos_c;
    result_texcoord.w = pos_c.w;
}
