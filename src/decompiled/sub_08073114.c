#include "global.h"

// @ 0x08073114
// 18/112 same-structure (108 bytes: 4 short of retail's 112). This is the "remove
// one object from the battle-object table" twin of sub_0807309C (which matches).
// retail: push {r4,r5,r6,lr}; r3=a; r0=&table -> ldr r1,[r0]; movs r5,#0 (i);
// r0=&count -> adds r2,r0,#0; ldrb r0,[r2]; cmp r5,r0; bcs after; r6=&live;
// r4=table; loop r1=[r4]; r0=[r1]; cmp r0,r3; bl sub_0806A434; *r4=0; live--;
// next: r4+=4; r5+=1; ldrb r0,[r2]; cmp r5,r0; bcc loop; after: ldr r0,=&count
// again; if (i == count) sub_08067B98(0x083D2690).
//
// Reproduced: everything except two sequences.
//   1. `i = 0` must be assigned BEFORE `count = ...` (that fixes the scheduling:
//      retail has `movs r5,#0` at +0x0c, before the count-address load).
//   2. retail keeps `a` in r3 and materialises the count address as
//      `ldr r0,=gBtlObjTableCount; adds r2,r0,#0` (2 bytes more than loading
//      straight into r2), and the loop reloads *count from r2 each test, so the
//      address is a retained pointer but the load is not hoisted (the body calls
//      sub_0806A434).
// The residual diff is the table pseudo's register: agbcc coalesces the address
// pseudo and the loaded value into r0 (`ldr r0,=gBtlObjTable; ldr r0,[r0]`), retail
// keeps the value in r1 (`ldr r1,[r0]`). With `i = 0` first agbcc emits exactly
// retail's schedule but still picks r0 for the value.
//
// Things that did NOT work (all 108 bytes, 16-18/112):
//   - `u8 count = *(u8 *)gBtlObjTableCount;` local (agbcc hoists the load, so the
//     bottom test stops reloading, and the loop shape changes),
//   - `while (i < *(u8 *)gBtlObjTableCount)` inline (folds the address into
//     `adds r0,#4` off the table literal and moves `a` to r2),
//   - for-loop / do-while / pointer-walk (`slot++`) forms,
//   - all 6 declaration orders of table/count/i.
// Next: permuter (register-only miss), or find a source shape that keeps the
// loaded table value out of the address pseudo's register.
void BtlObjTableRemove(void *a)
{
    struct BtlObj **table;
    u8 *count;
    u32 i;

    table = *(struct BtlObj ***)gBtlObjTable;
    if (table == 0)
        return;

    i = 0;
    count = (u8 *)gBtlObjTableCount;
    while (i < *count)
    {
        if (table[i] != 0 && table[i]->next == a)
        {
            HeapFree(table[i]);
            table[i] = 0;
            (*(u8 *)gBtlObjLiveCount)--;
            break;
        }
        i++;
    }

    if (i == *(u8 *)gBtlObjTableCount)
        DebugPrint((void *)0x083D2690);
}
