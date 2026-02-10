#version 430 core
// star.vert
//DEF

layout(set = 1, binding = 0) uniform Scene {
    mat4 g_transform;
};

layout(set = 1, binding = 1) uniform Batch {
    vec4 g_size_in_projection; //xy=scale, z=unused, w=max
    vec4 g_modifiers; //x=color_scale, y=color_offset, z=pos_scale, w=pos_offset
    vec4 g_thresholds; //x=threshold, yzw=unused
};

#if USE_VERTEX_ATTRIB
    layout(location = 0) in vec3 a_position;
    layout(location = 1) in float a_size;
    layout(location = 2) in vec4 a_color;
#else
    struct Vertex {
        float position[3];
        float size;
        float color[4];
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
    texcoord.x = float((gl_VertexID + 2) / 3 % 2);
    texcoord.y = float(gl_VertexID % 2);

    vec2 pos = texcoord * 2.0 - 1.0;

    vec3 vtx_position;
    float vtx_size;
    vec4 vtx_color;
    #if USE_VERTEX_ATTRIB
        vtx_position = a_position;
        vtx_size = a_size;
        vtx_color = a_color;
    #else
        Vertex vtx =  g_vertices[gl_VertexID / 6];

        vtx_position = vec3(vtx.position[0], vtx.position[1], vtx.position[2]);
        vtx_size = vtx.size;
        vtx_color = vec4(vtx.color[0], vtx.color[1], vtx.color[2], vtx.color[3]);
    #endif

    vec3 color = max(vtx_color.rgb * g_modifiers.x + g_modifiers.y, vec3(0.0));

    float size = vtx_size * g_modifiers.z + g_modifiers.w;
    size = min(size * float(size >= g_thresholds.x), g_size_in_projection.w);

    vec4 pos_c = vec4(vtx_position, 1.0) * g_transform;
    pos_c.xy += pos * (size * pos_c.w) * g_size_in_projection.xy;

    result_position = pos_c;
    result_color = vec4(color, 1.0);
    result_texcoord = texcoord;
}
