#include "global.h"

// @ 0x08061c48
// 52/56 same-size (92.9%) -- was 36/56 with literal addresses. Decrement the
// gData_03000794 counter, bail when it goes negative, and free + clear the 8-byte slot it
// points at in the gData_03000770 table.
//
// The two table addresses MUST come from data_symbols.s. With the numeric gUnk_ macros
// agbcc re-materialises the constant base as a literal-pool load at each of the two uses
// and never needs r5 (36/56, and every following branch offset shifts). As symbols it
// emits exactly retail's shape: one `ldr r5, =gData_03000770` kept live across the call
// to sub_0806A434 and two `adds r0, r0, r5`.
//
// Remaining DIFF is a single instruction swap (4 bytes) at +0x0e:
//     retail:  str r0,[r4]; ldr r5,[pc,#36]; lsls r0,r0,#3; adds r0,r0,r5; ldr r0,[r0]
//     agbcc :  str r0,[r4]; lsls r0,r0,#3;  ldr r5,[pc,#32]; adds r0,r0,r5; ldr r0,[r0]
// i.e. the base load must be scheduled BEFORE the index shift. Tried (all 52/56 or
// worse): `tbl[i]` indexing, `(tbl + i)->unk00` pointer arithmetic, a `slot`/`tbl` local
// assigned after the decrement (41/56 -- agbcc hoists it), symbols vs literals on the
// counter. Next: permuter.
void sub_08061C48(void)
{
    s32 i;

    i = gData_03000794[0] - 1;
    if (i < 0)
        return;
    gData_03000794[0] = i;
    if (((struct Unk0770 *)gData_03000770)[i].unk00 != 0)
    {
        sub_0806A434(((struct Unk0770 *)gData_03000770)[i].unk00);
        ((struct Unk0770 *)gData_03000770)[gData_03000794[0]].unk00 = 0;
    }
}
