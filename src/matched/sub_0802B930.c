#include "global.h"

// @ 0x0802b930
s32 sub_0802B930(s32 a)
{
    s32 i;
    struct Unk75AB8 *p;

    i = 0;
    p = (struct Unk75AB8 *)0x08075AB8;
    for (; i <= 0x3D; p++, i++)
    {
        if (p->unk04 == a)
            return p->unk00;
    }
    return -1;
}

