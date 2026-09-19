#include "global.h"

// @ 0x080712cc
void sub_080712CC(struct Unk712CC *a, u8 v)
{
    struct Unk705DC *p;
    s32 n;

    p = a->unk14;
    n = a->unk1C;
    n = n - 1;
    if (n != -1)
    {
        do
        {
            sub_080705A4(p, v);
            p = p->unk04;
            n = n - 1;
        } while (n != -1);
    }
    a->unk0E = v;
}

