#include "global.h"

// @ 0x080447cc
void sub_080447CC(void)
{
    register struct Unk447CC *p asm("r0");
    register void *v asm("r1");

    p = sub_08043B58();
    if (p != 0)
    {
        v = p->unk18;
        if (v != 0)
            sub_08059DC8(0);
    }
}

