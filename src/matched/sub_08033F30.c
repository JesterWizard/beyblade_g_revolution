#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08033f30
/* match-compiler: old_agbcc */
// Store the signed value and raise the flag, then publish the damping word: 0 for a
// non-negative value, 0x800 for a negative one. The polarity of the if/else is
// observable -- retail's `blt` jumps *over* the `movs r0,#0` into the 0x800 block,
// so the non-negative case is the inline arm (`if (b >= 0) ... else ...`).
// +0x1C is written as a byte here but read as an inner pointer by sub_08033D90,
// hence union Unk33F30Unk1C.
void sub_08033F30(struct Unk33F30 *a, s32 b)
{
    a->unk14 = b;
    a->unk1C.flag = 1;
    if (b >= 0)
        a->unk18 = 0;
    else
        a->unk18 = 0x800;
}

