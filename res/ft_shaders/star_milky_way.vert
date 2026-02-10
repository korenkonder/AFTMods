#version 430 core
// star_milky_way.vert

layout(set = 1, binding = 0) uniform Scene {
    mat4 g_transform;
};

#define result_position (gl_Position)

layout(location = 0) out vec2 result_texcoord;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texcoord;

void main() {
    vec4 pos_m = vec4(a_position, 1.0);

    vec4 pos_c = pos_m * g_transform;
    result_position = pos_c;

    result_texcoord = a_texcoord;
}
