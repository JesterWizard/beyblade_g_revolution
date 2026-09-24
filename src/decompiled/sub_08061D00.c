#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08061d00
void sub_08061D00(u16 arg0, s32 arg1) {
    s32 temp_r4;
    void *temp_r2;

    temp_r2 = gUnk_03000798;
    temp_r4 = (temp_r2->unk5C << 0xB) + 0x06000000;
    _08073C4C(sub_0806BB38((gUnk_03000798)->unk88, arg0), (temp_r2->unk5D << 0xE) + 0x06000000, 0x20, *(s32 *)0x080BB8C0);
    _08073C4C((u16) (arg1 << 0xC) | (arg1 << 0x1C) | 0x400, temp_r4, 0x800, *(s32 *)0x080BB8BC);
}

