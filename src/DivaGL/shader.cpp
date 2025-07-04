/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "shader.hpp"
#include "../KKdLib/io/file_stream.hpp"
#include "../KKdLib/io/path.hpp"
#include "../KKdLib/prj/vector_pair.hpp"
#include "../KKdLib/hash.hpp"
#include "../KKdLib/str_utils.hpp"
#include "gl_rend_state.hpp"
#include "print.hpp"
#include "shared.hpp"
#include "static_var.hpp"
#include "wrap.hpp"
#include <shlobj_core.h>

struct program_binary {
    GLsizei length;
    GLenum binary_format;
    size_t binary;
    uint64_t hash;
};

static GLuint shader_compile_shader(GLenum type, const char* data, const char* file);
static GLuint shader_compile(const char* vert, const char* frag, const char* vp, const char* fp);
static GLuint shader_compile_binary(const char* vert, const char* frag, const char* vp, const char* fp,
    program_binary* bin, GLsizei* buffer_size, void** binary);
static bool shader_load_binary_shader(program_binary* bin, GLuint* program, const char* vp, const char* fp);

int32_t shader::bind(p_gl_rend_state& p_gl_rend_st,
    uniform_value& shader_flags, shader_set_data* set, uint32_t sub_index) {
    if (num_sub < 1)
        return -1;

    int32_t sub_shader_index = 0;
    for (shader_sub* i = sub; i->sub_index != sub_index; i++)
        if (++sub_shader_index >= num_sub)
            return -1;

    shader_sub* sub_shader = &sub[sub_shader_index];

    int32_t unival_shad_curr = 1;
    int32_t unival_shad = 0;
    if (num_uniform > 0) {
        const int32_t* vp_unival_max = sub_shader->vp_unival_max;
        const int32_t* fp_unival_max = sub_shader->fp_unival_max;

        int32_t i = 0;
        for (i = 0; i < num_uniform; i++) {
            const int32_t unival = shader_flags.arr[use_uniform[i]];
            const int32_t unival_max = max_def(vp_unival_max[i], fp_unival_max[i]);
            unival_shad += unival_shad_curr * min_def(unival, unival_max);
            unival_shad_curr *= unival_max + 1;
        }
    }

    GLuint program = sub_shader->programs[unival_shad];
    p_gl_rend_st.use_program(program);
    return 0;
}

