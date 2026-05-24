/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "object.hpp"
#include "../KKdLib/hash.hpp"
#include "../AFTModsShared/file_handler.hpp"
#include "mdl/disp_manager.hpp"
#include "pv_game/firstread.hpp"
#include "gl_state.hpp"
#include "wrap.hpp"
#include <Helpers.h>
#include <map>

struct ObjsetInfo {
    p_file_handler obj_file_handler;
    bool obj_ready;
    p_file_handler tex_file_handler;
    bool tex_ready;
    prj::shared_ptr<void*> alloc_handler; // prj::stack_allocator
    obj_set* objdata_header;
    prj::vector<prj::pair<uint32_t, int32_t>> objdb_map;
    bool field_50;
    int32_t field_54;
    int32_t tex_num;
    prj::vector<GLuint> gentex_vec;
    prj::vector<prj::pair<int32_t, int32_t>> texidx_map;
    bool field_90;
    texture** textures;
    int32_t id;
    int32_t objvb_num;
    ObjVB* objvb;
    int32_t objib_num;
    ObjIB* objib;
    ObjVB* objvb_tangent;
    ObjIB* objib_tangent;
    int32_t load_count;
};

static_assert(sizeof(ObjsetInfo) == 0xD8, "\"ObjsetInfo\" struct should have a size of 0xD8");

IndexBuffer* (FASTCALL* get_object_index_buffer)(uint32_t obj_id, int32_t is_tangent)
    = (IndexBuffer * (FASTCALL*)(uint32_t obj_id, int32_t is_tangent))0x000000014045A250;
VertexBuffer* (FASTCALL* get_object_vertex_buffer)(uint32_t obj_id, int32_t is_tangent)
    = (VertexBuffer * (FASTCALL*)(uint32_t obj_id, int32_t is_tangent))0x000000014045A480;
GLuint(FASTCALL* get_objset_gen_textures_id)(int32_t objset_index, int32_t uid)
    = (GLuint(FASTCALL*)(int32_t objset_index, int32_t uid))0x000000014045A8F0;
prj::vector<GLuint>* (FASTCALL* get_objset_gen_textures_vec)(int32_t objset_index)
    = (prj::vector<GLuint> * (FASTCALL*)(int32_t objset_index))0x000000014045A9E0;

#if SHARED_OBJECT_BUFFER
static std::map<int32_t, GLuint> obj_ib;
static std::map<int32_t, GLuint> obj_vb;
#endif

static int32_t load_objset_index;

static int32_t align_val_32(int32_t value); // Added

#if SHARED_OBJECT_BUFFER
static void calc_index_buffer(obj_sub_mesh& sub_mesh, int32_t& size); // Added

static void calc_mesh_index_buffer(obj_mesh& mesh, int32_t& size); // Added
static int32_t calc_mesh_vertex_buffer(obj_mesh& mesh); // Added

static void calc_object_index_buffer(obj* obj, int32_t& size); // Added
static void calc_object_vertex_buffer(obj* obj, int32_t& size); // Added
#endif

static bool create_mesh_index_buffer_divagl(IndexBufferDivaGL* ibhn, obj_mesh* mesh);
static bool create_mesh_vertex_buffer_divagl(VertexBuffer* vbhn,
    obj_mesh* mesh, GL::BufferUsage usage = GL::BUFFER_USAGE_STATIC);
static bool create_mesh_vertex_buffer_divagl(VertexBufferDivaGL* vbhn,
    obj_mesh* mesh, GL::BufferUsage usage = GL::BUFFER_USAGE_STATIC);
#if SHARED_OBJECT_BUFFER
static void create_mesh_vertex_buffer_divagl(VertexBufferDivaGL* vbhn,
    obj_mesh* mesh, GLuint in_vb, uint32_t& offset); // Added
#endif

static bool create_object_index_buffer(ObjIB* objib, obj* obj);
static bool create_object_vertex_buffer(ObjVB* objvb, obj* obj);
#if SHARED_OBJECT_BUFFER
static bool create_object_vertex_buffer(ObjVB* objvb, obj* obj, GLuint in_vb, uint32_t& offset); // Added
#endif

static void fill_index_buffer(void* buf, obj_sub_mesh& sub_mesh, int32_t& offset); // Added

static void fill_mesh_index_buffer(void* buf, obj_mesh* mesh, int32_t& offset); // Added
static int32_t fill_mesh_vertex_buffer(void* buf, obj_mesh* mesh); // Added

#if SHARED_OBJECT_BUFFER
static void fill_object_index_buffer(void* buf, obj* obj, int32_t& offset); // Added
static void fill_object_vertex_buffer(void* buf, obj* obj, int32_t& offset); // Added
#endif

static void free_object_index_buffer(ObjIB* objib);
static void free_object_vertex_buffer(ObjVB* objvb);

static void load_objset_vertex_array(ObjsetInfo* info);

static void obj_vertex_add_bone_weight(vec4& bone_weight,
    vec4i16& bone_index, int16_t index, float_t weight);  // Added
static void obj_vertex_validate_bone_data(vec4& bone_weight, vec4i16& bone_index); // Added

HOOK(bool, FASTCALL, create_mesh_vertex_buffer, 0x0000000140458280, VertexBuffer* vbhn, obj_mesh* mesh) {
    if (!mesh->num_vertex || !mesh->vertex_array.position)
        return false;

    uint32_t size_vertex = get_vertex_size(mesh->vertex_format, mesh->attrib.m.compression);
    void* buf = prj::MemoryManager::alloc(prj::MemCTemp, (size_t)size_vertex * mesh->num_vertex, "TMP_VTXBUF");
    fill_mesh_vertex_buffer(buf, mesh);
    mesh->size_vertex = size_vertex;

    uint32_t size = size_vertex * mesh->num_vertex;
    if (size)
        size = ((uint32_t)GL::BUFFER_USAGE_STREAM << 30) | (size & ((1u << 30) - 1u));

    bool ret = vbhn->create(size, buf, mesh->attrib.m.soft_body ? 2 : 1) >= 0;
    prj::MemoryManager::free(prj::MemCTemp, buf);
    return ret;
}

HOOK(void, FASTCALL, create_objset_aabb, 0x00000001404588A0, ObjsetInfo* info) {
    originalcreate_objset_aabb(info);
    load_objset_vertex_array(info);
}

