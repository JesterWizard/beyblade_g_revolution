#include "global.h"

// @ 0x080346c0
void sub_080346C0(struct Unk346C0 *a, u32 b, u32 c, u32 d, u32 e)
{
    struct Unk346C0Inner *p;

    p = a->unk00;
    if (p != 0)
    {
        p->unk30 = b;
        p->unk34 = c;
        p->unk4C = d;
        p->unk48 = e;
    }
}

