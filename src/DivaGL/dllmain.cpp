/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include <Windows.h>
#include "../KKdLib/default.hpp"
#include "hook.hpp"
#include "print.hpp"
#include "static_var.hpp"
#include "wrap.hpp"
#include <intrin.h>
#include <knownfolders.h>
#include <shlobj_core.h>
#include <PluginConfigApi/PluginConfigApi.h>

size_t diva_handle;
size_t glut_handle;
size_t opengl32_handle;
size_t dll_handle;
bool cpu_caps_aes_ni;
bool cpu_caps_f16c;

static std::wstring GetDirPath();

std::wstring CONFIG_FILE_STRING = GetDirPath() + L"\\plugins\\DivaGL.ini";
LPCWSTR CONFIG_FILE = CONFIG_FILE_STRING.c_str();

void FASTCALL divagl_main() {
    int32_t cpuid_data[4] = {};
    __cpuid(cpuid_data, 1);
    cpu_caps_aes_ni = (cpuid_data[2] & (1 << 25)) ? true : false;
    cpu_caps_f16c = (cpuid_data[2] & (1 << 29)) ? true : false;

    glut_handle = (size_t)GetModuleHandleW(L"glut32.dll");
    opengl32_handle = (size_t)GetModuleHandleW(L"opengl32.dll");

    if (memcmp((void*)(glut_handle + 0x0004CA68),
        "D:\\F\\DIVA\\DIVAAC\\package\\glut-3.7.6\\vc11\\lib\\x64\\Release\\glut32.pdb", 0x43)) {
        printf_divagl("Error! Unsupported glut32.dll.");
        printf_divagl("Please use original glut32.dll.");
        MessageBoxA(0, "Unsupported glut32.dll.\r\nPlease use original glut32.dll.", 0, MB_OK);
        return;
    }

    wrap_addresses();

    printf_divagl("Patching memory");
    hook_funcs();
    wrap_patch();
}

bool APIENTRY DllMain(HMODULE handle, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        sv_reflect_full = GetPrivateProfileIntW(L"general", L"reflect_full", 0, CONFIG_FILE) > 0 ? true : false;
        sv_reflect_res_scale = GetPrivateProfileIntW(L"general", L"reflect_res_scale", 1, CONFIG_FILE);
        sv_reflect_res_scale = sv_reflect_res_scale ? clamp_def(sv_reflect_res_scale, 25, 100) : 100;

        sv_shared_storage_uniform_buffer = GetPrivateProfileIntW(L"experimentals",
            L"shared_storage_uniform_buffer", 0, CONFIG_FILE) > 0 ? true : false;

        sv_task_movie_player_no_interop = GetPrivateProfileIntW(L"experimentals",
            L"task_movie_player_no_interop", 0, CONFIG_FILE) > 0 ? true : false;

        sv_texture_skinning_buffer = GetPrivateProfileIntW(L"experimentals",
            L"texture_skinning_buffer", 0, CONFIG_FILE) > 0 ? true : false;

        dll_handle = (size_t)handle;
        printf_divagl("Current version - v0.8.1.0 (Build date: " __DATE__ ")");
        printf_divagl("Attach");
        divagl_main();
        break;
    }
    return true;
}

extern "C" __declspec(dllexport) LPCWSTR GetPluginName(void) {
    return L"DivaGL";
}

extern "C" __declspec(dllexport) LPCWSTR GetPluginDescription(void) {
    return L"DivaGL Plugin by korenkonder";
}

extern "C" __declspec(dllexport) LPCWSTR GetBuildDate(void) {
    return L"v0.8.1.0 (Build date: " __DATE__ ")";
}

static std::wstring GetDirPath() {
    wchar_t dll_file_path[MAX_PATH];
    GetModuleFileNameW((HMODULE)dll_handle, dll_file_path, MAX_PATH);

    wchar_t* dll_file_name = wcsrchr(dll_file_path, '\\');
    if (!dll_file_name)
        dll_file_name = wcsrchr(dll_file_path, '/');

    if (!dll_file_name)
        return L"";

    WCHAR buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    return std::wstring(dll_file_path, dll_file_name - dll_file_path);
}

PluginConfig::PluginConfigOption config[] = {
    {
        PluginConfig::CONFIG_BOOLEAN,
        new PluginConfig::PluginConfigBooleanData {
            L"reflect_full",
            L"general",
            CONFIG_FILE,
            L"Full Reflect",
            L"Enables Full Reflect for PVs from X Pack (MPFX).",
            false,
            false,
        }
    },
    {
        PluginConfig::CONFIG_NUMERIC,
        new PluginConfig::PluginConfigNumericData {
            L"reflect_res_scale",
            L"general",
            CONFIG_FILE,
            L"Reflect Resolution Scale",
            L"Sets resolution for Full Reflect as a percentage relative to the Internal Resolution values.\nImportant note! Scale can't go lower than 256x144 or Internal Resolution.",
            100,
            25,
            100,
        }
    },
    {
        PluginConfig::CONFIG_BOOLEAN,
        new PluginConfig::PluginConfigBooleanData {
            L"shared_storage_uniform_buffer",
            L"experimentals",
            CONFIG_FILE,
            L"Shared Storage/Uniform Buffer",
            L"May be useful for running AFT via Mesa or on Apple devices\nor when driver doesn't support OpenGL 4.3.",
            false,
            false,
        }
    },
    {
        PluginConfig::CONFIG_BOOLEAN,
        new PluginConfig::PluginConfigBooleanData {
            L"task_movie_player_no_interop",
            L"experimentals",
            CONFIG_FILE,
            L"TaskMovie Player No Interop",
            L"Should enable video playback if WGL_NV_DX_interop2 isn't supported.",
            false,
            false,
        }
    },
    {
        PluginConfig::CONFIG_BOOLEAN,
        new PluginConfig::PluginConfigBooleanData {
            L"texture_skinning_buffer",
            L"experimentals",
            CONFIG_FILE,
            L"Texture Skinning Buffer",
            L"If Shared Storage/Uniform Buffer isn't working for you.\nWorks only when driver doesn't support OpenGL 4.3.",
            false,
            false,
        }
    },
};

extern "C" __declspec(dllexport) PluginConfig::PluginConfigArray GetPluginOptions(void) {
    return PluginConfig::PluginConfigArray{ _countof(config), config };
}
