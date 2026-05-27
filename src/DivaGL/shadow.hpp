/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../KKdLib/default.hpp"
#include "../KKdLib/time.hpp"
#include "../KKdLib/mat.hpp"
#include "../KKdLib/vec.hpp"
#include "../AFTModsShared/shared.hpp"
#include "../AFTModsShared/types.hpp"
#include "render_texture.hpp"

class Shadow {
public:
    void* __vftable;

private:
    RenderTexture rtex_table[7];
    RenderTexture* rtex_shadowmap;
    RenderTexture* rtex_soft[2];
    float_t m_view_region;
    float_t m_shadow_range;
    vec3 m_light_pos[2];
    vec3 m_light_target[2];
    vec3 m_proj_dist_base[2];
    float_t m_ground_ypos[2];
    float_t m_proj_dist_base_range[2];
    prj::vector<vec3> m_proj_dist_base_vec[2];
    int32_t m_group[2];
    float_t m_shadow_depth_range;
    vec3 m_light_dir;
    vec3 m_avg_light_pos;
    vec3 m_avg_light_target;
    mat4 m_view_mtx;
    mat4 m_iview_mtx;
    uint32_t m_proj_near_repeat;
    ImgfBoxSampl m_proj_near_sampl;
    uint32_t m_proj_far_repeat;
    ImgfBoxSampl m_proj_far_sampl;
    float_t m_proj_dist_attn;
    float_t m_proj_dist_attn_offset;
    float_t m_shadowmap_near_clip;
    float_t m_shadowmap_far_clip;
    float_t m_polyoffset_factor;
    float_t m_polyoffset_unit;
    float_t m_esm_exponent;
    float_t m_gauss_sigma;
    float_t m_gauss_offset;
    float_t m_shadow_ambient;
    bool m_enable_show_textures;
    int32_t m_num_group;
    bool m_enable_group[2];
    bool m_enable_self_shadow;
    bool m_enable[2];
    bool m_separate;

    void init_members();

    static bool check_culling0(const struct BSphere* bsphere);
    static bool check_culling1(const struct BSphere* bsphere);
    static bool check_culling_sub(const struct BSphere* bsphere, const mat4* lview);

protected:
    void set_light_view_proj_mtx(struct cam_data& cam, const vec3* light_pos,
        const vec3* light_target, float_t range, float_t offset, float_t scale);
    void calc_tex_mtx(const vec3* light_pos,
        const vec3* light_target, float_t range, float_t offset, mat4* tex_mtx);

public:
    int32_t create();
    void destroy();
    void set_light_dir(const vec3* dir);
    void enable_group(int32_t group);
    void set_dist_base(int32_t group, const vec3* pos);
    void set_ground_ypos(int32_t group, float_t ground_ypos);
    void begin_make_shadow_textures(int32_t group[2]);
    void end_make_shadow_textures(struct p_gl_rend_state& p_gl_rend_st);
    void begin_make_silhouette_map(struct render_data_context& rend_data_ctx, struct cam_data& cam, int32_t group, int32_t index);
    void end_make_silhouette_map(struct render_data_context& rend_data_ctx, int32_t group, int32_t index);
    void bind_shadow(struct render_data_context& rend_data_ctx);
    void unbind_shadow(struct render_data_context& rend_data_ctx);
    void clear(struct p_gl_rend_state& p_gl_rend_st);
    void set_cull_func(int32_t group);

    float_t get_distance() const;
    RenderTexture& get_rtex(int32_t index);
};

static_assert(sizeof(Shadow) == 0x2F8, "\"Shadow\" struct should have a size of 0x2F8");

extern void(FASTCALL* finish_shadow)();
extern void(FASTCALL* init_shadow)();

extern Shadow* get_shadow();

extern void shadow_patch();

// Inlined
inline void Shadow::set_ground_ypos(int32_t group, float_t ground_ypos) {
    m_ground_ypos[group] = ground_ypos;
}

// Inlined
inline RenderTexture& Shadow::get_rtex(int32_t index) {
    return rtex_table[index];
}
