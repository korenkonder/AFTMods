/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#define _CRT_SECURE_NO_WARNINGS
#include "rob.hpp"
#include "../../KKdLib/io/path.hpp"
#include "../../KKdLib/prj/algorithm.hpp"
#include "../../KKdLib/prj/rijndael.hpp"
#include "../../KKdLib/deflate.hpp"
#include "../../KKdLib/hash.hpp"
#include "../../AFTModsShared/rob/rob.hpp"
#include "../../AFTModsShared/file_handler.hpp"
#include "../../AFTModsShared/task.hpp"
#include "../../AFTModsShared/types.hpp"
#include <Helpers.h>
#include <random>

struct pv_data_set_motion {
    uint32_t motion_id;
    prj::pair<float_t, int32_t> frame_stage_index;

    pv_data_set_motion();
    pv_data_set_motion(uint32_t motion_id);
    pv_data_set_motion(uint32_t motion_id, prj::pair<float_t, int32_t> frame_stage_index);
};

static_assert(sizeof(pv_data_set_motion) == 0x0C, "\"pv_data_set_motion\" struct should have a size of 0x0C");

struct osage_play_data_header {
    uint32_t signature;
    prj::pair<uint16_t, uint16_t> obj_info;
    uint32_t motion_id;
    uint32_t frame_count;
    uint16_t nodes_count;

    osage_play_data_header();
};

static_assert(sizeof(osage_play_data_header) == 0x14, "\"osage_play_data_header\" struct should have a size of 0x14");

struct osage_play_data_node_header {
    uint16_t count;
    int16_t shift;
#pragma warning(suppress: 4200)
    int16_t data[];
};

static_assert(sizeof(osage_play_data_node_header) == 0x04, "\"osage_play_data_node_header\" struct should have a size of 0x04");

struct opd_file_data {
    osage_play_data_header head;
    float_t* data;
    int32_t load_count;

    opd_file_data();
};

static_assert(sizeof(opd_file_data) == 0x28, "\"opd_file_data\" struct should have a size of 0x28");

struct opd_vec3_data_vec {
    prj::vector<float_t> x;
    prj::vector<float_t> y;
    prj::vector<float_t> z;

    opd_vec3_data_vec();
    ~opd_vec3_data_vec();
};

static_assert(sizeof(opd_vec3_data_vec) == 0x48, "\"opd_vec3_data_vec\" struct should have a size of 0x48");

struct p_farc_write {
    struct farc_write* ptr;
};

static_assert(sizeof(p_farc_write) == 0x08, "\"p_farc_write\" struct should have a size of 0x08");

struct opd_chara_data {
    int32_t chara_id;
    bool init;
    uint32_t frame_index;
    uint32_t frame_count;
    uint32_t motion_id;
    uint64_t field_18;
    prj::vector<prj::vector<opd_vec3_data_vec>> opd_data[ITEM_OSAGE_COUNT];
    p_farc_write opd[ITEM_OSAGE_COUNT];
    p_farc_write opdi[ITEM_OSAGE_COUNT];
};

static_assert(sizeof(opd_chara_data) == 0x2A0, "\"opd_chara_data\" struct should have a size of 0x2A0");

class OsagePlayDataManager : public app::Task {
public:
    int32_t state;
    prj::vector<prj::pair<object_info, int32_t>> req_data;
    prj::list<p_file_handler*> file_handlers;
    prj::map<prj::pair<object_info, uint32_t>, opd_file_data> file_data;

    void LoadOpdFileList();
};

static_assert(sizeof(OsagePlayDataManager) == 0xA8, "\"OsagePlayDataManager\" struct should have a size of 0xA8");

struct rob_osage_mothead_data {
    bool init;
    mothead_data_type type;
    const mothead_data* data;

    rob_osage_mothead_data(mothead_data_type type, uint32_t motion_id);
    ~rob_osage_mothead_data();

    const mothead_data* find_next_data();
};

static_assert(sizeof(rob_osage_mothead_data) == 0x10, "\"rob_osage_mothead_data\" struct should have a size of 0x10");

struct rob_osage_mothead {
    rob_chara* rob_chr;
    uint32_t motion_id;
    float_t frame;
    float_t last_frame;
    rob_osage_mothead_data* rob_parts_adjust;
    const mothead_data* rob_parts_adjust_data;
    rob_osage_mothead_data* rob_adjust_global;
    const mothead_data* rob_adjust_global_data;
    rob_osage_mothead_data* sleeve_adjust;
    const mothead_data* sleeve_adjust_data;
    rob_osage_mothead_data* disable_collision;
    const mothead_data* disable_collision_data;
    rob_osage_mothead_data* rob_chara_coli_ring;
    const mothead_data* rob_chara_coli_ring_data;
    int32_t field_68;

    rob_osage_mothead(rob_chara* rob_chr, int32_t stage_index,
        uint32_t motion_id, float_t frame);
    rob_osage_mothead(rob_chara* rob_chr, int32_t stage_index,
        uint32_t motion_id, float_t frame, bool set_motion_reset_data); // Added
    ~rob_osage_mothead();

    void ctrl();
    void init_data();
    void reset();
    void reset_data();
    void set_coli_ring(const mothead_data* mhd_data);
    void set_frame(float_t value);
    void set_disable_collision(const mothead_data* mhd_data);
    void set_mothead_frame();
    void set_rob_adjust_global(const mothead_data* mhd_data);
    void set_rob_parts_adjust(const mothead_data* mhd_data);
    void set_sleeve_adjust(const mothead_data* mhd_data);
};

static_assert(sizeof(rob_osage_mothead) == 0x70, "\"rob_osage_mothead\" struct should have a size of 0x70");

struct buf_data {
    uint8_t* data;
    size_t len;
    size_t size;
};

struct OpdPlayGen {
    struct Cache {
        struct EntryFile {
            object_info obj_info;
            uint32_t motion_id;

            size_t offset;
            uint32_t size : 31;
            uint32_t compressed : 1;
            uint32_t original_size : 31;
            uint32_t encrypted : 1;
            uint8_t key[prj::Rijndael_Nk256 * prj::Rijndael_Nb];
            uint64_t hash;

            EntryFile();

            void reset();
        };

        struct FreeRanges;

        struct Entry {
            EntryFile file_data;

            prj::vector<uint8_t> data;

            Entry();
            ~Entry();

            bool read(const char* path);
            bool write(const char* path, std::mt19937& mt_rand, FreeRanges* free_ranges);
        };

        struct FreeRanges {
            prj::vector<prj::pair<size_t, size_t>> data;

            FreeRanges();
            ~FreeRanges();

            void claim_range(size_t index, size_t req_size);
            size_t find_free_range(size_t req_size, size_t& offset);

            static void find_free_ranges(const char* path, const prj::vector<Entry>& entries,
                prj::vector_pair<object_info, OpdPlayGen::Cache::FreeRanges>& obj_free_ranges);
        };

        ::chara_index chara_index;
        bool write_data;
        prj::vector<Entry> entries;
        prj::vector_pair<prj::pair<object_info, uint32_t>, size_t> sorted_entries;

        Cache();
        ~Cache();

        Entry* add(object_info obj_info, uint32_t motion_id);
        Entry* find(object_info obj_info, uint32_t motion_id);
        void read(::chara_index chara_index, const char* path);
        void reset();
        void write(const char* path);
    };

    struct Object {
        uint64_t file_hash;
        bool generate;

        Object();
        Object(uint64_t file_hash);
    };

    std::atomic_int32_t state;
    std::thread* thread;
    prj::map<uint32_t, prj::vector<prj::pair<object_info, Object>>> gen_data;
    prj::vector<pv_data_set_motion> set_motion[ROB_CHARA_COUNT];
    object_info obj_info[ROB_CHARA_COUNT][ITEM_OSAGE_COUNT];

    Cache cache;

    OpdPlayGen();
    ~OpdPlayGen();

    bool CheckState();
    void Ctrl();
    void Reset();

    static void ThreadMain(OpdPlayGen* opd_play);
};

bool operator==(const OpdPlayGen::Object& left, const OpdPlayGen::Object& right) {
    return left.file_hash == right.file_hash;
}

bool operator!=(const OpdPlayGen::Object& left, const OpdPlayGen::Object& right) {
    return left.file_hash != right.file_hash;
}

bool operator<(const OpdPlayGen::Object& left, const OpdPlayGen::Object& right) {
    return left.file_hash < right.file_hash;
}

bool operator>(const OpdPlayGen::Object& left, const OpdPlayGen::Object& right) {
    return left.file_hash > right.file_hash;
}

bool operator<=(const OpdPlayGen::Object& left, const OpdPlayGen::Object& right) {
    return left.file_hash <= right.file_hash;
}

bool operator>=(const OpdPlayGen::Object& left, const OpdPlayGen::Object& right) {
    return left.file_hash >= right.file_hash;
}

OsagePlayDataManager& osage_play_data_manager = *(OsagePlayDataManager*)0x00000001411A72F0;

static const char* (FASTCALL* motion_database_get_motion_name_by_motion_id)(int32_t id)
    = (const char* (FASTCALL*)(int32_t id))0x0000000140403830;
static const char* (FASTCALL* objset_info_storage_get_obj_name)(object_info obj_info)
    = (const char* (FASTCALL*)(object_info obj_info))0x000000014045A340;

