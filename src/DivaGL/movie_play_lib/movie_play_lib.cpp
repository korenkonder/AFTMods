/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "movie_play_lib.hpp"

namespace MoviePlayLib {
    void(FASTCALL* trace)(const wchar_t* fmt, ...)
        = (void(FASTCALL*)(const wchar_t* fmt, ...))0x00000001404241F0;
}
