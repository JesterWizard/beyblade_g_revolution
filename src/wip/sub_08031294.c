#include "global.h"

// @ 0x08031294
void sub_08031294(struct Unk312EC *a)
{
    u8 r1;
    u8 r2;

    r1 = 0xFF;
    r2 = *(u8 *)&a->unk00;
    r2 |= r1;
    *(u8 *)&a->unk00 = r2;
    r2 = *(u8 *)&a->unk01;
    r1 |= r2;
    *(u8 *)&a->unk01 = r1;
    a->unk04 = -1;
    r1 = 0;
    a->unk0C = 0;
    a->unk08 = r1;
}