static char* get_uniform_location(char* data, prj::vector_pair<int32_t, std::string>& samplers,
    prj::vector_pair<int32_t, std::string>& uniforms, bool apple_fix) {
    std::string temp;
    temp.assign(data);
    free_def(data);

    size_t version_pos = temp.find("#version 430 core");
    if (version_pos != -1)
        if (DIVA_GL_VERSION_4_2)
            temp.replace(version_pos, 17, "#version 420 core", 17);
        else if (DIVA_GL_VERSION_4_1)
            temp.replace(version_pos, 17, "#version 410 core", 17);

    if (apple_fix) {
        size_t result_pos = temp.size() - 1;
        while ((result_pos = temp.rfind("result_", result_pos)) != -1)
            temp.replace(result_pos, 7, "frg_", 4);
    }

    if (sv_texture_skinning_buffer) {
        size_t buffer_skinning_pos = temp.find(
            "layout(std430, set = 2, binding = 0) readonly buffer Skinning");
        if (buffer_skinning_pos != -1) {
            size_t apply_skinning_pos = temp.find("vec4 apply_skinning(in const vec3 a_data,"
                " in const ivec4 mtxidx, in const vec4 weight)", buffer_skinning_pos);
            if (apply_skinning_pos != -1) {
                const char replacement[] =
                    "#define skinning_offset ivec2(g_bump_depth.zw)\n"
                    "uniform sampler2D g_skinning;\n"
                    "\n"
                    "vec3 apply_skinning(in const vec4 data, in const int mtxidx_comp) {\n"
                    "    const ivec3 mtxidx_row = ivec3(mtxidx_comp * 3) + ivec3(0, 1, 2);\n"
                    "\n"
                    "    return vec3(\n"
                    "        dot(data, texelFetch(g_skinning, ivec2(mtxidx_row.x, 0) + skinning_offset, 0)),\n"
                    "        dot(data, texelFetch(g_skinning, ivec2(mtxidx_row.y, 0) + skinning_offset, 0)),\n"
                    "        dot(data, texelFetch(g_skinning, ivec2(mtxidx_row.z, 0) + skinning_offset, 0))\n"
                    "    );\n"
                    "}\n"
                    "\n"
                    "vec3 apply_skinning_rotation(in const vec3 data, in const int mtxidx_comp) {\n"
                    "    const ivec3 mtxidx_row = ivec3(mtxidx_comp * 3) + ivec3(0, 1, 2);\n"
                    "\n"
                    "    return vec3(\n"
                    "        dot(data, texelFetch(g_skinning, ivec2(mtxidx_row.x, 0) + skinning_offset, 0).xyz),\n"
                    "        dot(data, texelFetch(g_skinning, ivec2(mtxidx_row.y, 0) + skinning_offset, 0).xyz),\n"
                    "        dot(data, texelFetch(g_skinning, ivec2(mtxidx_row.z, 0) + skinning_offset, 0).xyz)\n"
                    "    );\n"
                    " }\n"
                    "\n";
                temp.replace(buffer_skinning_pos, apply_skinning_pos - buffer_skinning_pos,
                    replacement, sizeof(replacement) - 1);

                samplers.push_back({ 21, "g_skinning" });
            }
        }
    }

    size_t binding_pos = 0;
    size_t binding_end_pos = 0;
    while ((binding_pos = temp.find("layout(set = 0, binding = ", binding_pos)) != -1
        && (binding_end_pos = temp.find(") uniform sampler", binding_pos)) != -1) {
        std::string binding_str = temp.substr(binding_pos + 26, binding_end_pos - (binding_pos + 26));
        int32_t binding = atoi(binding_str.c_str());

        bool sampler_2d = !temp.compare(binding_end_pos + 10, 9, "sampler2D");
        bool sampler_cube = !temp.compare(binding_end_pos + 10, 11, "samplerCube");
        if (DIVA_GL_VERSION_4_2) {
            if (sampler_2d) {
                char buf[0x40];
                sprintf_s(buf, sizeof(buf), "layout(binding = %d) uniform sampler2D", binding);
                temp.replace(binding_pos, binding_end_pos + 19 - binding_pos, buf);
            }
            else if (sampler_cube) {
                char buf[0x40];
                sprintf_s(buf, sizeof(buf), "layout(binding = %d) uniform samplerCube", binding);
                temp.replace(binding_pos, binding_end_pos + 21 - binding_pos, buf);
            }
        }
        else {
            if (sampler_2d) {
                size_t name_pos = binding_end_pos + 19;
                while (isspace(temp.data()[name_pos]))
                    name_pos++;

                size_t name_end_pos = temp.find(';', name_pos);
                if (name_end_pos != -1) {
                    while (isspace(temp.data()[name_end_pos - 1]))
                        name_end_pos--;

                    std::string name_str = temp.substr(name_pos, name_end_pos - name_pos);

                    bool found = false;
                    for (auto& i : samplers)
                        if (i.first == binding && i.second == name_str) {
                            found = true;
                            break;
                        }

                    if (!found)
                        samplers.push_back(binding, name_str);
                }
            }
            else if (sampler_cube) {
                size_t name_pos = binding_end_pos + 21;
                while (isspace(temp.data()[name_pos]))
                    name_pos++;

                size_t name_end_pos = temp.find(';', name_pos);
                if (name_end_pos != -1) {
                    while (isspace(temp.data()[name_end_pos - 1]))
                        name_end_pos--;

                    std::string name_str = temp.substr(name_pos, name_end_pos - name_pos);

                    bool found = false;
                    for (auto& i : samplers)
                        if (i.first == binding && i.second == name_str) {
                            found = true;
                            break;
                        }

                    if (!found)
                        samplers.push_back(binding, name_str);
                }
            }

            temp.erase(binding_pos, binding_end_pos + 2 - binding_pos);
        }
    }

    binding_pos = 0;
    binding_end_pos = 0;
    while ((binding_pos = temp.find("layout(set = 1, binding = ", binding_pos)) != -1
        && (binding_end_pos = temp.find(") uniform", binding_pos)) != -1) {
        std::string binding_str = temp.substr(binding_pos + 26, binding_end_pos - (binding_pos + 26));
        int32_t binding = atoi(binding_str.c_str());

        if (DIVA_GL_VERSION_4_2) {
            char buf[0x40];
            sprintf_s(buf, sizeof(buf), "layout(binding = %d) uniform", binding);
            temp.replace(binding_pos, binding_end_pos + 9 - binding_pos, buf);
        }
        else {
            size_t name_pos = binding_end_pos + 9;
            while (isspace(temp.data()[name_pos]))
                name_pos++;

            size_t name_end_pos = temp.find('{', name_pos);
            if (name_end_pos != -1) {
                while (isspace(temp.data()[name_end_pos - 1]))
                    name_end_pos--;

                std::string name_str = temp.substr(name_pos, name_end_pos - name_pos);

                bool found = false;
                for (auto& i : uniforms)
                    if (i.first == binding && i.second == name_str) {
                        found = true;
                        break;
                    }

                if (!found)
                    uniforms.push_back(binding, name_str);
            }

            temp.erase(binding_pos, binding_end_pos + 2 - binding_pos);
        }
    }

    binding_pos = 0;
    binding_end_pos = 0;
    while ((binding_pos = temp.find("layout(std430, set = 2, binding = ", binding_pos)) != -1
        && (binding_end_pos = temp.find(") readonly buffer", binding_pos)) != -1) {
        std::string binding_str = temp.substr(binding_pos + 34, binding_end_pos - (binding_pos + 34));
        int32_t binding = atoi(binding_str.c_str()) + 6;

        if (DIVA_GL_VERSION_4_2) {
            char buf[0x40];
            sprintf_s(buf, sizeof(buf), "layout(binding = %d) uniform", binding);
            temp.replace(binding_pos, binding_end_pos + 17 - binding_pos, buf);
        }
        else {
            size_t name_pos = binding_end_pos + 17;
            while (isspace(temp.data()[name_pos]))
                name_pos++;

            size_t name_end_pos = temp.find('{', name_pos);
            if (name_end_pos != -1) {
                while (isspace(temp.data()[name_end_pos - 1]))
                    name_end_pos--;

                std::string name_str = temp.substr(name_pos, name_end_pos - name_pos);

                bool found = false;
                for (auto& i : uniforms)
                    if (i.first == binding && i.second == name_str) {
                        found = true;
                        break;
                    }

                if (!found)
                    uniforms.push_back(binding, name_str);
            }

            temp.replace(binding_pos, binding_end_pos + 17 - binding_pos, "uniform", 7);
        }
    }

    size_t in_pos = temp.size() - 1;
    while ((in_pos = temp.rfind("in const", in_pos)) != -1)
        temp.replace(in_pos, 8, "const", 5);

    size_t const_pos = temp.size() - 1;
    size_t offsets_pos = temp.size() - 1;
    while ((const_pos = temp.rfind("const ", const_pos)) != -1) {
        offsets_pos = temp.find("offsets", const_pos);
        if (offsets_pos == -1 || offsets_pos - const_pos > 20)
            temp.erase(const_pos, 6);
        else
            const_pos--;
    }

    size_t use_vertex_attrib_pos = temp.size() - 1;
    while ((use_vertex_attrib_pos = temp.rfind("USE_VERTEX_ATTRIB", use_vertex_attrib_pos)) != -1)
        temp.replace(use_vertex_attrib_pos, 17, "(1)", 3);

    return str_utils_copy(temp.c_str());
}

