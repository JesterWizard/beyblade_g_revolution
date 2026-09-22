#include "global.h"

// @ 0x08062cc8
void sub_08062CC8(u32 idx, u8 *out)
{
    u32 shifted;
    u32 base;
    u16 color;
    u32 sh;
    u32 *p;

    shifted = idx << 24;
    base = 0x05000200;
    sh = 23;
    p = &shifted;
    shifted = *p >> sh;
    shifted = shifted + base;
    color = *(u16 *)shifted;
    out[0] = (u8)(color & 0x1F);
    out[1] = (u8)((color & 0x3E0) >> 5);
    out[2] = (u8)((color & 0x7C00) >> 10);
}
