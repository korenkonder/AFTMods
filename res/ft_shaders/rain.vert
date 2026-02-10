#version 430 core
// rain.vert
//DEF

layout(set = 1, binding = 0) uniform Scene {
    mat3x4 g_view;
    mat4 g_proj;
    vec4 g_range_scale;
    vec4 g_range_offset;
};

layout(set = 1, binding = 1) uniform Batch {
    vec4 g_pos_offset;
    vec4 g_tangent;
    vec4 g_color;
};

#if USE_VERTEX_ATTRIB
    layout(location = 0) in vec3 a_position;
#else
    struct Vertex {
        float position[3];
    };

    layout(std430, set = 2, binding = 0) readonly buffer VertexBuffer {
        Vertex g_vertices[];
    };
#endif

#define result_position (gl_Position)

layout(location = 0) out vec2 result_texcoord;

void main() {
    vec2 texcoord;
    texcoord.x = float((gl_VertexID + 2) / 3 % 2);
    texcoord.y = float(gl_VertexID % 2);

    vec3 vtx_position;
    #if USE_VERTEX_ATTRIB
        vtx_position = a_position;
    #else
        Vertex vtx =  g_vertices[gl_VertexID / 6];

        vtx_position = vec3(vtx.position[0], vtx.position[1], vtx.position[2]);
    #endif

    vec3 pos_w = fract(vtx_position + g_pos_offset.xyz) * g_range_scale.xyz + g_range_offset.xyz;

    vec3 pos_v = vec4(pos_w, 1.0) * g_view;

    vec3 tangent = g_tangent.xyz * mat3(g_view);
    vec3 binormal = normalize(cross(pos_v, tangent));

    pos_v += texcoord.x * g_tangent.w * binormal;
    pos_v += texcoord.y * tangent;

    vec4 pos_c = vec4(pos_v, 1.0) * g_proj;
    result_position = pos_c;

    result_texcoord = texcoord;
}
