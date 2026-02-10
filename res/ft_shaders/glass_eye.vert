#version 430 core
// glass_eye.vert
//DEF
// 0 - Skinning

#define SKINNING_DEF (_0 == 1)

layout(set = 1, binding = 3) uniform GlassEyeBatch {
    vec4 g_ellipsoid_radius;
    vec4 g_ellipsoid_scale;
    vec4 g_tex_model_param;
    vec4 g_tex_offset; //xy=tex_offset, zw=highlight_tex_offset
    vec4 g_eb_radius;
    vec4 g_eb_tex_model_param;
    vec4 g_fresnel; //x=1-((n_1-n_2)/(n_2-n_1))^2, y=((n_1-n_2)/(n_2-n_1))^2, zw=unused
    vec4 g_refract1; //x=(n_1/n_2)^2, y=1-(n_1/n_2)^2, z=n_1/n_2, w=unused
    vec4 g_refract2; //x=(n_2/n_1)^2, y=1-(n_2/n_1)^2, z=n_2/n_1, w=unused
    vec4 g_iris_radius;
    vec4 g_cornea_radius;
    vec4 g_pupil_radius;
    vec4 g_tex_scale; //xy=tex_scale, z=trsmit_coef, w=lens_depth
};

layout(set = 0, binding = 14) uniform sampler2D g_effect_texture;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#if SKINNING_DEF
#include "common_skinning.glsl"
#endif

#include "common_chara.glsl"

#define result_position (gl_Position)

layout(location = 0) out vec3 result_normal;
layout(location = 1) out vec4 result_texcoord; //xy=texcoord, zw=highlight_texcoord
layout(location = 2) out vec3 result_eye;
layout(location = 3) out vec4 result_texcoord_shadow0; //xyz=texcoord_shadow0, w=fog
layout(location = 4) out vec2 result_cornea_coord;
layout(location = 5) out vec4 result_normal_spec; //xyz=normal_spec, w=
layout(location = 6) out vec4 result_normal_diff; //xyz=normal_diff, w=
layout(location = 7) out vec4 result_model_pos;
layout(location = 8) out vec4 result_face_offset; //xyz=unused, w=face_offset
layout(location = 9) out vec4 result_fog_color; //xyz=fog_color, w=fresnel(unused)

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec3 a_normal;
layout(location = 8) in vec2 a_texcoords[2];

void main() {
    vec4 pos_m;
    vec3 normal_w;
    #if SKINNING_DEF
        ivec4 mtxidx;
        vec4 weight = get_skinning_data(mtxidx);

        pos_m = apply_skinning(vec4(a_position, 1.0), mtxidx, weight);

        normal_w = apply_skinning(a_normal, mtxidx, weight);
        normal_w = normalize(normal_w);
    #else
        pos_m = vec4(a_position, 1.0);
        vec3 normal_m = a_normal;

        normal_w = normal_m * mat3(g_worlds);
    #endif

    vec3 pos_w = pos_m * g_worlds;

    vec3 normal_v = normal_w * mat3(g_view);

    vec4 pos_c = pos_m * g_transforms;
    result_position = pos_c;

    result_normal = normal_w;

    result_normal_diff.xyz = normal_w;
    result_normal_diff.w = 1.0;

    vec2 tex_eb = a_texcoords[0] + g_tex_offset.xy;
    result_texcoord.xy = tex_eb;
    result_texcoord.zw = a_texcoords[0] + g_tex_offset.zw + normal_v.xy * vec2(-0.1, 0.06);

    result_texcoord_shadow0.xyz = get_texcoord_shadow_chara(pos_w);

    vec2 cornea_coord = tex_eb * vec2(-1.0, 1.0) + vec2(1.0, 0.0);
    cornea_coord -= g_tex_model_param.zw;
    cornea_coord *= g_tex_model_param.xy;
    result_cornea_coord = cornea_coord;

    result_model_pos = vec4(cornea_coord * g_ellipsoid_scale.xy, 0.0, 1.0);

    vec3 pos_eb;
    pos_eb.xy = tex_eb * vec2(-1.0, 1.0) + vec2(1.0, 0.0);
    pos_eb.xy -= g_eb_tex_model_param.zw;
    pos_eb.xy *= g_eb_tex_model_param.xy;
    float eb = dot(pos_eb.xy * g_eb_radius.xy, pos_eb.xy) * -g_eb_radius.w + g_eb_radius.w;
    pos_eb.z = eb > 0.000001 ? sqrt(eb) : 0.0;

    result_normal_spec.xyz = normalize(pos_eb * (2.0 * g_eb_radius.xyz)) * mat3(g_worlds);
    result_normal_spec.w = 0.0;

    vec3 eye_w = g_view_position.xyz - pos_w;
    result_eye = eye_w;

    eye_w = normalize(eye_w);

    result_face_offset.rgb = vec3(0.0);
    result_face_offset.w = get_face_offset(normal_v, eye_w);

    result_texcoord_shadow0.w = get_fog_chara(g_effect_texture, pos_m, pos_w, result_fog_color.rgb);
}
