#version 430 core
// fog_ptcl.vert
//DEF

#if USE_VERTEX_ATTRIB
    layout(location = 0) in vec2 a_position;
    layout(location = 1) in vec4 a_color;
    layout(location = 2) in float a_size;
#else
    struct Vertex {
        float position[2];
        float color[4];
        float size;
    };

    layout(std430, set = 2, binding = 0) readonly buffer VertexBuffer {
        Vertex g_vertices[];
    };
#endif

#define result_position (gl_Position)

layout(location = 0) out vec4 result_color;
layout(location = 1) out vec2 result_texcoord;

void main() {
    vec2 texcoord;
    texcoord.x = float((gl_VertexID + 1) / 3 % 2);
    texcoord.y = float(gl_VertexID % 2);

    vec2 pos;
    pos.x = texcoord.x;
    pos.y = 1.0 - texcoord.y;
    pos = pos * 2.0 - 1.0;

    vec2 vtx_position;
    vec4 vtx_color;
    float vtx_size;
    #if USE_VERTEX_ATTRIB
        vtx_position = a_position;
        vtx_color = a_color;
        vtx_size = a_size;
    #else
        Vertex vtx =  g_vertices[gl_VertexID / 6];

        vtx_position = vec2(vtx.position[0], vtx.position[1]);
        vtx_color = vec4(vtx.color[0], vtx.color[1], vtx.color[2], vtx.color[3]);
        vtx_size = vtx.size;
    #endif

    result_position = vec4(vtx_position + pos * vtx_size, 0.0, 1.0);
    result_color = vtx_color;
    result_texcoord = texcoord;
}