static void parse_define_inner(std::string& temp) {
    size_t off = 0;
    while (true) {
        size_t pos_set = temp.find("set = ", off);
        if (pos_set == -1)
            break;

        size_t pos_binding = temp.find("binding = ", pos_set);
        if (pos_binding == -1)
            break;

        if (pos_binding - pos_set > 10) {
            off = pos_binding + 10;
            continue;
        }

        temp.erase(pos_set, pos_binding - pos_set);
        off = pos_set + 10;
    }
}

bool shader::parse_define(const char* data, std::string& temp) {
    if (!data)
        return false;

    const char* def = strstr(data, "//DEF\n");
    if (def) {
        temp.clear();

        size_t len_a = def - data;
        def += 5;
        if (*def == '\n')
            def++;

        size_t len_b = utf8_length(def);

        size_t pos = 0;
        temp.insert(pos, data, len_a);
        pos += len_a;
        temp.insert(pos, def, len_b);
        pos += len_b;
    }
    else
        temp.assign(data);

    if (DIVA_GL_VERSION_4_3)
        parse_define_inner(temp);
    return true;
}

bool shader::parse_define(const char* data, int32_t num_uniform,
    int32_t* uniform_value, std::string& temp) {
    if (!data)
        return false;

    const char* def = strstr(data, "//DEF\n");
    if (def) {
        temp.clear();

        size_t len_a = def - data;
        def += 5;
        if (*def == '\n')
            def++;

        size_t len_b = utf8_length(def);

        size_t pos = 0;
        temp.insert(pos, data, len_a);
        pos += len_a;
        for (int32_t i = 0; i < num_uniform; i++) {
            char t[0x100];
            int32_t len = sprintf_s(t, sizeof(t), "#define _%d %d\n", i, uniform_value[i]);
            temp.insert(pos, t, len);
            pos += len;
        }
        temp.insert(pos, def, len_b);
        pos += len_b;
    }
    else
        temp.assign(data);

    if (DIVA_GL_VERSION_4_3)
        parse_define_inner(temp);
    return true;
}

char* shader::parse_include(char* data, farc* f) {
    if (!data || !f)
        return data;

    char* data_end = data + utf8_length(data);
    char* i0 = strstr(data, "#include \"");
    char* i1 = i0 ? strstr(i0, "\"\n") : 0;
    if (!i0 || !i1)
        return data;

    size_t count = 1;
    while (i1 && (i0 = strstr(i1, "#include \""))) {
        i0 += 10;
        i1 = strstr(i0, "\"\n");
        if (i1)
            i1 += 1;
        count++;
    }

    char** temp = force_malloc<char*>(count);
    size_t* temp_len = force_malloc<size_t>(count);
    char** temp_ptr0 = force_malloc<char*>(count);
    char** temp_ptr1 = force_malloc<char*>(count);
    if (!temp || !temp_len || !temp_ptr0 || !temp_ptr1) {
        free_def(temp);
        free_def(temp_len);
        free_def(temp_ptr0);
        free_def(temp_ptr1);
        return data;
    }

    i1 = data;
    for (size_t i = 0; i < count; i++) {
        temp[i] = 0;
        i0 = i1 ? strstr(i1, "#include \"") : 0;
        i1 = i0 ? strstr(i0, "\"\n") : 0;
        if (!i0 || !i1)
            continue;

        temp_ptr0[i] = i0;
        temp_ptr1[i] = i1 + 1;
        i0 += 10;
        size_t s = i1 - i0;
        i1 += 2;
        char* t = force_malloc<char>(s + 1);
        if (!t)
            continue;

        memcpy(t, i0, s);
        t[s] = 0;

        farc_file* ff = f->read_file(t);
        free_def(t);
        if (!ff)
            continue;

        t = force_malloc<char>(ff->size + 1);
        if (t) {
            memcpy(t, ff->data, ff->size);
            t[ff->size] = 0;
        }
        temp[i] = t;
        temp_len[i] = ff->size;
    }

    size_t len = data_end - data;
    i1 = data;
    for (size_t i = 0; i < count; i++) {
        i0 = temp_ptr0[i];
        i1 = temp_ptr1[i];
        if (!i0 || !i1)
            continue;

        len -= i1 - i0;
        len += temp_len[i];
    }

    char* temp_data = force_malloc<char>(len + 1);
    size_t pos = 0;
    memcpy(temp_data + pos, data, temp_ptr0[0] - data);
    pos += temp_ptr0[0] - data;
    for (int32_t i = 0; i < count; i++) {
        if (temp[i]) {
            size_t s = temp_len[i];
            memcpy(temp_data + pos, temp[i], s);
            pos += s;
        }

        if (i < count - 1 && temp_ptr1[i]) {
            size_t s = temp_ptr0[i + 1] - temp_ptr1[i];
            memcpy(temp_data + pos, temp_ptr1[i], s);
            pos += s;
        }
        else if (temp_ptr1[i]) {
            size_t s = data_end - temp_ptr1[i];
            memcpy(temp_data + pos, temp_ptr1[i], s);
            pos += s;
        }
    }
    temp_data[pos] = 0;

    free_def(data);
    for (size_t i = 0; i < count; i++)
        free_def(temp[i]);
    free_def(temp);
    free_def(temp_len);
    free_def(temp_ptr0);
    free_def(temp_ptr1);
    return temp_data;
}

void shader::unbind(p_gl_rend_state& p_gl_rend_st) {
    p_gl_rend_st.use_program(0);
}

shader_set_data::shader_set_data() : size(), shaders(), get_index_by_name_func() {

}

