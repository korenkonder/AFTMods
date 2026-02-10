#version 430 core
// ripple_emit.frag
//DEF
// 0 - Ripple
// 1 - Ripple Emit

#define      RIPPLE_DEF (_0 == 1)
#define RIPPLE_EMIT_DEF (_1 == 1)

layout(set = 1, binding = 0) uniform Scene {
    vec4 g_size_in_projection;
    vec4 g_transform;
    vec4 g_framebuffer_size;
};

#if RIPPLE_DEF
    layout(set = 0, binding = 7) uniform sampler2D g_texture;
#endif

layout(location = 0) out vec4 result;

layout(location = 0) in float frg_alpha;

void main() {
    #if RIPPLE_DEF
        #if RIPPLE_EMIT_DEF
            vec4 base = texture(g_texture, gl_FragCoord.xy * g_framebuffer_size.xy);
            result = base + vec4(frg_alpha * 0.2);
        #else
            result = vec4(frg_alpha - 0.2);
        #endif
    #else
        result = vec4(frg_alpha);
    #endif
}
