/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../../KKdLib/default.hpp"
#include "../wrap.hpp"

struct gl_state_struct;
struct p_gl_rend_state;

namespace GL {
    enum BufferUsage {
        BUFFER_USAGE_STREAM = 0,
        BUFFER_USAGE_STATIC,
        BUFFER_USAGE_DYNAMIC,
    };

    inline GLenum BufferUsageToGLenum(const BufferUsage usage) {
        if (usage == BUFFER_USAGE_STREAM)
            return GL_STREAM_DRAW;
        else if (usage == BUFFER_USAGE_STATIC)
            return GL_STATIC_DRAW;
        else if (usage == BUFFER_USAGE_DYNAMIC)
            return GL_DYNAMIC_DRAW;
        else
            return GL_NONE;
    }

    inline bool BufferUsageCheck(const BufferUsage usage, bool with_static = true) {
        return usage == BUFFER_USAGE_STREAM || with_static && usage == BUFFER_USAGE_STATIC
            || usage == BUFFER_USAGE_DYNAMIC;
    }
}