HOOK(bool, FASTCALL, create_objset_index_buffer, 0x00000001404588F0, ObjsetInfo* info) {
    obj_set* set = info->objdata_header;
    info->objib_num = set->obj_num;
    info->objib = prj::MemoryManager::alloc<ObjIB>(prj::MemCSystem, set->obj_num, "OBJIB");
    if (!info->objib)
        return false;

#if SHARED_OBJECT_BUFFER
    for (int32_t i = 0; i < set->obj_num; i++) {
        obj* obj = set->obj_data[i];
        ObjIB& objib = info->objib[i];

        objib.num_ib = obj->num_mesh;

        IndexBufferDivaGL* ibhn_array = prj::MemoryManager::alloc<IndexBufferDivaGL>(
            prj::MemCSystem, obj->num_mesh, "MESHIB");
        if (!ibhn_array)
            return false;

        objib.ibhn_array = new (ibhn_array) IndexBufferDivaGL[obj->num_mesh];
    }

    int32_t size = 0;
    for (int32_t i = 0; i < set->obj_num; i++)
        calc_object_index_buffer(set->obj_data[i], size);

    void* buf = prj::MemoryManager::alloc(prj::MemCTemp, size, "TMP_IDXBUF");
    memset(buf, 0, size);
    if (!buf)
        return false;

    int32_t fill_offset = 0;
    for (int32_t i = 0; i < set->obj_num; i++)
        fill_object_index_buffer(buf, set->obj_data[i], fill_offset);

    GLuint ib = 0;
    if (fill_offset > 0) { // size is bigger than filled buf
        ib = create_index_buffer(fill_offset, buf);
        obj_ib.insert({ info->id, ib });
    }

    if (buf)
        prj::MemoryManager::free(prj::MemCTemp, buf);

    for (int32_t i = 0; i < set->obj_num; i++) {
        obj* obj = set->obj_data[i];
        ObjIB& objib = info->objib[i];

        objib.num_ib = obj->num_mesh;
        for (int32_t j = 0; j < obj->num_mesh; j++)
#pragma warning(suppress: 6385)
            objib.ibhn_array[j].create(ib);
    }
#else
    for (int32_t i = 0; i < set->obj_num; i++)
        if (!create_object_index_buffer(&info->objib[i], set->obj_data[i]))
            return false;
#endif
    return true;
}

HOOK(bool, FASTCALL, create_objset_vertex_buffer, 0x00000001404589B0, ObjsetInfo* info) {
    obj_set* set = info->objdata_header;
    info->objvb_num = set->obj_num;
    info->objvb = prj::MemoryManager::alloc<ObjVB>(prj::MemCSystem, set->obj_num, "OBJVB");
    if (!info->objvb)
        return false;

#if SHARED_OBJECT_BUFFER
    int32_t size = 0;
    for (int32_t i = 0; i < set->obj_num; i++)
        calc_object_vertex_buffer(set->obj_data[i], size);

    void* buf = prj::MemoryManager::alloc(prj::MemCTemp, size, "TMP_VTXBUF");
    memset(buf, 0, size);

    int32_t fill_offset = 0;
    for (int32_t i = 0; i < set->obj_num; i++)
        fill_object_vertex_buffer(buf, set->obj_data[i], fill_offset);

    GLuint vb = 0;
    if (size > 0) {
        vb = create_vertex_buffer(size, buf);
        obj_vb.insert({ info->id, vb });
    }

    if (buf)
        prj::MemoryManager::free(prj::MemCTemp, buf);

    uint32_t offset = 0;
    for (int32_t i = 0; i < set->obj_num; i++)
        create_object_vertex_buffer(&info->objvb[i], set->obj_data[i], vb, offset);
#else
    for (int32_t i = 0; i < set->obj_num; i++)
        if (!info->objvb[i].load(set->obj_data[i]))
            return false;
#endif
    return true;
}

HOOK(void, FASTCALL, free_objset_index_buffer, 0x0000000140459B40, ObjsetInfo* info) {
    if (info->objib) {
        for (int32_t i = 0; i < info->objib_num; i++)
            free_object_index_buffer(&info->objib[i]);
        prj::MemoryManager::free(prj::MemCSystem, info->objib);
    }

    info->objib = 0;
    info->objib_num = 0;

#if SHARED_OBJECT_BUFFER
    auto elem = obj_ib.find(info->id);
    if (elem != obj_ib.end()) {
        free_index_buffer(elem->second);
        obj_ib.erase(elem);
    }
#endif
}

HOOK(void, FASTCALL, free_objset_vertex_buffer, 0x0000000140459C70, ObjsetInfo* info) {
    if (info->objvb) {
        for (int32_t i = 0; i < info->objvb_num; i++)
            free_object_vertex_buffer(&info->objvb[i]);
        prj::MemoryManager::free(prj::MemCSystem, info->objvb);
    }

    info->objvb = 0;
    info->objvb_num = 0;

#if SHARED_OBJECT_BUFFER
    auto elem = obj_vb.find(info->id);
    if (elem != obj_vb.end()) {
        free_vertex_buffer(elem->second);
        obj_vb.erase(elem);
    }
#endif
}

HOOK(IndexBuffer*, FASTCALL, get_object_index_buffer, 0x000000014045A250, uint32_t obj_info, int32_t is_tangent) {
    bool(FASTCALL * check_objset_index)(int32_t objset_index)
        = (bool(FASTCALL*)(int32_t objset_index))0x00000001404577D0;
    int32_t(FASTCALL * get_objnum_uid2idx)(int32_t set_uid, uint32_t obj_uid)
        = (int32_t(FASTCALL*)(int32_t set_uid, uint32_t obj_uid))0x000000014045A7A0;
    ObjsetInfo* (FASTCALL * get_objset_info)(int32_t objset_index)
        = (ObjsetInfo * (FASTCALL*)(int32_t objset_index))0x000000014045AC00;

    const object_info _obj_info = obj_info;
    if (check_objset_index(_obj_info.set_id))
        return 0;

    ObjsetInfo* info = get_objset_info(_obj_info.set_id);
    if (!info || !info->objvb)
        return 0;

    int32_t obj_index = get_objnum_uid2idx(_obj_info.set_id, _obj_info.id);
    if (obj_index >= 0) {
        if (!is_tangent)
            return info->objib[obj_index].ibhn_array;
        else if (info->objib_tangent)
            return info->objib_tangent[obj_index].ibhn_array;
    }
    return 0;
}

