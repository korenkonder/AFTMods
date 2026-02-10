#version 430 core
// sun.vert

layout(set = 1, binding = 0) uniform SunQuad {
    mat4 g_transform;
    vec4 g_emission;
};

#define result_position (gl_Position)

layout(location = 0) out vec2 result_texcoord;

void main() {
    vec2 pos;
    pos.x = -1.0 + float(gl_VertexID / 2 % 2) * 2.0;
    pos.y = 1.0 - float(gl_VertexID % 2) * 2.0;

    vec2 tex = pos * 0.35 + 0.5;

    result_position = vec4(pos, 0.0, 1.0) * g_transform;
    result_texcoord = tex;
}