static float_t(FASTCALL* rob_chara_bone_data_get_frame_count)(rob_chara_bone_data* rob_bone_data)
    = (float_t(FASTCALL*)(rob_chara_bone_data * rob_bone_data))0x0000000140419310;
static void (FASTCALL* rob_chara_adjust_ctrl)(rob_chara* rob_chr)
    = (void (FASTCALL*)(rob_chara * rob_chr))0x0000000140507AE0;
static void (FASTCALL* rob_chara_ctrl_rob_disp_thread_main)(rob_chara* rob_chr)
    = (void (FASTCALL*)(rob_chara * rob_chr))0x000000014054FF10;
static void (FASTCALL* rob_motion_modifier_rob_chara_ctrl)(rob_chara* rob_chr)
    = (void (FASTCALL*)(rob_chara * rob_chr))0x0000000014053ABF0;
static void (FASTCALL* rob_chara_set_motion_reset_data)(rob_chara* rob_chr,
    const uint32_t& motion_id, const float_t& frame)
    = (void (FASTCALL*)(rob_chara * rob_chr,
        const uint32_t & motion_id, const float_t & frame))0x00000001405504D0;
static void (FASTCALL* rob_chara_reset_osage)(rob_chara* rob_chr)
    = (void (FASTCALL*)(rob_chara * rob_chr))0x0000000140550CA0;
static void (FASTCALL* rob_chara_add_motion_reset_data)(rob_chara* rob_chr,
    const uint32_t& motion_id, const float_t& frame, int32_t iterations)
    = (void (FASTCALL*)(rob_chara * rob_chr,
        const uint32_t & motion_id, const float_t & frame, int32_t iterations))0x0000000140551F50;
static bool (FASTCALL* rob_chara_set_motion_id)(rob_chara* rob_chr, uint32_t motion_id, float_t frame,
    float_t blend_duration, bool blend, bool set_motion_reset_data, MotionBlendType blend_type)
    = (bool (FASTCALL*)(rob_chara * rob_chr, uint32_t motion_id, float_t frame, float_t blend_duration,
        bool blend, bool set_motion_reset_data, MotionBlendType blend_type))0x0000000140552340;
static void (FASTCALL* rob_chara_set_step_motion_step)(rob_chara* rob_chr, float_t step)
    = (void (FASTCALL*)(rob_chara * rob_chr, float_t step))0x0000000140554A50;
static void (FASTCALL* rob_chara_set_stage_data_ring)(rob_chara* rob_chr, const int32_t& stage_index)
    = (void (FASTCALL*)(rob_chara * rob_chr, const int32_t & stage_index))0x00000001405559D0;
static void (FASTCALL* rob_chara_set_motion_skin_param)(rob_chara* rob_chr,
    const uint32_t& motion_id, const float_t& frame)
    = (void (FASTCALL*)(rob_chara * rob_chr,
        const uint32_t & motion_id, const float_t & frame))0x0000000140555EF0;
static void (FASTCALL* rob_chara_set_bone_data_frame)(rob_chara* rob_chr, const float_t& frame)
    = (void (FASTCALL*)(rob_chara * rob_chr, const float_t & frame))0x0000000140556060;
static void (FASTCALL* rob_chara_item_equip_ctrl_iterate_nodes)(rob_chara_item_equip* rob_itm_eq, uint8_t iterations)
    = (void (FASTCALL*)(rob_chara_item_equip * rob_itm_eq, uint8_t iterations))0x00000001405135E0;

OpdPlayGen* opd_play_gen;
std::atomic_bool opd_play_gen_run;

bool opd_play_gen_use_cache;

static prj::string get_ram_osage_play_data_cache_dir();

static bool opd_cache_decrypt_data(const void* key, const buf_data& src, buf_data& dst);
static bool opd_cache_encrypt_data(const void* key, std::mt19937& mt_rand, const buf_data& src, buf_data& dst);

static size_t opd_cache_get_align(size_t size);
static bool opd_cache_write_data(const void* key, bool encrypt, std::mt19937& mt_rand,
    const void* data, size_t size, size_t& act_size, FILE* f, bool& encrypted);

HOOK(void, FASTCALL, RobCloth__CtrlOsagePlayData_mid1, 0x0000000140218F45);
HOOK(void, FASTCALL, RobCloth__CtrlOsagePlayData_mid2, 0x0000000140218FC4);
HOOK(void, FASTCALL, RobOsage__CtrlOsagePlayData_mid1, 0x000000014047E501);
HOOK(void, FASTCALL, RobOsage__CtrlOsagePlayData_mid2, 0x000000014047E56E);
HOOK(void, FASTCALL, rob_chara_item_equip__set_opd_blend_data_mid, 0x0000000140513CE9);

HOOK(void, FASTCALL, ExClothBlock__CtrlMain_mid, 0x00000001405F1F7D);
HOOK(void, FASTCALL, ExOsageBlock__CtrlMain_mid, 0x00000001405F21B7);
HOOK(void, FASTCALL, ExExpressionBlock__Calc_mid, 0x00000001405FA5E8);
HOOK(void, FASTCALL, ExOsageBlock__CtrlStep_mid, 0x00000001405F4A26);

HOOK(bool, FASTCALL, OsagePlayDataManager__ctrl, 0x00000001404881F0, OsagePlayDataManager* This) {
    bool ret = originalOsagePlayDataManager__ctrl(This);

    if (ret && opd_play_gen && !opd_play_gen->CheckState())
        return false;

    return ret;
}

HOOK(bool, FASTCALL, OsagePlayDataManager__dest, 0x0000000140488330, OsagePlayDataManager* This) {
    bool ret = originalOsagePlayDataManager__dest(This);
    if (ret && opd_play_gen) {
        delete opd_play_gen;
        opd_play_gen = 0;
    }
    return ret;
}

HOOK(void, FASTCALL, OsagePlayDataManager__GetOpdFileData, 0x00000001404894D0,
    OsagePlayDataManager* This, object_info obj_info, int32_t motion_id, const float_t*& data, uint32_t& count) {
    data = 0;
    count = 0;

    auto elem = This->file_data.find({ obj_info, motion_id });
    if (elem != This->file_data.end()) {
        data = elem->second.data;
        count = elem->second.head.frame_count;

        osage_play_data_header* head = &elem->second.head;
        if (*(uint16_t*)((uint8_t*)head + 0x12) & 0x01)
            count |= 0x80000000u;
    }
}

HOOK(void, FASTCALL, OsagePlayDataManager__Reset, 0x0000000140488B70, OsagePlayDataManager* This) {
    if (opd_play_gen)
        opd_play_gen->Reset();

    originalOsagePlayDataManager__Reset(This);
}

HOOK(void, FASTCALL, OsagePlayDataManager__LoadOpdFileList, 0x0000000140489640, OsagePlayDataManager* This) {
    This->LoadOpdFileList();
}

HOOK(void, FASTCALL, OsagePlayDataManager__LoadOpdFile, 0x0000000140489E10,
    OsagePlayDataManager* This, p_file_handler* pfhndl) {
    if (pfhndl->get_data() && pfhndl->get_size() == 0x14
        && *(uint32_t*)pfhndl->get_data() == 'OPDP') {
        if (!opd_play_gen)
            opd_play_gen = new OpdPlayGen;

        uint64_t file_hash = hash_fnv1a64m(pfhndl->ptr->file_path.data(), pfhndl->ptr->file_path.size());
        for (auto& i : opd_play_gen->gen_data)
            for (auto& j : i.second)
                if (j.second.file_hash == file_hash) {
                    j.second.generate = true;
                    opd_play_gen->state = 1;
                    return;
                }
        return;
    }

    originalOsagePlayDataManager__LoadOpdFile(This, pfhndl);
}

HOOK(void, FASTCALL, rob_chara_item_equip_object__load_opd_data, 0x00000001405F9640, rob_chara_item_equip_object* This) {
    if (!This->osage_blocks.size() && !This->cloth_blocks.size())
        return;

    static void(FASTCALL * osage_play_data_manager_get_opd_file_data)(uint32_t obj_info, int32_t motion_id, const float_t * &data, uint32_t & count)
        = (void(FASTCALL*)(uint32_t obj_info, int32_t motion_id, const float_t * &data, uint32_t & count))0x0000000140489480;
    static const float_t* (FASTCALL * ExOsageBlock__LoadOpdData)(ExOsageBlock * This, size_t node_index, const float_t * opd_data, size_t opd_count)
        = (const float_t * (FASTCALL*)(ExOsageBlock * This, size_t node_index, const float_t * opd_data, size_t opd_count))0x00000001405F9A40;
    static const float_t* (FASTCALL * ExClothBlock__LoadOpdData)(ExClothBlock * This, size_t node_index, const float_t * opd_data, size_t opd_count)
        = (const float_t * (FASTCALL*)(ExClothBlock * This, size_t node_index, const float_t * opd_data, size_t opd_count))0x00000001405F9A30;

    rob_chara_item_equip* rob_itm_equip = This->item_equip;
    size_t index = 0;
    for (opd_blend_data& i : rob_itm_equip->opd_blend_data) {
        const float_t* opd_data = 0;
        uint32_t opd_count = 0;

        osage_play_data_manager_get_opd_file_data(This->obj_info, i.motion_id, opd_data, opd_count);
        if (!opd_data)
            break;

        bool no_loop = opd_count & 0x80000000u;
        opd_count &= ~0x80000000u;

        (&i.use_blend)[1] = no_loop;

        for (ExOsageBlock*& j : This->osage_blocks)
            opd_data = ExOsageBlock__LoadOpdData(j, index, opd_data, opd_count);

        for (ExClothBlock*& j : This->cloth_blocks)
            opd_data = ExClothBlock__LoadOpdData(j, index, opd_data, opd_count);
        index++;
    }
}

