#include "global.h"

// @ 0x080312b0
void sub_080312B0(struct Unk312EC *a, struct Unk705DC *b, u8 c, s32 d)
{
    register u16 val asm("r5");
    register u32 shifted asm("r0");

    if (a->unk08 == 0 && b != NULL)
    {
        val = b->unk14;
        shifted = val >> 0xC;
        a->unk00 = c;
        a->unk01 = shifted;
        a->unk04 = d;
        a->unk0C = b;
        a->unk08 = 1;
    }
}

