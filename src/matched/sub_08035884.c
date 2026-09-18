#include "global.h"

// @ 0x08035884
void sub_08035884(struct Unk35878 *a)
{
    struct Unk35878 *p;
    s32 v;
    s32 lo;
    s32 hi;

    p = (struct Unk35878 *)a->unk04;
    v = a->unk00;
    if (p != 0)
    {
        goto check;
        do
        {
            lo = p->unk00;
            hi = lo + p->unk04;
            if (lo == v || lo < 0 || (v >= lo && v < hi))
            {
                if (p->unk08 != 0)
                    _08073C4C((void *)a->unk08, (void *)a->unk0C, p->unk0C, (void *)p->unk08);
            }
            p++;
        check:
            ;
        } while (p->unk08 != 0);
    }
    a->unk00++;
}

