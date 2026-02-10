#ifndef COMMON_BATCH
#define COMMON_BATCH

layout(set = 1, binding = 2) uniform Batch {
    mat4 g_transforms;
    mat3x4 g_worlds;
    mat3x4 g_worlds_invtrans;
    mat3x4 g_worldview;
    mat3x4 g_worldview_inverse;
    mat3x4 g_joint;
    mat3x4 g_joint_inverse;
    mat2x4 g_texcoord_transforms[2];
    vec4 g_blend_color;
    vec4 g_offset_color;
    vec4 g_material_state_diffuse;
    vec4 g_material_state_ambient;
    vec4 g_material_state_emission;
    vec4 g_material_state_shininess;
    vec4 g_material_state_specular;
    vec4 g_fresnel_coefficients;
    vec4 g_texture_color_coefficients;
    vec4 g_texture_color_offset;
    vec4 g_texture_specular_coefficients;
    vec4 g_texture_specular_offset;
    vec4 g_shininess;
    vec4 g_max_alpha;
    vec4 g_morph_weight;
    vec4 g_sss_param;
    vec4 g_bump_depth;
    vec4 g_intensity;
    vec4 g_reflect_uv_scale;
};

vec4 get_fresnel_coefficient(in const float fres, in const float coef) {
    vec4 fres_coef;
    fres_coef.rgb = vec3(fres * g_fresnel_coefficients.x + g_fresnel_coefficients.y);
    fres_coef.w = fres * g_fresnel_coefficients.x * coef + 1.0;
    return fres_coef;
}

float get_max_alpha(in const float alpha) {
    #if ALPHA_TEST_DEF
        return g_max_alpha.z < 0.5 ? max(alpha, g_max_alpha.w) : 1.0;
    #else
        return max(alpha, g_max_alpha.w);
    #endif
}
#endif  // COMMON_BATCH
