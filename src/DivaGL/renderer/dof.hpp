/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../../KKdLib/default.hpp"
#include "../GL/uniform_buffer.hpp"
#include "fbo.hpp"

enum dof_debug_flags {
    DOF_DEBUG_USE_UI_PARAMS   = 0x01,
    DOF_DEBUG_ENABLE_DOF      = 0x02,
    DOF_DEBUG_ENABLE_PHYS_DOF = 0x04,
    DOF_DEBUG_AUTO_FOCUS      = 0x08,
};

struct dof_f2 {
    float_t focus;
    float_t focus_range;
    float_t fuzzing_range;
    float_t ratio;
};

static_assert(sizeof(dof_f2) == 0x10, "\"dof_f2\" struct should have a size of 0x10");

struct dof_debug {
    dof_debug_flags flags;
    float_t focus;
    float_t focal_length;
    float_t f_number;
    dof_f2 f2;
};

static_assert(sizeof(dof_debug) == 0x20, "\"dof_debug\" struct should have a size of 0x14");

struct dof_pv {
    bool enable;
    dof_f2 f2;
};

static_assert(sizeof(dof_pv) == 0x14, "\"dof_pv\" struct should have a size of 0x14");

struct RenderTexture;
struct render_data_context;

namespace renderer {
    class DOF3 {
    private:
        int32_t m_width;
        int32_t m_height;
        GLuint m_tex[6];
        FBO m_fbo[4];
        GLuint m_sampler[2];
        GLuint m_vao;
        GL::UniformBuffer m_common_ubo;
        GL::UniformBuffer m_texcoord_ubo[7];

    public:
        DOF3(int32_t width, int32_t height);
        ~DOF3();

        void apply(render_data_context& rend_data_ctx, RenderTexture* rt, RenderTexture* buf_rt);
        void resize(int32_t width, int32_t height); // Added

    private:
        void destroy();
        void create_render_buffer(int32_t width, int32_t height);

        void apply(render_data_context& rend_data_ctx,
            RenderTexture* rt, RenderTexture* buf_rt, GLuint color_texture,
            GLuint depth_texture, float_t min_distance, float_t max_distance,
            float_t focus, float_t focal_length, float_t fov, float_t f_number);
        void apply_f2(render_data_context& rend_data_ctx,
            RenderTexture* rt, RenderTexture* buf_rt, GLuint color_texture,
            GLuint depth_texture, float_t min_distance, float_t max_distance, float_t fov,
            float_t focus, float_t focus_range, float_t fuzzing_range, float_t ratio);

        void render_tiles(render_data_context& rend_data_ctx, GLuint depth_texture, bool f2);
        void downsample(render_data_context& rend_data_ctx, GLuint color_texture, GLuint depth_texture, bool f2);
        void apply_main_filter(render_data_context& rend_data_ctx, bool f2);
        void upsample(render_data_context& rend_data_ctx,
            RenderTexture* rt, RenderTexture* buf_rt,
            GLuint color_texture, GLuint depth_texture, bool f2);

        void bind_texture(p_gl_rend_state& p_gl_rend_st, GLuint unit, int32_t tex_index, int32_t sampler_index);
        void draw_quad(render_data_context& rend_data_ctx);

        void init_textures(int32_t width, int32_t height);
        void write_data(render_data_context& rend_data_ctx,
            float_t min_dist, float_t max_dist, float_t fov, float_t dist, float_t focal_length,
            float_t f_number, float_t focus_range, float_t fuzzing_range, float_t ratio);

        template <int32_t sample_division>
        static void calculate_texcoords(GL::UniformBuffer& buffer, const float_t size);
    };
}

extern dof_debug* dof_debug_data;
extern dof_pv* dof_pv_data;
