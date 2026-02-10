#version 430 core
// dof_gather_tile.frag
//DEF

layout(set = 0, binding = 0) uniform sampler2D g_tile; //r=min_depth_m, g=max_coc_pixel

layout(location = 0) out vec2 result; //r=min_depth_m, g=max_coc_pixel

layout(location = 0) in vec2 frg_texcoord;

void main() {
    //3x3 sample
    vec2 texture_size = textureSize(g_tile, 0);
    vec2 texel_size = vec2(1.0) / texture_size;
    vec2 uv = frg_texcoord;
    const vec2 v00 = textureLod(g_tile, uv + vec2(-texel_size.x, -texel_size.y), 0.0).rg;
    const vec2 v01 = textureLod(g_tile, uv + vec2(          0.0, -texel_size.y), 0.0).rg;
    const vec2 v02 = textureLod(g_tile, uv + vec2( texel_size.x, -texel_size.y), 0.0).rg;
    const vec2 v10 = textureLod(g_tile, uv + vec2(-texel_size.x,           0.0), 0.0).rg;
    const vec2 v11 = textureLod(g_tile, uv + vec2(          0.0,           0.0), 0.0).rg;
    const vec2 v12 = textureLod(g_tile, uv + vec2( texel_size.x,           0.0), 0.0).rg;
    const vec2 v20 = textureLod(g_tile, uv + vec2(-texel_size.x,  texel_size.y), 0.0).rg;
    const vec2 v21 = textureLod(g_tile, uv + vec2(          0.0,  texel_size.y), 0.0).rg;
    const vec2 v22 = textureLod(g_tile, uv + vec2( texel_size.x,  texel_size.y), 0.0).rg;

    //depth min
    result.r = min(v00.r, v01.r);
    result.r = min(result.r, v02.r);
    result.r = min(result.r, v10.r);
    result.r = min(result.r, v11.r);
    result.r = min(result.r, v12.r);
    result.r = min(result.r, v20.r);
    result.r = min(result.r, v21.r);
    result.r = min(result.r, v22.r);
    //CoC max
    result.g = max(v00.g, v01.g);
    result.g = max(result.g, v02.g);
    result.g = max(result.g, v10.g);
    result.g = max(result.g, v11.g);
    result.g = max(result.g, v12.g);
    result.g = max(result.g, v20.g);
    result.g = max(result.g, v21.g);
    result.g = max(result.g, v22.g);
}
