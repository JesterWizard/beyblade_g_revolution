#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08035258
/* match-compiler: old_agbcc */
// Stops animation block `type` (0..2) if its active bit in unk2C5 is set:
// notifies sub_08038638, releases the block and clears the bit.
void BattleAnimStop(struct Unk35258 *a, u32 b)
{
    u8 type = b;

    switch (type)
    {
    case 0:
        if (a->unk2C5 & 1)
        {
            PaletteSlotRefRelease(a->unk1C.unk3A >> 1);
            SceneObjFreeResources(&a->unk1C);
            a->unk2B0 = 0;
            a->unk2B4 = 0;
            a->unk2C5 &= ~1;
        }
        break;
    case 1:
        if (a->unk2C5 & 2)
        {
            PaletteSlotRefRelease(a->unkF8.unk3A >> 1);
            SceneObjFreeResources(&a->unkF8);
            a->unk2C5 &= ~2;
        }
        break;
    case 2:
        if (a->unk2C5 & 4)
        {
            PaletteSlotRefRelease(a->unk1D4.unk3A >> 1);
            SceneObjFreeResources(&a->unk1D4);
            a->unk2C5 &= ~4;
        }
        break;
    }
}