HOOK(VertexBuffer*, FASTCALL, get_object_vertex_buffer, 0x000000014045A480, uint32_t obj_info, int32_t is_tangent) {
    bool(FASTCALL * check_objset_index)(int32_t objset_index)
        = (bool(FASTCALL*)(int32_t objset_index))0x00000001404577D0;
    int32_t(FASTCALL * get_objnum_uid2idx)(int32_t set_uid, uint32_t obj_uid)
        = (int32_t(FASTCALL*)(int32_t set_uid, uint32_t obj_uid))0x000000014045A7A0;
    ObjsetInfo* (FASTCALL * get_objset_info)(int32_t objset_index)
        = (ObjsetInfo * (FASTCALL*)(int32_t objset_index))0x000000014045AC00;

    const object_info _obj_info = obj_info;
    if (check_objset_index(_obj_info.set_id))
        return 0;

    ObjsetInfo* info = get_objset_info(_obj_info.set_id);
    if (!info || !info->objvb)
        return 0;

    int32_t obj_index = get_objnum_uid2idx(_obj_info.set_id, _obj_info.id);
    if (obj_index >= 0) {
        if (!is_tangent)
            return info->objvb[obj_index].vbhn_array;
        else if (info->objvb_tangent)
            return info->objvb_tangent[obj_index].vbhn_array;
    }
    return 0;
}

HOOK(obj_set*, FASTCALL, obj_set_parse_file, 0x000000014045CBC0,
    prj::shared_ptr<prj::stack_allocator>& alloc, __int64 set_file, int32_t& result) {
    obj_set* set = originalobj_set_parse_file(alloc, set_file, result);

    extern bool reflect_full;
    extern const firstread* firstread_ptr;
    if (reflect_full && firstread_ptr && firstread_ptr->objset_array && load_objset_index != -1) {
        const firstread_objset_array* objset_array = firstread_ptr->objset_array;
        if (objset_array->objset_id_array && objset_array->objset_array) {
            const uint32_t num_objset = objset_array->num_objset;
            for (uint32_t i = 0; i < num_objset; i++) {
                if (objset_array->objset_id_array[i] != load_objset_index || !objset_array->objset_array[i].data)
                    continue;

                const firstread_objset* frb_set = firstread_objset::read(alloc,
                    objset_array->objset_array[i].data, objset_array->objset_array[i].size);
                if (!frb_set || !set->obj_data || !frb_set->obj_data)
                    break;

                const int32_t frb_obj_num = frb_set->obj_num;
                for (int32_t j = 0; j < frb_obj_num; j++) {
                    const int32_t obj_num = set->obj_num;
                    for (int32_t k = 0; k < obj_num; k++) {
                        if (frb_set->obj_data[j].id != set->obj_id_data[k])
                            continue;

                        obj* obj = set->obj_data[k];
                        const firstread_obj* frb_obj = &frb_set->obj_data[j];
                        if (obj->mesh_array && frb_obj->mesh_array) {
                            const int32_t frb_num_mesh = frb_obj->num_mesh;
                            int32_t index_match = -1;
                            for (int32_t l = 0; l < frb_num_mesh; l++) {
                                const uint64_t name_hash = hash_utf8_xxh3_64bits(frb_obj->mesh_array[l].name);
                                const int32_t num_mesh = obj->num_mesh;
                                for (int32_t m = 0; m < num_mesh; m++) {
                                    if (name_hash != hash_utf8_xxh3_64bits(obj->mesh_array[m].name))
                                        continue;
                                    else if (frb_obj->mesh_array[l].index != (uint8_t)-1) {
                                        if (++index_match != frb_obj->mesh_array[l].index)
                                            continue;
                                    }

                                    obj_mesh* mesh = &obj->mesh_array[m];
                                    const firstread_obj_mesh* frb_mesh = &frb_obj->mesh_array[l];
                                    if (frb_mesh->remove) {
                                        mesh->flags = 0;
                                        mesh->bsphere = {};
                                        mesh->num_submesh = 0;
                                        mesh->submesh_array = 0;
                                        mesh->vertex_format = (obj_vertex_format)0;
                                        mesh->size_vertex = 0;
                                        mesh->num_vertex = 0;
                                        for (int32_t n = 0; n < 20; n++)
                                            mesh->vertex_array_ptr[n] = 0;
                                        mesh->attrib = {};
                                        break;
                                    }

                                    if (mesh->submesh_array && mesh->num_submesh) {
                                        const int32_t num_submesh = mesh->num_submesh;
                                        for (int32_t n = 0; n < num_submesh; n++) {
                                            obj_sub_mesh* submesh = &mesh->submesh_array[n];
                                            submesh->attrib.m.no_reflect = frb_mesh->attrib.m.no_reflect;
                                            submesh->attrib.m.reflect = frb_mesh->attrib.m.reflect;
                                            submesh->attrib.m.reflect_cam_back = frb_mesh->attrib.m.reflect_cam_back;
                                        }
                                    }

                                    if (mesh->submesh_array && frb_mesh->submesh_array
                                        && mesh->num_submesh && mesh->num_submesh == frb_mesh->num_submesh) {
                                        const int32_t num_submesh = mesh->num_submesh;
                                        int32_t num_submesh_split = num_submesh;
                                        for (int32_t n = 0; n < num_submesh; n++) {
                                            const firstread_obj_sub_mesh* frb_submesh = &frb_mesh->submesh_array[n];
                                            if (frb_submesh->split)
                                                num_submesh_split++;
                                        }

                                        if (num_submesh < num_submesh_split) {
                                            obj_sub_mesh* submesh_array = mesh->submesh_array;
                                            mesh->num_submesh = num_submesh_split;
                                            mesh->submesh_array = alloc->allocate<obj_sub_mesh>(num_submesh_split);
                                            for (int32_t n = 0, o = 0; n < num_submesh; n++, o++) {
                                                const firstread_obj_sub_mesh* frb_submesh = &frb_mesh->submesh_array[n];
                                                mesh->submesh_array[o] = submesh_array[n];
                                                if (frb_submesh->split)
                                                    mesh->submesh_array[++o] = submesh_array[n];
                                            }
                                        }

                                        for (int32_t n = 0, o = 0; n < num_submesh; n++, o++) {
                                            obj_sub_mesh* submesh = &mesh->submesh_array[o];
                                            const firstread_obj_sub_mesh* frb_submesh = &frb_mesh->submesh_array[n];

                                            if (frb_submesh->split) {
                                                firstread_obj_sub_mesh_split* split = frb_submesh->split;
                                                if (split->material_index[0] != -1)
                                                    submesh->material_index = split->material_index[0];
                                                if (split->num_index[0] && split->index_array[0]) {
                                                    submesh->bsphere = split->bsphere[0];
                                                    submesh->index_format = split->index_format;
                                                    submesh->num_index = split->num_index[0];
                                                    submesh->index_array = (void*)split->index_array[0];
                                                }
                                                submesh->attrib = split->attrib[0];

                                                obj_sub_mesh* submesh_before = &mesh->submesh_array[++o];
                                                if (split->material_index[1] != -1)
                                                    submesh_before->material_index = split->material_index[1];
                                                if (split->num_index[1] && split->index_array[1]) {
                                                    submesh_before->bsphere = split->bsphere[1];
                                                    submesh_before->index_format = split->index_format;
                                                    submesh_before->num_index = split->num_index[1];
                                                    submesh_before->index_array = (void*)split->index_array[1];
                                                }
                                                submesh_before->attrib = split->attrib[1];
                                                continue;
                                            }
                                            else if (frb_submesh->num_index && frb_submesh->index_array) {
                                                submesh->bsphere = frb_submesh->bsphere;
                                                submesh->index_format = frb_submesh->index_format;
                                                submesh->num_index = frb_submesh->num_index;
                                                submesh->index_array = (void*)frb_submesh->index_array;
                                            }

                                            submesh->attrib = frb_submesh->attrib;
                                        }
                                    }

                                    if (frb_mesh->vertex_format && frb_mesh->num_vertex) {
                                        mesh->vertex_format = frb_mesh->vertex_format;
                                        mesh->size_vertex = frb_mesh->size_vertex;
                                        mesh->num_vertex = frb_mesh->num_vertex;
                                        for (int32_t n = 0; n < 20; n++)
                                            mesh->vertex_array_ptr[n] = frb_mesh->vertex_array_ptr[n];
                                    }

                                    mesh->attrib = frb_mesh->attrib;
                                    break;
                                }
                            }
                        }

                        if (frb_obj->num_material && frb_obj->material_array) {
                            obj->num_material = frb_obj->num_material;
                            obj->material_array = (obj_material_data*)frb_obj->material_array;
                        }
                        break;
                    }
                }
                break;
            }
        }
    }

    return set;
}

