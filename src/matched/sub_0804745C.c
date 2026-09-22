#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0804745c
#include "global.h"

// @ 0x0804745c
void sub_0804745C(void)
{
    struct Unk473F8 **slot;
    s32 i;
    struct Unk474ACSlot *p;

    if (gUnk_03000630 != 0)
    {
        i = 0;
        slot = &gUnk_03000630;
        do
        {
            p = (*slot)->unk00[i];
            if (p != 0)
            {
                sub_0806FE84(p);
                (*slot)->unk00[i] = 0;
            }
            i++;
        } while (i <= 0xF);
    }
    if (gUnk_03000638 != 0)
    {
        sub_0806A434(gUnk_03000638);
        gUnk_03000638 = 0;
    }
    gUnk_03000630 = 0;
}

