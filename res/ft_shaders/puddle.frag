#version 430 core
// puddle.frag
//DEF

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 2) uniform sampler2D g_normal;
layout(set = 0, binding = 6) uniform sampler2D g_shadow0;
layout(set = 0, binding = 7) uniform sampler2D g_shadow1;
layout(set = 0, binding = 14) uniform sampler2D g_ripple;
layout(set = 0, binding = 15) uniform sampler2D g_reflect;
layout(set = 0, binding = 20) uniform sampler2D g_shadow_depth1;

#include "common_shader.glsl"
#include "common_scene.glsl"
#include "common_batch.glsl"

#include "common_stage.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec3 frg_normal;
layout(location = 1) in vec4 frg_color;
layout(location = 2) in vec4 frg_spec_color;
layout(location = 3) in vec2 frg_texcoord;
layout(location = 4) in vec3 frg_eye;
layout(location = 5) in vec4 frg_texcoord_shadow0; //xyz=texcoord_shadow0, w=fog
layout(location = 6) in vec4 frg_texcoord_shadow1; //xyz=texcoord_shadow1, w=

void main() {
    vec4 color_map = texture(g_diffuse, frg_texcoord);

    vec3 normal_w;
    if (SHADER_FLAGS_NORMAL == 1)
        normal_w = texture(g_normal, frg_texcoord).xzy * 2.0 - 1.0;
    else
        normal_w = frg_normal;

    vec3 eye = normalize(frg_eye);

    vec2 ripple = texture(g_ripple, frg_texcoord).xy * 2.0 - 1.0;
    vec2 screen_uv = gl_FragCoord.xy * g_framebuffer_size.xy + (normal_w.xz + ripple) * g_bump_depth.y;
    vec4 reflect_map = texture(g_reflect, screen_uv);
    normal_w.xz += ripple;
    normal_w = normalize(normal_w);

    float fres = pow(clamp(1.0 - dot(normal_w, eye), 0.0, 1.0), 5.0);

    reflect_map *= get_fresnel_coefficient(fres, 10.0);

    vec4 diff = color_map;
    vec4 spec = frg_spec_color;

    if (SHADER_FLAGS_STAGE_SHADOW != 0)
        apply_stage_shadow(g_shadow0, g_shadow1, g_shadow_depth1,
            frg_texcoord_shadow0.xyz, frg_texcoord_shadow1.xyz, diff, spec);

    diff *= frg_color;
    spec += reflect_map * frg_spec_color.a;

    diff.rgb += spec.rgb * color_map.a;

    result.rgb = apply_fog_stage_depth(diff.rgb, frg_texcoord_shadow0.w);
    result.a = 1.0;
}
