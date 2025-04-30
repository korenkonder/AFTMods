/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "draw_object.hpp"
#include "../../KKdLib/hash.hpp"
#include "../../AFTModsShared/light_param/light.hpp"
#include "../shader_ft.hpp"
#include "../texture.hpp"

static bool draw_object_blend_set(render_data_context& rend_data_ctx,
    const mdl::ObjSubMeshArgs* args, obj_material_shader_lighting_type lighting_type);
static bool draw_object_blend_set_check_use_default_blend(int32_t index);
static void draw_object_chara_color_fog_set(render_data_context& rend_data_ctx,
    const mdl::ObjSubMeshArgs* args, bool disable_fog);
static void draw_object_material_reset_cheap(render_data_context& rend_data_ctx);
static void draw_object_material_reset_default(
    render_data_context& rend_data_ctx, const obj_material_data* mat_data);
static void draw_object_material_set_cheap(
    render_data_context& rend_data_ctx, const mdl::ObjSubMeshArgs* args);
static void draw_object_material_set_default(render_data_context& rend_data_ctx,
    const mdl::ObjSubMeshArgs* args, bool use_shader);
static void draw_object_material_set_parameter(
    render_data_context& rend_data_ctx, const obj_material_data* mat_data);
static void draw_object_material_set_uniform(render_data_context& rend_data_ctx,
    const obj_material_data* mat_data, bool disable_color_l);
static void draw_object_vertex_attrib_reset_cheap(
    render_data_context& rend_data_ctx, const mdl::ObjSubMeshArgs* args);
static void draw_object_vertex_attrib_reset_default(
    render_data_context& rend_data_ctx, const mdl::ObjSubMeshArgs* args);
static void draw_object_vertex_attrib_set_default(
    render_data_context& rend_data_ctx, const mdl::ObjSubMeshArgs* args);
static void draw_object_vertex_attrib_set_cheap(
    render_data_context& rend_data_ctx, const mdl::ObjSubMeshArgs* args);

static bool(FASTCALL* use_shader_get)() = (bool(FASTCALL*)())0x0000000140440E30;

namespace mdl {
    void draw(render_data_context& rend_data_ctx, obj_primitive_type primitive_type, uint32_t count,
        uint16_t start, uint16_t end, obj_index_format index_format, size_t indices) {
        GLenum mesh_draw_mode[] = {
            GL_ZERO, //GL_POINTS,
            GL_LINES,
            GL_LINE_STRIP,
            GL_LINE_LOOP,
            GL_TRIANGLES,
            GL_TRIANGLE_STRIP,
            GL_TRIANGLE_FAN,
            GL_ZERO, //GL_QUADS,
            GL_ZERO, //GL_QUAD_STRIP,
            GL_ZERO, //GL_POLYGON,
        };

        GLenum mesh_indices_type[] = {
            GL_ZERO,
            GL_UNSIGNED_SHORT,
            GL_UNSIGNED_INT,
        };

        rend_data_ctx.set_render_data_state();

        if (primitive_type == OBJ_PRIMITIVE_TRIANGLE_STRIP && index_format == OBJ_INDEX_U16)
            rend_data_ctx.state.draw_range_elements(GL_TRIANGLE_STRIP,
                start, end, count, GL_UNSIGNED_SHORT, (void*)indices);
        else
            rend_data_ctx.state.draw_elements(mesh_draw_mode[primitive_type],
                count, mesh_indices_type[index_format], (void*)indices);

        draw_state_stats& stats = rctx->draw_state_rend_data[rend_data_ctx.index].stats;
        stats.draw_count += count;
        if (primitive_type == OBJ_PRIMITIVE_TRIANGLES)
            stats.draw_triangle_count += count / 3;
        else if (primitive_type == OBJ_PRIMITIVE_TRIANGLE_STRIP)
            stats.draw_triangle_count += count - 2;
    }

