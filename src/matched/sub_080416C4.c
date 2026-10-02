#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080416c4
/* match-compiler: old_agbcc */
// Build the four HUD digit/bar sprites from the descriptor at a->unk248 and
// enable the matching BG layers.
void HudBuildDigitSprites(struct MenuState *a)
{
    struct Unk4109CInput *desc;
    u16 dispFlags;
    s32 i;
    u8 *walk;
    void *src;

    desc = a->unk248;
    dispFlags = 0;
    HeapFreeSlots8((struct Unk41394 *)a);
    BgScrollReset();
    for (i = 0, walk = (u8 *)a; i <= 3; i++)
    {
        src = desc->unk30[i];
        if (src != NULL)
        {
            a->unk220[i] = Lz77ImageBlit(walk, i, src, 0, 0);
            dispFlags |= gData_080908B4[i];
        }
        walk += 0x88;
    }
    if (desc->unk40 != NULL)
        BgPaletteLoad(desc->unk40);
    if (desc->unk44 != NULL)
        ObjPaletteLoad(desc->unk44);
    VBlankIntrWait();
    REG_DISPCNT = dispFlags | 0x1040;
    BgSetPriorities(0, 1, 2, 3);
}