HOOK(bool, FASTCALL, wait_objset, 0x000000014045DA60, int32_t set) {
    load_objset_index = set;
    bool ret = originalwait_objset(set);
    load_objset_index = -1;
    return ret;
}

HOOK(GLuint, FASTCALL, create_index_buffer, 0x00000001404616F0, uint32_t size, const void* buf) {
    GLuint ib = 0;
    glGenBuffers(1, &ib);
    gl_state.bind_element_array_buffer(ib);
    if (DIVA_GL_VERSION_4_4)
        glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)size, buf, 0);
    else
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)size, buf, GL_STATIC_DRAW);
    gl_state.bind_element_array_buffer(0);

    if (glGetErrorDLL()) {
        glDeleteBuffers(1, &ib);
        return 0;
    }

    bufobj_mgr.ib_all_size += size;
    bufobj_mgr.ib_peak_size = max_def(bufobj_mgr.ib_peak_size, bufobj_mgr.ib_all_size);
    return ib;
}

HOOK(GLuint, FASTCALL, create_vertex_buffer, 0x00000001404617B0, uint32_t size, const void* buf) {
    GL::BufferUsage usage = (GL::BufferUsage)(size >> 30);
    size &= (1u << 30) - 1u;

    GLuint vb = 0;
    glGenBuffers(1, &vb);
    gl_state.bind_array_buffer(vb);
    if (DIVA_GL_VERSION_4_4 && usage != GL::BUFFER_USAGE_STREAM) {
        GLbitfield flags = usage == GL::BUFFER_USAGE_DYNAMIC
            ? GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT : 0;
        glBufferStorage(GL_ARRAY_BUFFER, size, buf, flags);
    }
    else
        glBufferData(GL_ARRAY_BUFFER, size, buf, GL::BufferUsageToGLenum(usage));
    gl_state.bind_array_buffer(0);

    if (glGetErrorDLL()) {
        glDeleteBuffers(1, &vb);
        return 0;
    }

    bufobj_mgr.vb_all_size += size;
    bufobj_mgr.vb_peak_size = max_def(bufobj_mgr.vb_peak_size, bufobj_mgr.vb_all_size);
    return vb;
}

HOOK(void, FASTCALL, VertexBuffer__destroy, 0x0000000140461870, VertexBufferDivaGL* This) {
    This->destroy();
}

HOOK(uint32_t, FASTCALL, VertexBuffer__get_size, 0x00000000140461A50, VertexBufferDivaGL* This) {
    GLuint buffer;
    uint32_t size;
    if (This->vb[0]) {
        glGetIntegervDLL(GL_ARRAY_BUFFER_BINDING, (GLint*)&buffer);
        glBindBuffer(This->target, This->vb[0]);
        glGetBufferParameteriv(This->target, GL_BUFFER_SIZE, (GLint*)&size);
        glBindBufferARB(This->target, buffer);
        return size;
    }
    return 0;
}

HOOK(void, FASTCALL, free_index_buffer, 0x0000000140461900, GLuint ib) {
    if (!ib)
        return;

    disp_manager->remove_index_buffer(ib);

    GLint size = 0;
    if (DIVA_GL_VERSION_4_5)
        glGetNamedBufferParameteriv(ib, GL_BUFFER_SIZE, &size);
    else {
        gl_state.bind_element_array_buffer(ib);
        glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
        gl_state.bind_element_array_buffer(0);
    }

    bufobj_mgr.ib_all_size -= size;

    glDeleteBuffers(1, &ib);
    glGetErrorDLL();
}

HOOK(void, FASTCALL, free_vertex_buffer, 0x0000000140461990, GLuint vb) {
    if (!vb)
        return;

    disp_manager->remove_vertex_buffer(vb);

    GLint size = 0;
    if (DIVA_GL_VERSION_4_5)
        glGetNamedBufferParameteriv(vb, GL_BUFFER_SIZE, &size);
    else {
        gl_state.bind_array_buffer(vb);
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
        gl_state.bind_array_buffer(0);
    }

    bufobj_mgr.vb_all_size -= size;

    glDeleteBuffers(1, &vb);
    glGetErrorDLL();
}

