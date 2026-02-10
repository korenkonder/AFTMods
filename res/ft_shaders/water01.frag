#version 430 core
// water01.frag
//DEF
// 0 - Morph

#define MORPH_DEF (_0 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 1) uniform sampler2D g_mask;
layout(set = 0, binding = 2) uniform sampler2D g_normal;
layout(set = 0, binding = 3) uniform sampler2D g_specular;
layout(set = 0, binding = 5) uniform samplerCube g_envmap;
layout(set = 0, binding = 15) uniform sampler2D g_reflect;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#include "common_stage.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec3 frg_normal;
layout(location = 1) in float frg_fog;
layout(location = 2) in vec3 frg_tangent;
layout(location = 3) in vec3 frg_binormal;
layout(location = 4) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 5) in vec3 frg_eye;
layout(location = 6) in vec4 frg_color;
layout(location = 7) in vec4 frg_bump; //xyz=unused, w=bump

void main() {
    vec4 color_map;
    if (SHADER_FLAGS_TEXTURE_COUNT == 0)
        color_map = frg_color;
    else if (SHADER_FLAGS_TEXTURE_COUNT == 1) {
        color_map = texture(g_diffuse, frg_texcoord.xy);
        color_map *= frg_color;
    }
    else if (SHADER_FLAGS_TEXTURE_COUNT == 2) {
        color_map = texture_blend_apply(0,
            texture(g_diffuse, frg_texcoord.xy), texture(g_mask, frg_texcoord.zw));
        color_map *= frg_color;
    }
    else
        color_map = vec4(0.0, 0.0, 0.0, 0.0);

    vec3 normal_t;
    vec3 normal_w;
    if (SHADER_FLAGS_NORMAL == 1) {
        normal_t.xy = texture(g_normal, frg_texcoord.xy).wy * 2.0 - 1.0;
        normal_t.z = frg_bump.w * 0.15;
        normal_t = normalize(normal_t);

        normal_w = frg_normal;
        normal_w += frg_tangent * normal_t.x;
        normal_w += frg_binormal * normal_t.y;
        normal_w = normalize(normal_w);
    }
    else {
        normal_t = vec3(0.0);
        normal_w = normalize(frg_normal);
    }

    vec3 reflect_map;
    if (SHADER_FLAGS_WATER_REFLECT == 1) {
        vec2 screen_uv = gl_FragCoord.xy * g_framebuffer_size.xy + normal_t.xy * g_reflect_uv_scale.xy;
        reflect_map = texture(g_reflect, screen_uv).rgb;
    }
    else
        reflect_map = vec3(0.0);

    vec3 eye = normalize(frg_eye);
    if (SHADER_FLAGS_ENV_MAP == 1) {
        vec3 reflect_vec = -reflect(eye, normal_w);
        vec4 cube_map = texture(g_envmap, reflect_vec);
        reflect_map += cube_map.rgb * (cube_map.w * 25.5 * g_intensity.x);
    }

    if (SHADER_FLAGS_SPECULAR == 1)
        reflect_map *= texture(g_specular, frg_texcoord.xy).rgb;

    reflect_map *= g_material_state_specular.rgb;

    float fres = pow(clamp(1.0 - dot(normal_w, eye), 0.0, 1.0), 5.0);
    fres = get_fresnel_coefficient(fres, 10.0).x;
    fres *= g_material_state_specular.w;

    bool has_fog = SHADER_FLAGS_FOG_STAGE == 1;
    vec4 color;
    color.rgb = color_map.rgb + reflect_map * fres;
    color.a = color_map.a;

    if (has_fog)
        color.rgb = mix(color.rgb, g_fog_depth_color.rgb, frg_fog);

    result = color;
}
