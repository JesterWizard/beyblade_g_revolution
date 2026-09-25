#include "global.h"

// @ 0x08031094
void sub_08031094(struct Unk346A8 *a, s32 b, s32 c, struct Unk310F0b *d)
{
    s32 v;

    v = ScaleRatio(b >> 8, c >> 8, 36);
    if (d == 0)
        return;
    if (a->unk04 != 0 && a->unk04->unk28 != 0 && a->unk04->unk28->unk21 <= 0)
    {
        sub_080346A8(a, 0);
        d->shown = 36;
        return;
    }
    if ((s16)v != -1)
    {
        sub_080346A8(a, v);
        d->shown = 36 - v;
    }
}