void object_patch() {
#if SHARED_OBJECT_BUFFER
    WRITE_MEMORY(0x000000014045A4E7, uint8_t, sizeof(ObjVB));
#endif

    INSTALL_HOOK(create_mesh_vertex_buffer);
    INSTALL_HOOK(create_objset_aabb);
    INSTALL_HOOK(create_objset_index_buffer);
    INSTALL_HOOK(create_objset_vertex_buffer);
    INSTALL_HOOK(free_objset_index_buffer);
    INSTALL_HOOK(free_objset_vertex_buffer);
    INSTALL_HOOK(get_object_index_buffer);
    INSTALL_HOOK(get_object_vertex_buffer);
    INSTALL_HOOK(obj_set_parse_file);
    INSTALL_HOOK(wait_objset);
    INSTALL_HOOK(create_index_buffer);
    INSTALL_HOOK(create_vertex_buffer);
    INSTALL_HOOK(VertexBuffer__destroy);
    INSTALL_HOOK(VertexBuffer__get_size);
    INSTALL_HOOK(free_index_buffer);
    INSTALL_HOOK(free_vertex_buffer);
}

// Added
static int32_t align_val_32(int32_t value) {
    return value + (32 - value % 32) % 32;
}

#if SHARED_OBJECT_BUFFER
// Added
inline static void calc_index_buffer(obj_sub_mesh& sub_mesh, int32_t& size) {
    if (sub_mesh.index_format == OBJ_INDEX_U16) {
        int32_t _size = sizeof(uint16_t) * sub_mesh.num_index;
        size += align_val_32(_size);
    }
}

// Added
inline static void calc_mesh_index_buffer(obj_mesh& mesh, int32_t& size) {
    for (int32_t i = 0; i < mesh.num_submesh; i++)
        calc_index_buffer(mesh.submesh_array[i], size);
}

// Added
inline static int32_t calc_mesh_vertex_buffer(obj_mesh& mesh) {
    uint32_t vertex_size = get_vertex_size(mesh.vertex_format);
    return mesh.num_vertex * vertex_size;
}

// Added
inline static void calc_object_index_buffer(obj* obj, int32_t& size) {
    for (int32_t i = 0; i < obj->num_mesh; i++)
        calc_mesh_index_buffer(obj->mesh_array[i], size);
}

// Added
inline static void calc_object_vertex_buffer(obj* obj, int32_t& size) {
    for (int32_t i = 0; i < obj->num_mesh; i++) {
        int32_t _size = calc_mesh_vertex_buffer(obj->mesh_array[i]);
        size += align_val_32(_size);
    }
}
#endif

// 0x140458040
static bool create_mesh_index_buffer_divagl(IndexBufferDivaGL* ibhn, obj_mesh* mesh) {
    uint32_t size = 0;
    for (int32_t i = 0; i < mesh->num_submesh; i++) {
        obj_sub_mesh& sub_mesh = mesh->submesh_array[i];
        if (sub_mesh.index_format == OBJ_INDEX_U16)
            size += align_val_32((int32_t)(sizeof(uint16_t) * sub_mesh.num_index));
    }

    if (!size) {
        ibhn->ib = 0;
        return true;
    }

    void* buf = force_malloc(size);
    int32_t offset = 0;
    fill_mesh_index_buffer(buf, mesh, offset);

    ibhn->create(offset, buf);
    free_def(buf);
    return true;
}

// 0x140458280
static bool create_mesh_vertex_buffer_divagl(VertexBufferDivaGL* vbhn, obj_mesh* mesh, GL::BufferUsage usage) {
    if (!mesh->num_vertex || !mesh->vertex_array.position)
        return false;

    uint32_t size_vertex = get_vertex_size(mesh->vertex_format, mesh->attrib.m.compression);
    void* buf = prj::MemoryManager::alloc(prj::MemCTemp, (size_t)size_vertex * mesh->num_vertex, "TMP_VTXBUF");
    fill_mesh_vertex_buffer(buf, mesh);
    mesh->size_vertex = size_vertex;

    bool ret = vbhn->create((size_t)size_vertex * mesh->num_vertex,
        buf, mesh->attrib.m.soft_body ? 2 : 1, usage);
    prj::MemoryManager::free(prj::MemCTemp, buf);
    return ret;
}

#if SHARED_OBJECT_BUFFER
// Added
inline static void create_mesh_vertex_buffer_divagl(VertexBufferDivaGL* vbhn,
    obj_mesh* mesh, GLuint in_vb, uint32_t& offset) {
    if (!mesh->num_vertex || !mesh->vertex_array.position)
        return;

    uint32_t size_vertex = get_vertex_size(mesh->vertex_format, mesh->attrib.m.compression);
    mesh->size_vertex = size_vertex;

    uint32_t size = size_vertex * mesh->num_vertex;
    vbhn->create(in_vb, size, offset);
    offset += align_val_32(size);
}
#endif

// 0x1404586E0
static bool create_object_index_buffer(ObjIB* objib, obj* obj) {
    if (!obj)
        return false;

    objib->num_ib = obj->num_mesh;
    objib->ibhn_array = prj::MemoryManager::alloc<IndexBufferDivaGL>(prj::MemCSystem, obj->num_mesh, "MESHIB");
    if (!objib->ibhn_array)
        return false;

    for (int32_t i = 0; i < objib->num_ib; i++)
        if (!create_mesh_index_buffer_divagl(&objib->ibhn_array[i], &obj->mesh_array[i]))
            return false;
    return true;
}

// 0x140458790
static bool create_object_vertex_buffer(ObjVB* objvb, obj* obj) {
    if (!obj)
        return false;

    objvb->num_vb = obj->num_mesh;
    objvb->vbhn_array = new VertexBufferDivaGL[obj->num_mesh];
    if (!objvb->vbhn_array)
        return false;

    for (int32_t i = 0; i < objvb->num_vb; i++)
        if (!create_mesh_vertex_buffer_divagl(&objvb->vbhn_array[i], &obj->mesh_array[i]))
            return false;
    return true;
}

#if SHARED_OBJECT_BUFFER
// Added
inline static bool create_object_vertex_buffer(ObjVB* objvb, obj* obj, GLuint in_vb, uint32_t& offset) {
    if (!obj)
        return false;

    objvb->num_vb = obj->num_mesh;
    objvb->vbhn_array = new VertexBufferDivaGL[obj->num_mesh];
    if (!objvb->vbhn_array)
        return false;

    for (int32_t i = 0; i < obj->num_mesh; i++)
        create_mesh_vertex_buffer_divagl(&objvb->vbhn_array[i], &obj->mesh_array[i], in_vb, offset);
    return true;
}
#endif

