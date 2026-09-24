#include "global.h"
#include "ram_map.h"

void sub_0804A028(struct Unk2F520 *a)
{
    u8 pal;
    u8 cur;
    s16 doubled;
    u32 tmp;
    u32 base;

    pal = *(u8 *)&a->unk2D5;
    cur = *(u8 *)&a->unk2FC;
    if (gMainWorkPtr->unk1855 == 0)
        goto low;
    tmp = (u32)cur << 24;
    tmp = (u32)((s32)tmp >> 8);
    base = 0xA0;
    base <<= 11;
    tmp += base;
    tmp >>= 16;
    TextRowSetPaletteBank(tmp, 0xF, 9, 0x14);
    tmp = (u32)pal << 24;
    tmp = (u32)((s32)tmp >> 8);
    base = 0xA0;
    base <<= 11;
    tmp += base;
    tmp >>= 16;
    TextRowSetPaletteBank(tmp, 0xE, 9, 0x14);
    goto done;
low:
    doubled = ((s32)cur << 24) >> 23;
    TextRowSetPaletteBank((u16)(doubled + 5), 0xF, 9, 0x14);
    doubled = doubled + 6;
    TextRowSetPaletteBank((u16)doubled, 0xF, 9, 0x14);
    doubled = ((s32)pal << 24) >> 23;
    TextRowSetPaletteBank((u16)(doubled + 5), 0xE, 9, 0x14);
    doubled = doubled + 6;
    TextRowSetPaletteBank((u16)doubled, 0xE, 9, 0x14);
done:
    return;
}
