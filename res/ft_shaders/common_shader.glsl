#ifndef COMMON_SHADER
#define COMMON_SHADER

layout(set = 1, binding = 0) uniform Shader {
    uvec4 g_shader_flags;
};

#define SHADER_FLAGS_ALPHA_MASK     (bitfieldExtract(g_shader_flags.x, 0, 1)) // bit 0
#define SHADER_FLAGS_ALPHA_TEST     (bitfieldExtract(g_shader_flags.x, 1, 1)) // bit 1
#define SHADER_FLAGS_ANISO          (bitfieldExtract(g_shader_flags.x, 2, 2)) // bit 2:3
#define SHADER_FLAGS_COMPOSITE_BACK (bitfieldExtract(g_shader_flags.x, 4, 1)) // bit 4
#define SHADER_FLAGS_TEXTURE_BLEND  (bitfieldExtract(g_shader_flags.x, 5, 3)) // bit 5:7
#define SHADER_FLAGS_UNK            (bitfieldExtract(g_shader_flags.x, 8, 2)) // bit 8:9
#define SHADER_FLAGS_CHARA_COLOR    (bitfieldExtract(g_shader_flags.x, 10, 1)) // bit 10
#define SHADER_FLAGS_CLIP_PLANE     (bitfieldExtract(g_shader_flags.x, 11, 1)) // bit 11
#define SHADER_FLAGS_U08            (bitfieldExtract(g_shader_flags.x, 12, 1)) // bit 12
#define SHADER_FLAGS_DEPTH_PEEL     (bitfieldExtract(g_shader_flags.x, 13, 1)) // bit 13
#define SHADER_FLAGS_DEPTH          (bitfieldExtract(g_shader_flags.x, 14, 1)) // bit 14
#define SHADER_FLAGS_U0B            (bitfieldExtract(g_shader_flags.x, 15, 1)) // bit 15
#define SHADER_FLAGS_ALPHA_BLEND    (bitfieldExtract(g_shader_flags.x, 16, 3)) // bit 16:18
#define SHADER_FLAGS_RIPPLE_EMIT    (bitfieldExtract(g_shader_flags.x, 19, 1)) // bit 19
#define SHADER_FLAGS_ESM_FILTER     (bitfieldExtract(g_shader_flags.x, 20, 2)) // bit 20:21
#define SHADER_FLAGS_EXPOSURE       (bitfieldExtract(g_shader_flags.x, 22, 2)) // bit 22:23
#define SHADER_FLAGS_SCENE_FADE     (bitfieldExtract(g_shader_flags.x, 24, 1)) // bit 24
#define SHADER_FLAGS_FADE           (bitfieldExtract(g_shader_flags.x, 25, 3)) // bit 25:27
#define SHADER_FLAGS_STAGE_AMBIENT  (bitfieldExtract(g_shader_flags.x, 28, 1)) // bit 28
#define SHADER_FLAGS_FLARE          (bitfieldExtract(g_shader_flags.x, 29, 2)) // bit 29:30

#define SHADER_FLAGS_FOG_STAGE      (bitfieldExtract(g_shader_flags.y, 0, 2)) // bit 32+0:1
#define SHADER_FLAGS_FOG_CHARA      (bitfieldExtract(g_shader_flags.y, 2, 2)) // bit 32+2:3
#define SHADER_FLAGS_U16            (bitfieldExtract(g_shader_flags.y, 4, 1)) // bit 32+4
#define SHADER_FLAGS_GAUSS          (bitfieldExtract(g_shader_flags.y, 5, 2)) // bit 32+5:6
#define SHADER_FLAGS_EYE_LENS       (bitfieldExtract(g_shader_flags.y, 7, 1)) // bit 32+7
#define SHADER_FLAGS_IMAGE_FILTER   (bitfieldExtract(g_shader_flags.y, 8, 3)) // bit 32+8:10
#define SHADER_FLAGS_INSTANCE       (bitfieldExtract(g_shader_flags.y, 11, 1)) // bit 32+11
#define SHADER_FLAGS_TONE_CURVE     (bitfieldExtract(g_shader_flags.y, 12, 1)) // bit 32+12
#define SHADER_FLAGS_LIGHT_PROJ     (bitfieldExtract(g_shader_flags.y, 13, 1)) // bit 32+13
#define SHADER_FLAGS_MAGNIFY        (bitfieldExtract(g_shader_flags.y, 14, 4)) // bit 32+14:17
#define SHADER_FLAGS_MEMBRANE       (bitfieldExtract(g_shader_flags.y, 18, 2)) // bit 32+18:19
#define SHADER_FLAGS_MLAA           (bitfieldExtract(g_shader_flags.y, 20, 2)) // bit 32+20:21
#define SHADER_FLAGS_MLAA_SEARCH    (bitfieldExtract(g_shader_flags.y, 22, 2)) // bit 32+22:23
#define SHADER_FLAGS_MORPH_COLOR    (bitfieldExtract(g_shader_flags.y, 24, 1)) // bit 32+24
#define SHADER_FLAGS_MORPH          (bitfieldExtract(g_shader_flags.y, 25, 1)) // bit 32+25
#define SHADER_FLAGS_MOVIE          (bitfieldExtract(g_shader_flags.y, 26, 2)) // bit 32+26:27
#define SHADER_FLAGS_U24            (bitfieldExtract(g_shader_flags.y, 28, 2)) // bit 32+28:29
#define SHADER_FLAGS_U25            (bitfieldExtract(g_shader_flags.y, 30, 1)) // bit 32+30
#define SHADER_FLAGS_NPR_NORMAL     (bitfieldExtract(g_shader_flags.y, 31, 1)) // bit 32+31