void rob_patch() {
    // NOP get_delta_frame()
    WRITE_JUMP(0x00000001405F1F7D, 0x00000001405F1F82);
    WRITE_JUMP(0x00000001405F21B7, 0x00000001405F21BC);
    WRITE_JUMP(0x00000001405FA5E8, 0x00000001405FA5ED);
    WRITE_JUMP(0x00000001405F4A26, 0x00000001405F4A2B);

    // NOP to write DWORD instead of WORD
    WRITE_NOP_1(0x0000000140489E4A);

    INSTALL_HOOK(RobCloth__CtrlOsagePlayData_mid1);
    INSTALL_HOOK(RobCloth__CtrlOsagePlayData_mid2);
    INSTALL_HOOK(RobOsage__CtrlOsagePlayData_mid1);
    INSTALL_HOOK(RobOsage__CtrlOsagePlayData_mid2);
    INSTALL_HOOK(rob_chara_item_equip__set_opd_blend_data_mid);

    INSTALL_HOOK(ExClothBlock__CtrlMain_mid);
    INSTALL_HOOK(ExOsageBlock__CtrlMain_mid);
    INSTALL_HOOK(ExExpressionBlock__Calc_mid);
    INSTALL_HOOK(ExOsageBlock__CtrlStep_mid);

    INSTALL_HOOK(OsagePlayDataManager__ctrl);
    INSTALL_HOOK(OsagePlayDataManager__dest);
    INSTALL_HOOK(OsagePlayDataManager__GetOpdFileData);
    INSTALL_HOOK(OsagePlayDataManager__Reset);
    INSTALL_HOOK(OsagePlayDataManager__LoadOpdFileList);
    INSTALL_HOOK(OsagePlayDataManager__LoadOpdFile);

    // Remove addition of missing OPD on boot
    WRITE_NOP_4(0x0000000140471A69); // lea  rcx, [rsi+20h]
    WRITE_NOP_7(0x0000000140471A6D); // lea  rdx, [rbp+108h]
    WRITE_NOP_5(0x0000000140471A74); // call prj::vector<prj::string>::push_back at 0x00000001400C0A40
}

pv_data_set_motion::pv_data_set_motion() : frame_stage_index() {
    motion_id = -1;
}

pv_data_set_motion::pv_data_set_motion(uint32_t motion_id) : frame_stage_index() {
    this->motion_id = motion_id;
}

pv_data_set_motion::pv_data_set_motion(uint32_t motion_id, prj::pair<float_t, int32_t> frame_stage_index) {
    this->motion_id = motion_id;
    this->frame_stage_index = frame_stage_index;
}

constexpr bool operator==(const pv_data_set_motion& left, const pv_data_set_motion& right) {
    return left.motion_id == right.motion_id && left.frame_stage_index == right.frame_stage_index;
}

constexpr bool operator!=(const pv_data_set_motion& left, const pv_data_set_motion& right) {
    return !(left == right);
}

constexpr bool operator<(const pv_data_set_motion& left, const pv_data_set_motion& right) {
    return left.motion_id < right.motion_id || (!(right.motion_id < left.motion_id)
        && left.frame_stage_index < right.frame_stage_index);
}

constexpr bool operator>(const pv_data_set_motion& left, const pv_data_set_motion& right) {
    return right < left;
}

constexpr bool operator<=(const pv_data_set_motion& left, const pv_data_set_motion& right) {
    return !(right < left);
}

constexpr bool operator>=(const pv_data_set_motion& left, const pv_data_set_motion& right) {
    return !(left < right);
}

osage_play_data_header::osage_play_data_header() : frame_count(), nodes_count() {
    signature = 0x11033115;
    obj_info = { -1, -1 };
    motion_id = -1;
}

opd_file_data::opd_file_data() : data(), load_count() {

}

opd_vec3_data_vec::opd_vec3_data_vec() {

}

opd_vec3_data_vec::~opd_vec3_data_vec() {

}

void OsagePlayDataManager::LoadOpdFileList() {
    prj::vector_pair<uint32_t, prj::vector<prj::pair<object_info, OpdPlayGen::Object>>> req_data_mot;

    std::sort(req_data.begin(), req_data.end());
    req_data.erase(std::unique(req_data.begin(), req_data.end()), req_data.end());

    auto i_begin = req_data.begin();
    auto i_end = req_data.end();
    for (auto i = i_begin; i != i_end; ) {
        auto elem = file_data.find(*i);
        if (elem != file_data.end()) {
            elem->second.load_count++;

            i = req_data.erase(i);
            i_end = req_data.end();
            continue;
        }

        const char* object_name = objset_info_storage_get_obj_name(i->first);
        if (object_name) {
            std::string obj_name_buf = string_to_lower(std::string(object_name));

            const char* motion_name = motion_database_get_motion_name_by_motion_id(i->second);
            if (motion_name) {
                std::string mot_name_buf = string_to_lower(std::string(motion_name));

                std::string file_buf = sprintf_s_string("%s_%s.%s",
                    obj_name_buf.c_str(), mot_name_buf.c_str(), "opd");
                std::string _farc_buf = sprintf_s_string("%s.farc", obj_name_buf.c_str());
                prj::string farc_buf(_farc_buf.data(), _farc_buf.size());

                size_t idx = -1;
                for (auto& j : req_data_mot)
                    if (j.first == i->second) {
                        idx = &j - req_data_mot.data();
                        break;
                    }

                if (idx == -1) {
                    idx = req_data_mot.size();
                    req_data_mot.push_back(i->second, {});
                }

                req_data_mot.data()[idx].second.push_back({ i->first, hash_string_fnv1a64m(file_buf) });

                static prj::string (FASTCALL* OsagePlayDataManager__GetOpdFarcFilePath)(const prj::string& path)
                    = (prj::string(FASTCALL * )(const prj::string & path))0x0000000140488E00;
                prj::string farc_path = OsagePlayDataManager__GetOpdFarcFilePath(farc_buf);

                static bool (FASTCALL * path_get_file_first_mount_path_0)(prj::string & path)
                    = (bool (FASTCALL*)(prj::string & path))0x0000000140183F30;
                if (path_get_file_first_mount_path_0(farc_path)) {
                    file_handlers.push_back(new (_operator_new(sizeof(p_file_handler)))p_file_handler);
                    file_handlers.back()->read_file(farc_path.c_str(), file_buf.c_str(), prj::MemCTemp, true);
                    i++;
                    continue;
                }

                req_data_mot.data()[idx].second.back().second.generate = true;
            }
        }

        i = req_data.erase(i);
        i_end = req_data.end();
    }

    if (req_data_mot.size()) {
        if (!opd_play_gen)
            opd_play_gen = new OpdPlayGen;

        bool generate = false;
        for (auto& i : req_data_mot) {
            auto& object = opd_play_gen->gen_data[i.first];
            object.insert(object.end(), i.second.begin(), i.second.end());

            std::sort(object.begin(), object.end());
            object.erase(std::unique(object.begin(), object.end()), object.end());

            for (auto& j : i.second)
                if (j.second.generate) {
                    generate = true;
                    break;
                }
        }

        if (generate)
            opd_play_gen->state = 1;
    }
}

inline rob_osage_mothead_data::rob_osage_mothead_data(mothead_data_type type, uint32_t motion_id) {
    data = 0;
    this->type = type;
    static mothead_mot* (FASTCALL * mothead_storage_get_mot_by_motion_id)(uint32_t motion_id)
        = (mothead_mot * (FASTCALL*)(uint32_t motion_id))0x0000000140539F10;
    data = mothead_storage_get_mot_by_motion_id(motion_id)->data;
    init = true;
}

inline rob_osage_mothead_data::~rob_osage_mothead_data() {

}

inline const mothead_data* rob_osage_mothead_data::find_next_data() {
    if (!data)
        return 0;

    if (init)
        init = false;
    else
        data++;

    const mothead_data* data = this->data;
    if (data && data->type >= MOTHEAD_DATA_TYPE_0) {
        mothead_data_type type = data->type;
        while (type != this->type) {
            data++;
            type = data->type;
            if (type < MOTHEAD_DATA_TYPE_0) {
                data = 0;
                break;
            }
        }
    }
    else
        data = 0;

    this->data = data;
    return data;
}

