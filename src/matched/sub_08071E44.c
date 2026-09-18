#include "global.h"

// @ 0x08071e44
void sub_08071E44(struct Unk71E84 *p, void *a, s16 *idx)
{
    register s32 val asm("r4");
    s32 zero;
    s32 one;
    s32 offset;

    offset = *idx;
    offset = offset << 2;
    offset = offset + (s32)a;
    val = *(s32 *)offset;
    zero = 0;
    one = 1;
    p->unk16 = one;
    p->unk00 = val;
    p->unk14 = zero;
    p->unk17 = 0;
    p->unk10 = 0x100;
    val += 0x10;
    p->unk04 = val;
    p->unk08 = **(s32 **)0x030000C4;
    p->unk0C = zero;
    p->unk1C = a;
    p->unk20 = idx;
    p->unk24 = one;
}
