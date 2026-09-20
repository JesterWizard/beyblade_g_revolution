#include "global.h"

// @ 0x080447cc
void sub_080447CC(void)
{
    struct Unk447CC *p;
    void *v;

    p = sub_08043B58();
    if (p != 0)
    {
        v = p->unk18;
        if (v != 0)
            sub_08059DC8(0, v);
    }
}

