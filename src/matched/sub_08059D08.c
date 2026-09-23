#include "global.h"

// @ 0x08059d08
void sub_08059D08(struct Unk59D08 *a)
{
    void *z;
    void *cb;

    if (a != 0)
    {
        cb = a->unk08;
        if (cb != 0)
            _08073C44(a, cb);
        z = 0;
        a->unk00 = z;
        a->unk04 = z;
        a->unk08 = z;
        a->unk14 = z;
        if (a->unk0C != 0)
        {
            HeapFree(a->unk0C);
            a->unk0C = z;
        }
    }
}

