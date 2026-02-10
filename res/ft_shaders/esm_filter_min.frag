#version 430 core
// esm_filter_min.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord;

layout(set = 1, binding = 1) uniform Batch {
    vec4 g_params;
    vec4 g_gauss[2];
};

void main() {
    float dep0;
    float dep1;
    dep1 = texture(g_texture, frg_texcoord + g_params.xy * vec2( 1.0,  1.0)).x;
    dep0 = dep1;
    dep1 = texture(g_texture, frg_texcoord + g_params.xy * vec2(-1.0,  1.0)).x;
    dep0 = min(dep0, dep1);
    dep1 = texture(g_texture, frg_texcoord + g_params.xy * vec2( 1.0, -1.0)).x;
    dep0 = min(dep0, dep1);
    dep1 = texture(g_texture, frg_texcoord + g_params.xy * vec2(-1.0, -1.0)).x;
    dep0 = min(dep0, dep1);
    result = vec4(dep0);
}
