#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080428c4
/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

// @ 0x080428c4
// If bit 0x2000 of unk1808 is clear, zero the two bytes of the 0x03000538 object.
void sub_080428C4(void)
{
    u32 v = gMainWorkPtr->unk1808 & 0x2000;

    if (v != 0)
        return;
    gUnk_03000538->unk00 = v;
    gUnk_03000538->unk01 = v;
}

