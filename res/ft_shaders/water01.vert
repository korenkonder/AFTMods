#version 430 core
// water01.vert
//DEF
// 0 - Morph

#define MORPH_DEF (_0 == 1)

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#if MORPH_DEF
#include "common_morph.glsl"
#endif


#define result_position (gl_Position)

layout(location = 0) out vec3 result_normal;
layout(location = 1) out float result_fog;
layout(location = 2) out vec3 result_tangent;
layout(location = 3) out vec3 result_binormal;
layout(location = 4) out vec4 result_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 5) out vec3 result_eye;
layout(location = 6) out vec4 result_color;
layout(location = 7) out vec4 result_bump; //xyz=unused, w=bump

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec4 a_color;
layout(location = 6) in vec4 a_tangent;
layout(location = 8) in vec2 a_texcoords[2];

#if MORPH_DEF
layout(location = 5) in vec4 a_morph_color;
layout(location = 10) in vec3 a_morph_position;
layout(location = 11) in vec3 a_morph_normal;
layout(location = 12) in vec4 a_morph_tangent;
layout(location = 13) in vec2 a_morph_texcoords[2];
#endif

void main() {
    vec4 pos_m;
    vec3 normal_m;
    vec3 tangent_m;
    #if MORPH_DEF
        pos_m = vec4(apply_morph(a_position, a_morph_position), 1.0);
        normal_m = apply_morph(a_normal, a_morph_normal);
        tangent_m = apply_morph(a_tangent.xyz, a_morph_tangent.xyz);
    #else
        pos_m = vec4(a_position, 1.0);
        normal_m = a_normal;
        tangent_m = a_tangent.xyz;
    #endif

    vec3 pos_w = pos_m * g_worlds;

    vec4 pos_c = pos_m * g_transforms;
    result_position = pos_c;

    vec3 normal_w = normal_m * mat3(g_worlds);
    vec3 tangent_w = tangent_m * mat3(g_worlds);
    vec3 binormal_w = cross(normal_w, tangent_w) * a_tangent.w;

    result_normal = normal_w;
    result_tangent = tangent_w;
    result_binormal = binormal_w;

    float depth = dot(g_forward_z_projection_row2, vec4(0.0, 0.0, dot(g_worldview[2], pos_m), 1.0));
    result_fog = clamp((depth - g_fog_state_params.y) * g_fog_state_params.w, 0.0, 1.0)
        * g_fog_state_params.x;
    result_bump.w = clamp((depth - g_fog_bump_params.y) * g_fog_bump_params.w, 0.0, 1.0)
        * g_fog_bump_params.x * g_bump_depth.x + 1.0;
    result_bump.rgb = vec3(0.0);

    vec2 texcoord0;
    #if MORPH_DEF
        texcoord0 = apply_morph(a_texcoords[0], a_morph_texcoords[0]);
    #else
        texcoord0 = a_texcoords[0];
    #endif
    result_texcoord.xy = vec4(texcoord0, 0.0, 1.0) * g_texcoord_transforms[0];

    vec2 texcoord1;
    #if MORPH_DEF
        texcoord1 = apply_morph(a_texcoords[1], a_morph_texcoords[1]);
    #else
        texcoord1 = a_texcoords[1];
    #endif
    result_texcoord.zw = vec4(texcoord1, 0.0, 1.0) * g_texcoord_transforms[1];

    result_eye = g_view_position.xyz - pos_w;

    vec4 diff;
    #if MORPH_DEF
        diff = apply_morph_color(diff, a_color, a_morph_color);
    #else
        diff = a_color;
    #endif
    result_color = diff * g_material_state_diffuse * g_blend_color;
}
