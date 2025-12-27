/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "hook.hpp"
#include "Glitter/glitter.hpp"
#include "data_test/rob_osage_test.hpp"
#include "graphics/color_change_dw.hpp"
#include "mdl/disp_manager.hpp"
#include "pv_game/pv_game.hpp"
#include "rob/rob.hpp"
#include "auth_3d.hpp"
#include "camera.hpp"
#include "effect.hpp"
#include "light_param.hpp"
#include "object.hpp"
#include "print.hpp"
#include "resource.h"
#include "render_manager.hpp"
#include "render_texture.hpp"
#include "screen_shot.hpp"
#include "shader_ft.hpp"
#include "sprite.hpp"
#include "stage.hpp"
#include "static_var.hpp"
#include "task_movie.hpp"
#include "texture.hpp"
#include <Helpers.h>

static HGLRC FASTCALL glut_create_context(int64_t a1, int64_t a2, int64_t a3, int64_t a4, int32_t a5);

#ifdef DEBUG
static void APIENTRY gl_debug_output(GLenum source, GLenum type, uint32_t id,
    GLenum severity, GLsizei length, const char* message, const void* userParam);
#endif

HOOK(int32_t, FASTCALL, data_init, 0x0000000140192FF0) {
#ifdef DEBUG
    if (DIVA_GL_VERSION_4_3) {
        typedef void (APIENTRY* GLDEBUGPROC)(GLenum source, GLenum type, GLuint id,
            GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

        typedef void (GLAPIENTRY* PFNGLDEBUGMESSAGECALLBACKPROC)(GLDEBUGPROC callback, const void* userParam);
        PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback
            = (PFNGLDEBUGMESSAGECALLBACKPROC)wglGetProcAddressDLL("glDebugMessageCallback");
        typedef void (GLAPIENTRY* PFNGLDEBUGMESSAGECONTROLPROC)(GLenum source,
            GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled);
        PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl
            = (PFNGLDEBUGMESSAGECONTROLPROC)wglGetProcAddressDLL("glDebugMessageControl");

        glEnableDLL(GL_DEBUG_OUTPUT);
        glEnableDLL(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(gl_debug_output, 0);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
    }
#endif

    glGetIntegervDLL(GL_MAX_TEXTURE_SIZE, &sv_max_texture_size);
    glGetIntegervDLL(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &sv_max_texture_max_anisotropy);
    glGetIntegervDLL(GL_MAX_UNIFORM_BLOCK_SIZE, &sv_max_uniform_buffer_size);
    if (DIVA_GL_VERSION_4_3)
        glGetIntegervDLL(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, &sv_max_storage_buffer_size);
    glGetIntegervDLL(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &sv_min_uniform_buffer_alignment);
    if (DIVA_GL_VERSION_4_3)
        glGetIntegervDLL(GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT, &sv_min_storage_buffer_alignment);

    sprite_shared_init();

    auth_3d_patch();
    camera_patch();
    color_change_dw_patch();
    mdl::disp_manager_patch();
    effect_patch();
    light_param_patch();
    object_patch();
    pv_game_patch();
    render_manager_patch();
    render_texture_patch();
    rob_patch();
    screen_shot_patch();
    shadow_patch();
    sprite_patch();
    stage_patch();
    task_movie_patch();
    texture_patch();
    Glitter::Patch();

    rctx = new render_context;
    reflect_full_init();
    int32_t ret = originaldata_init();

    extern size_t diva_handle;
    diva_handle = (size_t)WindowFromDC(wglGetCurrentDC());

    rctx->init();
    Glitter::Init();
    sprite_manager_init();
    pv_game_init();
    color_change_dw_init();
    rob_osage_test_init();
    return ret;
}

HOOK(int32_t, FASTCALL, data_free, 0x000000140192490) {
    rob_osage_test_free();
    color_change_dw_free();
    pv_game_free();
    sprite_manager_free();
    Glitter::Free();
    rctx->free();

    int32_t ret = originaldata_free();
    reflect_full_free();
    delete rctx;
    rctx = 0;
    return ret;
}

HOOK(void, FASTCALL, display_callback, 0x000000140194CD0) {
    rctx->ctrl();
    originaldisplay_callback();
    render_data_context rend_data_ctx(GL_REND_STATE_POST_2D);
    rend_data_ctx.state.finish();
}

HOOK(void, FASTCALL, draw_state_stats_update, 0x0000000140441410) {
    draw_state.stats_prev.reset();

    for (draw_state_struct::render_data& i : rctx->draw_state_rend_data) {
        draw_state.stats_prev.sub_mesh_count += i.stats.sub_mesh_count;
        draw_state.stats_prev.sub_mesh_no_mat_count += i.stats.sub_mesh_no_mat_count;
        draw_state.stats_prev.sub_mesh_cheap_count += i.stats.sub_mesh_cheap_count;
        draw_state.stats_prev.field_C += i.stats.field_C;
        draw_state.stats_prev.field_10 += i.stats.field_10;
        draw_state.stats_prev.draw_count += i.stats.draw_count;
        draw_state.stats_prev.draw_triangle_count += i.stats.draw_triangle_count;
        draw_state.stats_prev.field_1C += i.stats.field_1C;
        i.stats.reset();
    }
}

HOOK(void, FASTCALL, rndr__Render__update_res, 0x00000001404A9480, rndr::Render* rend, bool set, int32_t base_downsample) {
    rend->update_res(set, base_downsample);
}

HOOK(void, FASTCALL, rndr__Render__take_ss, 0x00000001404A9CD0,
    rndr::Render* rend, texture* tex, bool vertical, float_t horizontal_offset) {
    render_data_context rend_data_ctx(GL_REND_STATE_POST_2D);
    rend->take_ss(rend_data_ctx, tex, vertical, horizontal_offset);
}

HOOK(void, FASTCALL, rndr__Render__init_post_process_buffers, 0x00000001404A9FF0, rndr::Render* rend) {
    rend->init_post_process_buffers();
}

HOOK(void, FASTCALL, rndr__Render__init_render_buffers, 0x00000001404AB0C0, rndr::Render* rend,
    int32_t width, int32_t height, int32_t ssaa, int32_t hd_res, int32_t ss_alpha_mask) {
    rend->init_render_buffers(width, height, ssaa, hd_res, ss_alpha_mask);
}

HOOK(void, FASTCALL, rndr__Render__free, 0x00000001404AB900, rndr::Render* rend) {
    rend->free();
}

HOOK(void, FASTCALL, rndr__Render__frame_texture_free, 0x00000001404AE6C0, rndr::Render* rend) {
    return rend->frame_texture_free();
}

HOOK(void, FASTCALL, rndr__Render__render_texture_set, 0x00000001404B1560,
    rndr::Render* rend, texture* render_texture, bool task_photo) {
    rend->render_texture_set(render_texture, task_photo);
}

HOOK(int32_t, FASTCALL, rndr__Render__frame_texture_load, 0x00000001404B1600,
    rndr::Render* rend, int32_t slot, rndr::Render::FrameTextureType type, texture* tex) {
    return rend->frame_texture_load(slot, type, tex);
}

HOOK(void, FASTCALL, rndr__Render__movie_texture_set, 0x00000001404B16A0,
    rndr::Render* rend, texture* movie_texture) {
    rend->movie_texture_set(movie_texture);
}

HOOK(void, FASTCALL, rndr__Render__render_texture_free, 0x00000001404B1880,
    rndr::Render* rend, texture* render_texture, bool task_photo) {
    rend->render_texture_free(render_texture, task_photo);
}

HOOK(void, FASTCALL, rndr__Render__movie_texture_free, 0x00000001404B18F0,
    rndr::Render* rend, texture* movie_texture) {
    rend->movie_texture_free(movie_texture);
}

HOOK(bool, FASTCALL, rndr__Render__frame_texture_unload, 0x00000001404B30A0,
    rndr::Render* rend, int32_t slot, texture* tex) {
    return rend->frame_texture_unload(slot, tex);
}

HOOK(void, FASTCALL, rndr__RenderManager__rndpass_pre_proc, 0x0000000140502C90) {
    render_data_context rend_data_ctx(GL_REND_STATE_PRE_3D);
    rend_data_ctx.state.get();
    rend_data_ctx.state.begin_event("rndpass_pre_proc");
    render_manager.render->pre_proc(rend_data_ctx);
    Glitter::glt_particle_manager->CalcDisp();
    Glitter::glt_particle_manager_x->CalcDisp();
    rctx->pre_proc();
    rend_data_ctx.state.end_event();
}

HOOK(void, FASTCALL, rndr__RenderManager__render_all, 0x0000000140502CA0) {
    render_manager.render_all();
}

HOOK(void, FASTCALL, rndr__RenderManager__rndpass_post_proc, 0x0000000140502C70) {
    render_data_context rend_data_ctx(GL_REND_STATE_POST_2D);
    rend_data_ctx.state.begin_event("rndpass_post_proc");
    rctx->post_proc();
    render_manager.render->post_proc();
    render_manager.npr_mask = false;
    rend_data_ctx.state.end_event();
}

HOOK(void, FASTCALL, SelModule__DispRandom, 0x000000014058FCE0, __int64 a1) {
    float_t alpha_next = (float_t)*(int32_t*)(a1 + 748) * 4.0f * 0.025f;
    alpha_next = clamp_def(alpha_next, 0.0f, 1.0f);

    static size_t(FASTCALL * module_data_handler_data_get)() = (size_t(FASTCALL*)())0x00000001403F8C30;
    static bool (FASTCALL * module_data_handler__check_random)(size_t This, int32_t id)
        = (bool (FASTCALL*)(size_t This, int32_t id))0x00000001403F8E70;
    static int32_t(FASTCALL * sub_1405905D0)(int32_t* a1)
        = (int32_t(FASTCALL*)(int32_t* a1))0x00000001405905D0;

    static const int32_t* dword_140A36538 = (const int32_t*)0x0000000140A36538;
    static const int32_t* spr_sel_module_rnd_only_spr = (const int32_t*)0x0000000140A36620;
    static const int32_t* spr_sel_module_rnd_all_spr = (const int32_t*)0x0000000140A36650;

    vec3* pos = (vec3*)(a1 + 600);
    int32_t* v5 = (int32_t*)(a1 + 148);
    int32_t* v6 = (int32_t*)(a1 + 124);
    for (int32_t i = 0; i < 3; i++, v6 += 2, v5++, pos++) {
        if (i >= *(int32_t*)(a1 + 720) || *v5 != 9
            || !*(uint8_t*)(a1 + 595 + i) || !*(uint8_t*)(a1 + 592 + i))
            continue;

        if (!module_data_handler__check_random(module_data_handler_data_get(), v6[1]))
            continue;

        int32_t index = sub_1405905D0(v6);
        if (index < 0)
            continue;

        int32_t index_next = -1;
        if (!index) {
            int32_t v14 = *(int32_t*)(a1 + 744);
            int32_t v15 = v14;
            if (++v15 >= 10)
                v15 = 0;

            index = dword_140A36538[v14];
            index_next = dword_140A36538[v15];
        }

        float_t alpha = 1.0f;
        texture* rnd_tex = 0;
        texture* rnd_tex_next = 0;
        if (index_next >= 0) {
            rnd_tex = sprite_manager_get_spr_texture(
                sprite_database_get_spr_by_id(spr_sel_module_rnd_all_spr[index])->info);
            rnd_tex_next = sprite_manager_get_spr_texture(
                sprite_database_get_spr_by_id(spr_sel_module_rnd_all_spr[index_next])->info);
            alpha = 1.0f - alpha_next;
        }
        else
            rnd_tex = sprite_manager_get_spr_texture(
                sprite_database_get_spr_by_id(spr_sel_module_rnd_only_spr[index])->info);

        if (!rnd_tex)
            continue;

        mat4 mat;
        mat4_translate(pos->x + 0.04f, pos->y, pos->z, &mat);
        mat4_mul_rotate_x(&mat, (float_t)(12.0 * DEG_TO_RAD), &mat);
        mat4_scale_rot(&mat, 0.92f, 1.03f, 1.0f, &mat);
        mat4_transpose(&mat, &mat);

        texture_pattern_struct tex_pat(0x9A61, rnd_tex->id);
        disp_manager->set_texture_pattern(1, &tex_pat);
        disp_manager->entry_obj_by_object_info(mat, object_info(0x00, 0x07F5), alpha);
        disp_manager->set_texture_pattern();

        if (rnd_tex_next) {
            mat4_transpose(&mat, &mat);
            mat4_mul_translate_z(&mat, 0.01f, &mat);
            mat4_transpose(&mat, &mat);

            texture_pattern_struct tex_pat(0x9A61, rnd_tex_next->id);
            disp_manager->set_texture_pattern(1, &tex_pat);
            disp_manager->entry_obj_by_object_info(mat, object_info(0x00, 0x07F5), alpha_next);
            disp_manager->set_texture_pattern();
        }
    }

    int32_t& v24 = *(int32_t*)(a1 + 748);
    if (++v24 > 40) {
        v24 = 0;
        int32_t& v23 = *(int32_t*)(a1 + 744);
        if (++v23 >= 10)
            v23 = 0;
    }
}

HOOK(void, FASTCALL, shader_free, 0x00000001405E4DB0) {
    shaders_ft.unload();
}

HOOK(void, FASTCALL, shader_load_all_shaders, 0x00000001405E4FC0) {
    extern size_t dll_handle;
    HRSRC res = FindResourceA((HMODULE)dll_handle, MAKEINTRESOURCEA(IDR_FT_SHADERS_FARC1), "ft_shaders_farc");
    if (res) {
        DWORD size = SizeofResource((HMODULE)dll_handle, res);
        HGLOBAL data = LoadResource((HMODULE)dll_handle, res);

        farc f;
        f.read(data, size, true);
        shaders_ft.load(&f, false, "ft", shader_ft_table, shader_ft_table_size,
            shader_ft_bind_func_table, shader_ft_bind_func_table_size,
            shader_ft_get_index_by_name);
    }
}

HOOK(int32_t, FASTCALL, shader_get_index_by_name, 0x00000001405E4ED0, const char* name) {
    return shaders_ft.get_index_by_name(name);
}

HOOK(void, FASTCALL, set_render_defaults, 0x00000001401948B0) {
    glClearDepthDLL(1.0);
    glClearStencilDLL(0);
    //glShadeModelDLL(GL_SMOOTH);
    glPolygonModeDLL(GL_FRONT_AND_BACK, GL_FILL);
    glDisableDLL(GL_MULTISAMPLE);
    glDisableDLL(GL_DITHER);
    glEnableDLL(GL_DEPTH_TEST);
    glDepthFuncDLL(GL_LEQUAL);
    glEnableDLL(GL_CULL_FACE);
    glFrontFaceDLL(GL_CCW);
    glCullFaceDLL(GL_BACK);
    //glClampColorARB(GL_CLAMP_VERTEX_COLOR_ARB, GL_ZERO);
    //glClampColorARB(GL_CLAMP_FRAGMENT_COLOR_ARB, GL_FIXED_ONLY_ARB);
    //glClampColorARB(GL_CLAMP_READ_COLOR_ARB, GL_FIXED_ONLY_ARB);
    glPixelStoreiDLL(GL_UNPACK_ALIGNMENT, 1);
}

HOOK(GLenum, FASTCALL, gl_check_framebuffer_status, 0x0000000140503240) {
    GLenum ret = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (ret != GL_FRAMEBUFFER_COMPLETE)
        return ret;

    return GL_FRAMEBUFFER_COMPLETE;
}

void hook_funcs() {
    WRITE_NOP_5(0x0000000140441290);
    WRITE_JUMP(0x00000001404412E2, 0x00000001404413BD);
    WRITE_NOP(0x00000001404412E7, 0xD6);

    INSTALL_HOOK(data_init);
    INSTALL_HOOK(data_free);

    INSTALL_HOOK(display_callback);

    INSTALL_HOOK(draw_state_stats_update);

    INSTALL_HOOK(rndr__Render__update_res);
    INSTALL_HOOK(rndr__Render__take_ss);
    INSTALL_HOOK(rndr__Render__init_post_process_buffers);
    INSTALL_HOOK(rndr__Render__init_render_buffers);
    INSTALL_HOOK(rndr__Render__free);
    INSTALL_HOOK(rndr__Render__frame_texture_free);
    INSTALL_HOOK(rndr__Render__render_texture_set);
    INSTALL_HOOK(rndr__Render__frame_texture_load);
    INSTALL_HOOK(rndr__Render__movie_texture_set);
    INSTALL_HOOK(rndr__Render__render_texture_free);
    INSTALL_HOOK(rndr__Render__movie_texture_free);
    INSTALL_HOOK(rndr__Render__frame_texture_unload);

    INSTALL_HOOK(rndr__RenderManager__rndpass_pre_proc);
    INSTALL_HOOK(rndr__RenderManager__render_all);
    INSTALL_HOOK(rndr__RenderManager__rndpass_post_proc);

    INSTALL_HOOK(SelModule__DispRandom);

    INSTALL_HOOK(shader_free);
    INSTALL_HOOK(shader_load_all_shaders);
    INSTALL_HOOK(shader_get_index_by_name);

    INSTALL_HOOK(set_render_defaults);

    INSTALL_HOOK(gl_check_framebuffer_status);

    uint8_t buf[0x0C] = {};
    buf[0x00] = 0x48; // mov rax, 0
    buf[0x01] = 0xB8;
    buf[0x0A] = 0xFF; // jmp rax
    buf[0x0B] = 0xE0;

#if 0
    // auth_3d_event_printf
    *(uint64_t*)&buf[0x02] = (uint64_t)&printf_proxy;
    WRITE_MEMORY_STRING(0x00000001401D3860, buf, 0x0C);

    // Debug printf I think?
    *(uint64_t*)&buf[0x02] = (uint64_t)&printf_proxy;
    WRITE_MEMORY_STRING(0x00000001400DE640, buf, 0x0C);
#endif

    extern size_t glut_handle;
    *(uint64_t*)&buf[0x02] = (uint64_t)&glut_create_context;
    WRITE_MEMORY_STRING(glut_handle + 0x0000A970, buf, 0x0C);

    WRITE_RETURN(0x0000000140442DF0); // gl_rend_state::get

    WRITE_RETURN(0x00000001405E5600); // env_set_blend_color
    WRITE_RETURN(0x00000001405E5630); // env_set_offset_color
}

static HGLRC FASTCALL glut_create_context(int64_t a1, int64_t a2, int64_t a3, int64_t a4, int32_t a5) {
    extern size_t glut_handle;
    HDC& XHDC = *(HDC*)(glut_handle + 0x55F20);

    if (true/*a5*/) {
        typedef HGLRC(GLAPIENTRY* PFNWGLCREATECONTEXTGLUTPROC)(HDC hDc);

        HGLRC tmp_ctx = wglCreateContextGLUT(XHDC);;
        wglMakeCurrentGLUT(XHDC, tmp_ctx);
        PFNWGLCREATECONTEXTATTRIBSARBPROC _wglCreateContextAttribsARB
            = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddressGLUT("wglCreateContextAttribsARB");

        int32_t minor = 6;
        HGLRC ctx = 0;
        while (!ctx && minor >= 1) {
            const int32_t attrib_list[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
                WGL_CONTEXT_MINOR_VERSION_ARB, minor,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifdef DEBUG
                WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB,
#else
                WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
#endif
                0,
            };
            ctx = _wglCreateContextAttribsARB(XHDC, 0, attrib_list);;
            minor--;
        }
        wglMakeCurrentGLUT(XHDC, ctx);
        wglDeleteContextGLUT(tmp_ctx);
        return ctx;
    }
    else
        return wglCreateContextGLUT(XHDC);
}

#ifdef DEBUG
static void APIENTRY gl_debug_output(GLenum source, GLenum type, uint32_t id,
    GLenum severity, GLsizei length, const char* message, const void* userParam) {
    if (!id && severity == GL_DEBUG_SEVERITY_NOTIFICATION
        || id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;

    printf_divagl("########################################\n");
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        printf_divagl("Type: Error;                ");
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        printf_divagl("Type: Deprecated Behaviour; ");
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        printf_divagl("Type: Undefined Behaviour;  ");
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        printf_divagl("Type: Portability;          ");
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        printf_divagl("Type: Performance;          ");
        break;
    case GL_DEBUG_TYPE_MARKER:
        printf_divagl("Type: Marker;               ");
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        printf_divagl("Type: Push Group;           ");
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        printf_divagl("Type: Pop Group;            ");
        break;
    case GL_DEBUG_TYPE_OTHER:
        printf_divagl("Type: Other;                ");
        break;
    }

    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        printf_divagl("Severity: high;   ");
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        printf_divagl("Severity: medium; ");
        break;
    case GL_DEBUG_SEVERITY_LOW:
        printf_divagl("Severity: low;    ");
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        printf_divagl("Severity: notif;  ");
        break;
    }

    switch (source) {
    case GL_DEBUG_SOURCE_API:
        printf_divagl("Source: API\n");
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        printf_divagl("Source: Window System\n");
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        printf_divagl("Source: Shader Compiler\n");
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        printf_divagl("Source: Third Party\n");
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        printf_divagl("Source: Application\n");
        break;
    case GL_DEBUG_SOURCE_OTHER:
        printf_divagl("Source: Other\n");
        break;
    }

    printf_divagl("Debug message (%d): %s\n", id, message);
    printf_divagl("########################################\n\n");
}
#endif