rob_osage_mothead::rob_osage_mothead(rob_chara* rob_chr, int32_t stage_index,
    uint32_t motion_id, float_t frame) : rob_chr(),
    motion_id(), frame(), last_frame(),
    rob_parts_adjust(), rob_parts_adjust_data(), rob_adjust_global(), rob_adjust_global_data(),
    sleeve_adjust(), sleeve_adjust_data(), disable_collision(), disable_collision_data(),
    rob_chara_coli_ring(), rob_chara_coli_ring_data(), field_68() {
    rob_parts_adjust = 0;
    rob_adjust_global = 0;
    sleeve_adjust = 0;
    disable_collision = 0;
    rob_chara_coli_ring = 0;
    this->rob_chr = rob_chr;
    if (rob_chr) {
        rob_chara_set_motion_id(rob_chr, motion_id, frame, 0.0f,
            true, false, MOTION_BLEND_CROSS);
        this->frame = frame;
        this->motion_id = motion_id;
        last_frame = rob_chara_bone_data_get_frame_count(rob_chr->bone_data) - 1.0f;
        rob_chara_set_stage_data_ring(rob_chr, stage_index);
        rob_chara_reset_osage(rob_chr);
        rob_chara_set_bone_data_frame(rob_chr, frame);
        rob_chara_item_equip_ctrl_iterate_nodes(rob_chr->item_equip, 0);
        init_data();
        set_mothead_frame();
    }
    else
        reset();

}

rob_osage_mothead::rob_osage_mothead(rob_chara* rob_chr, int32_t stage_index,
    uint32_t motion_id, float_t frame, bool set_motion_reset_data) : rob_chr(),
    motion_id(), frame(), last_frame(),
    rob_parts_adjust(), rob_parts_adjust_data(), rob_adjust_global(), rob_adjust_global_data(),
    sleeve_adjust(), sleeve_adjust_data(), disable_collision(), disable_collision_data(),
    rob_chara_coli_ring(), rob_chara_coli_ring_data(), field_68() {
    rob_parts_adjust = 0;
    rob_adjust_global = 0;
    sleeve_adjust = 0;
    disable_collision = 0;
    rob_chara_coli_ring = 0;
    this->rob_chr = rob_chr;
    if (rob_chr) {
        rob_chara_set_motion_id(rob_chr, motion_id, frame, 0.0f,
            true, set_motion_reset_data, MOTION_BLEND_CROSS);
        this->frame = frame;
        this->motion_id = motion_id;
        last_frame = rob_chara_bone_data_get_frame_count(rob_chr->bone_data) - 1.0f;
        rob_chara_set_stage_data_ring(rob_chr, stage_index);
        rob_chara_reset_osage(rob_chr);
        rob_chara_set_bone_data_frame(rob_chr, frame);
        rob_chara_item_equip_ctrl_iterate_nodes(rob_chr->item_equip, 0);
        init_data();
        set_mothead_frame();
    }
    else
        reset();

}

rob_osage_mothead::~rob_osage_mothead() {
    reset();
}

// 0x14053D360
void rob_osage_mothead::ctrl() {
    rob_chara* rob_chr = this->rob_chr;
    if (!rob_chr)
        return;

    rob_chara_set_bone_data_frame(rob_chr, frame);
    set_mothead_frame();
    rob_chara_adjust_ctrl(rob_chr);
    rob_motion_modifier_rob_chara_ctrl(rob_chr);
    rob_chara_ctrl_rob_disp_thread_main(rob_chr);
}

// 0x14053D3E0
void rob_osage_mothead::reset() {
    rob_chr = 0;
    motion_id = -1;
    frame = 0.0f;
    last_frame = 0.0f;
    reset_data();
}

// 0x14053D6C0
void rob_osage_mothead::init_data() {
    reset_data();

    rob_parts_adjust = new (_operator_new(sizeof(rob_osage_mothead_data)))
        rob_osage_mothead_data(MOTHEAD_DATA_ROB_PARTS_ADJUST, motion_id);
    rob_parts_adjust_data = rob_parts_adjust->find_next_data();

    rob_adjust_global = new (_operator_new(sizeof(rob_osage_mothead_data)))
        rob_osage_mothead_data(MOTHEAD_DATA_ROB_ADJUST_GLOBAL, motion_id);
    rob_adjust_global_data = rob_adjust_global->find_next_data();

    sleeve_adjust = new (_operator_new(sizeof(rob_osage_mothead_data)))
        rob_osage_mothead_data(MOTHEAD_DATA_SLEEVE_ADJUST, motion_id);
    sleeve_adjust_data = sleeve_adjust->find_next_data();

    disable_collision = new (_operator_new(sizeof(rob_osage_mothead_data)))
        rob_osage_mothead_data(MOTHEAD_DATA_DISABLE_COLLISION, motion_id);
    disable_collision_data = disable_collision->find_next_data();

    rob_chara_coli_ring = new (_operator_new(sizeof(rob_osage_mothead_data)))
        rob_osage_mothead_data(MOTHEAD_DATA_ROB_CHARA_COLI_RING, motion_id);
    rob_chara_coli_ring_data = rob_chara_coli_ring->find_next_data();
}

// 0x14053D450
void rob_osage_mothead::reset_data() {
    if (rob_parts_adjust) {
        rob_parts_adjust->~rob_osage_mothead_data();
        _operator_delete(rob_parts_adjust);
    }
    rob_parts_adjust = 0;
    rob_parts_adjust_data = 0;

    if (rob_adjust_global) {
        rob_adjust_global->~rob_osage_mothead_data();
        _operator_delete(rob_adjust_global);
    }
    rob_adjust_global = 0;
    rob_adjust_global_data = 0;

    if (sleeve_adjust) {
        sleeve_adjust->~rob_osage_mothead_data();
        _operator_delete(sleeve_adjust);
    }
    sleeve_adjust = 0;
    sleeve_adjust_data = 0;

    if (disable_collision) {
        disable_collision->~rob_osage_mothead_data();
        _operator_delete(disable_collision);
    }
    disable_collision = 0;
    disable_collision_data = 0;

    if (rob_chara_coli_ring) {
        rob_chara_coli_ring->~rob_osage_mothead_data();
        _operator_delete(rob_chara_coli_ring);
    }
    rob_chara_coli_ring_data = 0;
    rob_chara_coli_ring = 0;
}

void rob_osage_mothead::set_coli_ring(const mothead_data* mhd_data) {
    static void (FASTCALL * rob_osage_mothead_set_coli_ring)(rob_osage_mothead * rob_osg_mhd, const mothead_data * mhd_data)
        = (void (FASTCALL*)(rob_osage_mothead * rob_osg_mhd, const mothead_data * mhd_data))0x000000014053EC90;
    rob_osage_mothead_set_coli_ring(this, mhd_data);
}

// 0x14053E7B0
void rob_osage_mothead::set_frame(float_t value) {
    if (last_frame > value)
        frame = value;
}

void rob_osage_mothead::set_disable_collision(const mothead_data* mhd_data) {
    static void (FASTCALL * rob_osage_mothead_set_disable_collision)(rob_osage_mothead * rob_osg_mhd, const mothead_data * mhd_data)
        = (void (FASTCALL*)(rob_osage_mothead * rob_osg_mhd, const mothead_data * mhd_data))0x000000014053E7C0;
    rob_osage_mothead_set_disable_collision(this, mhd_data);
}

// 0x14053E170
void rob_osage_mothead::set_mothead_frame() {
    while (rob_parts_adjust_data) {
        if ((float_t)rob_parts_adjust_data->frame > frame)
            break;

        set_rob_parts_adjust(rob_parts_adjust_data);

        rob_parts_adjust_data = rob_parts_adjust->find_next_data();
    }

    while (rob_adjust_global_data) {
        if ((float_t)rob_adjust_global_data->frame > frame)
            break;

        set_rob_adjust_global(rob_adjust_global_data);

        rob_adjust_global_data = rob_adjust_global->find_next_data();
    }

    while (sleeve_adjust_data) {
        if ((float_t)sleeve_adjust_data->frame > frame)
            break;

        set_sleeve_adjust(sleeve_adjust_data);

        sleeve_adjust_data = sleeve_adjust->find_next_data();
    }

    while (disable_collision_data) {
        if ((float_t)disable_collision_data->frame > frame)
            break;

        set_disable_collision(disable_collision_data);

        disable_collision_data = disable_collision->find_next_data();
    }

    while (rob_chara_coli_ring_data) {
        if ((float_t)rob_chara_coli_ring_data->frame > frame)
            break;

        set_coli_ring(rob_chara_coli_ring_data);

        rob_chara_coli_ring_data = rob_chara_coli_ring->find_next_data();
    }
}

void rob_osage_mothead::set_rob_adjust_global(const mothead_data* mhd_data) {
    static void (FASTCALL * rob_osage_mothead_set_rob_adjust_global)(rob_osage_mothead * rob_osg_mhd, const mothead_data * mhd_data)
        = (void (FASTCALL*)(rob_osage_mothead * rob_osg_mhd, const mothead_data * mhd_data))0x000000014053EA00;
    rob_osage_mothead_set_rob_adjust_global(this, mhd_data);
}

void rob_osage_mothead::set_rob_parts_adjust(const mothead_data* mhd_data) {
    static void (FASTCALL * rob_osage_mothead_set_rob_parts_adjust)(rob_osage_mothead * rob_osg_mhd, const mothead_data * mhd_data)
        = (void (FASTCALL*)(rob_osage_mothead * rob_osg_mhd, const mothead_data * mhd_data))0x000000014053E810;
    rob_osage_mothead_set_rob_parts_adjust(this, mhd_data);
}

void rob_osage_mothead::set_sleeve_adjust(const mothead_data* mhd_data) {
    static void (FASTCALL * rob_osage_mothead_set_sleeve_adjust)(rob_osage_mothead * rob_osg_mhd, const mothead_data * mhd_data)
        = (void (FASTCALL*)(rob_osage_mothead * rob_osg_mhd, const mothead_data * mhd_data))0x000000014053EBE0;
    rob_osage_mothead_set_sleeve_adjust(this, mhd_data);
}