// Added
inline static void fill_index_buffer(void* buf, obj_sub_mesh& sub_mesh, int32_t& offset) {
    sub_mesh.min_index = 0;
    sub_mesh.max_index = 0;
    sub_mesh.index_offset = 0;
    if (sub_mesh.index_format != OBJ_INDEX_U16)
        return;

    const uint16_t* index = (uint16_t*)sub_mesh.index_array;
    uint16_t* indices = (uint16_t*)buf;
    for (int32_t j = sub_mesh.num_index; j > 0; j--, index++)
        *indices++ = *index;

    uint16_t min_index = 0xFFFF;
    uint16_t max_index = 0;
    indices = (uint16_t*)buf;
    for (int32_t j = sub_mesh.num_index; j > 0; j--) {
        uint16_t index = *indices++;
        if (index == 0xFFFF)
            continue;

        if (min_index > index)
            min_index = index;
        if (max_index < index)
            max_index = index;
    }

    sub_mesh.min_index = min_index;
    sub_mesh.max_index = max_index;
    sub_mesh.index_offset = offset;

    int32_t size = sizeof(uint16_t) * sub_mesh.num_index;
    offset += align_val_32(size);
}

// Added
static void fill_mesh_index_buffer(void* buf, obj_mesh* mesh, int32_t& offset) {
    for (int32_t i = 0; i < mesh->num_submesh; i++)
        fill_index_buffer((uint8_t*)buf + offset, mesh->submesh_array[i], offset);
}

