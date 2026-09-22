#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08062e88
void sub_08062CC8(u32 idx, u8 *out);
void sub_08062CF4(u32 idx, struct Unk62D50 *rgb);

// Twin of sub_08062D80. Reads with sub_08062CC8 and writes with sub_08062CF4.
void sub_08062E88(u8 a, u8 b, u8 c, u8 d)
{
    struct Unk62D50 rgb;
    s16 i;
    u8 idx;
    s32 v0;

    if (a >= b)
        goto done;
    if (c == 0)
        goto add;
    if (c == 1)
        goto sub;
    goto done;

add:
    for (i = a; i <= b; i++)
    {
        idx = (u8)i;
        sub_08062CC8(idx, (u8 *)&rgb);
        v0 = rgb.unk00 + d;
        rgb.unk00 = v0;
        rgb.unk01 = d + rgb.unk01;
        rgb.unk02 = d + rgb.unk02;
        v0 <<= 24;
        v0 >>= 24;
        if (v0 > 31)
            rgb.unk00 = 31;
        if ((s8)rgb.unk01 > 31)
            rgb.unk01 = 31;
        if ((s8)rgb.unk02 > 31)
            rgb.unk02 = 31;
        sub_08062CF4(idx, &rgb);
    }
    goto done;

sub:
    for (i = a; i <= b; i++)
    {
        idx = (u8)i;
        sub_08062CC8(idx, (u8 *)&rgb);
        v0 = rgb.unk00 - d;
        rgb.unk00 = v0;
        rgb.unk01 = rgb.unk01 - d;
        rgb.unk02 = rgb.unk02 - d;
        v0 <<= 24;
        if (v0 < 0)
            rgb.unk00 = 0;
        if (((s32)rgb.unk01 << 24) < 0)
            rgb.unk01 = 0;
        if (((s32)rgb.unk02 << 24) < 0)
            rgb.unk02 = 0;
        sub_08062CF4(idx, &rgb);
    }

done:
    return;
}