inline OpdPlayGen::Cache::EntryFile::EntryFile() : obj_info(),
offset(), size(), compressed(), original_size(), encrypted(), key(), hash() {
    motion_id = -1;
}

inline void OpdPlayGen::Cache::EntryFile::reset() {
    offset = 0;
    size = 0;
    compressed = 0;
    original_size = 0;
    encrypted = 0;
    memset(key, 0, prj::Rijndael_Nk256 * prj::Rijndael_Nb);
    hash = 0;
}

inline OpdPlayGen::Cache::Entry::Entry() {

}

inline OpdPlayGen::Cache::Entry::~Entry() {

}

bool OpdPlayGen::Cache::Entry::read(const char* path) {
    if (!file_data.size)
        return false;

    const char* object_name = objset_info_storage_get_obj_name(file_data.obj_info);
    if (!object_name)
        return false;

    const char* motion_name = motion_database_get_motion_name_by_motion_id(file_data.motion_id);
    if (!motion_name)
        return false;

    std::string cache_path = sprintf_s_string("%s/%s", path, object_name);

    FILE* f = _wfopen(utf8_to_utf16(cache_path).c_str(), L"rb");
    if (!f)
        return false;

    if (_fseeki64(f, file_data.offset, SEEK_SET)) {
        fclose(f);
        return false;
    }

    data.resize(max_def(file_data.original_size, file_data.size));
    if (!fread(data.data(), file_data.size, 1, f)) {
        fclose(f);
        return false;
    }
    fclose(f);

    void* data = this->data.data();
    size_t size = this->data.size();

    const uint8_t* src = this->data.data();
    if (!src)
        return false;

    size_t buf_count;
    if (!file_data.encrypted)
        buf_count = file_data.compressed ? 1 : 0;
    else
        buf_count = file_data.compressed ? 2 : 1;

    buf_count++;
    if (buf_count > 3)
        return false;

    if (buf_count == 1) {
        if (size >= file_data.size) {
            memmove(data, src, file_data.size);
            return file_data.hash == hash_xxh3_64bits(this->data.data(), this->data.size());
        }
        return false;
    }

    std::vector<uint8_t> temp;
    temp.resize(file_data.size);

    buf_data buf[3];
    buf[0].data = (uint8_t*)src;
    buf[0].len = file_data.size;
    buf[0].size = file_data.size;

    for (size_t i = 1; i < buf_count; i++) {
        uint8_t* buf_data;
        size_t buf_size;
        if ((i % 2) == (buf_count % 2)) {
            buf_data = temp.data();
            buf_size = temp.size();
        }
        else {
            buf_data = (uint8_t*)data;
            buf_size = size;
        }
        buf[i].data = buf_data;
        buf[i].len = 0;
        buf[i].size = buf_size;
    }

    if (buf[buf_count - 1].data != data)
        return false;

    size_t buf_off = 0;
    if (file_data.encrypted) {
        if (buf_count <= 1)
            return false;

        if (!opd_cache_decrypt_data(file_data.key, buf[0], buf[1]))
            return false;

        buf_off = 1;
    }

    size = file_data.original_size;
    if (file_data.compressed) {
        if (buf_off + 1 >= buf_count)
            return false;

        if (deflate::decompress(buf[1].data, buf[1].len,
            data, size, deflate::MODE_GZIP, 0) < 0)
            return false;
    }

    this->data.resize(size);
    return file_data.hash == hash_xxh3_64bits(this->data.data(), this->data.size());
}

bool OpdPlayGen::Cache::Entry::write(const char* path, std::mt19937& mt_rand, FreeRanges* free_ranges) {
    const char* object_name = objset_info_storage_get_obj_name(file_data.obj_info);
    if (!object_name)
        return false;

    const char* motion_name = motion_database_get_motion_name_by_motion_id(file_data.motion_id);
    if (!motion_name)
        return false;

    std::string cache_path = sprintf_s_string("%s/%s", path, object_name);

    size_t file_size = path_stat_get_file_size(cache_path);

    FILE* f = _wfopen(utf8_to_utf16(cache_path).c_str(), file_size == -1 ? L"wb" : L"rb+");
    if (!f)
        return false;

    if (file_size == -1)
        file_size = 0;

    std::string opd_file_name = string_to_lower(sprintf_s_string("%s_%s.opd", object_name, motion_name));

    const void* data = this->data.data();
    size_t size = this->data.size();
    uint64_t hash = hash_xxh3_64bits(data, size);

    file_data.reset();

    uint8_t key[prj::Rijndael_Nk256 * prj::Rijndael_Nb];
    for (int32_t i = 0; i < prj::Rijndael_Nk256 * prj::Rijndael_Nb; i += sizeof(uint32_t))
        store_reverse_endianness_uint32_t(&key[i], mt_rand());
    bool compress = true;
    bool encrypt = true;

    void* temp = 0;
    const void* comp_data = data;
    size_t comp_size = size;
    bool compressed = false;
    if (compress) {
        size_t _comp_size = deflate::compress_bound(size, deflate::MODE_GZIP) + (opd_file_name.size() + 1);
        int32_t res = deflate::compress_gzip(data, size, temp, _comp_size, 9, opd_file_name.c_str());
        if (_comp_size < size && res >= 0) {
            comp_data = temp;
            comp_size = _comp_size;

            compressed = true;
        }
    }

    size_t req_size;
    if (encrypt) {
        size_t align = align_val(comp_size, prj::Rijndael_Nlen) - comp_size;
        if (!align)
            align = prj::Rijndael_Nlen;
        req_size = comp_size + align + prj::Rijndael_Nlen;
    }
    else
        req_size = comp_size;

    size_t offset = -1;
    size_t range_index = -1;
    if (free_ranges)
        range_index = free_ranges->find_free_range(req_size, offset);

    if (offset == -1) {
        if (_fseeki64(f, file_size, SEEK_SET)) {
            fclose(f);
            return false;
        }
    }
    else {
        if (_fseeki64(f, offset, SEEK_SET)) {
            fclose(f);
            return false;
        }
    }

    offset = _ftelli64(f);

    if (free_ranges)
        free_ranges->claim_range(range_index, req_size);

    size_t act_size = 0;
    bool encrypted = false;
    if (!opd_cache_write_data(key, encrypt, mt_rand, comp_data, comp_size, act_size, f, encrypted)) {
        free_def(temp);
        fclose(f);
        return false;
    }

    file_data.compressed = compressed ? 1 : 0;
    file_data.encrypted = encrypted ? 1 : 0;

    file_data.offset = offset;
    file_data.size = (uint32_t)act_size;
    file_data.original_size = (uint32_t)size;
    memcpy(file_data.key, key, prj::Rijndael_Nk256 * prj::Rijndael_Nb);
    file_data.hash = hash;

    free_def(temp);

    fclose(f);
    return true;
}

inline OpdPlayGen::Cache::FreeRanges::FreeRanges() {

}

inline OpdPlayGen::Cache::FreeRanges::~FreeRanges() {

}

void OpdPlayGen::Cache::FreeRanges::claim_range(size_t index, size_t req_size) {
    if (index == -1)
        return;

    auto range = data.begin() + index;
    range->first += req_size;
    range->second -= req_size;
    if (!range->second)
        data.erase(range);
}

size_t OpdPlayGen::Cache::FreeRanges::find_free_range(size_t req_size, size_t& offset) {
    for (auto& i : data)
        if (i.second >= req_size) {
            offset = i.first;
            return &i - data.data();
        }
    return -1;
}

void OpdPlayGen::Cache::FreeRanges::find_free_ranges(const char* path, const prj::vector<Entry>& entries,
    prj::vector_pair<object_info, OpdPlayGen::Cache::FreeRanges>& obj_free_ranges) {

    prj::vector_pair<object_info, prj::vector<prj::pair<size_t, size_t>>> preserved_ranges;
    for (const OpdPlayGen::Cache::Entry& i : entries)
        if (i.data.size() && !i.file_data.size)
            preserved_ranges.push_back(i.file_data.obj_info, {});

    preserved_ranges.sort_unique();

    if (preserved_ranges.size()) {
        for (const OpdPlayGen::Cache::Entry& i : entries) {
            if (i.data.size() && !i.file_data.size)
                continue;

            auto elem = preserved_ranges.find(i.file_data.obj_info);
            if (elem != preserved_ranges.end())
                elem->second.push_back({ i.file_data.offset, i.file_data.size });
        }
    }

    obj_free_ranges.reserve(preserved_ranges.size());
    for (auto& i : preserved_ranges) {
        const char* object_name = objset_info_storage_get_obj_name(i.first);
        if (!object_name)
            continue;

        std::string cache_path = sprintf_s_string("%s/%s", path, object_name);

        size_t file_size = path_stat_get_file_size(cache_path);
        if (!file_size || file_size == -1)
            continue;

        std::sort(i.second.begin(), i.second.end());

        obj_free_ranges.push_back(i.first, {});
        auto& free_ranges = obj_free_ranges.back().second;

        size_t pos = 0;
        for (auto& j : i.second) {
            if (pos < j.first && (j.first - pos) > prj::Rijndael_Nlen)
                free_ranges.data.push_back({ pos, j.first - pos });
            pos = j.first + j.second + opd_cache_get_align(j.second);
        }

        if (pos < file_size && (file_size - pos))
            free_ranges.data.push_back({ pos, file_size - pos });
    }
}

