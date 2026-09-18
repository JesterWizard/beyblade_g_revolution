#include "global.h"

// @ 0x0806f8c4
void sub_0806F8C4(struct Unk6F8C4 *a)
{
    struct Unk6F8C4 *p;
    struct Unk6F8C4 *n;

    p = a;
    if (p == 0)
        return;
    n = p->unk00;
    if (n != 0)
        sub_08067B98((void *)0x083D2074);
    do
    {
        if (n != 0)
        {
            if (n->unk04 != p)
                sub_08067B98((void *)0x083D2090);
        }
        if (p->unk00 != n)
            sub_08067B98((void *)0x083D20AC);
        n = p;
        p = p->unk04;
    } while (p != 0);
}

