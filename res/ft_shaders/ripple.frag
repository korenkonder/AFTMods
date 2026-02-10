#version 430 core
// ripple.frag
//DEF
// 0 - Ripple

#define RIPPLE_DEF (_0 == 1)

layout(set = 1, binding = 1) uniform Batch {
    vec4 g_params;
};

layout(set = 0, binding = 0) uniform sampler2D g_texture_current;
layout(set = 0, binding = 1) uniform sampler2D g_texture_prev;

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord0; //xy=texcoord0
layout(location = 1) in vec4 frg_texcoord1; //xy=texcoord1, zw=texcoord2
layout(location = 2) in vec4 frg_texcoord2; //xy=texcoord3, zw=texcoord4

void main() {
    #if RIPPLE_DEF
        float t0 = texture(g_texture_current, frg_texcoord0).w;
        float t1 = texture(g_texture_current, frg_texcoord1.xy).w;
        float t2 = texture(g_texture_current, frg_texcoord1.zw).w;
        float t3 = texture(g_texture_current, frg_texcoord2.xy).w;
        float t4 = texture(g_texture_current, frg_texcoord2.zw).w;
        vec4 sand;
        sand.x = t0 - t1;
        sand.y = t0 - t2;
        sand.z = t0 - t3;
        sand.w = t0 - t4;

        sand.x = dot(sand, sand) * 0.25 - g_params.z;
        sand.y = (t1 + t2 + t3 + t4) * 0.25 - t0;
        result.w = t0 + (sand.x > 0.0 ? sand.y * g_params.w : 0.0);

        vec3 normal;
        normal.x = t1 - t2;
        normal.y = t3 - t4;
        normal.z = 0.1;
        result.xyz = normalize(normal) * 0.5 + 0.5;
    #else
        float t1 = texture(g_texture_current, frg_texcoord1.xy).w * 2.0 - 1.0;
        float t2 = texture(g_texture_current, frg_texcoord1.zw).w * 2.0 - 1.0;
        float t3 = texture(g_texture_current, frg_texcoord2.xy).w * 2.0 - 1.0;
        float t4 = texture(g_texture_current, frg_texcoord2.zw).w * 2.0 - 1.0;
        float t_prev = texture(g_texture_prev, frg_texcoord0).w * 2.0 - 1.0;
        float t = t1 + t2 + t3 + t4 - t_prev * 2.0;
        vec4 h;
        h.x = t1 - t2;
        h.y = t2 - t3;
        h.z = 0.0;
        h.w = t - t * g_params.x;
        result = h * vec4(0.25, 0.25, 0.25, 0.5) + 0.5;
    #endif
}
