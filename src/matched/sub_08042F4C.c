#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08042f4c
#include "global.h"
#include "data_symbols.h"

void sub_08042F4C(s32 expBase, s32 strengthBase, s32 bladeId, s32 gained)
{
    struct Unk42E78 *row;
    s32 old;
    s32 scaled;

    row = (struct Unk42E78 *)sub_08042E78((u32)bladeId);
    if (row != 0)
    {
        old = row->bitBeastExp;
        scaled = 0x64 * gained;
        row->bitBeastExp = expBase + scaled;
        scaled = strengthBase + gained;
        if (scaled > 0)
            strengthBase = scaled;
        row->strength = (u8)strengthBase;
        DebugPrint((void *)gData_083A2CF4, (void *)gData_083A2D28, bladeId, old, row->bitBeastExp, gained);
    }
}

