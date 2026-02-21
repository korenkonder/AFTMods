/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "file_handler.hpp"
#include "../AFTModsShared/file_handler.hpp"
#include <Helpers.h>

HOOK(bool, FASTCALL, file_handler__read_farc_file, 0x0000000140182730, file_handler* This) {
    bool ret = originalfile_handler__read_farc_file(This);
    if (ret)
        return ret;

    if (This->file_path.size() >= 4 && !This->file_path.compare(This->file_path.size() - 4, 4, ".opd")) {
        static void* (*file_handler__alloc)(prj::MemCType type, size_t size, const char* id)
            = (void* (*)(prj::MemCType, size_t, const char*))0x0000000140181C30;

        This->size = 0x14;
        This->data = file_handler__alloc(This->mem_c_type, This->size, This->file_path.c_str());;
        if (This->data) {
            memset(This->data, 0, 0x14);
            *(uint32_t*)This->data = 'OPDP';
            return true;
        }
    }
    return ret;
}

void file_handler_patch() {
    INSTALL_HOOK(file_handler__read_farc_file);
}
