#include "global.h"

// @ 0x08062cc8
void sub_08062CC8(u32 idx, u8 *out)
{
    register u32 shifted asm("r0") = idx << 24;
    register u32 base asm("r2") = 0x05000200;
    u16 color;

    asm("" : "+r"(base));
    shifted = shifted >> 23;
    shifted = shifted + base;
    color = *(u16 *)shifted;
    out[0] = color & 0x1F;
    out[1] = (color & 0x3E0) >> 5;
    out[2] = (color & 0x7C00) >> 10;
}