int32_t shader_set_data::get_index_by_name(const char* name) {
    if (get_index_by_name_func) {
        int32_t index = get_index_by_name_func(name);
        if (index != -1)
            return index;
    }

    for (size_t i = 0; i < size; i++)
        if (!str_utils_compare(shaders[i].name, name))
            return (int32_t)shaders[i].name_index;
    return -1;
}

extern "C" __declspec(dllexport) LPCWSTR GetBuildDate(void);

void shader_set_data::load(farc* f, bool ignore_cache,
    const char* name, const shader_table* shaders_table, const size_t size,
    const shader_bind_func* bind_func_table, const size_t bind_func_table_size,
    PFNSHADERGETINDEXFUNCPROC get_index_by_name) {
    if (!this || !f || !shaders_table || !size)
        return;

    wchar_t temp_buf[MAX_PATH];
    if (FAILED(SHGetFolderPathW(0, CSIDL_LOCAL_APPDATA, 0, 0, temp_buf)))
        return;

    const bool apple = !!strstr((const char*)glGetStringGLUT(GL_VENDOR), "Apple");

    if (strstr((const char*)glGetStringGLUT(GL_VERSION), "Mesa"))
        ignore_cache = true;

    wcscat_s(temp_buf, sizeof(temp_buf) / sizeof(wchar_t), L"\\PDAFT");
    path_create_directory(temp_buf);

    wchar_t buf[MAX_PATH];
    swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"\\%hs_shader_cache", name);
    wcscat_s(temp_buf, sizeof(temp_buf) / sizeof(wchar_t), buf);

    bool shader_cache_changed = false;
    farc shader_cache_farc;
    swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"%ls.farc", temp_buf);
    if (!ignore_cache && path_check_file_exists(buf))
        shader_cache_farc.read(buf, true, false);

    uint64_t build_date_hash = hash_utf16_xxh3_64bits(GetBuildDate());

    char vert_buf[MAX_PATH];
    char frag_buf[MAX_PATH];
    char vert_file_buf[MAX_PATH];
    char frag_file_buf[MAX_PATH];
    char shader_cache_file_name[MAX_PATH];

    GLsizei buffer_size = 0x100000;
    void* binary = force_malloc(buffer_size);
    std::string temp_vert;
    std::string temp_frag;
    std::vector<int32_t> vec_vert;
    std::vector<int32_t> vec_frag;
    std::vector<program_binary> program_data_binary;
    shader* shaders = force_malloc<shader>(size);
    this->shaders = shaders;
    this->size = size;
    for (size_t i = 0; i < size; i++) {
        shader* shader = &shaders[i];
        shader->name = shaders_table[i].name;
        shader->name_index = shaders_table[i].name_index;
        shader->num_sub = shaders_table[i].num_sub;
        shader->sub = force_malloc<shader_sub>(shader->num_sub);
        shader->num_uniform = shaders_table[i].num_uniform;
        shader->use_uniform = shaders_table[i].use_uniform;

        int32_t num_sub = shader->num_sub;
        const shader_sub_table* sub_table = shaders_table[i].sub;
        shader_sub* sub = shader->sub;
        vec_vert.resize(shader->num_uniform);
        vec_frag.resize(shader->num_uniform);
        int32_t* vec_vert_data = vec_vert.data();
        int32_t* vec_frag_data = vec_frag.data();
        for (int32_t j = 0; j < num_sub; j++, sub++, sub_table++) {
            sub->sub_index = sub_table->sub_index;
            sub->vp_unival_max = sub_table->vp_unival_max;
            sub->fp_unival_max = sub_table->fp_unival_max;

            strcpy_s(vert_file_buf, sizeof(vert_file_buf), sub_table->vp);
            strcat_s(vert_file_buf, sizeof(vert_file_buf), ".vert");
            farc_file* vert_ff = f->read_file(vert_file_buf);

            char* vert_data = 0;
            if (vert_ff && vert_ff->data) {
                vert_data = force_malloc<char>(vert_ff->size + 1);
                if (vert_data) {
                    memcpy(vert_data, vert_ff->data, vert_ff->size);
                    vert_data[vert_ff->size] = 0;
                }
            }

            strcpy_s(frag_file_buf, sizeof(frag_file_buf), sub_table->fp);
            strcat_s(frag_file_buf, sizeof(frag_file_buf), ".frag");
            farc_file* frag_ff = f->read_file(frag_file_buf);

            char* frag_data = 0;
            if (frag_ff && frag_ff->data) {
                frag_data = force_malloc<char>(frag_ff->size + 1);
                if (frag_data) {
                    memcpy(frag_data, frag_ff->data, frag_ff->size);
                    frag_data[frag_ff->size] = 0;
                }
            }

            if (!vert_data || !frag_data) {
                free_def(vert_data);
                free_def(frag_data);
                continue;
            }

            uint32_t uniform_vert_flags = 0;
            uint32_t uniform_frag_flags = 0;
            for (int32_t k = 0; k < shader->num_uniform; k++) {
                if (sub_table->vp_unival_max[k] > 0)
                    uniform_vert_flags |= 1 << k;
                if (sub_table->fp_unival_max[k] > 0)
                    uniform_frag_flags |= 1 << k;
            }

            char uniform_vert_flags_buf[9];
            char uniform_frag_flags_buf[9];
            for (int32_t k = 0, l = 7; k < 32; k += 4, l--) {
                int32_t vert_flags_digit = (uniform_vert_flags >> k) & 0xF;
                if (vert_flags_digit >= 0x00 && vert_flags_digit <= 0x09)
                    uniform_vert_flags_buf[l] = (char)('0' + vert_flags_digit);
                else
                    uniform_vert_flags_buf[l] = (char)('A' + (vert_flags_digit - 0x0A));

                int32_t frag_flags_digit = (uniform_frag_flags >> k) & 0xF;
                if (frag_flags_digit >= 0x00 && frag_flags_digit <= 0x09)
                    uniform_frag_flags_buf[l] = (char)('0' + frag_flags_digit);
                else
                    uniform_frag_flags_buf[l] = (char)('A' + (frag_flags_digit - 0x0A));
            }
            uniform_vert_flags_buf[8] = 0;
            uniform_frag_flags_buf[8] = 0;

            strcpy_s(vert_buf, sizeof(vert_buf), vert_file_buf);
            strcpy_s(frag_buf, sizeof(frag_buf), frag_file_buf);
            strcat_s(vert_buf, sizeof(vert_buf), ".");
            strcat_s(frag_buf, sizeof(frag_buf), ".");
            strcat_s(vert_buf, sizeof(vert_buf), uniform_vert_flags_buf);
            strcat_s(frag_buf, sizeof(frag_buf), uniform_frag_flags_buf);

            uint64_t vert_file_name_hash = hash_utf8_xxh3_64bits(vert_buf) ^ build_date_hash;
            uint64_t frag_file_name_hash = hash_utf8_xxh3_64bits(frag_buf) ^ build_date_hash;

            strcpy_s(shader_cache_file_name, sizeof(shader_cache_file_name), sub_table->vp);
            if (str_utils_compare(sub_table->vp, sub_table->fp)) {
                strcat_s(shader_cache_file_name, sizeof(shader_cache_file_name), ".");
                strcat_s(shader_cache_file_name, sizeof(shader_cache_file_name), sub_table->fp);
            }
            strcat_s(shader_cache_file_name, sizeof(shader_cache_file_name), ".bin");

            vert_data = shader::parse_include(vert_data, f);
            frag_data = shader::parse_include(frag_data, f);

            prj::vector_pair<int32_t, std::string> samplers;
            prj::vector_pair<int32_t, std::string> uniforms;
            if (!DIVA_GL_VERSION_4_3) {
                vert_data = get_uniform_location(vert_data, samplers, uniforms, apple);
                frag_data = get_uniform_location(frag_data, samplers, uniforms, apple);
            }

            uint64_t vert_data_hash = hash_utf8_xxh3_64bits(vert_data);
            uint64_t frag_data_hash = hash_utf8_xxh3_64bits(frag_data);

            farc_file* shader_cache_file = shader_cache_farc.read_file(shader_cache_file_name);
            program_binary* bin = 0;
            if (!ignore_cache) {
                if (!shader_cache_file || !shader_cache_file->data)
                    printf_debug("Shader not compiled: %s %s\n", vert_file_buf, frag_file_buf);
                else if (vert_file_name_hash != ((uint64_t*)shader_cache_file->data)[0]
                    || frag_file_name_hash != ((uint64_t*)shader_cache_file->data)[1])
                    printf_debug("Shader flags not equal: %s %s\n", vert_file_buf, frag_file_buf);
                else if (vert_data_hash != ((uint64_t*)shader_cache_file->data)[2]
                    || frag_data_hash != ((uint64_t*)shader_cache_file->data)[3])
                    printf_debug("Shader hash not equal: %s %s\n", vert_file_buf, frag_file_buf);
                else
                    bin = (program_binary*)&((uint64_t*)shader_cache_file->data)[4];
            }

            if (shader->num_uniform > 0
                && (sub_table->vp_unival_max[0] != -1 || sub_table->fp_unival_max[0] != -1)) {
                int32_t num_uniform = shader->num_uniform;
                int32_t unival_shad_curr = 1;
                int32_t unival_shad_count = 1;
                const int32_t* vp_unival_max = sub_table->vp_unival_max;
                const int32_t* fp_unival_max = sub_table->fp_unival_max;
                for (int32_t k = 0; k < num_uniform; k++) {
                    const int32_t unival_max = max_def(vp_unival_max[k], fp_unival_max[k]);
                    unival_shad_count += unival_shad_curr * unival_max;
                    unival_shad_curr *= unival_max + 1;
                }

                if (!ignore_cache)
                    program_data_binary.reserve(unival_shad_count);
                GLuint* programs = force_malloc<GLuint>(unival_shad_count);
                sub->programs = programs;
                if (programs) {
                    strcpy_s(vert_buf, sizeof(vert_buf), sub_table->vp);
                    size_t vert_buf_pos = utf8_length(vert_buf);
                    vert_buf[vert_buf_pos++] = '.';
                    vert_buf[vert_buf_pos] = 0;
                    memset(&vert_buf[vert_buf_pos], '0', num_uniform);
                    vert_buf[vert_buf_pos + num_uniform] = 0;
                    strcat_s(vert_buf, sizeof(vert_buf), ".vert");

                    strcpy_s(frag_buf, sizeof(frag_buf), sub_table->fp);
                    size_t frag_buf_pos = utf8_length(frag_buf);
                    frag_buf[frag_buf_pos++] = '.';
                    frag_buf[frag_buf_pos] = 0;
                    memset(&frag_buf[frag_buf_pos], '0', num_uniform);
                    frag_buf[frag_buf_pos + num_uniform] = 0;
                    strcat_s(frag_buf, sizeof(frag_buf), ".frag");

                    for (int32_t k = 0; k < unival_shad_count; k++) {
                        for (int32_t l = 0, m = k; l < num_uniform; l++) {
                            int32_t unival_max = max_def(vp_unival_max[l], fp_unival_max[l]) + 1;
                            vec_vert_data[l] = min_def(m % unival_max, vp_unival_max[l]);
                            m /= unival_max;
                            vert_buf[vert_buf_pos + l] = (char)('0' + vec_vert_data[l]);
                        }

                        for (int32_t l = 0, m = k; l < num_uniform; l++) {
                            int32_t unival_max = max_def(vp_unival_max[l], fp_unival_max[l]) + 1;
                            vec_frag_data[l] = min_def(m % unival_max, fp_unival_max[l]);
                            m /= unival_max;
                            frag_buf[frag_buf_pos + l] = (char)('0' + vec_frag_data[l]);
                        }

                        if (!bin || !bin->binary_format || !bin->length
                            || !shader_load_binary_shader(bin, &programs[k], vert_buf, frag_buf)) {
                            bool vert_succ = shader::parse_define(vert_data,
                                num_uniform, vec_vert_data, temp_vert);
                            bool frag_succ = shader::parse_define(frag_data,
                                num_uniform, vec_frag_data, temp_frag);

                            if (ignore_cache)
                                programs[k] = shader_compile(vert_succ ? temp_vert.c_str() : 0,
                                    frag_succ ? temp_frag.c_str() : 0, vert_buf, frag_buf);
                            else {
                                program_data_binary.push_back({});
                                programs[k] = shader_compile_binary(vert_succ ? temp_vert.c_str() : 0,
                                    frag_succ ? temp_frag.c_str() : 0, vert_buf, frag_buf,
                                    &program_data_binary.back(), &buffer_size, &binary);

                                shader_cache_changed |= !!programs[k];
                            }
                        }
                        else {
                            program_data_binary.push_back({});
                            program_binary* b = &program_data_binary.back();
                            b->length = bin->length;
                            b->binary_format = bin->binary_format;
                            b->binary = (size_t)force_malloc(bin->length);
                            memcpy((void*)b->binary, (void*)((size_t)bin + bin->binary), bin->length);
                        }

                        if (!DIVA_GL_VERSION_4_3) {
                            if (programs[k] && samplers.size()) {
                                GLuint program = programs[k];

                                glUseProgram(program);
                                for (auto& i : samplers) {
                                    GLint loc = glGetUniformLocation(program, i.second.c_str());
                                    if (loc != -1)
                                        glUniform1i(loc, i.first);
                                }
                                glUseProgram(0);
                            }

                            if (programs[k] && uniforms.size()) {
                                GLuint program = programs[k];

                                for (auto& i : uniforms) {
                                    GLuint loc = glGetUniformBlockIndex(program, i.second.c_str());
                                    if (loc != -1)
                                        glUniformBlockBinding(program, loc, i.first);
                                }
                            }
                        }

                        if (!ignore_cache && bin)
                            bin++;
                    }
                }
            }
            else {
                program_data_binary.reserve(1);
                GLuint* programs = force_malloc<GLuint>();
                sub->programs = programs;
                if (programs) {
                    strcpy_s(vert_buf, sizeof(vert_buf), sub_table->vp);
                    strcpy_s(frag_buf, sizeof(vert_buf), sub_table->fp);
                    strcat_s(vert_buf, sizeof(vert_buf), "..vert");
                    strcat_s(frag_buf, sizeof(vert_buf), "..frag");

                    if (!bin || !bin->binary_format || !bin->length
                        || !shader_load_binary_shader(bin, &programs[0], vert_buf, frag_buf)) {
                        bool vert_succ = shader::parse_define(vert_data, temp_vert);
                        bool frag_succ = shader::parse_define(frag_data, temp_frag);

                        if (ignore_cache)
                            programs[0] = shader_compile(vert_succ ? temp_vert.c_str() : 0,
                                frag_succ ? temp_frag.c_str() : 0, vert_buf, frag_buf);
                        else {
                            program_data_binary.push_back({});
                            programs[0] = shader_compile_binary(vert_succ ? temp_vert.c_str() : 0,
                                frag_succ ? temp_frag.c_str() : 0, vert_buf, frag_buf,
                                &program_data_binary.back(), &buffer_size, &binary);

                            shader_cache_changed |= !!programs[0];
                        }
                    }
                    else {
                        program_data_binary.push_back({});
                        program_binary* b = &program_data_binary.back();
                        b->length = bin->length;
                        b->binary_format = bin->binary_format;
                        b->binary = (size_t)force_malloc(bin->length);
                        memcpy((void*)b->binary, (void*)((size_t)bin + bin->binary), bin->length);
                    }

                    if (!DIVA_GL_VERSION_4_3) {
                        if (programs[0] && samplers.size()) {
                            GLuint program = programs[0];

                            glUseProgram(program);
                            for (auto& i : samplers) {
                                GLint loc = glGetUniformLocation(program, i.second.c_str());
                                if (loc != -1)
                                    glUniform1i(loc, i.first);
                            }
                            glUseProgram(0);
                        }

                        if (programs[0] && uniforms.size()) {
                            GLuint program = programs[0];

                            for (auto& i : uniforms) {
                                GLint loc = glGetUniformBlockIndex(program, i.second.c_str());
                                if (loc != -1)
                                    glUniformBlockBinding(program, loc, i.first);
                            }
                        }
                    }

                    if (!ignore_cache && bin)
                        bin++;
                }
            }

            if (!ignore_cache) {
                if (!shader_cache_file)
                    shader_cache_file = shader_cache_farc.add_file(shader_cache_file_name);
                else
                    free_def(shader_cache_file->data);

                size_t bin_count = program_data_binary.size();
                size_t bin_size = sizeof(uint64_t) * 4 + bin_count * sizeof(program_binary);
                for (program_binary& k : program_data_binary)
                    bin_size += align_val(k.length, 0x04);
                shader_cache_file->data = force_malloc(bin_size);
                shader_cache_file->size = bin_size;
                shader_cache_file->compressed = true;
                shader_cache_file->data_changed = true;

                ((uint64_t*)shader_cache_file->data)[0] = vert_file_name_hash;
                ((uint64_t*)shader_cache_file->data)[1] = frag_file_name_hash;
                ((uint64_t*)shader_cache_file->data)[2] = vert_data_hash;
                ((uint64_t*)shader_cache_file->data)[3] = frag_data_hash;
                bin = (program_binary*)&((uint64_t*)shader_cache_file->data)[4];
                size_t bin_data_base = (size_t)shader_cache_file->data + sizeof(uint64_t) * 4;
                size_t bin_data = bin_data_base + bin_count * sizeof(program_binary);
                for (program_binary& k : program_data_binary) {
                    bin->length = k.length;
                    bin->binary_format = k.binary_format;
                    bin->binary = bin_data - bin_data_base;
                    bin->hash = hash_xxh3_64bits((void*)k.binary, k.length);
                    memcpy((void*)bin_data, (void*)k.binary, k.length);
                    bin_data_base += sizeof(program_binary);
                    bin_data += align_val(k.length, 0x04);
                    void* binary = (void*)k.binary;
                    free_def(binary);
                    k.binary = 0;
                    bin++;
                }
            }

            free_def(vert_data);
            free_def(frag_data);
            program_data_binary.clear();
        }
        vec_vert.clear();
        vec_frag.clear();

        for (size_t j = 0; j < bind_func_table_size; j++)
            if (shader->name_index == bind_func_table[j].name_index) {
                shader->bind_func = bind_func_table[j].bind_func;
                break;
            }
    }
    free_def(binary);

    if (!ignore_cache && shader_cache_changed)
        shader_cache_farc.write(temp_buf, FARC_FArC, FARC_NONE, true, false);

    this->get_index_by_name_func = get_index_by_name;
}