#define SHADER_FLAGS_NPR            (bitfieldExtract(g_shader_flags.z, 0, 1)) // bit 64+0
#define SHADER_FLAGS_STAGE_SHADOW2  (bitfieldExtract(g_shader_flags.z, 1, 2)) // bit 64+1:2
#define SHADER_FLAGS_REFLECT        (bitfieldExtract(g_shader_flags.z, 3, 2)) // bit 64+3:4
#define SHADER_FLAGS_REDUCE         (bitfieldExtract(g_shader_flags.z, 5, 4)) // bit 64+5:8
#define SHADER_FLAGS_CHARA_SHADOW   (bitfieldExtract(g_shader_flags.z, 9, 1)) // bit 64+9
#define SHADER_FLAGS_CHARA_SHADOW2  (bitfieldExtract(g_shader_flags.z, 10, 2)) // bit 64+10:11
#define SHADER_FLAGS_U2D            (bitfieldExtract(g_shader_flags.z, 12, 3)) // bit 64+12:14
#define SHADER_FLAGS_DISP_LOD       (bitfieldExtract(g_shader_flags.z, 15, 2)) // bit 64+15:16
#define SHADER_FLAGS_SHOW_VECTOR    (bitfieldExtract(g_shader_flags.z, 17, 2)) // bit 64+17:18
#define SHADER_FLAGS_SKINNING       (bitfieldExtract(g_shader_flags.z, 19, 1)) // bit 64+19
#define SHADER_FLAGS_SNOW_PARTICLE  (bitfieldExtract(g_shader_flags.z, 20, 2)) // bit 64+20:21
#define SHADER_FLAGS_SPECULAR_IBL   (bitfieldExtract(g_shader_flags.z, 22, 2)) // bit 64+22:23
#define SHADER_FLAGS_COMBINER       (bitfieldExtract(g_shader_flags.z, 24, 1)) // bit 64+24
#define SHADER_FLAGS_TEX_0_TYPE     (bitfieldExtract(g_shader_flags.z, 25, 2)) // bit 64+25:26
#define SHADER_FLAGS_TEX_1_TYPE     (bitfieldExtract(g_shader_flags.z, 27, 2)) // bit 64+27:28
#define SHADER_FLAGS_SSS_FILTER     (bitfieldExtract(g_shader_flags.z, 29, 2)) // bit 64+29:30

#define SHADER_FLAGS_SSS_CHARA      (bitfieldExtract(g_shader_flags.w, 0, 1)) // bit 96+0
#define SHADER_FLAGS_STAR           (bitfieldExtract(g_shader_flags.w, 1, 1)) // bit 96+1
#define SHADER_FLAGS_TEXTURE_COUNT  (bitfieldExtract(g_shader_flags.w, 2, 2)) // bit 96+2:3
#define SHADER_FLAGS_ENV_MAP        (bitfieldExtract(g_shader_flags.w, 4, 1)) // bit 96+4
#define SHADER_FLAGS_RIPPLE         (bitfieldExtract(g_shader_flags.w, 5, 2)) // bit 96+5:6
#define SHADER_FLAGS_TRANSLUCENCY   (bitfieldExtract(g_shader_flags.w, 7, 1)) // bit 96+7
#define SHADER_FLAGS_NORMAL         (bitfieldExtract(g_shader_flags.w, 8, 1)) // bit 96+8
#define SHADER_FLAGS_TRANSPARENCY   (bitfieldExtract(g_shader_flags.w, 9, 1)) // bit 96+9
#define SHADER_FLAGS_WATER_REFLECT  (bitfieldExtract(g_shader_flags.w, 10, 1)) // bit 96+10
#define SHADER_FLAGS_U40            (bitfieldExtract(g_shader_flags.w, 11, 1)) // bit 96+11
#define SHADER_FLAGS_U41            (bitfieldExtract(g_shader_flags.w, 12, 1)) // bit 96+12
#define SHADER_FLAGS_STAGE_SHADOW   (bitfieldExtract(g_shader_flags.w, 13, 1)) // bit 96+13
#define SHADER_FLAGS_SPECULAR       (bitfieldExtract(g_shader_flags.w, 14, 1)) // bit 96+14
#define SHADER_FLAGS_TONE_MAP       (bitfieldExtract(g_shader_flags.w, 15, 2)) // bit 96+15
#define SHADER_FLAGS_U45            (bitfieldExtract(g_shader_flags.w, 16, 1)) // bit 96+16

#define SHADER_FLAGS_DOF            (SHADER_FLAGS_TEX_0_TYPE)
#define SHADER_FLAGS_DOF_STAGE      (SHADER_FLAGS_TEX_1_TYPE)
#endif  // COMMON_SHADER
