#include "global.h"

struct PalRgb
{
    s32 r : 8;
    s32 g : 8;
    s32 b : 8;
};

u32 sub_0806314C(u8 useObjPal, u8 start, u8 end, u16 *target)
{
    u32 done = 1;
    u16 *pal = (u16 *)0x05000000;
    u16 i;
    u16 last;

    if (!useObjPal)
        pal = (u16 *)0x05000200;
    for (i = start; i <= (u16)end; i++)
    {
        struct PalRgb cur;
        struct PalRgb dst;
        u16 c = pal[i];
        u16 t = target[i];

        cur.r = c & 0x1F;
        cur.g = (c & 0x3E0) >> 5;
        cur.b = (c & 0x7C00) >> 10;
        dst.r = t & 0x1F;
        dst.g = (t & 0x3E0) >> 5;
        dst.b = (t & 0x7C00) >> 10;

        if (cur.r < dst.r) { cur.r++; done = 0; }
        else if (cur.r > dst.r) { cur.r--; done = 0; }
        if (cur.g < dst.g) { cur.g++; done = 0; }
        else if (cur.g > dst.g) { cur.g--; done = 0; }
        if (cur.b < dst.b) { cur.b++; done = 0; }
        else if (cur.b > dst.b) { cur.b--; done = 0; }
        if (!done)
            pal[i] = (cur.r & 0x1F) | ((cur.g & 0x1F) << 5) | ((cur.b & 0x1F) << 10);
    }
    return done;
}