void shader_set_data::set(p_gl_rend_state& p_gl_rend_st, uniform_value& shader_flags, uint32_t index) {
    if (this && index && index != -1) {
        shader* shader = &shaders[index];
        if (shader->bind_func)
            shader->bind_func(p_gl_rend_st, shader_flags, this, shader);
        else
            shader->bind(p_gl_rend_st, shader_flags, this, shader->sub[0].sub_index);
    }
    else
        shader::unbind(p_gl_rend_st);
}

void shader_set_data::unload() {
    size_t size = this->size;
    shader* shaders = this->shaders;
    for (size_t i = 0; i < size; i++) {
        shader* shader = &shaders[i];
        if (!shader->sub)
            continue;

        int32_t num_sub = shader->num_sub;
        shader_sub* sub = shader->sub;
        for (int32_t j = 0; j < num_sub; j++, sub++) {
            int32_t unival_shad_count = 1;
            if (shader->num_uniform > 0) {
                int32_t num_uniform = shader->num_uniform;
                int32_t unival_shad_curr = 1;
                const int32_t* vp_unival_max = sub->vp_unival_max;
                const int32_t* fp_unival_max = sub->fp_unival_max;
                for (int32_t k = 0; k < num_uniform; k++) {
                    const int32_t unival_max = max_def(vp_unival_max[k], fp_unival_max[k]);
                    unival_shad_count += unival_shad_curr * unival_max;
                    unival_shad_curr *= unival_max + 1;
                }
            }

            if (sub->programs) {
                GLuint* programs = sub->programs;
                for (int32_t k = 0; k < unival_shad_count; k++)
                    glDeleteProgram(programs[k]);
                free(programs);
                sub->programs = 0;
            }
        }
        free(shader->sub);
        shader->sub = 0;
    }
    free_def(shaders);
    this->shaders = 0;

    get_index_by_name_func = 0;
}