inline OpdPlayGen::Cache::Cache() : chara_index(), write_data() {

}

inline OpdPlayGen::Cache::~Cache() {

}

OpdPlayGen::Cache::Entry* OpdPlayGen::Cache::add(object_info obj_info, uint32_t motion_id) {
    write_data = true;

    OpdPlayGen::Cache::Entry* cache_entry = find(obj_info, motion_id);
    if (cache_entry) {
        cache_entry->file_data.reset();
        cache_entry->data.clear();
        cache_entry->data.shrink_to_fit();
        return cache_entry;
    }

    sorted_entries.push_back({ obj_info, motion_id }, entries.size());
    sorted_entries.sort();

    entries.push_back({});
    cache_entry = &entries.back();
    cache_entry->file_data.obj_info = obj_info;
    cache_entry->file_data.motion_id = motion_id;
    return cache_entry;
}

OpdPlayGen::Cache::Entry* OpdPlayGen::Cache::find(object_info obj_info, uint32_t motion_id) {
    auto elem = sorted_entries.find({ obj_info, motion_id });
    if (elem != sorted_entries.end())
        return &entries.data()[elem->second];
    return 0;
}

void OpdPlayGen::Cache::read(::chara_index chara_index, const char* path) {
    this->chara_index = chara_index;

    std::string db_path = sprintf_s_string("%s/%s_%s",
        path, chara_index_get_chara_name(chara_index), "db");

    FILE* f = _wfopen(utf8_to_utf16(db_path).c_str(), L"rb");
    if (!f)
        return;

    uint64_t count = 0;
    if (fread(&count, sizeof(uint64_t), 1, f)) {
        entries.reserve(count);
        for (size_t i = 0; i < count; i++) {
            OpdPlayGen::Cache::Entry entry;
            if (!fread(&entry.file_data, sizeof(OpdPlayGen::Cache::EntryFile), 1, f))
                break;

            entries.push_back(entry);
        }

        sorted_entries.reserve(count);
        for (const OpdPlayGen::Cache::Entry& i : entries)
            sorted_entries.push_back({ i.file_data.obj_info, i.file_data.motion_id }, &i - entries.data());
        sorted_entries.sort();
    }

    fclose(f);
}

void OpdPlayGen::Cache::reset() {
    sorted_entries.clear();
    sorted_entries.shrink_to_fit();
    entries.clear();
    entries.shrink_to_fit();
}

void OpdPlayGen::Cache::write(const char* path) {
    if (!write_data)
        return;

    prj::vector_pair<object_info, OpdPlayGen::Cache::FreeRanges> obj_free_ranges;
    OpdPlayGen::Cache::FreeRanges::find_free_ranges(path, entries, obj_free_ranges);

    path_create_directory(path);

    std::string db_path = sprintf_s_string("%s/%s_%s",
        path, chara_index_get_chara_name(chara_index), "db");

    FILE* f = _wfopen(utf8_to_utf16(db_path).c_str(), L"wb");
    if (!f)
        return;

    std::random_device rd;
    std::mt19937 mt_rand;
    mt_rand.seed(rd());

    uint64_t count = entries.size();
    if (fwrite(&count, sizeof(uint64_t), 1, f)) {
        for (OpdPlayGen::Cache::Entry& i : entries) {
            if (i.data.size() && !i.file_data.size) {
                auto elem = obj_free_ranges.find(i.file_data.obj_info);
                i.write(path, mt_rand, elem != obj_free_ranges.end() ? &elem->second : 0);
            }

            if (i.file_data.size && !fwrite(&i.file_data, sizeof(OpdPlayGen::Cache::EntryFile), 1, f))
                break;
        }
    }

    fclose(f);

    write_data = false;
}

inline OpdPlayGen::Object::Object() : file_hash(hash_fnv1a64m_empty), generate(true) {

}

inline OpdPlayGen::Object::Object(uint64_t file_hash) : file_hash(file_hash), generate(false) {

}

OpdPlayGen::OpdPlayGen() : state(), thread() {

}

OpdPlayGen::~OpdPlayGen() {

}

bool OpdPlayGen::CheckState() {
    static bool(FASTCALL * skin_param_manager_array_check_task_ready)()
        = (bool(FASTCALL*)())0x00000001406116B0;

    switch (state) {
    default:
        if (thread) {
            thread->join();
            delete thread;
            thread = 0;
        }
        return true;
    case 1:
        if (skin_param_manager_array_check_task_ready())
            return false;

        state = 2;
        return false;
    case 2:
        state = 3;
        thread = new std::thread(OpdPlayGen::ThreadMain, this);
        if (thread)
            SetThreadDescription((HANDLE)thread->native_handle(), L"OPD Play Gen");
        return false;
    case 3:
        return false;
    }
}

