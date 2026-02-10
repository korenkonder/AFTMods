#ifndef COMMON_SCENE
#define COMMON_SCENE

layout(set = 1, binding = 1) uniform Scene {
    mat4 g_irradiance_r_transforms;
    mat4 g_irradiance_g_transforms;
    mat4 g_irradiance_b_transforms;
    vec4 g_light_env_stage_diffuse;
    vec4 g_light_env_stage_specular;
    vec4 g_light_env_chara_diffuse;
    vec4 g_light_env_chara_ambient;
    vec4 g_light_env_chara_specular;
    vec4 g_light_env_reflect_diffuse;
    vec4 g_light_env_reflect_ambient;
    vec4 g_light_env_reflect_specular;
    vec4 g_light_env_proj_diffuse;
    vec4 g_light_env_proj_specular;
    vec4 g_light_env_proj_position;
    vec4 g_light_stage_dir;
    vec4 g_light_stage_diff;
    vec4 g_light_stage_spec;
    vec4 g_light_chara_dir;
    vec4 g_light_chara_spec;
    vec4 g_light_chara_luce;
    vec4 g_light_chara_back;
    vec4 g_light_face_diff;
    vec4 g_chara_color0;
    vec4 g_chara_color1;
    vec4 g_chara_f_dir;
    vec4 g_chara_f_ambient;
    vec4 g_chara_f_diffuse;
    vec4 g_chara_tc_param;
    vec4 g_fog_depth_color;
    vec4 g_fog_height_params; //x=density, y=start, z=end, w=1/(end-start)
    vec4 g_fog_height_color;
    vec4 g_fog_bump_params; //x=density, y=start, z=end, w=1/(end-start)
    vec4 g_fog_state_params; //x=density, y=start, z=end, w=1/(end-start)
    mat3x4 g_normal_tangent_transforms;
    vec4 g_esm_param;
    mat3x4 g_self_shadow_receivers[2];
    vec4 g_shadow_ambient;
    vec4 g_shadow_ambient1;
    vec4 g_framebuffer_size;
    vec4 g_light_reflect_dir;
    vec4 g_clip_plane;
    vec4 g_npr_cloth_spec_color;
    mat3x4 g_view;
    mat3x4 g_view_inverse;
    mat4 g_projection_view;
    vec4 g_view_position;
    mat4 g_light_projection;
    mat4 g_light_projection_depth;
    vec4 g_forward_z_projection_row2;
};

vec3 irradiance_transforms_get_color(in const vec3 normal) {
    vec4 _normal = vec4(normal, 1.0);
    vec3 col;
    col.r = dot(_normal, _normal * g_irradiance_r_transforms);
    col.g = dot(_normal, _normal * g_irradiance_g_transforms);
    col.b = dot(_normal, _normal * g_irradiance_b_transforms);
    return col;
}

vec3 sample_normal_texture(sampler2D normal_tex, in const vec2 texcoord,
    in const vec3 frg_normal, in const vec3 frg_tangent, in const vec3 frg_binormal) {
    vec4 normal_t;
    normal_t.xy = texture(normal_tex, texcoord).wy * 2.0 - 1.0;
    normal_t.zw = normal_t.xy * normal_t.xy * normal_t.xy;
    normal_t *= vec4(1.5, 1.5, 2.0, 2.0);
    normal_t.xy += normal_t.w;

    vec3 normal_w = frg_tangent * normal_t.x;
    normal_w += frg_binormal * normal_t.y;
    normal_w += frg_normal;
    return normalize(normal_w);
}
#endif  // COMMON_SCENE