static GLuint shader_compile_shader(GLenum type, const char* data, const char* file) {
    if (!data)
        return 0;

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &data, 0);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        GLchar* info_log = force_malloc<GLchar>(length);
        glGetShaderInfoLog(shader, length, 0, info_log);
        const char* type_str = "Unknown";
        switch (type) {
        case GL_FRAGMENT_SHADER:
            type_str = "Fragment";
            break;
        case GL_VERTEX_SHADER:
            type_str = "Vertex";
            break;
        }
        printf_debug("%s shader compile error:\nfile: %s\n%s\n", type_str, file, info_log);

        wchar_t temp_buf[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathW(0, CSIDL_LOCAL_APPDATA, 0, 0, temp_buf))) {
            wcscat_s(temp_buf, sizeof(temp_buf) / sizeof(wchar_t), L"\\PDAFT");
            temp_buf[sizeof(temp_buf) / sizeof(wchar_t) - 1] = 0;
            path_create_directory(temp_buf);

            wchar_t buf[MAX_PATH];
            swprintf_s(buf, sizeof(buf) / sizeof(wchar_t),
                L"%ls\\shader_error", temp_buf);
            buf[sizeof(buf) / sizeof(wchar_t) - 1] = 0;
            path_create_directory(buf);

            swprintf_s(buf, sizeof(buf) / sizeof(wchar_t),
                L"%ls\\shader_error\\%hs", temp_buf, file);
            buf[sizeof(buf) / sizeof(wchar_t) - 1] = 0;

            file_stream s;
            s.open(buf, L"wb");
            s.write_utf8_string(data);
            s.write_utf8_string("\n/*\n");
            s.write_utf8_string(info_log);
            s.write_utf8_string("*/\n");
        }

        free_def(info_log);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static GLuint shader_compile(const char* vert, const char* frag, const char* vp, const char* fp) {
    GLuint vert_shad = shader_compile_shader(GL_VERTEX_SHADER, vert, vp);
    GLuint frag_shad = shader_compile_shader(GL_FRAGMENT_SHADER, frag, fp);

    GLuint program = glCreateProgram();
    if (vert_shad)
        glAttachShader(program, vert_shad);
    if (frag_shad)
        glAttachShader(program, frag_shad);
    glLinkProgram(program);

    if (vert_shad)
        glDeleteShader(vert_shad);
    if (frag_shad)
        glDeleteShader(frag_shad);

    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLint length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        GLchar* info_log = force_malloc<GLchar>(length);
        glGetProgramInfoLog(program, length, 0, info_log);
        printf_debug("Program Shader Permut linking error:\nvp: %s; fp: %s\n%s\n", vp, fp, info_log);

        wchar_t temp_buf[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathW(0, CSIDL_LOCAL_APPDATA, 0, 0, temp_buf))) {
            wcscat_s(temp_buf, sizeof(temp_buf) / sizeof(wchar_t), L"\\PDAFT");
            temp_buf[sizeof(temp_buf) / sizeof(wchar_t) - 1] = 0;
            path_create_directory(temp_buf);

            wchar_t buf[MAX_PATH];
            swprintf_s(buf, sizeof(buf) / sizeof(wchar_t),
                L"%ls\\shader_error", temp_buf);
            buf[sizeof(buf) / sizeof(wchar_t) - 1] = 0;
            path_create_directory(buf);

            swprintf_s(buf, sizeof(buf) / sizeof(wchar_t),
                L"%ls\\shader_error\\%hs", temp_buf, vp);
            buf[sizeof(buf) / sizeof(wchar_t) - 1] = 0;

            file_stream s;
            s.open(buf, L"wb");
            s.write_utf8_string(vert);
            s.write_utf8_string("\n/*\n");
            s.write_utf8_string(info_log);
            s.write_utf8_string("*/\n");
            s.close();

            swprintf_s(buf, sizeof(buf) / sizeof(wchar_t),
                L"%ls\\shader_error\\%hs", temp_buf, fp);
            buf[sizeof(buf) / sizeof(wchar_t) - 1] = 0;

            s.open(buf, L"wb");
            s.write_utf8_string(frag);
            s.write_utf8_string("\n/*\n");
            s.write_utf8_string(info_log);
            s.write_utf8_string("*/\n");
            s.close();
        }

        free_def(info_log);
        glDeleteProgram(program);
        return 0;
    }
    else {
        gl_get_error_all_print();
        return program;
    }
}

