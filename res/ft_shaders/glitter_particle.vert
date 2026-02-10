#version 430 core
// glitter_particle.vert
//DEF

layout(set = 1, binding = 3) uniform GlitterBatch {
    mat4 g_mvp;
    mat3x4 g_wv;
    vec4 g_fz_proj_row2;
    vec4 g_glitter_blend_color;
    vec4 g_state_material_diffuse;
    vec4 g_state_material_emission;
};

layout(set = 0, binding = 14) uniform sampler2D g_effect_texture;

#include "common_shader.glsl"
#include "common_scene.glsl"

#define COMMON_BATCH
#define g_worldview g_wv
#define g_forward_z_projection_row2 g_fz_proj_row2
#define g_material_state_shininess vec4(0.0)

#include "common_stage.glsl"

#define result_position (gl_Position)

layout(location = 0) out vec4 result_color;
layout(location = 1) out vec4 result_texcoord0; //xy=texcoord0, z=unused, w=position.z
layout(location = 2) out vec4 result_texcoord1; //xy=texcoord1, z=unused, w=fog

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texcoords[2];
layout(location = 3) in vec4 a_color;

void main() {
    vec4 pos_m = vec4(a_position, 1.0);
    vec3 pos_w = pos_m * g_wv;

    vec4 pos_c = pos_m * g_mvp;
    result_position = pos_c;

    result_texcoord0.xy = a_texcoords[0];
    result_texcoord1.xy = a_texcoords[1];

    result_color = a_color * g_glitter_blend_color;

    result_texcoord0.z = 0.0;
    result_texcoord1.z = 0.0;

    result_texcoord0.w = pos_c.z;
    result_texcoord1.w = get_fog_stage(g_effect_texture, pos_m, pos_w);
}