    void draw_etc_obj(render_data_context& rend_data_ctx, const mdl::EtcObj* etc, const mat4* mat) {
        switch (etc->type) {
        case mdl::ETC_OBJ_TEAPOT:
        case mdl::ETC_OBJ_GRID:
        case mdl::ETC_OBJ_CUBE:
        case mdl::ETC_OBJ_SPHERE:
        case mdl::ETC_OBJ_PLANE:
        case mdl::ETC_OBJ_CONE:
        case mdl::ETC_OBJ_LINE:
        case mdl::ETC_OBJ_CROSS:
        case mdl::ETC_OBJ_CAPSULE:  // Added
        case mdl::ETC_OBJ_CYLINDER: // Added
            break;
        default:
            return;
        }

        if (!etc->count)
            return;

        GLuint vao = disp_manager->get_vertex_array(etc);
        if (!vao)
            return;

        rend_data_ctx.set_batch_worlds(*mat);

        const vec4 color = etc->color;

        if (etc->constant) {
            vec4 diffuse = color;
            vec4 ambient = color * 0.5f;
            ambient.w = color.w;
            vec4 emission = etc->constant ? 1.0f : vec4(0.0f, 0.0f, 0.0f, 1.0f);
            vec4 specular = { 0.0f, 0.0f, 0.0f, 1.0f };

            rend_data_ctx.set_batch_material_color(diffuse, ambient, emission,
                0.0f, specular, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
            rend_data_ctx.set_batch_blend_color_offset_color(1.0f, 0.0f);
        }
        else
            rend_data_ctx.set_batch_blend_color_offset_color(color, 0.0f);

        rend_data_ctx.state.bind_vertex_array(vao);
        //rend_data_ctx.set_shader(SHADER_FT_SIMPLE);
        rend_data_ctx.set_shader(etc->constant ? SHADER_FT_CONSTANT : SHADER_FT_SIMPLE);
        rend_data_ctx.set_render_data_state();
        switch (etc->type) {
        case mdl::ETC_OBJ_TEAPOT:
            rend_data_ctx.state.draw_elements(GL_TRIANGLES, etc->count, GL_UNSIGNED_INT, 0);
            break;
        case mdl::ETC_OBJ_GRID:
            rend_data_ctx.state.set_line_width(0.2f);
            rend_data_ctx.state.draw_arrays(GL_LINES, 0, etc->count);
            rend_data_ctx.state.set_line_width(2.0f);
            rend_data_ctx.state.draw_arrays(GL_LINES, (GLint)etc->count, 4);
            rend_data_ctx.state.set_line_width(1.0f);
            break;
        case mdl::ETC_OBJ_CUBE:
            if (etc->data.sphere.wire)
                rend_data_ctx.state.draw_elements(GL_LINES, etc->count, GL_UNSIGNED_INT, (void*)etc->offset);
            else
                rend_data_ctx.state.draw_elements(GL_TRIANGLES, etc->count, GL_UNSIGNED_INT, (void*)etc->offset);
            break;
        case mdl::ETC_OBJ_SPHERE:
            if (etc->data.sphere.wire)
                rend_data_ctx.state.draw_elements(GL_LINES, etc->count, GL_UNSIGNED_INT, (void*)etc->offset);
            else
                rend_data_ctx.state.draw_elements(GL_TRIANGLES, etc->count, GL_UNSIGNED_INT, (void*)etc->offset);
            break;
        case mdl::ETC_OBJ_PLANE:
            rend_data_ctx.state.draw_arrays(GL_TRIANGLE_STRIP, 0, etc->count);
            break;
        case mdl::ETC_OBJ_CONE:
            if (etc->data.cone.wire)
                rend_data_ctx.state.draw_elements(GL_LINES, etc->count, GL_UNSIGNED_INT, (void*)etc->offset);
            else
                rend_data_ctx.state.draw_elements(GL_TRIANGLES, etc->count, GL_UNSIGNED_INT, (void*)etc->offset);
            break;
        case mdl::ETC_OBJ_LINE:
            rend_data_ctx.state.draw_arrays(GL_LINES, 0, etc->count);
            break;
        case mdl::ETC_OBJ_CROSS:
            rend_data_ctx.state.draw_arrays(GL_LINES, 0, etc->count);
            break;
        case mdl::ETC_OBJ_CAPSULE: // Added
            if (etc->data.capsule.wire)
                rend_data_ctx.state.draw_elements(GL_LINES, etc->count, GL_UNSIGNED_INT, (void*)etc->offset);
            else
                rend_data_ctx.state.draw_elements(GL_TRIANGLES, etc->count, GL_UNSIGNED_INT, (void*)etc->offset);
            break;
        case mdl::ETC_OBJ_CYLINDER: // Added
            if (etc->data.cylinder.wire)
                rend_data_ctx.state.draw_elements(GL_LINES, etc->count, GL_UNSIGNED_INT, (void*)etc->offset);
            else
                rend_data_ctx.state.draw_elements(GL_TRIANGLES, etc->count, GL_UNSIGNED_INT, (void*)etc->offset);
            break;
        }
        shader::unbind(rend_data_ctx.state);
        rend_data_ctx.reset_shader_flags();

        rend_data_ctx.set_batch_blend_color_offset_color(1.0f, 0.0f);
    }

    void draw_sub_mesh(render_data_context& rend_data_ctx, const ObjSubMeshArgs* args,
        const mat4* mat, void(*func)(render_data_context& rend_data_ctx,
            const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat), const cam_data& cam) {
        GLuint vao = disp_manager->get_vertex_array(args);
        if (!vao)
            return;

        if (args->mats) {
            rend_data_ctx.set_skinning_data(rend_data_ctx.state, args->mats, args->mat_count);

            rend_data_ctx.set_batch_worlds(mat4_identity);

            rend_data_ctx.shader_flags.arr[U_SKINNING] = 1;
            rend_data_ctx.state.bind_vertex_array(vao);
            func(rend_data_ctx, args, cam, mat);
            rend_data_ctx.shader_flags.arr[U_SKINNING] = 0;
        }
        else {
            mat4 _mat;
            if (args->mesh->attrib.m.billboard)
                model_mat_face_camera_view(cam, mat, &_mat);
            else if (args->mesh->attrib.m.billboard_y_axis)
                model_mat_face_camera_position(cam, mat, &_mat);
            else
                _mat = *mat;

            rend_data_ctx.shader_flags.arr[U_SKINNING] = 0;
            rend_data_ctx.state.bind_vertex_array(vao);
            if (func != draw_sub_mesh_default || !args->instances_count) {
                rend_data_ctx.set_batch_worlds(_mat);
                func(rend_data_ctx, args, cam, &_mat);
            }
            else
                draw_sub_mesh_default_instanced(rend_data_ctx, args, cam, &_mat);
            rend_data_ctx.shader_flags.arr[U_SKINNING] = 0;
        }
    }

    void draw_sub_mesh_cheap(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat) {
        const obj_material_data* material = args->material;
        draw_object_vertex_attrib_set_cheap(rend_data_ctx, args);
        obj_material_shader_lighting_type lighting_type
            = material->material.shader_info.get_lighting_type();
        bool disable_fog = draw_object_blend_set(rend_data_ctx, args, lighting_type);
        draw_object_chara_color_fog_set(rend_data_ctx, args, disable_fog);
        draw_object_material_set_cheap(rend_data_ctx, args);

        const obj_sub_mesh* sub_mesh = args->sub_mesh;
        if (sub_mesh->index_format != OBJ_INDEX_U8)
            draw(rend_data_ctx,
                sub_mesh->primitive_type,
                sub_mesh->num_index,
                sub_mesh->first_index,
                sub_mesh->last_index,
                sub_mesh->index_format,
                sub_mesh->index_offset);

        draw_object_material_reset_cheap(rend_data_ctx);
        draw_object_vertex_attrib_reset_cheap(rend_data_ctx, args);
        rend_data_ctx.reset_shader_flags();

        rctx->draw_state_rend_data[rend_data_ctx.index].stats.sub_mesh_cheap_count++;
    }

    void draw_sub_mesh_cheap_reflect_map(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat) {
        draw_object_vertex_attrib_set_cheap(rend_data_ctx, args);
        draw_object_material_set_cheap(rend_data_ctx, args);

        const obj_sub_mesh* sub_mesh = args->sub_mesh;
        if (sub_mesh->index_format != OBJ_INDEX_U8)
            draw(rend_data_ctx,
                sub_mesh->primitive_type,
                sub_mesh->num_index,
                sub_mesh->first_index,
                sub_mesh->last_index,
                sub_mesh->index_format,
                sub_mesh->index_offset);

        draw_object_material_reset_cheap(rend_data_ctx);
        draw_object_vertex_attrib_reset_cheap(rend_data_ctx, args);

        rctx->draw_state_rend_data[rend_data_ctx.index].stats.sub_mesh_cheap_count++;
    }

    void draw_sub_mesh_default(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat) {
        if (args->set_blend_color)
            rend_data_ctx.set_batch_blend_color_offset_color(args->blend_color, 0.0f);

        if (!args->func)
            draw_object_vertex_attrib_set_default(rend_data_ctx, args);

        draw_object_material_set_default(rend_data_ctx, args, use_shader_get());

        const obj_sub_mesh* sub_mesh = args->sub_mesh;
        draw(rend_data_ctx,
            sub_mesh->primitive_type,
            sub_mesh->num_index,
            sub_mesh->first_index,
            sub_mesh->last_index,
            sub_mesh->index_format,
            sub_mesh->index_offset);

        draw_object_material_reset_default(rend_data_ctx, args->material);
        if (!args->func)
            draw_object_vertex_attrib_reset_default(rend_data_ctx, args);

        if (args->set_blend_color)
            rend_data_ctx.set_batch_blend_color_offset_color(1.0f, 0.0f);

        rctx->draw_state_rend_data[rend_data_ctx.index].stats.sub_mesh_count++;
    }

    void draw_sub_mesh_default_instanced(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat) {
        if (args->set_blend_color)
            rend_data_ctx.set_batch_blend_color_offset_color(args->blend_color, 0.0f);

        if (!args->func)
            draw_object_vertex_attrib_set_default(rend_data_ctx, args);

        draw_object_material_set_default(rend_data_ctx, args, use_shader_get());

        const obj_sub_mesh* sub_mesh = args->sub_mesh;
        const mat4* instances_mat = args->instances_mat;
        mat4 _mat;
        for (int32_t i = args->instances_count; i >= 0; i--, instances_mat++) {
            mat4_mul(instances_mat, mat, &_mat);
            rend_data_ctx.set_batch_worlds(_mat);
            draw(rend_data_ctx,
                sub_mesh->primitive_type,
                sub_mesh->num_index,
                sub_mesh->first_index,
                sub_mesh->last_index,
                sub_mesh->index_format,
                sub_mesh->index_offset);
        }

        draw_object_material_reset_default(rend_data_ctx, args->material);
        if (!args->func)
            draw_object_vertex_attrib_reset_default(rend_data_ctx, args);

        if (args->set_blend_color)
            rend_data_ctx.set_batch_blend_color_offset_color(1.0f, 0.0f);

        rctx->draw_state_rend_data[rend_data_ctx.index].stats.sub_mesh_count++;
    }

    void draw_sub_mesh_no_mat(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat) {
        const obj_material_data* material = args->material;
        const prj::vector<GLuint>* textures = args->textures;
        if (rctx->draw_state_rend_data[rend_data_ctx.index].shader_index != -1) {
            rend_data_ctx.set_batch_material_color_emission(args->emission);
            draw_object_material_set_uniform(rend_data_ctx, material, false);
            if (material->material.attrib.m.alpha_texture)
                rend_data_ctx.shader_flags.arr[U_TEXTURE_COUNT] = 0;
            rend_data_ctx.set_shader(rctx->draw_state_rend_data[rend_data_ctx.index].shader_index);
        }

        draw_object_vertex_attrib_set_default(rend_data_ctx, args);
        if (args->material->material.attrib.m.double_sided)
            rend_data_ctx.state.disable_cull_face();

        GLuint tex_id = -1;
        int32_t tex_index = 0;
        if (material->material.attrib.m.alpha_texture) {
            const obj_material_texture_data* texdata = material->material.texdata;
            uint32_t texture_id = -1;
            if (!material->material.shader_compo.m.transparency) {
                for (int32_t i = 0; i < 8; i++, texdata++)
                    if (texdata->shader_info.m.tex_type == OBJ_MATERIAL_TEXTURE_COLOR) {
                        texture_id = texdata->tex_index;
                        break;
                    }
                tex_index = 0;
            }
            else {
                for (int32_t i = 0; i < 8; i++, texdata++)
                    if (texdata->shader_info.m.tex_type == OBJ_MATERIAL_TEXTURE_TRANSPARENCY) {
                        if (texdata->attrib.m.flag_29)
                            texture_id = texdata->tex_index;
                        break;
                    }
                tex_index = 3;
            }

            if (texture_id != -1) {
                texture_id &= 0xFFFFF;
                for (int32_t j = 0; j < args->texture_pattern_count; j++)
                    if (args->texture_pattern_array[j].src == ::texture_id(0x00, tex_index)) {
                        texture* tex = texture_manager_get_texture(args->texture_pattern_array[j].dst);
                        if (tex)
                            tex_id = tex->glid;
                        break;
                    }

                if (tex_id == -1)
                    tex_id = (*textures)[texdata->tex_index >> 20];

                if (tex_id == -1)
                    tex_id = rctx->empty_texture_2d->glid;;

                rend_data_ctx.state.active_bind_texture_2d(tex_index, tex_id);

                int32_t wrap_s;
                if (texdata->attrib.m.mirror_u)
                    wrap_s = 2;
                else if (texdata->attrib.m.repeat_u)
                    wrap_s = 1;
                else
                    wrap_s = 0;

                int32_t wrap_t;
                if (texdata->attrib.m.mirror_v)
                    wrap_t = 2;
                else if (texdata->attrib.m.repeat_v)
                    wrap_t = 1;
                else
                    wrap_t = 0;

                texture* tex = texture_manager_get_texture(texture_id);
                rend_data_ctx.state.bind_sampler(tex_index, rctx->samplers[(wrap_t * 3 + wrap_s) * 2
                    + (!tex || tex->max_mipmap_level > 0 ? 1 : 0)]);
            }
        }

        const obj_sub_mesh* sub_mesh = args->sub_mesh;
        if (sub_mesh->index_format != OBJ_INDEX_U8)
            draw(rend_data_ctx,
                sub_mesh->primitive_type,
                sub_mesh->num_index,
                sub_mesh->first_index,
                sub_mesh->last_index,
                sub_mesh->index_format,
                sub_mesh->index_offset);

        if (tex_id != -1)
            rend_data_ctx.state.active_bind_texture_2d(tex_index, rctx->empty_texture_2d->glid);

        rend_data_ctx.state.enable_cull_face();
        draw_object_vertex_attrib_reset_default(rend_data_ctx, args);

        if (rctx->draw_state_rend_data[rend_data_ctx.index].shader_index != -1)
            rend_data_ctx.reset_shader_flags();

        rctx->draw_state_rend_data[rend_data_ctx.index].stats.sub_mesh_no_mat_count++;
    }

    void draw_sub_mesh_shadow(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat) {
        obj_material_attrib_member attrib = args->material->material.attrib.m;
        if (!attrib.flag_28 && (args->blend_color.w < 1.0f
            || (attrib.alpha_texture || attrib.alpha_material) && !attrib.punch_through
            || args->sub_mesh->attrib.m.translucent)
            || attrib.punch_through) {
            rend_data_ctx.shader_flags.arr[U_ALPHA_TEST] = 1;
            rend_data_ctx.set_batch_alpha_threshold(0.5f);
            draw_sub_mesh_no_mat(rend_data_ctx, args, cam, mat);
            rend_data_ctx.shader_flags.arr[U_ALPHA_TEST] = 0;
            rend_data_ctx.set_batch_alpha_threshold(0.0f);
        }
        else
            draw_sub_mesh_no_mat(rend_data_ctx, args, cam, mat);
    }

    void draw_sub_mesh_sss(render_data_context& rend_data_ctx,
        const ObjSubMeshArgs* args, const cam_data& cam, const mat4* mat) {
        obj_material_attrib_member attrib = args->material->material.attrib.m;
        rend_data_ctx.shader_flags.arr[U_ALPHA_TEST] = (!attrib.flag_28 && (args->blend_color.w < 1.0f
            || (attrib.alpha_texture || attrib.alpha_material) && !attrib.punch_through
            || args->sub_mesh->attrib.m.translucent)
            || attrib.punch_through) ? 1 : 0;

        rend_data_ctx.shader_flags.arr[U_NPR_NORMAL] = 1;
        bool chara = false;
        const obj_material_data* material = args->material;
        switch (material->material.shader.index) {
        case SHADER_FT_CLOTH:
            if (!render_manager.npr_param && material->material.color.ambient.w < 1.0f
                && material->material.shader_info.m.aniso_direction == OBJ_MATERIAL_ANISO_DIRECTION_NORMAL)
                chara = true;
            break;
        case SHADER_FT_TIGHTS:
            if (!render_manager.npr_param)
                chara = true;
            break;
        case SHADER_FT_GLASEYE:
            rend_data_ctx.shader_flags.arr[U_NPR_NORMAL] = 0;
            chara = true;
            break;
        case SHADER_FT_SKIN:
            chara = true;
            break;
        }

        if (chara) {
            rend_data_ctx.set_batch_sss_param({ 0.0f, 0.0f, 0.0f, 0.5f });
            rend_data_ctx.shader_flags.arr[U_SSS_CHARA] = 1;
        }
        else {
            const vec4& sss_param = sss_data_get()->param;
            rend_data_ctx.set_batch_sss_param({ sss_param.x, sss_param.y, sss_param.z, 0.5f });
            rend_data_ctx.shader_flags.arr[U_SSS_CHARA] = 0;
        }
        draw_sub_mesh_default(rend_data_ctx, args, cam, mat);
    }
}

inline void model_mat_face_camera_position(const cam_data& cam, const mat4* src, mat4* dst) {
    mat4 mat;
    mat4_invert_fast(&cam.get_view_mat(), &mat);

    vec3 dir = vec3::normalize(*(vec3*)&mat.row3 - *(vec3*)&src->row3);

    vec3 x_rot;
    vec3 y_rot;
    vec3 z_rot;

    y_rot = *(vec3*)&src->row1;
    x_rot = vec3::normalize(vec3::cross(y_rot, dir));
    z_rot = vec3::cross(x_rot, y_rot);

    *(vec3*)&dst->row0 = x_rot;
    *(vec3*)&dst->row1 = y_rot;
    *(vec3*)&dst->row2 = z_rot;
    *(vec3*)&dst->row3 = *(vec3*)&src->row3;
    dst->row0.w = 0.0f;
    dst->row1.w = 0.0f;
    dst->row2.w = 0.0f;
    dst->row3.w = 1.0f;
}

inline void model_mat_face_camera_view(const cam_data& cam, const mat4* src, mat4* dst) {
    mat3 mat;
    mat4_to_mat3(&cam.get_view_mat(), &mat);
    mat3_invert(&mat, &mat);
    mat4_from_mat3(&mat, dst);
    mat4_mul(dst, src, dst);
}

static bool draw_object_blend_set(render_data_context& rend_data_ctx,
    const mdl::ObjSubMeshArgs* args, obj_material_shader_lighting_type lighting_type) {
    static const GLenum blend_factor_table[] = {
        GL_ZERO,
        GL_ONE,
        GL_SRC_COLOR,
        GL_ONE_MINUS_SRC_COLOR,
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA,
        GL_DST_ALPHA,
        GL_ONE_MINUS_DST_ALPHA,
        GL_DST_COLOR,
        GL_ONE_MINUS_DST_COLOR,
        GL_SRC_ALPHA_SATURATE,
        GL_ZERO,
        GL_ZERO,
        GL_ZERO,
        GL_ZERO,
        GL_ZERO,
    };

    const obj_material_data* material = args->material;
    obj_material_attrib_member attrib = material->material.attrib.m;
    if ((!attrib.alpha_texture && !attrib.alpha_material) || attrib.punch_through)
        return false;

    GLenum src_blend_factor = blend_factor_table[attrib.src_blend_factor];
    GLenum dst_blend_factor = blend_factor_table[attrib.dst_blend_factor];
    if (args->chara_color) {
        light_set* set = &light_set_data[LIGHT_SET_MAIN];
        light_data* chara_color = &set->lights[LIGHT_CHARA_COLOR];
        vec4 specular;
        chara_color->get_specular(specular);
        if (specular.w >= 4.0f && chara_color->get_type() == LIGHT_PARALLEL
            && (src_blend_factor != GL_ONE || dst_blend_factor)) {
            int32_t shader_index = rctx->draw_state_rend_data[rend_data_ctx.index].shader_index;
            if (shader_index == -1) {
                shader_index = material->material.shader.index;
                if (shader_index == SHADER_FT_BLINN) {
                    if (lighting_type == OBJ_MATERIAL_SHADER_LIGHTING_CONSTANT)
                        shader_index = SHADER_FT_CONSTANT;
                    if (lighting_type == OBJ_MATERIAL_SHADER_LIGHTING_LAMBERT)
                        shader_index = SHADER_FT_LAMBERT;
                }
            }

            if (draw_object_blend_set_check_use_default_blend(shader_index)) {
                src_blend_factor = GL_SRC_ALPHA;
                dst_blend_factor = GL_ONE_MINUS_SRC_ALPHA;
            }
        }
    }
    rend_data_ctx.state.set_blend_func(src_blend_factor, dst_blend_factor);
    return dst_blend_factor == GL_ONE;
}

static bool draw_object_blend_set_check_use_default_blend(int32_t index) {
    bool use_default_blend[] = {
        false, false,  true, false,  true, false, false,  true,  true,  true, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false,
        false, false,
    };

    if (index >= 0 && index < SHADER_FT_MAX)
        return use_default_blend[index];
    return false;
}

static void draw_object_chara_color_fog_set(render_data_context& rend_data_ctx,
    const mdl::ObjSubMeshArgs* args, bool disable_fog) {
    rend_data_ctx.shader_flags.arr[U_CHARA_COLOR] = 0;
    if (args->chara_color) {
        light_set* set = &light_set_data[LIGHT_SET_MAIN];
        light_data* chara_color = &set->lights[LIGHT_CHARA_COLOR];
        vec4 specular;
        chara_color->get_specular(specular);
        if (specular.w > 0.0f && chara_color->get_type() == LIGHT_PARALLEL)
            rend_data_ctx.shader_flags.arr[U_CHARA_COLOR] = 1;
    }

    obj_material_attrib_member attrib = args->material->material.attrib.m;
    if (!attrib.no_fog && !disable_fog) {
        rend_data_ctx.shader_flags.arr[U_FOG_STAGE] = attrib.has_fog_height ? (attrib.fog_height ? 3 : 2) : 1;
        rend_data_ctx.shader_flags.arr[U_FOG_CHARA] = draw_state.fog_height ? 2 : 1;
    }
}

static void draw_object_material_reset_cheap(render_data_context& rend_data_ctx) {
    rend_data_ctx.state.active_bind_texture_2d(0, rctx->empty_texture_2d->glid);
    rend_data_ctx.state.enable_cull_face();
    rend_data_ctx.reset_shader_flags();
}

static void draw_object_material_reset_default(
    render_data_context& rend_data_ctx, const obj_material_data* mat_data) {
    if (mat_data) {
        rend_data_ctx.state.enable_cull_face();
        obj_material_attrib_member attrib = mat_data->material.attrib.m;
        if ((attrib.alpha_texture || attrib.alpha_material) && !attrib.punch_through)
            rend_data_ctx.state.set_blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    rend_data_ctx.reset_shader_flags();
}

static void draw_object_material_set_cheap(
    render_data_context& rend_data_ctx, const mdl::ObjSubMeshArgs* args) {
    const obj_material_data* material = args->material;
    const prj::vector<GLuint>* textures = args->textures;
    if (material->material.attrib.m.double_sided)
        rend_data_ctx.state.disable_cull_face();

    const obj_material_texture_data* texdata = material->material.texdata;
    for (int32_t i = 0; i < 1; i++, texdata++) {
        uint32_t texture_id = texdata->tex_index & 0xFFFFF;
        if (texdata->tex_index == -1)
            break;

        GLuint tex_id = -1;
        for (int32_t j = 0; j < args->texture_pattern_count; j++)
            if (args->texture_pattern_array[j].src == ::texture_id(0x00, texture_id)) {
                texture* tex = texture_manager_get_texture(args->texture_pattern_array[j].dst);
                if (tex)
                    tex_id = tex->glid;
                break;
            }

        if (tex_id == -1)
            tex_id = (*textures)[texdata->tex_index >> 20];

        if (tex_id == -1)
            tex_id = rctx->empty_texture_2d->glid;;

        rend_data_ctx.state.active_bind_texture_2d(i, tex_id);

        int32_t wrap_s;
        if (texdata->attrib.m.mirror_u)
            wrap_s = 2;
        else if (texdata->attrib.m.repeat_u)
            wrap_s = 1;
        else
            wrap_s = 0;

        int32_t wrap_t;
        if (texdata->attrib.m.mirror_v)
            wrap_t = 2;
        else if (texdata->attrib.m.repeat_v)
            wrap_t = 1;
        else
            wrap_t = 0;

        texture* tex = texture_manager_get_texture(texture_id);
        rend_data_ctx.state.bind_sampler(i, rctx->samplers[(wrap_t * 3 + wrap_s) * 2
            + (!tex || tex->max_mipmap_level > 0 ? 1 : 0)]);
    }

    vec4 ambient;
    vec4 diffuse;
    vec4 emission;
    vec4 specular;
    if (material->material.shader.index == -1) {
        ambient = 1.0f;
        diffuse = material->material.color.diffuse;
        emission = 1.0f;
        specular = material->material.color.specular;
    }
    else {
        ambient = material->material.color.ambient;
        diffuse = material->material.color.diffuse;
        emission = args->emission;
        specular = material->material.color.specular;
    }

    draw_object_material_set_uniform(rend_data_ctx, material, true);
    rend_data_ctx.set_shader(rctx->draw_state_rend_data[rend_data_ctx.index].shader_index);
    rend_data_ctx.set_batch_material_color(diffuse, ambient, emission,
        0.0f, specular, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    draw_object_material_set_parameter(rend_data_ctx, args->material);
}

static void draw_object_material_set_default(render_data_context& rend_data_ctx,
    const mdl::ObjSubMeshArgs* args, bool use_shader) {
    const prj::vector<GLuint>* textures = args->textures;
    const obj_material_data* material = args->material;
    obj_material_shader_lighting_type lighting_type =
        material->material.shader_info.get_lighting_type();
    bool disable_fog = draw_object_blend_set(rend_data_ctx, args, lighting_type);
    draw_object_material_set_uniform(rend_data_ctx, material, false);
    if (!rctx->draw_state_rend_data[rend_data_ctx.index].shadow)
        rend_data_ctx.shader_flags.arr[U_STAGE_SHADOW] = 0;
    else if (!args->self_shadow)
        rend_data_ctx.shader_flags.arr[U_STAGE_SHADOW] = args->sub_mesh->attrib.m.recieve_shadow ? 1 : 0;
    else if (args->self_shadow != 1)
        rend_data_ctx.shader_flags.arr[U_STAGE_SHADOW] = 0;
    else
        rend_data_ctx.shader_flags.arr[U_STAGE_SHADOW] = 1;

    rend_data_ctx.shader_flags.arr[U_CHARA_SHADOW2] = args->shadow > SHADOW_CHARA ? 1 : 0;
    rend_data_ctx.shader_flags.arr[U_CHARA_SHADOW]
        = rctx->draw_state_rend_data[rend_data_ctx.index].self_shadow ? 1 : 0;

    const obj_material_texture_data* texdata = material->material.texdata;
    for (int32_t i = 0, j = 0; i < 8; i++, texdata++) {
        if (texdata->tex_index == -1)
            continue;

        GLuint tex_id = -1;
        uint32_t texture_id = texdata->tex_index & 0xFFFFF;
        for (int32_t j = 0; j < args->texture_pattern_count; j++)
            if (args->texture_pattern_array[j].src == ::texture_id(0x00, texture_id)) {
                texture* tex = texture_manager_get_texture(args->texture_pattern_array[j].dst);
                if (tex)
                    tex_id = tex->glid;
                break;
            }

        if (tex_id == -1)
            tex_id = (*textures)[texdata->tex_index >> 20];

        if (tex_id == -1)
            continue;

        int32_t tex_index = obj_material_texture_type_get_texture_index(texdata->shader_info.m.tex_type, j);
        if (tex_index < 0)
            continue;

        obj_material_texture_type tex_type = texdata->shader_info.m.tex_type;
        if (tex_type == OBJ_MATERIAL_TEXTURE_COLOR)
            j++;

        if (texdata->attrib.m.flag_29) {
            switch (tex_type) {
            case OBJ_MATERIAL_TEXTURE_NORMAL:
                rend_data_ctx.shader_flags.arr[U_NORMAL] = 0;
                break;
            case OBJ_MATERIAL_TEXTURE_SPECULAR:
                rend_data_ctx.shader_flags.arr[U_SPECULAR] = 0;
                break;
            case OBJ_MATERIAL_TEXTURE_TRANSLUCENCY:
                rend_data_ctx.shader_flags.arr[U_TRANSLUCENCY] = 0;
                break;
            case OBJ_MATERIAL_TEXTURE_TRANSPARENCY:
                rend_data_ctx.shader_flags.arr[U_TRANSPARENCY] = 0;
                break;
            }
            continue;
        }

        if (tex_type == OBJ_MATERIAL_TEXTURE_ENVIRONMENT_CUBE) {
            rend_data_ctx.state.active_bind_texture_cube_map(tex_index, tex_id);
            rend_data_ctx.state.bind_sampler(tex_index, 0);
        }
        else {
            rend_data_ctx.state.active_bind_texture_2d(tex_index, tex_id);

            int32_t wrap_s;
            if (texdata->attrib.m.mirror_u)
                wrap_s = 2;
            else if (texdata->attrib.m.repeat_u)
                wrap_s = 1;
            else
                wrap_s = 0;

            int32_t wrap_t;
            if (texdata->attrib.m.mirror_v)
                wrap_t = 2;
            else if (texdata->attrib.m.repeat_v)
                wrap_t = 1;
            else
                wrap_t = 0;

            texture* tex = texture_manager_get_texture(texture_id);
            rend_data_ctx.state.bind_sampler(tex_index, rctx->samplers[(wrap_t * 3 + wrap_s) * 2
                + (!tex || tex->max_mipmap_level > 0 ? 1 : 0)]);
        }

        if (material->material.shader.index == SHADER_FT_SKY) {
            uniform_name uni_type = U_TEX_0_TYPE;
            if (tex_index == 1)
                uni_type = U_TEX_1_TYPE;

            texture* tex = texture_manager_get_texture(texture_id);
            if (!tex)
                rend_data_ctx.shader_flags.arr[uni_type] = 1;
            else if (tex->internal_format == GL_COMPRESSED_RED_RGTC1_EXT)
                rend_data_ctx.shader_flags.arr[uni_type] = 3;
            else if (tex->internal_format == GL_COMPRESSED_RED_GREEN_RGTC2_EXT)
                rend_data_ctx.shader_flags.arr[uni_type] = 2;
            else
                rend_data_ctx.shader_flags.arr[uni_type] = 1;
        }

        if (tex_index >= 0 && tex_index <= 1)
            rend_data_ctx.shader_flags.arr[U_TEXTURE_BLEND] = texdata->attrib.get_blend();
    }

    if (material->material.attrib.m.double_sided) {
        rend_data_ctx.state.disable_cull_face();
        if (!material->material.attrib.m.normal_dir_light)
            rend_data_ctx.shader_flags.arr[U0B] = 1;
    }

    draw_object_chara_color_fog_set(rend_data_ctx, args, disable_fog);

    vec4 ambient = material->material.color.ambient;
    if (!sss_data_get()->enable)
        ambient.w = 1.0f;
    vec4 diffuse = material->material.color.diffuse;
    vec4 emission = args->emission;
    vec4 specular = { 0.0f, 0.0f, 0.0f, 1.0f };

    float_t line_light;
    if (lighting_type == OBJ_MATERIAL_SHADER_LIGHTING_PHONG) {
        specular = material->material.color.specular;

        float_t luma = vec3::dot(*(vec3*)&specular, { 0.30f, 0.59f, 0.11f });
        if (luma >= 0.01f || args->texture_color_coefficients.w >= 0.1f)
            rend_data_ctx.shader_flags.arr[U_SPECULAR_IBL] = 1;
        else
            rend_data_ctx.shader_flags.arr[U_SPECULAR_IBL] = 0;

        if (!material->material.shader_info.m.fresnel_type)
            rend_data_ctx.shader_flags.arr[U_TRANSLUCENCY] = 0;

        line_light = (float_t)material->material.shader_info.m.line_light * (float_t)(1.0 / 9.0);
    }
    else
        line_light = 0.0f;

    float_t material_shininess = 0.0f;
    vec4 fresnel_coefficients;
    float_t shininess = 0.0f;
    vec4 texture_color_coefficients;
    vec4 texture_color_offset;
    vec4 texture_specular_coefficients;
    vec4 texture_specular_offset;
    if (lighting_type != OBJ_MATERIAL_SHADER_LIGHTING_CONSTANT) {
        if (material->material.shader.index == SHADER_FT_GLASEYE)
            material_shininess = 10.0f;
        else {
            material_shininess = (material->material.color.shininess - 16.0f) * (float_t)(1.0 / 112.0);
            material_shininess = max_def(material_shininess, 0.0f);
        }

        float_t fresnel = (float_t)material->material.shader_info.m.fresnel_type;
        if (fresnel > 9.0f)
            fresnel = 9.0f;
        else if (fresnel == 0.0f)
            fresnel = draw_state.fresnel;
        fresnel = (fresnel - 1.0f) * 0.12f * 0.82f;

        fresnel_coefficients = { fresnel, 0.18f, line_light, 0.0f };

        shininess = max_def(material->material.color.shininess, 1.0f);

        switch (material->material.shader.index) {
        case SHADER_FT_SKIN: {
            texture_color_coefficients = args->texture_color_coefficients;
            texture_color_offset = args->texture_color_offset;
            texture_specular_coefficients = args->texture_specular_coefficients;
            texture_specular_offset = args->texture_specular_offset;

            texture_color_coefficients.w *= 0.015f;
            texture_specular_coefficients.w *= 0.015f;
        } break;
        case SHADER_FT_HAIR:
        case SHADER_FT_CLOTH:
        case SHADER_FT_TIGHTS:
            texture_color_coefficients = {
                1.0f - args->texture_color_coefficients.w * 0.4f,
                0.0f, 0.0f, args->texture_color_coefficients.w * 0.02f };
            break;
        }
    }

    rend_data_ctx.set_batch_material_color(diffuse, ambient, emission, material_shininess,
        specular, fresnel_coefficients, texture_color_coefficients, texture_color_offset,
        texture_specular_coefficients, texture_specular_offset, shininess);

    if (!use_shader)
        rend_data_ctx.set_shader(SHADER_FT_SIMPLE);
    else if (rctx->draw_state_rend_data[rend_data_ctx.index].shader_index != -1)
        rend_data_ctx.set_shader(rctx->draw_state_rend_data[rend_data_ctx.index].shader_index);
    else if (material->material.shader.index != -1) {
        if (material->material.shader.index != SHADER_FT_BLINN)
            rend_data_ctx.set_shader(material->material.shader.index);
        else if (lighting_type == OBJ_MATERIAL_SHADER_LIGHTING_LAMBERT)
            rend_data_ctx.set_shader(SHADER_FT_LAMBERT);
        else if (lighting_type == OBJ_MATERIAL_SHADER_LIGHTING_PHONG)
            rend_data_ctx.set_shader(SHADER_FT_BLINN);
        else
            rend_data_ctx.set_shader(SHADER_FT_CONSTANT);
    }
    else
        rend_data_ctx.set_shader(SHADER_FT_CONSTANT);

    draw_object_material_set_parameter(rend_data_ctx, material);
}

static void draw_object_material_set_parameter(
    render_data_context& rend_data_ctx, const obj_material_data* mat_data) {
    vec4 specular;
    float_t bump_depth;
    float_t intensity;
    float_t reflect_uv_scale;
    float_t refract_uv_scale;
    float_t inv_bump_depth;
    bool has_specular;
    if (draw_state.use_global_material) {
        bump_depth = draw_state.global_material.bump_depth;
        intensity = draw_state.global_material.intensity;
        reflect_uv_scale = draw_state.global_material.reflect_uv_scale;
        refract_uv_scale = draw_state.global_material.refract_uv_scale;
        inv_bump_depth = (1.0f - draw_state.global_material.bump_depth) * 64.0f + 1.0f;

        specular = mat_data->material.color.specular;
        specular.w = draw_state.global_material.reflectivity;
        has_specular = true;
    }
    else {
        bump_depth = mat_data->material.bump_depth;
        intensity = mat_data->material.color.intensity;
        reflect_uv_scale = 0.1f;
        refract_uv_scale = 0.1f;
        inv_bump_depth = (1.0f - bump_depth) * 256.0f + 1.0f;
        has_specular = false;
    }

    rend_data_ctx.set_batch_material_parameter(has_specular ? &specular : 0,
        { inv_bump_depth, bump_depth, 0.0f, 0.0f },
        { intensity, max_def(intensity, 1.0f), intensity * 25.5f, 1.0f },
        reflect_uv_scale, refract_uv_scale);
}

static void draw_object_material_set_uniform(render_data_context& rend_data_ctx,
    const obj_material_data* mat_data, bool disable_color_l) {
    obj_shader_compo_member shader_compo = mat_data->material.shader_compo.m;
    obj_material_shader_attrib_member shader_info = mat_data->material.shader_info.m;

    if (disable_color_l) {
        if (shader_compo.color)
            shader_compo.color_l1 = 0;
        shader_compo.color_l2 = 0;
    }

    int32_t v4 = 0;
    if (shader_compo.color) {
        if (!shader_compo.color_l2)
            if (shader_compo.color_l1) {
                rend_data_ctx.shader_flags.arr[U_TEXTURE_COUNT] = 2;
                v4 = 3;
            }
            else {
                rend_data_ctx.shader_flags.arr[U_TEXTURE_COUNT] = 1;
                v4 = 1;
            }
    }
    else if (shader_compo.color_l1 && !shader_compo.color_l2) {
        rend_data_ctx.shader_flags.arr[U_TEXTURE_COUNT] = 1;
        v4 = 1;
    }
    else
        rend_data_ctx.shader_flags.arr[U_TEXTURE_COUNT] = 0;

    if (shader_compo.normal_01)
        rend_data_ctx.shader_flags.arr[U_NORMAL] = 1;
    if (shader_compo.specular)
        rend_data_ctx.shader_flags.arr[U_SPECULAR] = 1;
    if (shader_compo.transparency) {
        rend_data_ctx.shader_flags.arr[U_TRANSPARENCY] = 1;
        v4 |= 2;
    }
    if (shader_compo.translucency) {
        rend_data_ctx.shader_flags.arr[U_TRANSLUCENCY] = 1;
        v4 |= 2;
    }
    if (shader_compo.override_ibl)
        rend_data_ctx.shader_flags.arr[U_ENV_MAP] = 1;

    if (shader_info.aniso_direction != OBJ_MATERIAL_ANISO_DIRECTION_NORMAL)
        rend_data_ctx.shader_flags.arr[U_ANISO] = shader_info.aniso_direction;

    if (v4 == 1)
        rend_data_ctx.shader_flags.arr[U45] = 0;
    else if (v4 == 2 || v4 == 3)
        rend_data_ctx.shader_flags.arr[U45] = 1;
}

static void draw_object_vertex_attrib_reset_cheap(
    render_data_context& rend_data_ctx, const mdl::ObjSubMeshArgs* args) {
    const obj_mesh* mesh = args->mesh;
    obj_vertex_format vertex_format = mesh->vertex_format;

    if ((vertex_format & OBJ_VERTEX_BONE_DATA) == OBJ_VERTEX_BONE_DATA)
        rend_data_ctx.shader_flags.arr[U_SKINNING] = 0;

    if (args->morph_vertex_buffer) {
        rend_data_ctx.shader_flags.arr[U_MORPH] = 0;
        rend_data_ctx.shader_flags.arr[U_MORPH_COLOR] = 0;
    }

    rend_data_ctx.state.active_texture(0);
}

static void draw_object_vertex_attrib_reset_default(
    render_data_context& rend_data_ctx, const mdl::ObjSubMeshArgs* args) {
    const obj_mesh* mesh = args->mesh;
    obj_vertex_format vertex_format = mesh->vertex_format;

    if ((vertex_format & OBJ_VERTEX_BONE_DATA) == OBJ_VERTEX_BONE_DATA)
        rend_data_ctx.shader_flags.arr[U_SKINNING] = 0;

    if (args->morph_vertex_buffer) {
        rend_data_ctx.shader_flags.arr[U_MORPH] = 0;
        rend_data_ctx.shader_flags.arr[U_MORPH_COLOR] = 0;
    }

    /*if (args->instances_count)
        rend_data_ctx.shader_flags.arr[U_INSTANCE] = 0;*/

    rend_data_ctx.state.active_texture(0);
}

static void draw_object_vertex_attrib_set_cheap(
    render_data_context& rend_data_ctx, const mdl::ObjSubMeshArgs* args) {
    const obj_mesh* mesh = args->mesh;
    obj_vertex_format vertex_format = mesh->vertex_format;

    mat4 mats[2];
    mats[0] = mat4_identity;
    mats[1] = mat4_identity;
    const obj_material_data* material = args->material;
    if (material->material.texdata[0].tex_index != -1) {
        uint32_t texture_id = material->material.texdata[0].tex_index & 0xFFFFF;

        mats[0] = material->material.texdata[0].tex_coord_mat;
        if (material->material.texdata[0].shader_info.m.tex_type == OBJ_MATERIAL_TEXTURE_COLOR)
            for (int32_t j = 0; j < args->texture_transform_count; j++)
                if (args->texture_transform_array[j].id == texture_id) {
                    mats[0] = args->texture_transform_array[j].mat;
                    break;
                }
    }

    rend_data_ctx.set_batch_texcoord_transforms(mats);

    if (vertex_format & OBJ_VERTEX_BONE_DATA)
        rend_data_ctx.shader_flags.arr[U_SKINNING] = 1;
    else
        rend_data_ctx.shader_flags.arr[U_SKINNING] = 0;

    if (args->morph_vertex_buffer) {
        rend_data_ctx.shader_flags.arr[U_MORPH] = 1;

        if (vertex_format & OBJ_VERTEX_COLOR0)
            rend_data_ctx.shader_flags.arr[U_MORPH_COLOR] = 1;
        else
            rend_data_ctx.shader_flags.arr[U_MORPH_COLOR] = 0;

        rend_data_ctx.set_batch_morph_weight(args->morph_weight);
    }
    else {
        rend_data_ctx.shader_flags.arr[U_MORPH] = 0;
        rend_data_ctx.shader_flags.arr[U_MORPH_COLOR] = 0;
    }
}

static void draw_object_vertex_attrib_set_default(
    render_data_context& rend_data_ctx, const mdl::ObjSubMeshArgs* args) {
    const obj_mesh* mesh = args->mesh;
    obj_vertex_format vertex_format = mesh->vertex_format;

    mat4 mats[2];
    mats[0] = mat4_identity;
    mats[1] = mat4_identity;
    bool texcoord_mat_set[4] = { false };
    const obj_material_data* material = args->material;
    const obj_material_texture_data* texdata = material->material.texdata;
    for (int32_t i = 0, j = 0, l = 0; i < 4; i++, texdata++) {
        if (texdata->tex_index == -1)
            continue;

        int32_t texcoord_index = obj_material_texture_type_get_texcoord_index(
            texdata->shader_info.m.tex_type, j);
        if (texcoord_index < 0)
            continue;

        if (texdata->shader_info.m.tex_type == OBJ_MATERIAL_TEXTURE_COLOR)
            j++;

        l++;

        if (texcoord_mat_set[texcoord_index])
            continue;

        uint32_t texture_id = texdata->tex_index & 0xFFFFF;

        mats[texcoord_index] = texdata->tex_coord_mat;
        if (texdata->shader_info.m.tex_type == OBJ_MATERIAL_TEXTURE_COLOR)
            for (int32_t k = 0; k < args->texture_transform_count; k++)
                if (args->texture_transform_array[k].id == texture_id) {
                    mats[texcoord_index] = args->texture_transform_array[k].mat;
                    texcoord_mat_set[texcoord_index] = true;
                    break;
                }
    }

    rend_data_ctx.set_batch_texcoord_transforms(mats);

    if (vertex_format & OBJ_VERTEX_BONE_DATA)
        rend_data_ctx.shader_flags.arr[U_SKINNING] = 1;
    else
        rend_data_ctx.shader_flags.arr[U_SKINNING] = 0;

    if (args->morph_vertex_buffer) {
        rend_data_ctx.shader_flags.arr[U_MORPH] = 1;

        if (vertex_format & OBJ_VERTEX_COLOR0)
            rend_data_ctx.shader_flags.arr[U_MORPH_COLOR] = 1;
        else
            rend_data_ctx.shader_flags.arr[U_MORPH_COLOR] = 0;

        rend_data_ctx.set_batch_morph_weight(args->morph_weight);
    }
    else {
        rend_data_ctx.shader_flags.arr[U_MORPH] = 0;
        rend_data_ctx.shader_flags.arr[U_MORPH_COLOR] = 0;
    }

    /*if (args->instances_count)
        rend_data_ctx.shader_flags.arr[U_INSTANCE] = 1;
    else
        rend_data_ctx.shader_flags.arr[U_INSTANCE] = 0;*/
}