void OpdPlayGen::Ctrl() {
    if (state != 3)
        return;

    const prj::string cache_dir = get_ram_osage_play_data_cache_dir();

    opd_play_gen_run = true;
    prj::vector<uint32_t> motion_ids[6];
    for (auto& i : gen_data) {
        const uint32_t motion_id = i.first;

        for (int32_t chara_id = 0; chara_id < ROB_CHARA_COUNT && i.second.size(); chara_id++) {
            rob_chara* rob_chr = rob_chara_array_get(get_rob_chara_smth(), chara_id);
            if (!rob_chr)
                continue;

            prj::vector<pv_data_set_motion>& set_motion = this->set_motion[chara_id];

            if (set_motion.size()) {
                bool found_set_motion = false;
                for (pv_data_set_motion& j : set_motion)
                    if (j.motion_id == motion_id) {
                        found_set_motion = true;
                        break;
                    }

                if (!found_set_motion)
                    continue;
            }

            rob_chara_item_equip* rob_itm_equip = rob_chr->item_equip;

            for (int32_t j = ITEM_KAMI; j < ITEM_ITEM16 && i.second.size(); j++) {
                rob_chara_item_equip_object* itm_eq_obj = rob_itm_equip->get_item_equip_object((item_id)j);

                auto find = [](prj::vector<prj::pair<object_info, Object>>& vec, const object_info key) {
                    auto k = vec.begin();
                    size_t l = vec.size();
                    size_t temp;
                    while (l > 0) {
                        if (k[temp = l / 2].first >= key)
                            l /= 2;
                        else {
                            k += temp + 1;
                            l -= temp + 1;
                        }
                    }
                    if (k == vec.end() || key < k->first)
                        return vec.end();
                    return k;
                };

                auto elem = find(i.second, itm_eq_obj->obj_info);
                if (elem != i.second.end()) {
                    if (elem->second.generate) {
                        obj_info[chara_id][j - ITEM_OSAGE_FIRST] = itm_eq_obj->obj_info;
                        motion_ids[chara_id].push_back(motion_id);
                    }

                    i.second.erase(elem);
                }
            }
        }
    }

    for (int32_t chara_id = 0; chara_id < ROB_CHARA_COUNT; chara_id++) {
        prj::vector<uint32_t>& _motion_ids = motion_ids[chara_id];
        std::sort(_motion_ids.begin(), _motion_ids.end());
        _motion_ids.erase(std::unique(_motion_ids.begin(), _motion_ids.end()), _motion_ids.end());
    }

    for (int32_t chara_id = 0; chara_id < ROB_CHARA_COUNT; chara_id++) {
        rob_chara* rob_chr = rob_chara_array_get(get_rob_chara_smth(), chara_id);
        if (!rob_chr)
            continue;

        if (opd_play_gen_use_cache)
            cache.read(rob_chr->chara_index, cache_dir.c_str());

        for (const uint32_t motion_id : motion_ids[chara_id]) {
            if (opd_play_gen_use_cache) {
                bool generate = false;
                for (int32_t i = 0; i < ITEM_OSAGE_COUNT; i++) {
                    object_info obj_info = this->obj_info[chara_id][i];
                    if (obj_info.is_null())
                        continue;

                    OpdPlayGen::Cache::Entry* cache_entry = cache.find(obj_info, motion_id);
                    if (!cache_entry)
                        generate = true;
                    else if (!cache_entry->read(cache_dir.c_str())) {
                        cache.write_data = true;
                        cache_entry->file_data.reset();
                        cache_entry->data.clear();
                        cache_entry->data.shrink_to_fit();
                        generate = true;
                    }
                }

                if (!generate)
                    continue;
            }

            rob_chara_set_motion_id(rob_chr, motion_id, 0.0f, 0.0f,
                true, false, MOTION_BLEND_CROSS);
            rob_chara_set_step_motion_step(rob_chr, 1.0f);

            float_t frame_count = (float_t)(int32_t)rob_chara_bone_data_get_frame_count(rob_chr->bone_data) - 1.0f;
            uint32_t iterations = 60;
            if (rob_chr->data.field_1588.field_0.iterations > 0)
                iterations = rob_chr->data.field_1588.field_0.iterations;

            bool has_opd = false;
            {
                static uint32_t(FASTCALL* motion_database_get_motion_set_by_motion_id)(int32_t id)
                    = (uint32_t(FASTCALL*)(int32_t id))0x0000000140403940;
                static const uint32_t* (FASTCALL* get_opd_motion_ids)()
                    = (const uint32_t * (FASTCALL*)())0x00000001404789B0;
                static const uint32_t* (FASTCALL* get_opd_motion_set_ids)()
                    = (const uint32_t * (FASTCALL*)())0x00000001404789C0;

                const uint32_t* opd_motion_ids = get_opd_motion_ids();
                while (*opd_motion_ids != -1 && !has_opd) {
                    if (*opd_motion_ids == motion_id)
                        has_opd = true;
                    opd_motion_ids++;
                }

                const uint32_t motion_set_id = motion_database_get_motion_set_by_motion_id(motion_id);
                const uint32_t* opd_motion_set_ids = get_opd_motion_set_ids();
                while (*opd_motion_set_ids != -1 && !has_opd) {
                    if (*opd_motion_set_ids == motion_set_id)
                        has_opd = true;
                    opd_motion_set_ids++;
                }
            }

            prj::vector<pv_data_set_motion>& set_motion = this->set_motion[chara_id];

            bool has_osage_reset = false; // Added
            rob_osage_mothead osg_mhd(rob_chr, 0, motion_id, 0.0f, true);
            if (has_opd) {
                rob_osage_mothead_data* osage_reset = new (_operator_new(sizeof(rob_osage_mothead_data))) // Added
                    rob_osage_mothead_data(MOTHEAD_DATA_OSAGE_RESET, motion_id);
                const mothead_data* osage_reset_data = osage_reset->find_next_data();

                uint64_t frame = 0;
                uint64_t iteration = 0;
                while (true) {
                    osg_mhd.set_frame((float_t)(int64_t)frame);
                    osg_mhd.ctrl();

                    if (osage_reset_data) { // Added
                        if (osage_reset_data->frame == 0) {
                            uint32_t _motion_id = motion_id;
                            float_t _frame = (float_t)(int64_t)frame;

                            rob_chara_item_equip* rob_itm_equip = rob_chr->item_equip;
                            for (int32_t i = 0; i < 600; i++) // Should calm phys
                                osg_mhd.ctrl();

                            rob_chara_add_motion_reset_data(rob_chr, _motion_id, _frame, iterations);
                            set_motion.push_back({ motion_id, { (float_t)(int64_t)frame, 0  } });
                            has_osage_reset = true;
                        }

                        osage_reset_data = 0;
                    }

                    frame++;
                    iteration++;
                    if ((float_t)(int64_t)frame >= frame_count) {
                        if (iteration > iterations)
                            break;

                        frame = 0;
                        osg_mhd.init_data();
                    }
                }

                if (osage_reset) { // Added
                    osage_reset->~rob_osage_mothead_data();
                    _operator_delete(osage_reset);
                }
                osage_reset_data = 0;
                osage_reset = 0;
            }

            osg_mhd.init_data();

            static void (FASTCALL * opd_chara_data_array_init_data)(int32_t chara_id, uint32_t motion_id)
                = (void (FASTCALL*)(int32_t chara_id, uint32_t motion_id))0x000000014048E840;
            opd_chara_data_array_init_data(chara_id, motion_id);

            bool no_loop = has_osage_reset; // Added

            size_t set_motion_index = 0;
            uint64_t frame_int = 0;
            float_t frame = 0.0f;
            while (frame <= frame_count) {
                osg_mhd.set_frame(frame);

                while (set_motion_index < set_motion.size()) {
                    if (set_motion.data()[set_motion_index].motion_id != motion_id) {
                        set_motion_index++;
                        continue;
                    }

                    float_t _frame = (float_t)(int32_t)prj::roundf(
                        set_motion.data()[set_motion_index].frame_stage_index.first);
                    if (_frame > frame)
                        break;

                    rob_chara_set_motion_skin_param(rob_chr, motion_id, _frame);
                    rob_chara_set_motion_reset_data(rob_chr, motion_id, _frame);
                    set_motion_index++;
                }

                osg_mhd.ctrl();

                static void (FASTCALL * opd_chara_data_array_add_frame_data)(int32_t chara_id)
                    = (void (FASTCALL*)(int32_t chara_id))0x000000014048E050;
                opd_chara_data_array_add_frame_data(chara_id);

                frame = (float_t)(int64_t)++frame_int;
            }

            static opd_chara_data* (FASTCALL* opd_chara_data_array_get)(int32_t chara_id)
                = (opd_chara_data * (FASTCALL*)(int32_t chara_id))0x000000014048D460;
            opd_chara_data* opd_chr_data = opd_chara_data_array_get(chara_id);

            rob_chara_item_equip* rob_itm_equip = rob_chr->item_equip;

            for (int32_t i = 0; i < ITEM_OSAGE_COUNT; i++) {
                object_info obj_info = this->obj_info[chara_id][i];
                if (obj_info.is_null())
                    continue;

                int32_t load_count = 1;
                auto elem = osage_play_data_manager.file_data.find({ obj_info, motion_id });
                if (elem != osage_play_data_manager.file_data.end())
                    continue;

                if (opd_play_gen_use_cache) {
                    rob_chara_item_equip_object* itm_eq_obj
                        = rob_itm_equip->get_item_equip_object((item_id)(ITEM_OSAGE_FIRST + i));
                    if (!itm_eq_obj->osage_nodes_count)
                        continue;

                    OpdPlayGen::Cache::Entry* cache_entry = cache.find(obj_info, motion_id);
                    if (cache_entry && cache_entry->file_data.size)
                        continue;

                    cache_entry = cache.add(obj_info, motion_id);

                    const prj::vector<prj::vector<opd_vec3_data_vec>>& opd_data = opd_chr_data->opd_data[i];

                    size_t nodes_count = 0;
                    for (const prj::vector<opd_vec3_data_vec>& j : opd_data)
                        nodes_count += j.size();

                    size_t max_size = sizeof(osage_play_data_header)
                        + (6ULL * (opd_chr_data->frame_count + 2ULL) * nodes_count);
                    cache_entry->data.resize(max_size);
                    uint8_t* data = cache_entry->data.data();

                    osage_play_data_header* opd_head = (osage_play_data_header*)data;
                    opd_head->signature = 0;
                    opd_head->frame_count = opd_chr_data->frame_count;
                    opd_head->motion_id = motion_id;
                    opd_head->obj_info = { (uint16_t)obj_info.id, (uint16_t)obj_info.set_id };
                    opd_head->nodes_count = (uint16_t)itm_eq_obj->osage_nodes_count;
                    *(uint16_t*)((uint8_t*)opd_head + 0x12) = no_loop ? 0x01 : 0x00; // Added

                    size_t size = sizeof(osage_play_data_header);
                    uint8_t* d = data + size;

                    static const char* (FASTCALL * opd_encode_data)(const prj::vector<float_t>&src, uint8_t * &dst, size_t & dst_size, bool higher_accuracy)
                        = (const char* (FASTCALL*)(const prj::vector<float_t>&src, uint8_t * &dst, size_t & dst_size, bool higher_accuracy))0x000000014048CC90;

                    size_t osage_node_index = 0;
                    bool higher_accuracy = false;
                    for (const prj::vector<opd_vec3_data_vec>& j : opd_data) {
                        if (osage_node_index < itm_eq_obj->osage_blocks.size())
                            higher_accuracy = itm_eq_obj->osage_blocks.data()[osage_node_index]->has_children_node;

                        for (const opd_vec3_data_vec& k : j) {
                            size_t size_x = 0;
                            opd_encode_data(k.x, d, size_x, higher_accuracy);
                            d += size_x;
                            size += size_x;

                            size_t size_y = 0;
                            opd_encode_data(k.y, d, size_y, higher_accuracy);
                            d += size_y;
                            size += size_y;

                            size_t size_z = 0;
                            opd_encode_data(k.z, d, size_z, higher_accuracy);
                            d += size_z;
                            size += size_z;
                        }
                        osage_node_index++;
                    }

                    cache_entry->data.resize(size);
                }
                else {
                    const prj::vector<prj::vector<opd_vec3_data_vec>>& opd_data = opd_chr_data->opd_data[i];

                    size_t nodes_count = 0;
                    for (const prj::vector<opd_vec3_data_vec>& j : opd_data)
                        nodes_count += j.size();

                    int64_t _frame_count = (int64_t)frame_count;
                    float_t* buf = (float_t*)_operator_new(sizeof(float_t) * 3ULL * _frame_count * nodes_count);
                    if (!buf)
                        continue;

                    opd_file_data data;
                    memset(&data.head, 0, sizeof(data.head));
                    data.head.obj_info.first = obj_info.id;
                    data.head.obj_info.second = obj_info.set_id;
                    data.head.motion_id = motion_id;
                    data.head.frame_count = (uint32_t)_frame_count;
                    data.head.nodes_count = (uint16_t)nodes_count;
                    *(uint16_t*)((uint8_t*)&data.head + 0x12) = no_loop ? 0x01 : 0x00; // Added
                    data.data = buf;
                    data.load_count = load_count;

                    for (const prj::vector<opd_vec3_data_vec>& j : opd_data)
                        for (const opd_vec3_data_vec& k : j) {
                            memcpy(buf, k.x.data(), _frame_count * sizeof(float_t));
                            buf += _frame_count;
                            memcpy(buf, k.y.data(), _frame_count * sizeof(float_t));
                            buf += _frame_count;
                            memcpy(buf, k.z.data(), _frame_count * sizeof(float_t));
                            buf += _frame_count;
                        }

                    osage_play_data_manager.file_data.insert({ { obj_info, motion_id }, data });
                }
            }

            static void (FASTCALL* opd_chara_data__reset)(opd_chara_data* This)
                = (void (FASTCALL*)(opd_chara_data * This))0x000000014048E070;
            opd_chara_data__reset(opd_chr_data);
        }

        if (opd_play_gen_use_cache) {
            cache.write(cache_dir.c_str());

            static bool (FASTCALL* opd_decode_data)(void* data, float_t*& opd_decod_buf, osage_play_data_header& head)
                = (bool (FASTCALL*)(void* data, float_t * &opd_decod_buf, osage_play_data_header & head))0x000000014048CC70;

            for (const uint32_t motion_id : motion_ids[chara_id]) {
                for (int32_t i = 0; i < ITEM_OSAGE_COUNT; i++) {
                    object_info obj_info = this->obj_info[chara_id][i];
                    if (obj_info.is_null())
                        continue;

                    OpdPlayGen::Cache::Entry* cache_entry = cache.find(obj_info, motion_id);
                    if (!cache_entry || !cache_entry->data.size())
                        continue;

                    opd_file_data data;
                    *(uint16_t*)((uint8_t*)&data.head + 0x12) = 0; // Added
                    if (opd_decode_data(cache_entry->data.data(), data.data, data.head))
                        osage_play_data_manager.file_data.insert({ { obj_info, motion_id }, data });
                }
            }

            cache.reset();
        }

        for (int32_t i = 0; i < ITEM_OSAGE_COUNT; i++)
            obj_info[chara_id][i] = {};

        motion_ids[chara_id].clear();
        motion_ids[chara_id].shrink_to_fit();
    }
    opd_play_gen_run = false;

    Reset();
}

