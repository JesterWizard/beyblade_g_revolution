#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08062d80
void BgPaletteGetRgb(u32 idx, u8 *out);
void BgPaletteSetRgb(u32 idx, struct Unk62D50 *rgb);

// Walk palette indices a..b. c == 0 adds d to each RGB byte and clamps at 31;
// c == 1 subtracts d and clamps at 0. Stores are batched before the clamps so
// the first sum stays in r1; `v0 <<= 24; v0 >>= 24` is the in-place sign extend.
void BgPaletteShiftRange(u8 a, u8 b, u8 c, u8 d)
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
        BgPaletteGetRgb(idx, (u8 *)&rgb);
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
        BgPaletteSetRgb(idx, &rgb);
    }
    goto done;

sub:
    for (i = a; i <= b; i++)
    {
        idx = (u8)i;
        BgPaletteGetRgb(idx, (u8 *)&rgb);
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
        BgPaletteSetRgb(idx, &rgb);
    }

done:
    return;
}

