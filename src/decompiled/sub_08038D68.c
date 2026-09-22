#include "global.h"

void sub_08038D68(struct Unk38D68 *a)
{
    struct Unk38D68 *base;
    void **table;
    s32 value;
    s32 half;

    base = a;
    table = (void **)gUnk_030003E0;
    value = TextMeasureWidth(
        table[base->unk2FC + base->unk300],
        (const void *)0x080B7258,
        8,
        2);
    half = value >> 1;
    base->unk28C->unk08 = (0x5C - half) << 8;
    base->unk290->unk08 = (half + 0x8C) << 8;
    base->unk28C->unk0C = (base->unk300 << 11) + 0x7800;
    base->unk290->unk0C = (base->unk300 << 11) + 0x7800;
}
