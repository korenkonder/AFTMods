#version 430 core
// box8.vert

layout(set = 1, binding = 0) uniform Scene {
    vec4 g_transform;
    vec4 g_texcoord;
};

#define result_position (gl_Position)

layout(location = 0) out vec4 result_texcoord0; //xy=texcoord0, zw=texcoord1
layout(location = 1) out vec4 result_texcoord1; //xy=texcoord2, zw=texcoord3
layout(location = 2) out vec4 result_texcoord2; //xy=texcoord4, zw=texcoord5
layout(location = 3) out vec4 result_texcoord3; //xy=texcoord6, zw=texcoord7

layout(location = 0) in vec2 a_texcoords[8];

void main() {
    vec2 pos;
    pos.x = -1.0 + float(gl_VertexID / 2 % 2) * 2.0;
    pos.y = 1.0 - float(gl_VertexID % 2) * 2.0;
    result_position = vec4(pos, 0.0, 1.0);

    vec2 tex = pos * 0.5 + 0.5;
    result_texcoord0.xy = (tex + a_texcoords[0] * g_transform.xy) * g_texcoord.xy;
    result_texcoord0.zw = (tex + a_texcoords[1] * g_transform.xy) * g_texcoord.xy;
    result_texcoord1.xy = (tex + a_texcoords[2] * g_transform.xy) * g_texcoord.xy;
    result_texcoord1.zw = (tex + a_texcoords[3] * g_transform.xy) * g_texcoord.xy;
    result_texcoord2.xy = (tex + a_texcoords[4] * g_transform.xy) * g_texcoord.xy;
    result_texcoord2.zw = (tex + a_texcoords[5] * g_transform.xy) * g_texcoord.xy;
    result_texcoord3.xy = (tex + a_texcoords[6] * g_transform.xy) * g_texcoord.xy;
    result_texcoord3.zw = (tex + a_texcoords[7] * g_transform.xy) * g_texcoord.xy;
}
