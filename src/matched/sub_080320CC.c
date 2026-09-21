#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080320cc
/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

// @ 0x080320cc
// Clamp unk0C of each of the 4 Unk002A0 records up to 0 (negative -> 0).
void sub_080320CC(void)
{
    if (gUnk_030002A0.records[0].unk0C < 0)
        gUnk_030002A0.records[0].unk0C = 0;
    if (gUnk_030002A0.records[1].unk0C < 0)
        gUnk_030002A0.records[1].unk0C = 0;
    if (gUnk_030002A0.records[2].unk0C < 0)
        gUnk_030002A0.records[2].unk0C = 0;
    if (gUnk_030002A0.records[3].unk0C < 0)
        gUnk_030002A0.records[3].unk0C = 0;
}

