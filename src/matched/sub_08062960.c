#include "global.h"

// @ 0x08062960
void sub_08062960(void)
{
    void *p;

    p = *(void **)gUnk_030007A0;
    if (p != 0)
    {
        sub_0806A434(p);
        *(void **)gUnk_030007A0 = 0;
    }
    *(void **)gUnk_030007A4 = 0;
}

