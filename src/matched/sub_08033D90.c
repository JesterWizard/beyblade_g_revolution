#include "global.h"

// @ 0x08033d90
void sub_08033D90(struct Unk33F30 *a)
{
    u32 idx;

    idx = RandRange(a->unk1C.p->unk2C);
    if (a->unk1C.p->unk30 != 0 && a->unk1C.p->unk30[idx] != 0)
    {
        a->unk08 = idx;
        sub_08035878((struct Unk35878 *)&a->unk0C, (u32)a->unk1C.p->unk30[idx], a->unk00, a->unk04);
        a->unk09 = 1;
        a->unk0A = 1;
    }
}

