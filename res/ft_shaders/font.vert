#version 430 core
// font.vert

layout(set = 1, binding = 0) uniform Scene {
    mat4 g_transform;
    vec4 g_framebuffer_size;
};

#define result_position (gl_Position)

layout(location = 0) out vec4 result_color;
layout(location = 1) out vec2 result_texcoord;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texcoord;

void main() {
    result_position = vec4(a_position, 1.0) * g_transform;
    result_color = a_color;
    result_texcoord = a_texcoord;
}
