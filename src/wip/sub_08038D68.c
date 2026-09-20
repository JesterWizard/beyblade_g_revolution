#include "global.h"

void sub_08038D68(struct Unk38D68 *a)
{
    register struct Unk38D68 *base asm("r5");
    register void **table asm("r2");
    s32 value;
    s32 half;

    base = a;
    table = (void **)gUnk_030003E0;
    value = sub_08073988(
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
