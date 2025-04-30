/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include <string>
#include <vector>
#include "../KKdLib/default.hpp"
#include "../KKdLib/farc.hpp"
#include "../KKdLib/mat.hpp"
#include "../KKdLib/vec.hpp"
#include "../AFTModsShared/uniform.hpp"
#include "gl.hpp"

struct shader_sub_table {
    uint32_t sub_index;
    const int32_t* vp_unival_max;
    const int32_t* fp_unival_max;
    const char* vp;
    const char* fp;
};

struct shader_table {
    const char* name;
    uint32_t name_index;
    int32_t num_sub;
    const shader_sub_table* sub;
    int32_t num_uniform;
    const uniform_name* use_uniform;
};

struct shader;
struct shader_set_data;

typedef int32_t (*PFNSHADERGETINDEXFUNCPROC)(const char* name);

typedef void (*PFNSHADERBINDFUNCPROC)(struct p_gl_rend_state& p_gl_rend_st,
    struct uniform_value& shader_flags, shader_set_data* set, shader* shad);

struct shader_bind_func {
    uint32_t name_index;
    PFNSHADERBINDFUNCPROC bind_func;
};

struct shader_sub {
    uint32_t sub_index;
    const int32_t* vp_unival_max;
    const int32_t* fp_unival_max;
    GLuint* programs;
};

struct shader {
    const char* name;
    uint32_t name_index;
    int32_t num_sub;
    shader_sub* sub;
    int32_t num_uniform;
    const uniform_name* use_uniform;
    PFNSHADERBINDFUNCPROC bind_func;

    int32_t bind(struct p_gl_rend_state& p_gl_rend_st,
        struct uniform_value& shader_flags, shader_set_data* set, uint32_t sub_index);

    static bool parse_define(const char* data, std::string& temp);
    static bool parse_define(const char* data, int32_t num_uniform,
        int32_t* uniform_value, std::string& temp);
    static char* parse_include(char* data, farc* f);
    static void unbind(struct p_gl_rend_state& p_gl_rend_st);
};

struct shader_set_data {
    size_t size;
    shader* shaders;

    PFNSHADERGETINDEXFUNCPROC get_index_by_name_func;

    shader_set_data();

    int32_t get_index_by_name(const char* name);
    void load(farc* f, bool ignore_cache, const char* name,
        const shader_table* shaders_table, const size_t size,
        const shader_bind_func* bind_func_table, const size_t bind_func_table_size,
        PFNSHADERGETINDEXFUNCPROC get_index_by_name);
    void set(struct p_gl_rend_state& p_gl_rend_st, struct uniform_value& shader_flags, uint32_t index);
    void unload();
};
