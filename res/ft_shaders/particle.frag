#version 430 core
// particle.frag

layout(set = 1, binding = 0) uniform Scene {
    mat4 g_transform;
    vec4 g_view_pos;
    vec4 g_light_env_chara_diffuse;
    vec4 g_light_env_chara_specular;
};

layout(set = 0, binding = 9) uniform samplerCube g_ibl_diffuse;
layout(set = 0, binding = 10) uniform samplerCube g_ibl_specular;
layout(set = 0, binding = 11) uniform samplerCube g_ibl_specular_rough;

layout(location = 0) out vec4 result;

layout(location = 0) in vec3 frg_normal;
layout(location = 1) in vec4 frg_color;
layout(location = 2) in vec2 frg_texcoord;
layout(location = 3) in vec3 frg_eye;

void main() {
    vec3 normal = normalize(frg_normal);
    vec3 reflect_vec = -reflect(frg_eye, normal);

    vec4 diff = textureLod(g_ibl_diffuse, normal, 0.0);
    diff *= g_light_env_chara_diffuse;
    diff *= frg_color;

    vec4 ibl_spec = texture(g_ibl_specular, reflect_vec);
    vec3 ibl_spec_rough = texture(g_ibl_specular_rough, reflect_vec).rgb;
    ibl_spec.rgb = mix(ibl_spec_rough, ibl_spec.rgb, 1.0 / 28.000224);
    ibl_spec *= g_light_env_chara_specular;

    result = diff * 0.75 + ibl_spec * 0.5;
}
