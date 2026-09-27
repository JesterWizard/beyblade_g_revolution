#include "global.h"
#include "ram_map.h"

void sub_08038D68(struct Unk38D68 *a)
{
    void **table;
    s32 *sel;
    u32 width;

    table = gData_030003E0;
    sel = &a->unk300;
    width = TextMeasureWidth(table[a->unk2FC + *sel], gData_080B7258, 8, 2);
    a->unk28C->unk08 = (0x5C - ((u32)width >> 1)) << 8;
    a->unk290->unk08 = (((u32)width >> 1) + 0x8C) << 8;
    a->unk28C->unk0C = (*sel << 11) + 0x7800;
    a->unk290->unk0C = (*sel << 11) + 0x7800;
}
