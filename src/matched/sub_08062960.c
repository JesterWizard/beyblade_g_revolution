#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08062960
#include "global.h"

// @ 0x08062960
void sub_08062960(void)
{
    u32 p;

    p = gUnk_030007A0;
    if (p != 0)
    {
        sub_0806A434((void *)p);
        gUnk_030007A0 = 0;
    }
    gUnk_030007A4 = 0;
}

