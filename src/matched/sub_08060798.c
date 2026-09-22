#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08060798
#include "global.h"

// @ 0x08060798
void sub_08060798(void)
{
    void *p;

    p = *(void **)gUnk_03000754;
    if (p != 0)
    {
        sub_0806A434(p);
        *(void **)gUnk_03000754 = 0;
        gUnk_03000758 = 0;
    }
}

