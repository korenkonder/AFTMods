#version 430 core
// sun_no_textured.vert

layout(set = 1, binding = 0) uniform SunQuad {
    mat4 g_transform;
    vec4 g_emission;
};

#define result_position (gl_Position)

void main() {
    vec2 pos;
    pos.x = -1.0 + float(gl_VertexID / 2 % 2) * 2.0;
    pos.y = 1.0 - float(gl_VertexID % 2) * 2.0;
    result_position = vec4(pos, 0.0, 1.0) * g_transform;
}
