#version 430 core
// sprite.vert
//DEF
// 0 - Tex 0 Type
// 1 - Tex 1 Type
// 2 - Combiner

#define TEX_0_TYPE_1_DEF (_0 == 1)
#define TEX_0_TYPE_2_DEF (_0 == 2)
#define TEX_0_TYPE_3_DEF (_0 == 3)
#define TEX_1_TYPE_1_DEF (_1 == 1)
#define TEX_1_TYPE_2_DEF (_1 == 2)
#define TEX_1_TYPE_3_DEF (_1 == 3)
#define   COMBINER_1_DEF (_2 == 1)
#define   COMBINER_2_DEF (_2 == 2)

layout(set = 1, binding = 0) uniform Scene {
    mat4 g_transform;
    vec4 g_framebuffer_size;
};

#define result_position (gl_Position)

layout(location = 0) out vec4 result_color;
layout(location = 1) out vec4 result_texcoord; //xy=texcoord0, zw=texcoord1

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texcoords[2];

void main() {
    result_position = vec4(a_position, 1.0) * g_transform;
    result_color = a_color;
    result_texcoord.xy = a_texcoords[0];
    result_texcoord.zw = a_texcoords[1];
}
