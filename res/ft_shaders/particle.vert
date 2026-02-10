#version 430 core
// particle.vert

layout(set = 1, binding = 0) uniform Scene {
    mat4 g_transform;
    vec4 g_view_pos;
    vec4 g_light_env_chara_diffuse;
    vec4 g_light_env_chara_specular;
};

#define result_position (gl_Position)

layout(location = 0) out vec3 result_normal;
layout(location = 1) out vec4 result_color;
layout(location = 2) out vec2 result_texcoord;
layout(location = 3) out vec3 result_eye;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec4 a_color;
layout(location = 3) in vec2 a_texcoord;

void main() {
    vec4 pos_m = vec4(a_position, 1.0);

    vec4 pos_c = pos_m * g_transform;
    result_position = pos_c;

    result_normal = a_normal;
    result_color = a_color;
    result_texcoord = a_texcoord;
    result_eye = normalize(g_view_pos.xyz - pos_m.xyz);
}
