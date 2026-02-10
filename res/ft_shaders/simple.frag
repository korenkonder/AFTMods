#version 430 core
// simple.frag
//DEF
// 0 - Skinning
// 1 - Alpha Test

#define SKINNING_DEF (_0 == 1)
#define ALPHA_TEST_DEF (_1 == 1)

const vec3 level0_color = vec3(0.0, 0.0, 0.9);
const vec3 level1_color = vec3(0.0, 0.7, 0.0);
const vec3 level2_color = vec3(0.8, 0.7, 0.0);
const vec3 warning_color = vec3(0.8, 0.0, 0.0);

layout(set = 0, binding = 0) uniform sampler2D g_color;
layout(set = 0, binding = 1) uniform sampler2D g_translucency;
layout(set = 0, binding = 2) uniform sampler2D g_normal;
layout(set = 0, binding = 3) uniform sampler2D g_specular;
layout(set = 0, binding = 4) uniform sampler2D g_transparency;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord;
layout(location = 1) in vec4 frg_color;
layout(location = 2) in vec4 frg_offset_color;

vec3 disp_lod_nearest(float level) {
    if (level >= 2.0) {
        return level2_color;
    } else if (level >= 1.0) {
        return level1_color;
    } else {
        return level0_color;
    }
}

vec3 disp_lod_linear(float level) {
    if (level >= 2.0) {
        return level2_color;
    } else if (level >= 1.0) {
        return (level - 1.0) * warning_color + level1_color;
    } else {
        return mix(level0_color, level1_color, level);
    }
}

vec3 disp_lod_no_mipmap() {
    int levels;
    int texture_index = int(g_shininess.y);
    if (texture_index == 0) {
        levels = textureQueryLevels(g_color);
    } else if (texture_index == 1) {
        levels = textureQueryLevels(g_translucency);
    } else if (texture_index == 2) {
        levels = textureQueryLevels(g_normal);
    } else if (texture_index == 3) {
        levels = textureQueryLevels(g_specular);
    } else if (texture_index == 4) {
        levels = textureQueryLevels(g_transparency);
    } else {
        levels = 0;
    }

    if (levels == 1) {
        return warning_color;
    } else {
        return level0_color;
    }
}

void main() {
    if (SHADER_FLAGS_DISP_LOD == 0) {
        if (SHADER_FLAGS_TEXTURE_COUNT != 0) {
            result = texture(g_color, frg_texcoord) * frg_color + frg_offset_color;
        } else {
            result = frg_color + frg_offset_color;
        }
    } else {
        float level;
        int texture_index = int(g_shininess.y);
        if (texture_index == 0) {
            level = textureQueryLod(g_color, frg_texcoord).x;
        } else if (texture_index == 1) {
            level = textureQueryLod(g_translucency, frg_texcoord).x;
        } else if (texture_index == 2) {
            level = textureQueryLod(g_normal, frg_texcoord).x;
        } else if (texture_index == 3) {
            level = textureQueryLod(g_specular, frg_texcoord).x;
        } else if (texture_index == 4) {
            level = textureQueryLod(g_transparency, frg_texcoord).x;
        } else {
            level = 0.0;
        }

        if (SHADER_FLAGS_DISP_LOD == 1) {
            result.rgb = disp_lod_nearest(level);
        } else if (SHADER_FLAGS_DISP_LOD == 2) {
            result.rgb = disp_lod_linear(level);
        } else {
            result.rgb = disp_lod_no_mipmap();
        }

        if (SHADER_FLAGS_TEXTURE_COUNT != 0) {
            result.a = texture(g_color, frg_texcoord).a;
        } else {
            result.a = 1.0;
        }
    }

    #if ALPHA_TEST_DEF
        if (result.a <= g_max_alpha.z && result.a != 1.0)
            discard;
    #endif
}
