/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "screen_shot.hpp"
#include "gl_rend_state.hpp"
#include "gl_state.hpp"
#include "render_context.hpp"
#include "shader_ft.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include <Helpers.h>

struct ScreenShotData {
    prj::string path;
    int32_t format;
    bool screen_shot_4x;
    int32_t width;
    int32_t height;
    GLuint buffer;
    const void* tex_data;
};

struct ScreenShotImpl {
    void* __vftable;
    prj::string path;
    int32_t format;
    bool screen_shot_4x;
    int32_t width;
    int32_t height;
    int32_t curr_width;
    int32_t curr_height;
    bool capture;
    texture* tex;
    GLuint data_buffers[2];
    ScreenShotData ss_data[2];
    int32_t data_buffer_index;
    void* thread; // Thrd_t
};

HOOK(bool, FASTCALL, sub_1401898E0, 0x00000001401898E0, __int64 a1, texture* tex) {
    struct struc_21 {
        int32_t width;
        int32_t height;
        int32_t pix_fmt;
        void* field_10;
    };

    if (!tex || !tex->width || !tex->height || !tex->glid)
        return false;

    static struc_21* (FASTCALL* sub_140188010)(struc_21*, int32_t width, int32_t height, int32_t pix_fmt)
        = (struc_21 * (FASTCALL*)(struc_21*, int32_t width, int32_t height, int32_t pix_fmt))0x0000000140188010;
    static void (FASTCALL* sub_1401880E0)(struc_21*)
        = (void (FASTCALL*)(struc_21*))0x00000001401880E0;
    static struc_21* (FASTCALL* sub_140188100)(struc_21*, struc_21*)
        = (struc_21 * (FASTCALL*)(struc_21*, struc_21*))0x0000000140188100;
    static void* (FASTCALL* sub_140188410)(struc_21*)
        = (void* (FASTCALL*)(struc_21*))0x0000000140188410;
    static struc_21* (FASTCALL* sub_140189B10)(struc_21*, struc_21*, bool, bool)
        = (struc_21 * (FASTCALL*)(struc_21*, struc_21*, bool, bool))0x0000000140189B10;

    struc_21 v9 = {};
    sub_140188010(&v9, tex->width, tex->height, 1);

    gl_state.bind_texture_2d(tex->glid);
    glGetTexImageDLL(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, sub_140188410(&v9));
    gl_state.bind_texture_2d(0);

    struc_21 v10 = {};
    sub_140188100(&v9, sub_140189B10(&v9, &v10, false, true));
    sub_1401880E0(&v10);
    sub_140188100((struc_21*)a1, &v9);
    sub_1401880E0(&v9);
    return true;
}

