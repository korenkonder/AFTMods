#version 430 core
// lit_proj.frag
//DEF
// 0 - Skinning
// 1 - Alpha Test

#define   SKINNING_DEF (_0 == 1)
#define ALPHA_TEST_DEF (_1 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 2) uniform sampler2D g_normal;
layout(set = 0, binding = 3) uniform sampler2D g_specular;
layout(set = 0, binding = 4) uniform sampler2D g_transparency;
layout(set = 0, binding = 17) uniform sampler2D g_litproj_texture;
layout(set = 0, binding = 18) uniform sampler2D g_litproj_shadow;

#include "common_shader.glsl"
#include "common_scene.glsl"
#include "common_batch.glsl"

#include "common_stage.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec3 frg_normal;
layout(location = 1) in vec3 frg_tangent;
layout(location = 2) in vec3 frg_binormal;
layout(location = 3) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 4) in vec3 frg_eye;
layout(location = 5) in vec4 frg_texcoord_litproj;
layout(location = 6) in vec3 frg_lit;
layout(location = 7) in vec4 frg_texcoord_litproj_depth;

void main() {
    vec3 normal;
    if (SHADER_FLAGS_NORMAL == 1)
        normal = sample_normal_texture(g_normal, frg_texcoord.xy, frg_normal, frg_tangent, frg_binormal);
    else
        normal = normalize(frg_normal);

    vec3 eye = normalize(frg_eye);
    vec3 lit_dir = normalize(frg_lit);

    vec4 lc = get_light_coef_stage(normal, eye, lit_dir);

    vec4 col0 = texture(g_diffuse, frg_texcoord.xy);
    if (SHADER_FLAGS_TRANSPARENCY == 1)
        col0.a = texture(g_transparency, frg_texcoord.zw).r;
    result.a = col0.a;

    vec3 diff = col0.rgb;
    diff *= lc.y;

    vec3 spec;
    if (SHADER_FLAGS_SPECULAR == 1)
        spec = texture(g_specular, frg_texcoord.xy).rgb;
    else
        spec = g_material_state_specular.rgb;

    #if ALPHA_TEST_DEF
        if (result.a <= g_max_alpha.z && result.a != 1.0)
            discard;
    #endif

    spec *= lc.z;
    spec *= g_light_env_proj_specular.rgb;

    vec3 lit_col = textureProj(g_litproj_texture, frg_texcoord_litproj).rgb;
    float depth = textureProj(g_litproj_shadow, frg_texcoord_litproj_depth).r;
    depth = -frg_texcoord_litproj_depth.w + depth;
    depth *= 100.0;
    depth *= g_material_state_emission.a;
    lit_col *= clamp(exp2(depth), 0.0, 1.0);

    diff *= g_light_env_proj_diffuse.rgb;
    diff += spec;
    diff *= lit_col;

    result.rgb = diff;
}
