#version 430 core
// leaf_particle.frag

layout(set = 1, binding = 0) uniform Scene {
    mat4 g_transform;
    vec4 g_view_pos;
    vec4 g_color;
    vec4 g_light_env_stage_diffuse;
    vec4 g_light_env_stage_specular;
    vec4 g_lit_dir;
    vec4 g_lit_luce;
};

layout(set = 0, binding = 0) uniform sampler2D g_diffuse;
layout(set = 0, binding = 9) uniform samplerCube g_ibl_diffuse;
layout(set = 0, binding = 10) uniform samplerCube g_ibl_specular;

layout(location = 0) out vec4 result;

layout(location = 0) in vec3 frg_normal;
layout(location = 1) in vec2 frg_texcoord;
layout(location = 2) in vec3 frg_eye;

void main() {
    vec4 col = texture(g_diffuse, frg_texcoord);
    result.a = col.a * g_color.a;

    if (result.a < 0.5)
        discard;

    vec3 normal = normalize(frg_normal);
    vec3 eye = normalize(frg_eye);

    vec2 fres;
    fres.x = dot(normal, eye);
    float luce_coeff = fres.x * fres.x;
    fres.y = pow(1.001 - max(fres.x, 0.0), 5.0);

    vec3 luce;
    luce.y = dot(-eye, g_lit_dir.xyz) * 0.5 + 0.5;
    luce.x = luce.y * luce.y * luce.y * luce_coeff;
    luce = g_lit_luce.rgb * (luce.x * 0.5);

    vec3 diff = textureLod(g_ibl_diffuse, normal, 0.0).rgb;
    diff *= g_light_env_stage_diffuse.rgb;
    diff += luce;
    diff *= col.rgb;
    diff += luce;

    vec3 reflect_vec = -reflect(eye, normal);
    vec3 spec = texture(g_ibl_specular, reflect_vec).rgb;
    spec *= g_light_env_stage_specular.rgb;
    spec *= col.rgb * 0.5 + 0.1;
    spec *= fres.y * 0.9 + 0.1;
    result.rgb = diff * g_color.rgb + spec;
}
