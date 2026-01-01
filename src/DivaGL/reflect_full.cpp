/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "reflect_full.hpp"
#include "render_manager.hpp"
#include "static_var.hpp"

vec4 reflect_clip_plane = 0.0f;
bool reflect_draw = false;
mat4 reflect_mat = mat4_identity;
reflect_full_struct* reflect_full_ptr = 0;

reflect_full_struct::reflect_full_struct() : dof() {

}

reflect_full_struct::~reflect_full_struct() {
    free();
}

void reflect_full_struct::free() {
    if (dof) {
        delete dof;
        dof = 0;
    }

    reflect_contour_texture.Free();

    reflect_buffer_texture.Free();
    reflect_texture.Free();
}

void reflect_full_struct::init() {
    rndr::Render* render = render_manager.render;

    const float_t res_scale = clamp_def((float_t)((double_t)sv_reflect_res_scale / 100.0), 0.25f, 1.0f);

    int32_t render_width = (int32_t)prj::roundf((float_t)render->render_width[0] * res_scale);
    render_width = min_def(max_def(render_width, 128), render->render_width[0]);
    int32_t render_height = (int32_t)prj::roundf((float_t)render->render_height[0] * res_scale);
    render_height = min_def(max_def(render_height, 72), render->render_height[0]);

    reflect_texture.Init(render_width, render_height, 0, GL_RGBA16F, GL_DEPTH_COMPONENT24);
    reflect_buffer_texture.Init(render_width, render_height, 0, GL_RGBA16F, GL_DEPTH_COMPONENT24);

    reflect_contour_texture.SetColorDepthTextures(reflect_texture.GetColorTex());

    if (dof)
        dof->resize(render_width, render_height);
    else
        dof = new renderer::DOF3(render_width, render_height);
}