static GLuint shader_compile_binary(const char* vert, const char* frag, const char* vp, const char* fp,
    program_binary* bin, GLsizei* buffer_size, void** binary) {
    memset(bin, 0, sizeof(*bin));

    GLuint vert_shad = shader_compile_shader(GL_VERTEX_SHADER, vert, vp);
    GLuint frag_shad = shader_compile_shader(GL_FRAGMENT_SHADER, frag, fp);

    GLuint program = glCreateProgram();
    if (vert_shad)
        glAttachShader(program, vert_shad);
    if (frag_shad)
        glAttachShader(program, frag_shad);
    glLinkProgram(program);

    if (vert_shad)
        glDeleteShader(vert_shad);
    if (frag_shad)
        glDeleteShader(frag_shad);

    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLint length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        GLchar* info_log = force_malloc<GLchar>(length);
        glGetProgramInfoLog(program, length, 0, info_log);
        printf_debug("Program Shader Permut linking error:\nvp: %s; fp: %s\n%s\n", vp, fp, info_log);

        wchar_t temp_buf[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathW(0, CSIDL_LOCAL_APPDATA, 0, 0, temp_buf))) {
            wcscat_s(temp_buf, sizeof(temp_buf) / sizeof(wchar_t), L"\\PDAFT");
            temp_buf[sizeof(temp_buf) / sizeof(wchar_t) - 1] = 0;
            path_create_directory(temp_buf);

            wchar_t buf[MAX_PATH];
            swprintf_s(buf, sizeof(buf) / sizeof(wchar_t),
                L"%ls\\shader_error", temp_buf);
            buf[sizeof(buf) / sizeof(wchar_t) - 1] = 0;
            path_create_directory(buf);

            swprintf_s(buf, sizeof(buf) / sizeof(wchar_t),
                L"%ls\\shader_error\\%hs", temp_buf, vp);
            buf[sizeof(buf) / sizeof(wchar_t) - 1] = 0;

            file_stream s;
            s.open(buf, L"wb");
            s.write_utf8_string(vert);
            s.write_utf8_string("\n/*\n");
            s.write_utf8_string(info_log);
            s.write_utf8_string("*/\n");
            s.close();

            swprintf_s(buf, sizeof(buf) / sizeof(wchar_t),
                L"%ls\\shader_error\\%hs", temp_buf, fp);
            buf[sizeof(buf) / sizeof(wchar_t) - 1] = 0;

            s.open(buf, L"wb");
            s.write_utf8_string(frag);
            s.write_utf8_string("\n/*\n");
            s.write_utf8_string(info_log);
            s.write_utf8_string("*/\n");
            s.close();
        }

        free_def(info_log);
        glDeleteProgram(program);
        return 0;
    }
    else {
        gl_get_error_all_print();

        GLenum binary_format = 0x0;
        GLsizei length = 0;
        while (*buffer_size < 0x7FFFFFF) {
            glGetProgramBinary(program, *buffer_size, &length, &binary_format, *binary);
            if (!gl_get_error_print())
                break;

            free_def(*binary);
            *buffer_size <<= 1;
            *binary = force_malloc(*buffer_size);
        }

        bin->length = length;
        bin->binary_format = binary_format;
        bin->binary = (size_t)force_malloc(length);
        if (*binary)
            memcpy((void*)bin->binary, *binary, length);
        return program;
    }
}

static bool shader_load_binary_shader(program_binary* bin, GLuint* program, const char* vp, const char* fp) {
    if (bin->hash != hash_xxh3_64bits((void*)((size_t)bin + bin->binary), bin->length)) {
        printf_debug("Compiled binary hash could not be validated: %s %s\n", vp, fp);
        return false;
    }

    *program = glCreateProgram();
    glProgramBinary(*program, bin->binary_format, (void*)((size_t)bin + bin->binary), bin->length);
    GLint success = 0;
    glGetProgramiv(*program, GL_LINK_STATUS, &success);
    if (!success) {
        glDeleteProgram(*program);
        *program = 0;
        return false;
    }
    return true;
}
