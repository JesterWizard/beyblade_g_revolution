#include "global.h"

// @ 0x08041980
void sub_08041980(void)
{
    struct Actor **p;
    s32 n;
    struct Actor *z;

    p = (struct Actor **)gUnk_03000480;
    z = 0;
    n = 31;
    do
    {
        if (*p != 0)
            SceneObjFreeResources(*p);
        *p = z;
        p++;
        n--;
    } while (n >= 0);
    *(u16 *)gUnk_03000504 = 0;
}

