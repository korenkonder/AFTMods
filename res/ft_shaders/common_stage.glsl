#ifndef COMMON_STAGE
#define COMMON_STAGE

vec3 apply_fog_stage_depth(in const vec3 color, in const float fog) {
    if (SHADER_FLAGS_FOG_STAGE == 2 || SHADER_FLAGS_FOG_STAGE == 3)
        return mix(color.rgb, g_fog_height_color.rgb, fog);
    else
        return mix(color.rgb, g_fog_depth_color.rgb, fog);
}

vec3 apply_fog_stage(in const vec3 color, in float fog) {
    if (SHADER_FLAGS_FOG_STAGE == 2 || SHADER_FLAGS_FOG_STAGE == 3)
        return mix(color, g_fog_height_color.rgb, fog);
    else if (SHADER_FLAGS_FOG_STAGE == 1)
        return mix(color, g_fog_depth_color.rgb, fog);
    else
        return color;
}

vec4 get_shadow_stage(sampler2D shadow0_tex, sampler2D shadow_depth1_tex, in const vec3 texcoord_shadow0);
vec4 get_shadow_stage(sampler2D shadow0_tex, sampler2D shadow1_tex,
    sampler2D shadow_depth1_tex, in const vec3 texcoord_shadow0, in const vec3 texcoord_shadow1);

void apply_stage_shadow(sampler2D shadow0_tex,
    sampler2D shadow1_tex, sampler2D shadow_depth_tex,
    in const vec3 texcoord_shadow0, in const vec3 texcoord_shadow1,
    inout vec4 diff, inout vec4 spec) {
    if (SHADER_FLAGS_STAGE_SHADOW2 == 0) {
        vec4 shadow = get_shadow_stage(shadow0_tex,
            shadow_depth_tex, texcoord_shadow0);

        spec *= shadow;
        diff *= g_shadow_ambient1 * shadow + g_shadow_ambient;
    } else if (SHADER_FLAGS_STAGE_SHADOW2 == 1) {
        vec4 shadow = get_shadow_stage(shadow0_tex, shadow1_tex,
            shadow_depth_tex, texcoord_shadow0, texcoord_shadow1);

        spec *= shadow;
        diff *= g_shadow_ambient1 * shadow + g_shadow_ambient;
    }
}

float get_fog_stage(sampler2D effect_tex, in const vec4 pos_m, in const vec3 pos_w) {
    float depth = dot(vec2(dot(pos_m, g_worldview[2]), 1.0), g_forward_z_projection_row2.zw);

    if (SHADER_FLAGS_FOG_STAGE == 1) {
        float fog = clamp((depth - g_fog_state_params.y) * g_fog_state_params.w, 0.0, 1.0);
        return fog * g_fog_state_params.x;
    }
    else if (SHADER_FLAGS_FOG_STAGE == 2) {
        float fog = clamp((depth - g_fog_state_params.y) * g_fog_state_params.w, 0.0, 1.0);
        fog = fog * g_fog_state_params.x;

        float fog_height = clamp((-pos_w.y - g_fog_height_params.y) * g_fog_height_params.w, 0.0, 1.0);
        fog_height = fog_height * g_fog_height_params.x;

        return max(fog, fog_height);
    }
    else if (SHADER_FLAGS_FOG_STAGE == 3) {
        vec2 texcoord = pos_w.xz * vec2(0.0625, -0.0625) + vec2(0.5, 0.5);

        float eff_val = texture(effect_tex, texcoord).x;
        float fog = clamp(1.0 - (-pos_w.y - g_fog_height_params.y) * g_fog_height_params.w, 0.0, 1.0);
        eff_val = eff_val * 3.0 + 1.0;

        if (eff_val > 0.0)
            return (1.0 - pow(fog, eff_val)) * g_fog_height_params.x;
        else
            return 0.0;
    }
    else
        return 0.0;
}

vec4 get_light_coef_stage(in const vec3 normal_w, in const vec3 eye_w, in const vec3 lit_dir_w) {
    vec3 half_w = normalize(lit_dir_w + eye_w);

    vec4 lc;
    lc.x = 1.0;
    lc.y = clamp(dot(normal_w, lit_dir_w), 0.0, 1.0);
    lc.z = clamp(dot(normal_w, half_w), 0.0, 1.0);
    lc.z = pow(lc.z, g_material_state_shininess.x * 112.0 + 16.0);
    lc.w = 1.0;
    return lc;
}

vec4 get_shadow_stage(sampler2D shadow_tex, sampler2D shadow_depth1_tex, in const vec3 texcoord_shadow) {
    float shadow_depth = texture(shadow_depth1_tex, texcoord_shadow.xy).x;
    shadow_depth = clamp(exp2((shadow_depth - texcoord_shadow.z) * g_esm_param.x), 0.0, 1.0);

    vec4 shadow = texture(shadow_tex, texcoord_shadow.xy);
    return max(shadow, vec4(shadow_depth));
}

vec4 get_shadow_stage(sampler2D shadow0_tex, sampler2D shadow1_tex,
    sampler2D shadow_depth1_tex, in const vec3 texcoord_shadow0, in const vec3 texcoord_shadow1) {
    float shadow_depth0 = texture(shadow_depth1_tex, texcoord_shadow0.xy).x;
    shadow_depth0 = clamp(exp2((shadow_depth0 - texcoord_shadow0.z) * g_esm_param.x), 0.0, 1.0);

    float shadow_depth1 = texture(shadow_depth1_tex, texcoord_shadow1.xy).x;
    shadow_depth1 = clamp(exp2((shadow_depth1 - texcoord_shadow1.z) * g_esm_param.x), 0.0, 1.0);

    float shadow_depth = min(shadow_depth0, shadow_depth1);
    vec4 shadow0 = texture(shadow0_tex, texcoord_shadow0.xy);
    vec4 shadow1 = texture(shadow1_tex, texcoord_shadow1.xy);
    vec4 shadow = min(shadow0, shadow1);
    return max(shadow, vec4(shadow_depth));
}

void get_texcoord_shadow_stage(in const vec3 pos, out vec3 texcoord_shadow0, out vec3 texcoord_shadow1) {
    if (SHADER_FLAGS_STAGE_SHADOW != 0) {
        texcoord_shadow0 = vec4(pos, 1.0) * g_self_shadow_receivers[0];
        texcoord_shadow1 = vec4(pos, 1.0) * g_self_shadow_receivers[1];
    }
    else {
        texcoord_shadow0 = vec3(0.0);
        texcoord_shadow1 = vec3(0.0);
    }
}

vec4 texture_blend_apply(in const uint blend, in const vec4 col0, in const vec4 col1) {
    vec4 col;
    if (blend == 3) {
        col.rgb = col0.rgb * (col1.rgb * (1.0 / (0.004 + col1.a)));
        col.a = col0.a;
    } else if (blend == 0) {
        col.rgb = mix(col0.rgb, col1.rgb, col1.a);
        col.a = col0.a;
    } else if (blend == 1) {
        col = col0 * col1;
    } else if (blend == 2) {
        col.rgb = col0.rgb + col1.rgb;
        col.a = col0.a * col1.a;
    } else {
        col = col0;
    }
    return col;
}
#endif  // COMMON_STAGE