void OpdPlayGen::Reset() {
    state = 0;

    gen_data.clear();

    for (int32_t i = 0; i < ROB_CHARA_COUNT; i++)
        set_motion[i].clear();
}

void OpdPlayGen::ThreadMain(OpdPlayGen* opd_play) {
    opd_play->Ctrl();
}

static prj::string get_ram_osage_play_data_cache_dir() {
    static prj::string(FASTCALL * get_write_dir)() = (prj::string(FASTCALL*)())0x000000014066CED0;
    return get_write_dir() + "ram/osage_play_data_cache";
}

static size_t check_pkcs7_padding(const uint8_t* buff16) {
    size_t pad = buff16[prj::Rijndael_Nlen - 1];
    const uint8_t* end = buff16 + prj::Rijndael_Nlen;
    if ((int64_t)pad - 1 > prj::Rijndael_Nlen - 1)
        return 0;

    for (const uint8_t* ptr = end - pad; ptr != end; ptr++)
        if (*ptr != pad)
            return 0;
    return pad;
}

static bool opd_cache_decrypt_data(const void* key, const buf_data& src, buf_data& dst) {
    prj::Rijndael rijndael(prj::Rijndael_Nb, prj::Rijndael_Nk256, key);

    if (src.len < prj::Rijndael_Nlen)
        return false;

    uint8_t iv[prj::Rijndael_Nlen];
    memcpy(iv, src.data, prj::Rijndael_Nlen);
    size_t offset = min_def(src.len, prj::Rijndael_Nlen);

    size_t src_len = src.len - offset;
    size_t dst_len = dst.size;
    if (!dst_len)
        return false;

    if (src_len % prj::Rijndael_Nlen)
        return false;

    size_t src_block_count = src_len / prj::Rijndael_Nlen - 1;
    size_t src_len_align = src_block_count * prj::Rijndael_Nlen;
    if (dst_len < src_len_align)
        return false;

    memcpy(dst.data, src.data + offset, src_len_align + prj::Rijndael_Nlen);

    uint8_t next_iv[prj::Rijndael_Nlen];
    for (size_t i = 0; i < src_len_align; i += prj::Rijndael_Nlen) {
        memcpy(next_iv, dst.data + i, prj::Rijndael_Nlen);
        rijndael.decrypt16(dst.data + i);
        for (uint32_t j = 0; j < prj::Rijndael_Nlen / sizeof(uint32_t); j++)
            ((uint32_t*)(dst.data + i))[j] ^= ((uint32_t*)iv)[j];
        memcpy(iv, next_iv, prj::Rijndael_Nlen);
    }

    rijndael.decrypt16(dst.data + src_len_align);
    for (uint32_t i = 0; i < prj::Rijndael_Nlen / sizeof(uint32_t); i++)
        ((uint32_t*)(dst.data + src_len_align))[i] ^= ((uint32_t*)iv)[i];

    size_t pad = check_pkcs7_padding(dst.data + src_len_align);

    if (dst_len < src_len_align + prj::Rijndael_Nlen - pad)
        return false;

    dst_len = src_len - pad;

    size_t size = dst.size;
    if (dst.size < dst_len)
        return false;

    dst.len = dst_len;
    return true;
}

static bool opd_cache_encrypt_data(const void* key, std::mt19937& mt_rand, const buf_data& src, buf_data& dst) {
    prj::Rijndael rijndael(prj::Rijndael_Nb, prj::Rijndael_Nk256, key);

    if (dst.size < prj::Rijndael_Nlen)
        return false;

    uint8_t iv[prj::Rijndael_Nlen];
    for (int32_t i = 0; i < prj::Rijndael_Nlen; i += sizeof(uint32_t))
        store_reverse_endianness_uint32_t(&iv[i], mt_rand());

    memcpy(dst.data, iv, prj::Rijndael_Nlen);

    size_t offset = prj::Rijndael_Nlen;
    size_t src_len = src.len;
    size_t dst_len = dst.size;
    if (!dst_len || dst_len < prj::Rijndael_Nlen)
        return false;

    dst_len -= prj::Rijndael_Nlen;

    size_t src_block_count = src_len / prj::Rijndael_Nlen;
    size_t src_len_align = src_block_count * prj::Rijndael_Nlen;
    if (dst_len < src_len_align)
        return false;

    size_t pad = prj::Rijndael_Nlen;
    if (src_len % prj::Rijndael_Nlen)
        pad = prj::Rijndael_Nlen - (src_len - src_len_align);
    if (dst_len < src_len + pad)
        return false;

    dst_len = src_len + pad;

    memcpy(dst.data + offset, src.data, src_len);
    for (size_t i = 0; i < src_len_align; i += prj::Rijndael_Nlen) {
        for (uint32_t j = 0; j < prj::Rijndael_Nlen / sizeof(uint32_t); j++)
            ((uint32_t*)(dst.data + offset + i))[j] ^= ((uint32_t*)iv)[j];
        rijndael.encrypt16(dst.data + offset + i);
        memcpy(iv, dst.data + offset + i, prj::Rijndael_Nlen);
    }

    memset(dst.data + offset + src_len, (uint8_t)pad, pad);
    for (uint32_t i = 0; i < prj::Rijndael_Nlen / sizeof(uint32_t); i++)
        ((uint32_t*)(dst.data + offset + src_len_align))[i] ^= ((uint32_t*)iv)[i];
    rijndael.encrypt16(dst.data + offset + src_len_align);
    memcpy(iv, dst.data + offset + src_len_align, prj::Rijndael_Nlen);

    if (dst.size < dst_len)
        return false;

    dst.len = dst_len + prj::Rijndael_Nlen;
    return true;
}

static size_t opd_cache_get_align(size_t size) {
    const size_t align = 0x10;
    return ((size + (align - 1)) & ~(align - 1)) - size;
}

static bool opd_cache_write_pad(size_t align, bool random, std::mt19937& mt_rand, FILE* f) {
    for (size_t offset = 0; offset < align; offset += sizeof(uint32_t)) {
        uint32_t pad;
        if (random)
            pad = reverse_endianness_uint32_t(mt_rand());
        else
            pad = 'xxxx';

        size_t size = min_def(align - offset, sizeof(uint32_t));
        if (!fwrite(&pad, size, 1, f))
            return false;
    }
    return true;
}

static bool opd_cache_write_data(const void* key, bool encrypt, std::mt19937& mt_rand,
    const void* data, size_t size, size_t& act_size, FILE* f, bool& encrypted) {
    if (!encrypt) {
        if (fwrite(data, size, 1, f)
            && opd_cache_write_pad(opd_cache_get_align(size), false, mt_rand, f)) {
            act_size = size;
            encrypted = false;
            return true;
        }
        else
            return false;
    }

    buf_data src;
    src.data = (uint8_t*)data;
    src.size = size;
    src.len = size;

    std::vector<uint8_t> temp;
    size_t align = align_val(size, prj::Rijndael_Nlen) - size;
    if (!align)
        align = prj::Rijndael_Nlen;
    temp.resize(prj::Rijndael_Nlen + size + align);

    buf_data dst;
    dst.data = temp.data();
    dst.len = 0;
    dst.size = temp.size();
    if (opd_cache_encrypt_data(key, mt_rand, src, dst) && fwrite(dst.data, dst.len, 1, f)
        && opd_cache_write_pad(opd_cache_get_align(dst.len), true, mt_rand, f)) {
        act_size = dst.len;
        encrypted = true;
        return true;
    }

    return false;
}
