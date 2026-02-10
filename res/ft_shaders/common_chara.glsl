#ifndef COMMON_CHARA
#define COMMON_CHARA

vec3 apply_chara_color(in const vec3 color) {
    vec3 chara_color = mix(g_chara_color0.rgb, g_chara_color1.rgb, dot(color, vec3(0.2989, 0.5866, 0.1145)));
    return max(mix(color, chara_color, g_chara_color1.w), vec3(0.0));
}

vec3 apply_fog_chara(in const vec3 color, in const vec3 fog_color, in const float fog) {
    if (SHADER_FLAGS_CHARA_COLOR == 1)
        return apply_chara_color(color);
    else
        return mix(color, fog_color, fog);
}

float get_face_offset(in const vec3 normal_v, in const vec3 eye) {
    vec2 diff;
    diff.x = pow(clamp(dot(normal_v, vec3(0.0, 0.0, 1.0)), 0.0, 1.0), 0.4);
    diff.y = clamp(dot(g_light_chara_dir.xyz, -eye) * 0.5 + 0.5, 0.0, 1.0);
    diff.y *= diff.x;
    diff.xy *= g_light_face_diff.xy;
    return diff.x + diff.y;
}

float get_fog_chara(sampler2D effect_tex, in const vec4 pos_m, in const vec3 pos_w, out vec3 fog_color) {
    if (SHADER_FLAGS_FOG_CHARA == 1) {
        float depth = dot(g_forward_z_projection_row2.zw, vec2(dot(g_worldview[2], pos_m), 1.0));
        float fog = clamp((depth - g_fog_state_params.y) * g_fog_state_params.w, 0.0, 1.0);
        fog_color = g_fog_depth_color.rgb;
        return fog * g_fog_state_params.x;
    }
    else if (SHADER_FLAGS_FOG_CHARA == 2) {
        vec2 texcoord = pos_w.xz * vec2(0.0625, -0.0625) + 0.5;

        float eff_val = texture(effect_tex, texcoord).x;
        float fog = clamp(1.0 - (-pos_w.y - g_fog_height_params.y) * g_fog_height_params.w, 0.0, 1.0);
        eff_val = eff_val * 3.0 + 1.0;

        fog_color = g_fog_height_color.rgb;

        if (eff_val > 0.0)
            return (1.0 - pow(fog, eff_val)) * g_fog_height_params.x;
        else
            return 0.0;
    }
    else {
        fog_color = vec3(0.0);
        return 0.0;
    }
}

float get_fresnel(in const vec3 normal_w, in const vec3 eye_w, in const float power, in const float coeff) {
    vec2 fres;
    fres.x = clamp(dot(-eye_w, g_light_chara_dir.xyz), 0.0, 1.0);
    fres.x += pow(fres.x, power);
    fres.y = dot(normal_w, g_light_chara_dir.xyz) + 1.0;
    fres.y = clamp(fres.y * fres.y, 0.0, 1.0);
    return fres.x * fres.y * coeff;
}

vec3 get_ibl_diffuse(samplerCube diffuse_tex, in const vec3 ray, in const float lc) {
    vec3 col0 = textureLod(diffuse_tex, ray, 0.0).rgb;
    vec3 col1 = textureLod(diffuse_tex, ray, 1.0).rgb;
    return mix(col1, col0, lc);
}

vec3 get_light_coef_chara(sampler2D shadow_tex, in const vec3 normal, in const vec3 texcoord) {
    vec3 lc;
    if (SHADER_FLAGS_CHARA_SHADOW != 0) {
        lc.x = texture(shadow_tex, texcoord.xy).x;
        lc.x = (lc.x - texcoord.z) * g_esm_param.x;
        lc.x = clamp(exp2(lc.x * g_material_state_emission.w), 0.0, 1.0);

        lc.y = pow(clamp(dot(g_light_chara_dir.xyz, normal) + 1.0, 0.0, 1.0), 4.0);
        lc.y = min(lc.x, lc.y);
        lc.z = lc.y;
    }
    else
        lc = vec3(1.0);
    return lc;
}

vec3 get_normal_chara(in const vec3 normal_w, in const vec3 eye_w) {
    float view_facing = dot(eye_w, normal_w);
    float coeff = view_facing * 1.02;
    if (view_facing < 0.0) {
        return normal_w + eye_w * -coeff;
    } else {
        return normal_w;
    }
}

vec3 get_texcoord_shadow_chara(in const vec3 pos) {
    vec4 _pos = vec4(pos, 1.0);

    vec3 texcoord_shadow;
    if (SHADER_FLAGS_CHARA_SHADOW2 == 0)
        texcoord_shadow = vec4(pos, 1.0) * g_self_shadow_receivers[0];
    else
        texcoord_shadow = vec4(pos, 1.0) * g_self_shadow_receivers[1];
    return texcoord_shadow;
}

vec3 get_tone_curve(in const vec3 normal) {
    float tonecurve = dot(normal, g_chara_f_dir.xyz) * 0.5 + 0.5;
    tonecurve = clamp((tonecurve - g_chara_tc_param.x) * g_chara_tc_param.y, 0.0, 1.0);
    return mix(g_chara_f_ambient.rgb, g_chara_f_diffuse.rgb, tonecurve) * g_chara_tc_param.z;
}
#endif  // COMMON_CHARA
