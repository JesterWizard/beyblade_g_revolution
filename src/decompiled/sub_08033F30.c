/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08033f30
// 16/24 same-size. Retail: `cmp r1,#0; blt <0x800 block>` with the ZERO block as
// fallthrough (movs r0,#0; b end) and the 0x800 block out of line; agbcc always
// emits the 0x800 block first / inverts the branch. Only the branch layout differs.
// unk1C is a pointer in Unk33F30 (used by sub_08033D90) but retail stores a byte 1
// here, hence the (u8*)&a->unk1C store.
void sub_08033F30(struct Unk33F30 *a, s32 b)
{
    a->unk14 = b;
    *(u8 *)&a->unk1C = 1;
    if (b < 0)
        a->unk18 = 0x800;
    else
        a->unk18 = 0;
}
