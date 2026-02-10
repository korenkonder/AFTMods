#version 430 core
// ripple.vert
//DEF
// 0 - Ripple

#define RIPPLE_DEF (_0 == 1)

layout(set = 1, binding = 0) uniform Scene {
    vec4 g_transform;
    vec4 g_texcoord;
};

#define result_position (gl_Position)

layout(location = 0) out vec2 result_texcoord0; //xy=texcoord0
layout(location = 1) out vec4 result_texcoord1; //xy=texcoord1, zw=texcoord2
layout(location = 2) out vec4 result_texcoord2; //xy=texcoord3, zw=texcoord4

void main() {
    vec2 pos;
    pos.x = -1.0 + float(gl_VertexID / 2 % 2) * 2.0;
    pos.y = -1.0 + float(gl_VertexID % 2) * 2.0;
    result_position = vec4(pos * g_transform.zw, 0.0, 1.0);

    vec2 tex = pos * 0.5 + 0.5;
    result_texcoord0 = tex;
    result_texcoord1 = tex.xyxy + vec4(-1.0,  0.0, 1.0, 0.0) * g_transform.xyxy;
    result_texcoord2 = tex.xyxy + vec4( 0.0, -1.0, 0.0, 1.0) * g_transform.xyxy;
}
