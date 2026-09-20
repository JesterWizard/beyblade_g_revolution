#include "global.h"

void sub_080474AC(void)
{
    register struct MainWork *main asm("r3");
    struct Unk473F8 *pool;
    struct Unk474ACSlot *slot;
    s32 i;

    main = gMainWorkPtr;
    if (main->unk1825 == 0)
        return;
    pool = gUnk_03000630;
    if (pool == 0 || (main->unk1808 & 1) == 0)
        return;

    if (pool->unk44 > 0 && main->unk1827 != 0)
    {
        pool->unk44--;
        if (pool->unk44 == 0)
        {
            pool->unk40 = (sub_080628B4(0x1E) + 0x1E) << 6;
            return;
        }
    }
    if (pool->unk40 <= 0 || main->unk1827 == 0)
        return;
    pool->unk40--;
    if (pool->unk40 == 0)
    {
        pool->unk44 = 0xE1 << 5;
        for (i = 0; i <= 0x0F; i++)
        {
            slot = pool->unk00[i];
            slot->unk08 = -0x4000;
            slot->unk0C = -0x4000;
        }
    }
    else
    {
        for (i = 0; i <= 0x0F; i++)
        {
            slot = pool->unk00[i];
            slot->unk08 = sub_080628B4(0xE8) << 8;
            slot->unk0C = sub_080628B4(0x98) << 8;
            slot->unk18 = sub_080628B4(4);
        }
    }
}
