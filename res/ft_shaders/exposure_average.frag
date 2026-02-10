#version 430 core
// exposure_average.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

void main() {
    vec4 sum;
    sum = texture(g_texture, vec2(0.03125, 0.25));
    sum += texture(g_texture, vec2(0.09375, 0.25));
    sum += texture(g_texture, vec2(0.15625, 0.25));
    sum += texture(g_texture, vec2(0.21875, 0.25));
    sum += texture(g_texture, vec2(0.28125, 0.25));
    sum += texture(g_texture, vec2(0.34375, 0.25));
    sum += texture(g_texture, vec2(0.40625, 0.25));
    sum += texture(g_texture, vec2(0.46875, 0.25));
    sum += texture(g_texture, vec2(0.53125, 0.25));
    sum += texture(g_texture, vec2(0.59375, 0.25));
    sum += texture(g_texture, vec2(0.65625, 0.25));
    sum += texture(g_texture, vec2(0.71875, 0.25));
    sum += texture(g_texture, vec2(0.78125, 0.25));
    sum += texture(g_texture, vec2(0.84375, 0.25));
    sum += texture(g_texture, vec2(0.90625, 0.25));
    sum += texture(g_texture, vec2(0.96875, 0.25));
    result = sum * 0.0625;
}
