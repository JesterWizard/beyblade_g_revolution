#include "global.h"

// @ 0x08054558
void sub_08054558(void *a)
{
    struct Unk070C *p;

    p = *(struct Unk070C **)0x0300070C;
    if (p != 0)
    {
        if (a != 0)
            sub_08070AD4(&p->unk34, a, 2);
        else
            sub_08070678(&p->unk34);
    }
}

