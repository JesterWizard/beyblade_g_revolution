#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08038d68
void sub_08038D68(struct Unk38D68 *arg0) {
    u32 temp_r0;

    temp_r0 = TextMeasureWidth(*(gUnk_030003E0 + ((arg0->unk2FC + arg0->unk300) * 4)), 0x080B7258, 8, 2) >> 1;
    arg0->unk28C->unk08 = (s32) ((0x5C - temp_r0) << 8);
    arg0->unk290->unk08 = (s32) ((temp_r0 + 0x8C) << 8);
    arg0->unk28C->unk0C = (s32) ((arg0->unk300 << 0xB) + 0x7800);
    arg0->unk290->unk0C = (s32) ((arg0->unk300 << 0xB) + 0x7800);
}

