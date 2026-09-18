#include "global.h"

// @ 0x0802b95c
void *sub_0802B95C(void *a)
{
    struct Unk2B95C *p;
    struct Unk2B95C *q;

    p = sub_0802B994();
    if (p != 0)
        goto check;
    return 0;
found:
    return q;
check:
    if (p->unk04 == 0)
        return 0;
    q = p;
    do
    {
        if (sub_08073440(q->unk04, a) == 0)
            goto found;
        q++;
    } while (q->unk04 != 0);
    return 0;
}

