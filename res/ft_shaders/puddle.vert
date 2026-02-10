#version 430 core
// puddle.vert
//DEF

layout(set = 0, binding = 14) uniform sampler2D g_effect_texture;

#include "common_shader.glsl"
#include "common_scene.glsl"
#include "common_batch.glsl"

#include "common_stage.glsl"

#define result_position (gl_Position)

layout(location = 0) out vec3 result_normal;
layout(location = 1) out vec4 result_color;
layout(location = 2) out vec4 result_spec_color;
layout(location = 3) out vec2 result_texcoord;
layout(location = 4) out vec3 result_eye;
layout(location = 5) out vec4 result_texcoord_shadow0; //xyz=texcoord_shadow0, w=fog
layout(location = 6) out vec4 result_texcoord_shadow1; //xyz=texcoord_shadow1, w=

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec4 a_color;
layout(location = 8) in vec2 a_texcoords[2];

void main() {
    vec4 pos_m = vec4(a_position, 1.0);

    vec4 pos_c = pos_m * g_transforms;
    result_position = pos_c;

    vec3 pos_w = pos_m * g_worlds;

    vec3 normal_w = a_normal * mat3(g_worlds);
    result_normal = normal_w;

    result_texcoord_shadow0.w = get_fog_stage(g_effect_texture, pos_m, pos_w);
    result_texcoord_shadow1.w = 0.0;

    vec2 texcoord0 = a_texcoords[0];
    result_texcoord = vec4(texcoord0, 0.0, 1.0) * g_texcoord_transforms[0];

    vec3 eye_w = g_view_position.xyz - pos_w;
    result_eye = eye_w;

    get_texcoord_shadow_stage(pos_w, result_texcoord_shadow0.xyz, result_texcoord_shadow1.xyz);

    vec4 diff;
    diff.rgb = irradiance_transforms_get_color(normal_w);
    diff.a = 1.0;

    diff.rgb *= g_light_env_stage_diffuse.rgb;

    vec4 lc = get_light_coef_stage(normal_w, eye_w, g_light_stage_dir.xyz);

    diff.rgb += g_light_stage_diff.rgb * lc.y;

    vec4 spec;
    spec.rgb = g_light_env_stage_specular.rgb * lc.z;
    spec.w = 1.0;
    result_spec_color = spec * g_material_state_specular;

    diff *= g_material_state_diffuse;
    diff *= a_color;
    diff *= g_blend_color;
    result_color = diff;
}
