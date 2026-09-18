#include "global.h"

// @ 0x080310f0
void sub_080310F0(struct Unk310F0a *a, struct Unk310F0b *b)
{
    s32 v;

    if (b == 0)
        return;
    if (a->unk04 == 0)
        return;
    v = sub_08031124(a->unk04->unk28->unk24, 100, 182);
    if ((s16)v != -1)
        b->unk18 = v;
}

