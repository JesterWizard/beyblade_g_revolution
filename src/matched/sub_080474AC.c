#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080474ac
// Per-frame update of the gData_03000630 sparkle pool: count unk44 down to
// re-arm unk40 with a random delay, then count unk40 down, scattering the 16
// sprites randomly each frame and parking them off-screen when it expires.
void sub_080474AC(void)
{
    s32 i;

    if (gData_03000198->unk1825 == 0 || gData_03000630 == NULL || (gData_03000198->unk1808 & 1) == 0)
        return;
    if (gData_03000630->unk44 > 0 && gData_03000198->unk1827 != 0)
    {
        if (--gData_03000630->unk44 == 0)
            gData_03000630->unk40 = (RandRange(0x1E) + 0x1E) << 6;
        return;
    }
    if (gData_03000630->unk40 > 0 && gData_03000198->unk1827 != 0)
    {
        if (--gData_03000630->unk40 == 0)
        {
            gData_03000630->unk44 = 0xE1 << 5;
            for (i = 0; i <= 0x0F; i++)
            {
                gData_03000630->unk00[i]->unk08 = -0x4000;
                gData_03000630->unk00[i]->unk0C = -0x4000;
            }
        }
        else
        {
            for (i = 0; i <= 0x0F; i++)
            {
                gData_03000630->unk00[i]->unk08 = RandRange(0xE8) << 8;
                gData_03000630->unk00[i]->unk0C = RandRange(0x98) << 8;
                gData_03000630->unk00[i]->unk18 = RandRange(4);
            }
        }
    }
}

