#include "global.h"

// @ 0x080312b0
void sub_080312B0(struct Unk312EC *a, struct Unk705DC *b, u8 c, s32 d)
{
    if (a->unk08 == 0 && b != NULL)
    {
        u16 val = b->unk14;
        u8 shifted = val >> 0xC;
        a->unk00 = c;
        a->unk01 = shifted;
        a->unk04 = d;
        a->unk0C = b;
        a->unk08 = 1;
    }
}
