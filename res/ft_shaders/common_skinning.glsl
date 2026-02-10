#ifndef COMMON_SKINNING
#define COMMON_SKINNING

#if SKINNING_DEF
layout(location = 1) in vec4 a_weight;
layout(location = 15) in uvec4 a_matrix_index;

layout(std430, set = 2, binding = 0) readonly buffer Skinning {
    vec4 g_joint_transforms[768];
};

vec3 apply_skinning(in const vec3 data, in const int mtxidx_comp) {
    const ivec3 mtxidx_row = ivec3(mtxidx_comp * 3) + ivec3(0, 1, 2);

    return vec3(
        dot(data, g_joint_transforms[mtxidx_row.x].xyz),
        dot(data, g_joint_transforms[mtxidx_row.y].xyz),
        dot(data, g_joint_transforms[mtxidx_row.z].xyz)
    );
}

vec3 apply_skinning(in const vec4 data, in const int mtxidx_comp) {
    const ivec3 mtxidx_row = ivec3(mtxidx_comp * 3) + ivec3(0, 1, 2);

    return vec3(
        dot(data, g_joint_transforms[mtxidx_row.x]),
        dot(data, g_joint_transforms[mtxidx_row.y]),
        dot(data, g_joint_transforms[mtxidx_row.z])
    );
}

vec3 apply_skinning(in const vec3 data, in const ivec4 mtxidx, in const vec4 weight) {
    vec3 data_w;
    data_w = apply_skinning(data, mtxidx[0]) * weight[0];
    data_w += apply_skinning(data, mtxidx[1]) * weight[1];
    data_w += apply_skinning(data, mtxidx[2]) * weight[2];
    data_w += apply_skinning(data, mtxidx[3]) * weight[3];
    return data_w;
}

vec4 apply_skinning(in const vec4 data, in const ivec4 mtxidx, in const vec4 weight) {
    vec3 data_w;
    data_w = apply_skinning(data, mtxidx[0]) * weight[0];
    data_w += apply_skinning(data, mtxidx[1]) * weight[1];
    data_w += apply_skinning(data, mtxidx[2]) * weight[2];
    data_w += apply_skinning(data, mtxidx[3]) * weight[3];
    return vec4(data_w, 1.0);
}

vec4 get_skinning_data(out ivec4 mtxidx) {
    mtxidx = min(ivec4(a_matrix_index), ivec4(255.0));
    return mix(vec4(0.0), vec4(a_weight.xyz, 1.0 - (a_weight.x + a_weight.y + a_weight.z)),
        lessThanEqual(ivec4(a_matrix_index), ivec4(255.0)));
}
#endif  // SKINNING_DEF
#endif  // COMMON_SKINNING
