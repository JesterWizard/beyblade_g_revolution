#include "global.h"

void sub_08037318(struct Unk346C0 *a, u32 index_arg)
{
    u8 index;
    u8 *base;
    struct Unk002A0Record *record;

    index = index_arg;
    a->unk28C = sub_0806FDD0(0);
    base = (u8 *)&gUnk_030002A0;
    record = (struct Unk002A0Record *)(base + index * 0x2C);
    sub_0806FF58(
        a->unk28C,
        sub_08042B28(record->unk00),
        0xFC00,
        0x2E00,
        0,
        0,
        0,
        0);
    sub_08038580(sub_08042B50(record->unk00), 0x0E);
    sub_080705DC(a->unk28C, 0x0E);
}
