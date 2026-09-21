#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08037318
void sub_08037318(struct Unk346C0 *a, u32 index_arg)
{
    u8 index;
    u32 r1;
    u32 r0;
    u32 r5;
    struct Unk002A0Record *record;
    void *p;
    struct Unk705DC **slot;

    index = (u8)index_arg;
    p = sub_0806FDD0(0);
    slot = &a->unk28C;
    *slot = p;
    r1 = (u32)gData_030002A0;
    r0 = 0x2C;
    r5 = index;
    r5 *= r0;
    r5 += r1;
    record = (struct Unk002A0Record *)r5;
    sub_0806FF58(
        *slot,
        sub_08042B28(record->unk00),
        0xFC00,
        0x2E00,
        0,
        0,
        0,
        0);
    sub_08038580(sub_08042B50(record->unk00), 0x0E);
    sub_080705DC(*slot, 0x0E);
}

