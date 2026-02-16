/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "../AFTModsShared/types.hpp"
#include "rob/rob.hpp"
#include "file_handler.hpp"
#include <stdio.h>
#include <stdlib.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <PluginConfigApi/PluginConfigApi.h>

extern bool opd_play_gen_use_cache;

bool cpu_caps_aes_ni;

static std::wstring GetDirPath();

std::wstring CONFIG_FILE_STRING = GetDirPath() + L"\\plugins\\OPDPlayGen.ini";
LPCWSTR CONFIG_FILE = CONFIG_FILE_STRING.c_str();

void FASTCALL opd_play_gen_main() {
    int32_t cpuid_data[4] = {};
    __cpuid(cpuid_data, 1);
    cpu_caps_aes_ni = (cpuid_data[2] & (1 << 25)) ? true : false;

    printf("[OPD Play Gen] Patching memory\n");
    rob_patch();
    file_handler_patch();
}

bool APIENTRY DllMain(HMODULE handle, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        opd_play_gen_use_cache = GetPrivateProfileIntW(L"general",
            L"use_cache", 1, CONFIG_FILE) > 0 ? true : false;

        printf("[OPD Play Gen] Current version - v1.0 (Build date: " __DATE__ ")\n");
        printf("[OPD Play Gen] Attach\n");

        opd_play_gen_main();
        break;
    }
    return true;
}

extern "C" __declspec(dllexport) LPCWSTR GetPluginName(void) {
    return L"OPD Play Gen";
}

extern "C" __declspec(dllexport) LPCWSTR GetPluginDescription(void) {
    return L"OPD Play Gen Plugin by korenkonder";
}

extern "C" __declspec(dllexport) LPCWSTR GetBuildDate(void) {
    return L"v1.0 (Build date: " __DATE__ ")";
}

static std::wstring GetDirPath() {
    wchar_t exe_file_path[MAX_PATH];
    GetModuleFileNameW(0, exe_file_path, MAX_PATH);

    wchar_t* exe_file_name = wcsrchr(exe_file_path, '\\');
    if (!exe_file_name)
        exe_file_name = wcsrchr(exe_file_path, '/');

    if (!exe_file_name)
        return L"";

    WCHAR buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    return std::wstring(exe_file_path, exe_file_name - exe_file_path);
}

PluginConfig::PluginConfigOption config[] = {
    {
        PluginConfig::CONFIG_BOOLEAN,
        new PluginConfig::PluginConfigBooleanData {
            L"use_cache",
            L"general",
            CONFIG_FILE,
            L"Use OPD Cache",
            L"May result in faster load times on weaker machines, but it will consume space on your local drive.\n"
            "There might be a slowdown on first module load if data wasn't present in cache.",
            true,
            false,
        }
    },
};

extern "C" __declspec(dllexport) PluginConfig::PluginConfigArray GetPluginOptions(void) {
    return PluginConfig::PluginConfigArray{ _countof(config), config };
}
