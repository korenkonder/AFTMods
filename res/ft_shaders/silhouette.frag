#version 430 core
// silhouette.frag
//DEF
// 0 - Skinning
// 1 - Morph
// 2 - Alpha Test
// 3 - Depth

#define   SKINNING_DEF (_0 == 1)
#define      MORPH_DEF (_1 == 1)
#define ALPHA_TEST_DEF (_2 == 1)
#define      DEPTH_DEF (_3 == 1)

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 3) uniform sampler2D g_transparency;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec4 frg_texcoord; //xy=texcoord0, zw=texcoord1
layout(location = 1) in vec2 frg_linear_depth;

void main() {
    if (SHADER_FLAGS_TRANSPARENCY != 0) {
        if (SHADER_FLAGS_TRANSPARENCY == 1)
            result.a = texture(g_transparency, frg_texcoord.zw).a;
        else
            result.a = 0.0;
    }
    else
        result.a = texture(g_diffuse, frg_texcoord.xy).a;

    #if ALPHA_TEST_DEF
        if (result.a <= g_max_alpha.z && result.a != 1.0)
            discard;
    #endif

    float depth;
    #if DEPTH_DEF
        depth = frg_linear_depth.y;
    #else
        depth = 0.0;
    #endif

    result.rgb = vec3(depth, 0.0, 0.0);
}
