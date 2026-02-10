#version 430 core
// sss_filter_min.frag

layout(set = 0, binding = 0) uniform sampler2D g_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord0; //xy=texcoord0
layout(location = 1) in vec4 frg_texcoord1; //xy=texcoord1, zw=texcoord2
layout(location = 2) in vec4 frg_texcoord2; //xy=texcoord3, zw=texcoord4

void main() {
    vec4 col = texture(g_texture, frg_texcoord0);
    if (col.a != 1.0) {
        vec4 tmp = texture(g_texture, frg_texcoord1.xy);
        if (col.a < tmp.a)
            col = tmp;
        tmp = texture(g_texture, frg_texcoord1.zw);
        if (col.a < tmp.a)
            col = tmp;
        tmp = texture(g_texture, frg_texcoord2.xy);
        if (col.a < tmp.a)
            col = tmp;
        tmp = texture(g_texture, frg_texcoord2.zw);
        if (col.a < tmp.a)
            col = tmp;
    }
    result = col;
}
