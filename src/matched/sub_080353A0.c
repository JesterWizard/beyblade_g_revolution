#include "global.h"

// @ 0x080353a0
/* match-compiler: old_agbcc */
void sub_080353A0(struct Unk35258 *a)
{
    if ((1 & a->unk2C5) != 0)
    {
        a->unk2B0 += a->unk2B4;
        sub_080686D8(&a->unk1C);
        sub_08035468(
            &a->unk1C,
            a->unk00->unk0C,
            a->unk00->unk10,
            a->unk00->unk14,
            0,
            0,
            a->unk2B0 << 8);
    }
    if ((4 & a->unk2C5) != 0)
    {
        sub_080686D8(&a->unk1D4);
        sub_08035468(&a->unk1D4, a->unk2E4, a->unk2E8, a->unk2EC, 0, 0, 0);
    }
    if ((2 & a->unk2C5) != 0)
    {
        sub_080686D8(&a->unkF8);
        sub_08035468(
            &a->unkF8,
            a->unk00->unk0C,
            a->unk00->unk10,
            a->unk00->unk14,
            0,
            0x2000,
            a->unk00->unk52 << 8);
    }
}

