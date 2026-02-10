#ifndef COMMON_NPR_PARAM
#define COMMON_NPR_PARAM

// ITU-R BT.601
void to_ycbcr_601(out vec3 ybr, in vec3 rgb) {
    vec3  _y_coef_601 = vec3(    0.2989,     0.5866,     0.1145);
    vec3 _cb_coef_601 = vec3(-0.1687747, -0.3312253,        0.5);
    vec3 _cr_coef_601 = vec3(       0.5, -0.4183426, -0.0816574);
    ybr.r = dot(rgb, _cr_coef_601);
    ybr.g = dot(rgb,  _y_coef_601);
    ybr.b = dot(rgb, _cb_coef_601);
}

void to_rgb_601(out vec3 rgb, in vec3 ybr) {
    vec3 _red_coef_601 = vec3(   1.4022, 1.0,       0.0);
    vec3 _grn_coef_601 = vec3(-0.714486, 1.0, -0.345686);
    vec3 _blu_coef_601 = vec3(      0.0, 1.0,    1.7710);
    rgb.r = clamp(dot(ybr, _red_coef_601), 0.0, 1.0);
    rgb.g = clamp(dot(ybr, _grn_coef_601), 0.0, 1.0);
    rgb.b = clamp(dot(ybr, _blu_coef_601), 0.0, 1.0);
}
#endif  // COMMON_NPR_PARAM
