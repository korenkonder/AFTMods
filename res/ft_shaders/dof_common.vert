#version 430 core
// dof_common.vert
//DEF

#define result_position (gl_Position)

layout(location = 0) out vec2 result_texcoord;

void main() {
    vec2 pos;
    pos.x = -1.0 + float(gl_VertexID / 2 % 2) * 2.0;
    pos.y = 1.0 - float(gl_VertexID % 2) * 2.0;
    result_position = vec4(pos, 0.0, 1.0);
    result_texcoord = pos * 0.5 + 0.5;
}
