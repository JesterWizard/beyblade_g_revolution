#include "global.h"

// @ 0x080620d4
// 37/72 (walker form; plain `p[i]` indexing floors at 11/72). Offset every entry of the
// pointer array at a->unk0C by (dx, dy) in 8.8 fixed point, and snapshot the first
// entry's position into a->unk10/unk14 once.
//
// Retail walks with TWO registers off the same base:
//   r5 = a->unk0C (kept for the snapshot), r3 = r5 (the walker), r7 = dx << 8, r6 = dy << 8
//   loop: ldr r1,[r3]; cmp r1,#0; beq end; ...; cmp r2,#0; bne skip;
//         ldr r0,[r5]; ldr r1,[r0,#8]; str r1,[r4,#0x10]; ...
// So the source needs both a base pointer and a separate incrementing walker:
//   for (i = 0, q = p; i <= 0x7F; i++, q++)
// With `p[i]` for both uses agbcc unswitches the `i == 0` arm, hoists the `p[0] == 0`
// test ahead of the loop and keeps dx<<8 in ip (11/72). With the walker it is 37/72 but
// the loop is still 4 bytes off (size mismatch) and the snapshot scheduling differs.
// Also tried a do-while form with the counter at the bottom (19/72, same size).
// Next: permuter.
void sub_080620D4(struct Unk62044 *a, s32 dx, s32 dy)
{
    struct Unk620D4Entry **p;
    struct Unk620D4Entry **q;
    s32 i;

    if (a == 0)
        return;
    p = a->unk0C;
    if (p == 0)
        return;
    for (i = 0, q = p; i <= 0x7F; i++, q++)
    {
        if (*q == 0)
            break;
        (*q)->unk08 += dx << 8;
        (*q)->unk0C += dy << 8;
        if (i == 0)
        {
            a->unk10 = p[0]->unk08;
            a->unk14 = p[0]->unk0C;
        }
    }
}
