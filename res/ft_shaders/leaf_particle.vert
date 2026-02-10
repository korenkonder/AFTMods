#version 430 core
// leaf_particle.vert

layout(set = 1, binding = 0) uniform Scene {
    mat4 g_transform;
    vec4 g_view_pos;
    vec4 g_color;
    vec4 g_light_env_stage_diffuse;
    vec4 g_light_env_stage_specular;
    vec4 g_lit_dir;
    vec4 g_lit_luce;
};

#define result_position (gl_Position)

layout(location = 0) out vec3 result_normal;
layout(location = 1) out vec2 result_texcoord;
layout(location = 2) out vec3 result_eye;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texcoord;
layout(location = 2) in vec3 a_normal;

void main() {
    vec4 pos_m = vec4(a_position, 1.0);

    vec4 pos_c = pos_m * g_transform;
    result_position = pos_c;

    result_normal = a_normal;
    result_texcoord = a_texcoord;
    result_eye = g_view_pos.xyz - pos_m.xyz;
}
