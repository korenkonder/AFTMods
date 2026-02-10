#ifndef COMMON_MORPH
#define COMMON_MORPH

vec2 apply_morph(in const vec2 data, in const vec2 morph_data) {
    return data * g_morph_weight.y + morph_data * g_morph_weight.x;
}

vec3 apply_morph(in const vec3 data, in const vec3 morph_data) {
    return data * g_morph_weight.y + morph_data * g_morph_weight.x;
}

vec4 apply_morph(in const vec4 data, in const vec4 morph_data) {
    return data * g_morph_weight.y + morph_data * g_morph_weight.x;
}

vec4 apply_morph_color(in vec4 color, in const vec4 data, in const vec4 morph_data) {
    if (SHADER_FLAGS_MORPH_COLOR != 0) {
        return color * apply_morph(data, morph_data);
    } else {
        return color * data;
    }
}
#endif  // COMMON_MORPH
