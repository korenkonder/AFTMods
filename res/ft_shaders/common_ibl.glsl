#ifndef COMMON_IBL
#define COMMON_IBL

vec4 get_ibl_specular(samplerCube tex, samplerCube tex_rough, in const vec3 ray, in const float shininess) {
    vec4 spec = texture(tex, ray);
    vec4 spec_rough = texture(tex_rough, ray);
    return mix(spec_rough, spec, shininess);
}
#endif  // COMMON_IBL
