#version 430 core
// sun.frag

layout(set = 1, binding = 0) uniform SunQuad {
    mat4 g_transform;
    vec4 g_emission;
};

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord;

void main() {
    float alpha = texture(g_texture, frg_texcoord).a;
    if (alpha - 0.01 < 0.0)
        discard;

    result.rgb = alpha - 0.5 < 0.0 ? (vec3(2.0 * alpha)) : (g_emission.rgb * alpha);
    result.a = 1.0;
}
