#include "global.h"

// @ 0x08062640
void sub_08062640(struct Unk62634 *a)
{
    s32 v;

    if (a == 0)
        return;
    v = a->unk20;
    if (v > 0)
    {
        a->unk20 = v - 1;
        return;
    }
    v = a->unk1C;
    if (v > -1)
    {
        v--;
        a->unk1C = v;
        if (v == -1)
        {
            _08073C44(a, (void *)a->unk18);
            sub_08062684(a);
            return;
        }
    }
    _08073C44(a, (void *)a->unk18);
}

