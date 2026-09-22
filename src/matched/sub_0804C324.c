#include "global.h"

// @ 0x0804c324
void sub_0804B4B4(struct Unk2F520 *a)
{
    s8 field2D5;
    s16 doubled;

    field2D5 = a->unk2D5;
    doubled = a->unk2FC;
    doubled = doubled * 2;
    BgMapSetPaletteBankRun((u16)(doubled + 5), 0xF, 4, 0x1A);
    doubled = doubled + 6;
    BgMapSetPaletteBankRun((u16)doubled, 0xF, 4, 0x1A);
    doubled = ((s32)field2D5 << 24) >> 23;
    BgMapSetPaletteBankRun((u16)(doubled + 5), 0xE, 4, 0x1A);
    doubled = doubled + 6;
    BgMapSetPaletteBankRun((u16)doubled, 0xE, 4, 0x1A);
}
