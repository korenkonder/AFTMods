#version 430 core
// ripple_emit.vert
//DEF
// 0 - Ripple
// 1 - Ripple Emit

#define      RIPPLE_DEF (_0 == 1)
#define RIPPLE_EMIT_DEF (_1 == 1)

layout(set = 1, binding = 0) uniform Scene {
    vec4 g_size_in_projection;
    vec4 g_transform;
    vec4 g_framebuffer_size;
};

#if USE_VERTEX_ATTRIB
    layout(location = 0) in vec3 a_position_alpha; //xy=position, z=alpha
#else
    struct Vertex {
        float position[2];
        float alpha;
    };

    layout(std430, set = 2, binding = 0) readonly buffer VertexBuffer {
        Vertex g_vertices[];
    };
#endif

#define result_position (gl_Position)

layout(location = 0) out float result_alpha;

void main() {
    vec2 pos;
    pos.x = float((gl_VertexID + 1) / 3 % 2);
    pos.y = float(gl_VertexID % 2);
    pos = pos * 2.0 - 1.0;

    vec2 vtx_position;
    float vtx_alpha;
    #if USE_VERTEX_ATTRIB
        vtx_position = a_position_alpha.xy;
        vtx_alpha = a_position_alpha.z;
    #else
        Vertex vtx =  g_vertices[gl_VertexID / 6];

        vtx_position = vec2(vtx.position[0], vtx.position[1]);
        vtx_alpha = vtx.alpha;
    #endif

    result_position = vec4((pos.xy * g_size_in_projection.xy + vtx_position) * g_transform.xy + g_transform.zw, 0.0, 1.0);
    result_alpha = vtx_alpha;
}
