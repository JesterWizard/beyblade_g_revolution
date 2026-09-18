#include "global.h"

// @ 0x08041980
void sub_08041980(void)
{
    struct Unk68574 **p;
    s32 n;
    struct Unk68574 *z;

    p = (struct Unk68574 **)gUnk_03000480;
    z = 0;
    n = 31;
    do
    {
        if (*p != 0)
            sub_08068808(*p);
        *p = z;
        p++;
        n--;
    } while (n >= 0);
    *(u16 *)gUnk_03000504 = 0;
}