// Added
static int32_t fill_mesh_vertex_buffer(void* buf, obj_mesh* mesh) {
    uint32_t size_vertex = get_vertex_size(mesh->vertex_format, mesh->attrib.m.compression);
    obj_vertex_format vertex_format = mesh->vertex_format;
    obj_mesh_vertex_array vtx = mesh->vertex_array;
    int32_t num_vertex = mesh->num_vertex;
    size_t d = (size_t)buf;
    switch (mesh->attrib.m.compression) {
    case 0:
    default:
        if (vertex_format & OBJ_VERTEX_POSITION) {
            vec3* position = vtx.position;
            for (int32_t i = num_vertex; i > 0; i--) {
                *(vec3*)d = *position++;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 12;
        }

        if (vertex_format & OBJ_VERTEX_NORMAL) {
            vec3* normal = vtx.normal;
            for (int32_t i = num_vertex; i > 0; i--) {
                *(vec3*)d = *normal++;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 12;
        }

        if (vertex_format & OBJ_VERTEX_TANGENT) {
            vec4* tangent = vtx.tangent;
            for (int32_t i = num_vertex; i > 0; i--) {
                *(vec4*)d = *tangent++;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 16;
        }

        if (vertex_format & OBJ_VERTEX_BINORMAL) {
            vec3* binormal = vtx.binormal;
            for (int32_t i = num_vertex; i > 0; i--) {
                *(vec3*)d = *binormal++;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 12;
        }

        if (vertex_format & OBJ_VERTEX_TEXCOORD0) {
            vec2* texcoord0 = vtx.texcoord0;
            for (int32_t i = num_vertex; i > 0; i--) {
                *(vec2*)d = *texcoord0++;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 8;
        }

        if (vertex_format & OBJ_VERTEX_TEXCOORD1) {
            vec2* texcoord1 = vtx.texcoord1;
            for (int32_t i = num_vertex; i > 0; i--) {
                *(vec2*)d = *texcoord1++;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 8;
        }

        if (vertex_format & OBJ_VERTEX_TEXCOORD2) {
            vec2* texcoord2 = vtx.texcoord2;
            for (int32_t i = num_vertex; i > 0; i--) {
                *(vec2*)d = *texcoord2++;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 8;
        }

        if (vertex_format & OBJ_VERTEX_TEXCOORD3) {
            vec2* texcoord3 = vtx.texcoord3;
            for (int32_t i = num_vertex; i > 0; i--) {
                *(vec2*)d = *texcoord3++;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 8;
        }

        if (vertex_format & OBJ_VERTEX_COLOR0) {
            vec4* color0 = vtx.color0;
            for (int32_t i = num_vertex; i > 0; i--) {
                *(vec4*)d = *color0++;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 16;
        }

        if (vertex_format & OBJ_VERTEX_COLOR1) {
            vec4* color1 = vtx.color1;
            for (int32_t i = num_vertex; i > 0; i--) {
                *(vec4*)d = *color1++;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 16;
        }

        if ((vertex_format & OBJ_VERTEX_BONE_DATA) == OBJ_VERTEX_BONE_DATA) {
            vec4* bone_weight = vtx.bone_weight;
            vec4* bone_index = vtx.bone_index;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec4 _bone_weight = *bone_weight++;

                int32_t bone_index_x = (int32_t)bone_index->x;
                int32_t bone_index_y = (int32_t)bone_index->y;
                int32_t bone_index_z = (int32_t)bone_index->z;
                int32_t bone_index_w = (int32_t)bone_index->w;
                bone_index++;

                vec4i16 _bone_index;
                _bone_index.x = (int16_t)(bone_index_x >= 0 ? bone_index_x / 3 : -1);
                _bone_index.y = (int16_t)(bone_index_y >= 0 ? bone_index_y / 3 : -1);
                _bone_index.z = (int16_t)(bone_index_z >= 0 ? bone_index_z / 3 : -1);
                _bone_index.w = (int16_t)(bone_index_w >= 0 ? bone_index_w / 3 : -1);
                obj_vertex_validate_bone_data(_bone_weight, _bone_index);

                *(vec4*)d = _bone_weight;
                *(vec4i16*)(d + 16) = _bone_index;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 24;
        }

        if (vertex_format & OBJ_VERTEX_UNKNOWN) {
            vec4* unknown = vtx.unknown;
            for (int32_t i = num_vertex; i > 0; i--) {
                *(vec4*)d = *unknown++;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 16;
        }
        break;
    case 1:
        if (vertex_format & OBJ_VERTEX_POSITION) {
            vec3* position = vtx.position;
            for (int32_t i = num_vertex; i > 0; i--) {
                *(vec3*)d = *position++;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 12;
        }

        if (vertex_format & OBJ_VERTEX_NORMAL) {
            vec3* normal = vtx.normal;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec3_to_vec3i16(*normal++ * 32767.0f, *(vec3i16*)d);
                *(int16_t*)(d + 6) = 0;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 8;
        }

        if (vertex_format & OBJ_VERTEX_TANGENT) {
            vec4* tangent = vtx.tangent;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec4_to_vec4i16(*tangent++ * 32767.0f, *(vec4i16*)d);
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 8;
        }

        if (vertex_format & OBJ_VERTEX_TEXCOORD0) {
            vec2* texcoord0 = vtx.texcoord0;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec2_to_vec2h(*texcoord0++, *(vec2h*)d);
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 4;
        }

        if (vertex_format & OBJ_VERTEX_TEXCOORD1) {
            vec2* texcoord1 = vtx.texcoord1;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec2_to_vec2h(*texcoord1++, *(vec2h*)d);
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 4;
        }

        if (vertex_format & OBJ_VERTEX_TEXCOORD2) {
            vec2* texcoord2 = vtx.texcoord2;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec2_to_vec2h(*texcoord2++, *(vec2h*)d);
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 4;
        }

        if (vertex_format & OBJ_VERTEX_TEXCOORD3) {
            vec2* texcoord3 = vtx.texcoord3;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec2_to_vec2h(*texcoord3++, *(vec2h*)d);
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 4;
        }

        if (vertex_format & OBJ_VERTEX_COLOR0) {
            vec4* color0 = vtx.color0;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec4_to_vec4h(*color0++, *(vec4h*)d);
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 8;
        }

        if ((vertex_format & OBJ_VERTEX_BONE_DATA) == OBJ_VERTEX_BONE_DATA) {
            vec4* bone_weight = vtx.bone_weight;
            vec4* bone_index = vtx.bone_index;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec4 _bone_weight = *bone_weight++;

                int32_t bone_index_x = (int32_t)bone_index->x;
                int32_t bone_index_y = (int32_t)bone_index->y;
                int32_t bone_index_z = (int32_t)bone_index->z;
                int32_t bone_index_w = (int32_t)bone_index->w;
                bone_index++;

                vec4i16 _bone_index;
                _bone_index.x = (int16_t)(bone_index_x >= 0 ? bone_index_x / 3 : -1);
                _bone_index.y = (int16_t)(bone_index_y >= 0 ? bone_index_y / 3 : -1);
                _bone_index.z = (int16_t)(bone_index_z >= 0 ? bone_index_z / 3 : -1);
                _bone_index.w = (int16_t)(bone_index_w >= 0 ? bone_index_w / 3 : -1);
                obj_vertex_validate_bone_data(_bone_weight, _bone_index);

                vec4_to_vec4u16(_bone_weight * 65535.0f, *(vec4u16*)d);
                *(vec4i16*)(d + 16) = _bone_index;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 16;
        }
        break;
    case 2:
        if (vertex_format & OBJ_VERTEX_POSITION) {
            vec3* position = vtx.position;
            for (int32_t i = num_vertex; i > 0; i--) {
                *(vec3*)d = *position++;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 12;
        }

        if (vertex_format & OBJ_VERTEX_NORMAL) {
            vec3* normal = vtx.normal;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec3i16 normal_int;
                vec3_to_vec3i16(*normal++ * 511.0f, normal_int);
                *(uint32_t*)d = (((uint32_t)0 & 0x03) << 30)
                    | (((uint32_t)normal_int.z & 0x3FF) << 20)
                    | (((uint32_t)normal_int.y & 0x3FF) << 10)
                    | ((uint32_t)normal_int.x & 0x3FF);
                *(int16_t*)(d + 6) = 0;
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 4;
        }

        if (vertex_format & OBJ_VERTEX_TANGENT) {
            vec4* tangent = vtx.tangent;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec4i16 tangent_int;
                vec4_to_vec4i16(*tangent++ * 511.0f, tangent_int);
                *(uint32_t*)d = (((uint32_t)clamp_def(tangent_int.w, -1, 1) & 0x03) << 30)
                    | (((uint32_t)tangent_int.z & 0x3FF) << 20)
                    | (((uint32_t)tangent_int.y & 0x3FF) << 10)
                    | ((uint32_t)tangent_int.x & 0x3FF);
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 4;
        }

        if (vertex_format & OBJ_VERTEX_TEXCOORD0) {
            vec2* texcoord0 = vtx.texcoord0;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec2_to_vec2h(*texcoord0++, *(vec2h*)d);
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 4;
        }

        if (vertex_format & OBJ_VERTEX_TEXCOORD1) {
            vec2* texcoord1 = vtx.texcoord1;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec2_to_vec2h(*texcoord1++, *(vec2h*)d);
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 4;
        }

        if (vertex_format & OBJ_VERTEX_TEXCOORD2) {
            vec2* texcoord2 = vtx.texcoord2;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec2_to_vec2h(*texcoord2++, *(vec2h*)d);
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 4;
        }

        if (vertex_format & OBJ_VERTEX_TEXCOORD3) {
            vec2* texcoord3 = vtx.texcoord3;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec2_to_vec2h(*texcoord3++, *(vec2h*)d);
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 4;
        }

        if (vertex_format & OBJ_VERTEX_COLOR0) {
            vec4* color0 = vtx.color0;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec4_to_vec4h(*color0++, *(vec4h*)d);
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 8;
        }

        if ((vertex_format & OBJ_VERTEX_BONE_DATA) == OBJ_VERTEX_BONE_DATA) {
            vec4* bone_weight = vtx.bone_weight;
            vec4* bone_index = vtx.bone_index;
            for (int32_t i = num_vertex; i > 0; i--) {
                vec4 _bone_weight = *bone_weight++;

                int32_t bone_index_x = (int32_t)bone_index->x;
                int32_t bone_index_y = (int32_t)bone_index->y;
                int32_t bone_index_z = (int32_t)bone_index->z;
                int32_t bone_index_w = (int32_t)bone_index->w;
                bone_index++;

                vec4i16 _bone_index;
                _bone_index.x = (int16_t)(bone_index_x >= 0 ? bone_index_x / 3 : -1);
                _bone_index.y = (int16_t)(bone_index_y >= 0 ? bone_index_y / 3 : -1);
                _bone_index.z = (int16_t)(bone_index_z >= 0 ? bone_index_z / 3 : -1);
                _bone_index.w = (int16_t)(bone_index_w >= 0 ? bone_index_w / 3 : -1);
                obj_vertex_validate_bone_data(_bone_weight, _bone_index);

                vec4i16 bone_weight_int;
                vec4_to_vec4i16(_bone_weight * 1023.0f, bone_weight_int);
                *(uint32_t*)d = (((uint32_t)0 & 0x03) << 30)
                    | (((uint32_t)bone_weight_int.z & 0x3FF) << 20)
                    | (((uint32_t)bone_weight_int.y & 0x3FF) << 10)
                    | ((uint32_t)bone_weight_int.x & 0x3FF);

                vec4i bone_index;
                vec4i16_to_vec4i(_bone_index, bone_index);
                vec4i_to_vec4u8(bone_index, *(vec4u8*)(d + 4));
                d += size_vertex;
            }
            d -= (size_t)size_vertex * num_vertex;
            d += 8;
        }
        break;
    }
    return size_vertex * num_vertex;
}

#if SHARED_OBJECT_BUFFER
// Added
inline static void fill_object_index_buffer(void* buf, obj* obj, int32_t& offset) {
    for (int32_t i = 0; i < obj->num_mesh; i++)
        fill_mesh_index_buffer(buf, &obj->mesh_array[i], offset);
}

// Added
inline static void fill_object_vertex_buffer(void* buf, obj* obj, int32_t& offset) {
    for (int32_t i = 0; i < obj->num_mesh; i++) {
        int32_t size = fill_mesh_vertex_buffer((uint8_t*)buf + offset, &obj->mesh_array[i]);
        offset += align_val_32(size);
    }
}
#endif

// Inlined
inline static void free_object_index_buffer(ObjIB* objib) {
    if (objib->ibhn_array) {
#if SHARED_OBJECT_BUFFER
        for (int32_t i = 0; i < objib->num_ib; i++)
            objib->ibhn_array[i].destroy_shared();
#else
        for (int32_t i = 0; i < objib->num_ib; i++)
            objib->ibhn_array[i].destroy();
#endif
        prj::MemoryManager::free(prj::MemCSystem, objib->ibhn_array);
    }
    objib->ibhn_array = 0;
    objib->num_ib = 0;
}

// Inlined
inline static void free_object_vertex_buffer(ObjVB* objvb) {
    if (objvb->vbhn_array) {
#if SHARED_OBJECT_BUFFER
        for (int32_t i = 0; i < objvb->num_vb; i++)
            objvb->vbhn_array[i].destroy_shared();
#else
        for (int32_t i = 0; i < num_vb; i++)
            vbhn_array[i].destroy();
#endif
        delete[] objvb->vbhn_array;
    }
    objvb->vbhn_array = 0;
    objvb->num_vb = 0;
}

// Added
static void load_objset_vertex_array(ObjsetInfo* info) {
    obj_set* set = info->objdata_header;
    ObjVB* vbhn_array = info->objvb;
    ObjIB* ibhn_array = info->objib;
    for (int32_t i = 0; i < set->obj_num; i++) {
        obj* obj = set->obj_data[i];

#if SHARED_OBJECT_BUFFER
        bool soft_body = false;
        for (int32_t i = 0; i < obj->num_mesh; i++) {
            obj_mesh& mesh = obj->mesh_array[i];
            if (!mesh.num_vertex || !mesh.vertex_array.position)
                continue;

            soft_body |= !!mesh.attrib.m.soft_body;
        }

        int32_t num_flip = soft_body ? 2 : 1;
#endif

        for (int32_t j = 0; j < obj->num_mesh; j++) {
            obj_mesh* mesh = &obj->mesh_array[j];
            if (!mesh->num_vertex || !mesh->vertex_array.position)
                continue;

            for (int32_t k = 0; k < mesh->num_submesh; k++) {
                obj_sub_mesh* sub_mesh = &mesh->submesh_array[k];
                if (sub_mesh->attrib.m.hide)
                    continue;

                obj_material_data* material = &obj->material_array[sub_mesh->material_index];

#if !SHARED_OBJECT_BUFFER
                int32_t num_flip = mesh->attrib.m.soft_body ? 2 : 1;
#endif
                for (int32_t l = 0; l < num_flip; l++) {
                    GLuint vb = 0;
                    size_t vb_offset = 0;
                    if (vbhn_array && vbhn_array[i].vbhn_array) {
                        vb = vbhn_array[i].vbhn_array[j].get_glvb();
                        vb_offset = vbhn_array[i].vbhn_array[j].get_glvb_offset();
                    }

                    GLuint ib = 0;
                    if (ibhn_array && ibhn_array[i].ibhn_array)
                        ib = ibhn_array[i].ibhn_array[j].get_glib();

                    disp_manager->add_vertex_array(mesh, sub_mesh, material,
                        vb, vb_offset, ib, 0, 0);

                    if (vbhn_array && vbhn_array[i].vbhn_array)
                        vbhn_array[i].vbhn_array[j].flip();
                }
            }
        }
    }
}

// Added
static void obj_vertex_add_bone_weight(vec4& bone_weight, vec4i16& bone_index, int16_t index, float_t weight) {
    if (bone_index.x < 0) {
        bone_index.x = index;
        bone_weight.x = weight;
    }
    else if (bone_index.y < 0) {
        bone_index.y = index;
        bone_weight.y = weight;
    }
    else if (bone_index.z < 0) {
        bone_index.z = index;
        bone_weight.z = weight;
    }
    else if (bone_index.w < 0) {
        bone_index.w = index;
        bone_weight.w = weight;
    }
}

// Added
static void obj_vertex_validate_bone_data(vec4& bone_weight, vec4i16& bone_index) {
    vec4 _bone_weight = { 0.0f, 0.0f, 0.0f, 0.0f };
    vec4i16 _bone_index = { -1, -1, -1, -1 };

    if (bone_index.x >= 0 && bone_weight.x > 0.0f)
        obj_vertex_add_bone_weight(_bone_weight, _bone_index, bone_index.x, bone_weight.x);

    if (bone_index.y >= 0 && bone_weight.y > 0.0f)
        obj_vertex_add_bone_weight(_bone_weight, _bone_index, bone_index.y, bone_weight.y);

    if (bone_index.z >= 0 && bone_weight.z > 0.0f)
        obj_vertex_add_bone_weight(_bone_weight, _bone_index, bone_index.z, bone_weight.z);

    if (bone_index.w >= 0 && bone_weight.w > 0.0f)
        obj_vertex_add_bone_weight(_bone_weight, _bone_index, bone_index.w, bone_weight.w);

    float_t sum = _bone_weight.x + _bone_weight.y + _bone_weight.z + _bone_weight.w;
    if (sum > 0.0f && fabsf(sum - 1.0f) > 0.000001f)
        _bone_weight *= 1.0f / sum;

    bone_weight = _bone_weight;
    bone_index = _bone_index;
}
