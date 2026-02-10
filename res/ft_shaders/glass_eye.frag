#version 430 core
// glass_eye.frag
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

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 3) uniform sampler2D g_specular;
layout(set = 0, binding = 5) uniform samplerCube g_envmap;
layout(set = 0, binding = 9) uniform samplerCube g_ibl_diffuse;
layout(set = 0, binding = 10) uniform samplerCube g_ibl_specular;
layout(set = 0, binding = 12) uniform samplerCube g_ibl_specular_shadowed;
layout(set = 0, binding = 16) uniform sampler2D g_sss;
layout(set = 0, binding = 19) uniform sampler2D g_shadow_depth0;

#include "common_shader.glsl"
#include "common_batch.glsl"
#include "common_scene.glsl"

#include "common_chara.glsl"

layout(location = 0) out vec4 result;

layout(location = 0) in vec3 frg_normal;
layout(location = 1) in vec4 frg_texcoord; //xy=texcoord, zw=highlight_texcoord
layout(location = 2) in vec3 frg_eye;
layout(location = 3) in vec4 frg_texcoord_shadow0; //xyz=texcoord_shadow0, w=fog
layout(location = 4) in vec2 frg_cornea_coord;
layout(location = 5) in vec4 frg_normal_spec; //xyz=normal_spec, w=
layout(location = 6) in vec4 frg_normal_diff; //xyz=normal_diff, w=
layout(location = 7) in vec4 frg_model_pos;
layout(location = 8) in vec4 frg_face_offset; //xyz=unused, w=face_offset
layout(location = 9) in vec4 frg_fog_color; //xyz=fog_color, w=fresnel(unused)

vec3 get_diffuse(in const vec3 ray, in const vec3 normal, in const float lc, in const float face_offset) {
    vec3 diff = get_ibl_diffuse(g_ibl_diffuse, ray, lc);

    diff *= g_light_env_chara_diffuse.rgb;
    diff += face_offset;
    diff += g_light_env_chara_ambient.rgb;

    if (SHADER_FLAGS_TONE_CURVE == 1)
        diff += get_tone_curve(normal);
    return diff;
}

vec3 get_ibl_specular(in const vec3 ray, in const float lc) {
    vec3 spec = texture(g_ibl_specular, ray).rgb;
    vec3 spec_shad = texture(g_ibl_specular_shadowed, ray).rgb;
    spec = mix(spec_shad, spec, lc);
    return spec * g_light_env_chara_specular.rgb;
}

vec3 get_highlight_coeff(in const vec2 texcoord) {
    vec3 highlight = texture(g_specular, texcoord).aaa;
    highlight *= 0.9;
    return highlight;
}

bool get_length(in const vec3 ray, in const vec4 pos, in const vec4 radius, out vec2 tmp) {
    vec3 coef;
    coef.x = dot(ray * radius.xyz, ray);
    coef.y = dot(ray * radius.xyz, pos.xyz) * 2.0;
    coef.z = dot(pos * radius, pos);

    float _ftmp0 = coef.x * coef.z * -4.0 + coef.y * coef.y;
    bool cc = _ftmp0 - 0.000001 < 0.0;
    tmp = vec2(1.0, -1.0) * sqrt(_ftmp0) - coef.y;
    tmp = 0.5 * (1.0 / coef.x) * tmp;
    return cc;
}

