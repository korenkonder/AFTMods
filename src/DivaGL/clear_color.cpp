/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "clear_color.hpp"
#include "gl_rend_state.hpp"

color4u8& clear_color = *(color4u8*)0x0000000140EC57C8;

void clear_color_set_gl(p_gl_rend_state& p_gl_rend_st) {
    vec4 color = clear_color;
    p_gl_rend_st.clear_color(color.x, color.y, color.z, color.w);
}
