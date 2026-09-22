#include "global.h"

// @ 0x0806a580
void *sub_0806A580(struct Unk6A580 *p, u32 n)
{
    u32 t;

    while (1)
    {
        t = n;
        n--;
        if (t == 0)
            break;
        if (p->unk04 == 0)
        {
            if (p->unk00 == 0)
                return p;
        }
        p++;
    }
    DebugPrint((void *)0x083D1B5C, n);
    return 0;
}

