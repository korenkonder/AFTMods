#version 430 core
// ghost.vert

#define result_position (gl_Position)

layout(location = 0) out vec3 result_texcoord; //xy=texcoord, z=opacity

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec3 a_texcoord; //xy=texcoord, z=opacity

void main() {
    result_position = vec4(a_position * 2.0 - 1.0, 0.0, 1.0);
    result_texcoord = a_texcoord;
}
