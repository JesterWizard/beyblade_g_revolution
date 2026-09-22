#include "global.h"

// @ 0x08071fac

void sub_08071FAC(s32 a)
{
    struct Unk71E84 *p;

    p = sub_08071F44(a);
    if (p != 0 && p->unk16 == 2)
        p->unk16 = 1;
}