void main() {
    result = vec4(1.0, 0.0, 0.0, 1.0);

    vec4 pos_cornea1;
    pos_cornea1.xy = frg_model_pos.xy;
    pos_cornea1.z = dot(pos_cornea1.xy * g_ellipsoid_radius.xy, pos_cornea1.xy);
    pos_cornea1.zw = g_ellipsoid_radius.w - vec2(0.0, 0.000001) + pos_cornea1.z * -g_ellipsoid_radius.w;
    pos_cornea1.z = pos_cornea1.w > 0.0 ? sqrt(pos_cornea1.z) : frg_model_pos.z;
    pos_cornea1.w = frg_model_pos.w;

    vec3 nrm_cornea1 = normalize(pos_cornea1.xyz * (g_ellipsoid_radius.xyz * 2.0));
    nrm_cornea1 = nrm_cornea1 * mat3(g_joint);

    vec3 eye = normalize(frg_eye);

    vec3 lc = get_light_coef_chara(g_shadow_depth0, frg_normal_diff.xyz, frg_texcoord_shadow0.xyz);

    vec3 highlight_coeff = get_highlight_coeff(frg_texcoord.zw);

    if (dot(frg_cornea_coord, frg_cornea_coord) > 0.96) {
        vec3 nrm_sclera = normalize(frg_normal_diff.xyz);

        vec3 rot_ray = nrm_sclera * mat3(g_normal_tangent_transforms);

        vec3 diff = get_diffuse(rot_ray, nrm_sclera, lc.y, frg_face_offset.w);

        vec3 highlight = highlight_coeff * diff;

        vec2 dev_pos = gl_FragCoord.xy * g_framebuffer_size.xy;
        vec3 sss = texture(g_sss, dev_pos).rgb;
        diff = mix(diff, sss, g_sss_param.x);

        diff *= texture(g_diffuse, frg_texcoord.xy).rgb;

        vec3 ray = -reflect(eye, frg_normal_spec.xyz) * mat3(g_normal_tangent_transforms);

        vec3 ibl_spec = get_ibl_specular(ray, lc.z);
        diff = mix(ibl_spec, diff, 0.94);
        diff += highlight;

        result.rgb = apply_fog_chara(diff, frg_fog_color.rgb, frg_texcoord_shadow0.w);
        return;
    }

    vec2 cosine1; // x=cos(phi), y=k
    cosine1.x = clamp(dot(eye, nrm_cornea1), 0.0, 1.0); // refract (part 1)
    cosine1.y = cosine1.x * cosine1.x * g_refract1.x + g_refract1.y;
    cosine1.y = cosine1.y >= 0.000001 ? sqrt(cosine1.y) : 1.0;

    vec4 spec1;
    spec1.w = pow(clamp(1.0 - cosine1.x, 0.0, 1.0), 5.0) * g_fresnel.x + g_fresnel.y; // Schlick's approximation
    spec1.w = min(spec1.w, g_material_state_specular.w * 2.0);

    vec3 rot_ray = -reflect(eye, nrm_cornea1) * mat3(g_normal_tangent_transforms);

    spec1.rgb = texture(g_envmap, rot_ray).rgb;
    spec1.rgb = max(spec1.rgb * spec1.rgb * 7.0 - 0.5, vec3(0.0));
    spec1.rgb *= g_light_env_chara_specular.rgb;

    vec3 ray = nrm_cornea1 * (cosine1.x * g_refract1.z - cosine1.y) - eye * g_refract1.z; // refract (part 2)
    ray = ray * mat3(g_joint_inverse);

    vec2 tmp;
    if (get_length(ray, pos_cornea1, g_iris_radius, tmp)) {
        result = vec4(0.0, 0.0, 1.0, 1.0);
        return;
    }

    vec4 pos_iris = vec4(ray * tmp.x, 0.0) + pos_cornea1;
    if (pos_iris.z > 0.0) {
        result = vec4(0.0, 1.0, 0.0, 1.0);
        return;
    }

    float len = abs(tmp.x);

    vec2 texcoord_iris = (pos_iris.xy * g_tex_scale.xy + 0.5) * vec2(-1.0, 1.0) + vec2(1.0, 0.0);

    vec3 col0 = texture(g_diffuse, texcoord_iris).rgb;
    vec3 spec_col = col0;

    pos_cornea1.z -= g_tex_scale.w;

    tmp.y = get_length(ray, pos_cornea1, g_pupil_radius, tmp) ? 999999.0 : tmp.y;

    vec3 nrm_iris;
    vec4 spec3 = vec4(0.0);
    vec4 spec2 = vec4(0.0);
    if (SHADER_FLAGS_EYE_LENS == 1) {
        if (tmp.y - len < 0.0) {
            len = tmp.y;

            vec4 pos_pupil = vec4(ray * len, 0.0) + pos_cornea1;
            vec3 nrm_pupil = normalize(pos_pupil.xyz * (g_pupil_radius.xyz * 2.0));

            pos_iris = pos_pupil;
            nrm_iris = nrm_pupil;

            const float fresnel = 0.04;
            spec2.w = pow(1.0 - clamp(dot(-ray, nrm_pupil), 0.0, 1.0), 5.0) * (1.0 - fresnel) + fresnel; // Schlick's approximation

            col0 *= 0.5;
            spec_col = vec3(1.0);
        }
        else {
            nrm_iris = normalize(pos_iris.xyz * (g_iris_radius.xyz * -2.0));
            spec2.w = clamp(dot(spec_col, spec_col) * 0.2 - 0.02, 0.0, 1.0);
        }
    }
    else {
        if (tmp.y - len < 0.0) {
            len = tmp.y;

            vec4 pos_pupil = vec4(ray * len, 0.0) + pos_cornea1;
            vec3 nrm_pupil = normalize(pos_pupil.xyz * (g_pupil_radius.xyz * 2.0));

            vec3 rot_ray = reflect(ray, nrm_pupil) * mat3(g_joint) * mat3(g_normal_tangent_transforms);

            spec3.rgb = texture(g_ibl_specular, rot_ray).rgb;

            spec3.rgb *= spec_col;
            spec3.rgb *= 0.1;
            spec3.rgb *= g_light_env_chara_specular.rgb;

            col0 *= 0.75;
        }

        nrm_iris = normalize(pos_iris.xyz * (g_iris_radius.xyz * -2.0));
        spec2.w = clamp(dot(spec_col, spec_col) * 0.2 - 0.02, 0.0, 1.0);
    }

    rot_ray = nrm_iris * mat3(g_joint) * mat3(g_normal_tangent_transforms);

    vec3 diff = get_diffuse(rot_ray, nrm_iris * mat3(g_joint), lc.y, frg_face_offset.w);
    vec3 highlight = highlight_coeff * diff;

    diff *= 0.95;
    diff *= col0;

    vec3 trsmit_coef = g_material_state_diffuse.rgb * -2.0 + 2.0;
    trsmit_coef *= g_tex_scale.z;

    vec3 trsmit = exp2(trsmit_coef * -len);

    vec3 diff2 = mix(diff * trsmit, spec1.rgb, spec1.w);
    diff2 += highlight;

    ray = -reflect(-ray, nrm_iris);

    bool tmp2 = get_length(ray, pos_iris, g_cornea_radius, tmp);

    result.rgb = apply_fog_chara(diff2, frg_fog_color.rgb, frg_texcoord_shadow0.w);

    if (tmp2)
        return;

    vec4 pos_cornea2 = vec4(ray * tmp.x, 0.0) + pos_iris;
    if (pos_cornea2.z < 0.0)
        return;

    len = abs(tmp.x);

    vec3 nrm_cornea2 = normalize(pos_cornea2.xyz * (g_cornea_radius.xyz * 2.0));

    vec2 cosine2; // x=cos(phi), y=k
    cosine2.x = clamp(dot(-ray, -nrm_cornea2), 0.0, 1.0); // refract (part 1)
    cosine2.y = cosine2.x * cosine2.x * g_refract2.x + g_refract2.y;

    if (cosine2.y < 0.000001) {
        diff2 *= 0.85;

        result.rgb = apply_fog_chara(diff2, frg_fog_color.rgb, frg_texcoord_shadow0.w);
        return;
    }

    rot_ray = -nrm_cornea2 * (cosine2.x * g_refract2.z - sqrt(cosine2.y)) + ray * g_refract2.z; // refract (part 2)
    rot_ray = rot_ray * mat3(g_joint) * mat3(g_normal_tangent_transforms);

    vec3 ibl_spec = get_ibl_specular(rot_ray, lc.z);
    diff += ibl_spec * spec_col * exp2(-len * trsmit_coef) * spec2.w;

    diff = mix(diff * trsmit, spec1.rgb, spec1.w);
    diff += spec3.rgb;
    diff += highlight;

    result.rgb = apply_fog_chara(diff, frg_fog_color.rgb, frg_texcoord_shadow0.w);
}