HOOK(void*, FASTCALL, ScreenShotData__read_data, 0x0000000140557A70, ScreenShotData* data) {
    const int32_t pixels = data->width * data->height;
    if (pixels <= 0)
        return 0;

    const int32_t size = (data->format == 2 ? 4 : 3) * pixels;
    void* _data = malloc(size);
    if (!_data)
        return 0;

    uint8_t* d = (uint8_t*)_data;
    glBindBuffer(GL_PIXEL_PACK_BUFFER, data->buffer);
    const uint8_t* s = (const uint8_t*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
    switch (data->format) {
    case 0:
    case 4:
        for (uint32_t i = pixels; i; i--) {
            d[0] = s[2];
            d[1] = s[1];
            d[2] = s[0];
            d += 3;
            s += 4;
        }
        break;
    case 1:
    case 3:
        for (uint32_t i = pixels; i; i--) {
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
            d += 3;
            s += 4;
        }
        break;
    case 2:
        for (uint32_t i = pixels; i; i--) {
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
            d[3] = s[3];
            d += 4;
            s += 4;
        }
        break;
    default:
        free(_data);
        _data = 0;
        break;
    }
    glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    return _data;
}

HOOK(void, FASTCALL, ScreenShotData__get_data, 0x0000000140557BE0, ScreenShotData* data) {
    if (!data->screen_shot_4x) {
        glBindBuffer(GL_PIXEL_PACK_BUFFER, data->buffer);
        glReadPixelsDLL(0, 0, data->width, data->height, GL_BGRA, GL_UNSIGNED_BYTE, 0);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
        gl_get_error_print();
        return;
    }

    static void* (FASTCALL * sprite_manager_sub_14063C9C0)(resolution_mode & mode, rectangle & rect, int32_t index)
        = (void* (FASTCALL*)(resolution_mode & mode, rectangle & rect, int32_t index))0x000000014063C9C0;
    static void* (FASTCALL * sprite_manager_sub_14063F140)(int32_t index, resolution_mode mode, const rectangle & rect)
        = (void* (FASTCALL*)(int32_t index, resolution_mode mode, const rectangle & rect))0x000000014063F140;

    render_data_context rend_data_ctx(GL_REND_STATE_POST_2D);

    rndr::Render* rend = render_get();
    rend->taa_buffer[rend->taa_texture].Bind(rend_data_ctx.state, 0);

    std::pair<resolution_mode, rectangle> v20[2] = {};
    for (int32_t i = 0; i < 2; i++) {
        sprite_manager_sub_14063C9C0(v20[i].first, v20[i].second, i);

        std::pair<resolution_mode, rectangle> v19;
        v19.first = v20[i].first;
        v19.second.pos = v20[i].second.pos * 2.0f;
        v19.second.size = v20[i].second.size * 2.0f;
        sprite_manager_sub_14063F140(i, v19.first, v19.second);
    }

    sprite_manager_set_view_projection(0);
    rend_data_ctx.state.disable_depth_test();
    rend_data_ctx.state.enable_blend();
    rend_data_ctx.state.disable_cull_face();
    sprite_manager_draw(rend_data_ctx, 0, 0, rend->temp_buffer.color_texture);
    sprite_manager_draw(rend_data_ctx, 3, 0, rend->temp_buffer.color_texture);

    vec2 v17 = 0.0f;
    resolution_mode_scale_pos(v17, v20[1].first,
        v20[1].second.pos, res_window_get()->resolution_mode);
    v17 *= 2.0f;

    vec2 v18 = 0.0;
    resolution_mode_scale_pos(v18, v20[1].first,
        v20[1].second.pos + v20[1].second.size, res_window_get()->resolution_mode);
    v18 *= 2.0f;

    rend_data_ctx.state.set_viewport((int32_t)v17.x, (int32_t)v17.y,
        (int32_t)(v18.x - v17.x), (int32_t)(v18.y - v17.y));

    rend_data_ctx.state.enable_cull_face();
    rend_data_ctx.state.disable_blend();
    rend_data_ctx.state.enable_depth_test();
    rend_data_ctx.state.bind_framebuffer(0);

    for (int32_t i = 0; i < 2; i++)
        sprite_manager_sub_14063F140(i, v20[i].first, v20[i].second);

    glBindBuffer(GL_PIXEL_PACK_BUFFER, data->buffer);
    texture* taa_tex = rend->taa_tex[rend->taa_texture];
    rend_data_ctx.state.bind_texture_2d(taa_tex ? taa_tex->glid : 0);

    glGetTexImageDLL(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0i64);
    rend_data_ctx.state.bind_texture_2d(0);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    gl_get_error_print();
}

HOOK(void, FASTCALL, ScreenShotImpl__copy, 0x0000000140557F50, ScreenShotImpl* impl) {
    render_data_context rend_data_ctx(GL_REND_STATE_POST_2D);
    rend_data_ctx.state.active_bind_texture_2d(0, impl->tex->glid);
    rend_data_ctx.state.copy_tex_sub_image_2d(GL_TEXTURE_2D, 0, 0, 0, 0, 0, impl->width, impl->height);

    float_t ratio = (float_t)(impl->curr_height * impl->curr_width) / (float_t)(impl->width * impl->height);
    float_t scale = 1.0f;
    if (ratio < 0.1f)
        rend_data_ctx.shader_flags.arr[U_REDUCE] = 1;
    else if (ratio < 0.6f) {
        scale = 0.75f;
        rend_data_ctx.shader_flags.arr[U_REDUCE] = 1;
    }
    else
        rend_data_ctx.shader_flags.arr[U_REDUCE] = 0;

    quad_shader_data quad = {};
    quad.g_texcoord_modifier = { 0.5f, 0.5f, 0.5f, 0.5f };
    quad.g_texel_size = { scale / (float_t)impl->width, scale / (float_t)impl->height, 0.0f, 0.0f };
    quad.g_color = 0.0f;
    quad.g_texture_lod = 0.0f;

    rctx->quad_ubo.WriteMemory(rend_data_ctx.state, quad);
    rend_data_ctx.state.bind_uniform_buffer_base(0, rctx->quad_ubo);

    rend_data_ctx.state.disable_depth_test();
    rend_data_ctx.state.disable_blend();
    rend_data_ctx.state.disable_cull_face();
    rend_data_ctx.state.set_viewport(0, 0, impl->curr_width, impl->curr_height);

    shaders_ft.set(rend_data_ctx.state, rend_data_ctx.shader_flags, SHADER_FT_REDUCE);
    rend_data_ctx.state.bind_vertex_array(rctx->common_vao);
    rend_data_ctx.state.draw_arrays(GL_TRIANGLE_STRIP, 0, 4);
    rend_data_ctx.state.bind_vertex_array(0);
    shader::unbind(rend_data_ctx.state);

    rend_data_ctx.state.enable_cull_face();
    rend_data_ctx.state.enable_blend();
    rend_data_ctx.state.enable_depth_test();
}

void screen_shot_patch() {
    INSTALL_HOOK(sub_1401898E0);

    INSTALL_HOOK(ScreenShotData__read_data);
    INSTALL_HOOK(ScreenShotData__get_data);
    INSTALL_HOOK(ScreenShotImpl__copy);
}
