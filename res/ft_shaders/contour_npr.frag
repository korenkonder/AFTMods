#version 430 core
// contour_npr.frag

layout(set = 1, binding = 2) uniform ContourParams {
    vec4 g_near_far;
};

layout(set = 0, binding = 14) uniform sampler2D g_scene_depth_texture;
layout(set = 0, binding = 16) uniform sampler2D g_contour_color_texture;
layout(set = 0, binding = 17) uniform sampler2D g_contour_depth_texture;

layout(location = 0) out vec4 result;

layout(location = 0) in vec2 frg_texcoord;

void main() {
    float contour_depth = texture(g_contour_depth_texture,frg_texcoord).x;
    if (contour_depth < 1.0) {
        result = vec4(0.0, 0.0, 0.0, 1.0);

        bool has_contour = false;
        vec4 density = texture(g_contour_color_texture, frg_texcoord);
        if (any(greaterThan(density.xyz, vec3(0.0)))) {
            float scene_depth = texture(g_scene_depth_texture, frg_texcoord).x;

            contour_depth = (1.0 / (contour_depth - g_near_far.x)) * g_near_far.y;
            scene_depth = (1.0 / (scene_depth - g_near_far.x)) * g_near_far.y;

            has_contour = contour_depth <= scene_depth;
            if (has_contour) {
                if (density.y > 0.0) {
                    vec4 col1;
                    vec4 col2;
                    col1.x = textureOffset(g_contour_color_texture, frg_texcoord, ivec2(-1,  0)).x;
                    col1.y = textureOffset(g_contour_color_texture, frg_texcoord, ivec2( 1,  0)).x;
                    col1.z = textureOffset(g_contour_color_texture, frg_texcoord, ivec2( 0, -1)).x;
                    col1.w = textureOffset(g_contour_color_texture, frg_texcoord, ivec2( 0,  1)).x;
                    col2.x = textureOffset(g_contour_color_texture, frg_texcoord, ivec2(-1, -1)).x;
                    col2.y = textureOffset(g_contour_color_texture, frg_texcoord, ivec2( 1,  1)).x;
                    col2.z = textureOffset(g_contour_color_texture, frg_texcoord, ivec2(-1,  1)).x;
                    col2.w = textureOffset(g_contour_color_texture, frg_texcoord, ivec2( 1, -1)).x;

                    vec4 col1_mask = vec4(greaterThan(col1, vec4(density.y * 0.8)));
                    vec4 col2_mask = vec4(greaterThan(col2, vec4(density.y * 0.8)));
                    density.y *= float((dot(col1_mask, vec4(1.0)) + dot(col2_mask, vec4(1.0))) < 0.5);
                }

                if (density.w > 0.0) {
                    density.x = max(density.x, density.y * 0.05);

                    vec4 col2;
                    col2.x = textureOffset(g_contour_color_texture, frg_texcoord, ivec2(-1, -1)).x;
                    col2.y = textureOffset(g_contour_color_texture, frg_texcoord, ivec2( 1,  1)).x;
                    col2.z = textureOffset(g_contour_color_texture, frg_texcoord, ivec2(-1,  1)).x;
                    col2.w = textureOffset(g_contour_color_texture, frg_texcoord, ivec2( 1, -1)).x;
                    density.z *= (col2.x * col2.y) * (col2.z * col2.w);

                    if (density.x > 0.0 || density.z > 0.0)
                        density.x = max(density.x * 0.7 + 0.25, density.z);

                    result.a = density.x * 0.7;
                    result.rgb = vec3(0.4, 0.1, 0.2);
                }
                else {
                    density.x = max(density.x, density.y * 0.9);

                    density.x = max(density.x * 0.7 + 0.25, density.z);

                    result.a = density.x * 0.575;
                    result.rgb = vec3(0.0, 0.0, 0.158327416);
                }
            }
        }

        // Weird but needed
        if (has_contour == false)
            discard;

        return;
    }

    discard;
}
