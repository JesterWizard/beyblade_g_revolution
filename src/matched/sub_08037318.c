#include "global.h"

// @ 0x08037318
void sub_08037318(struct Unk346C0 *a, u32 index_arg)
{
    u8 index;
    register u32 r1 asm("r1");
    register u32 r0 asm("r0");
    register u32 r5 asm("r5");
    struct Unk002A0Record *record;

    index = index_arg;
    a->unk28C = sub_0806FDD0(0);
    r1 = (u32)&gUnk_030002A0;
    asm("" : "+r"(r1));
    r0 = 0x2C;
    r5 = index;
    r5 *= r0;
    r5 += r1;
    record = (struct Unk002A0Record *)r5;
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

