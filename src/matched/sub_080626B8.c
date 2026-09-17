#include "global.h"

// @ 0x080626b8
void sub_080626B8(struct Unk626B8 *a, u32 v)
{
    u32 i;
    u32 *p;

    i = 0;
    p = a->unk04;
    while (1)
    {
        if (*p == 0)
        {
            *p = v;
            break;
        }
        p++;
        i++;
        if (i >= a->unk08)
            break;
    }
}

