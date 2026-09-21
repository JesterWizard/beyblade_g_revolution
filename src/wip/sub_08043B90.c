#include "global.h"

// @ 0x08043b90
// 67/76 same-size (88.2%), stable across every source shape tried. Walk the
// 8-byte-stride scan table at gMainWorkPtr->unk16E0: return -1 when the table pointer is
// null, p->unk04 when the predicate matches, and 0 at the end.
// Retail's tail after the loop test is just the epilogue:
//   ...bl sub_08073440; cmp r0,#0; beq ret_unk04; adds r4,#8;
//   ldr r0,[r4]; cmp r0,#0; bne body; pop {r4}; pop {r1}; bx r1
// i.e. the final return needs NO instruction -- r0 already holds p->unk00 == 0 from the
// loop test. Neither spelling of that return reproduces it:
//   `return 0;`        -> `movs r0,#0`          (2 bytes, shifts 2 branch offsets)
//   `return p->unk00;` -> `ldr r0,[r4]` reload  (2 bytes, same)
//   `u32 v; ... return v;` with the load hoisted into the loop condition -> 80 bytes
// Every other shape (while / for / `p + 1` / `s32 r = 0` declared first) is also 67/76.
// The 67 matched bytes include the whole prologue, the -1 path, the call sequence and
// the loop; only this tail 2-byte pair is wrong.
// NOTE: do NOT replace the struct fields with data_symbols here -- retail synthesises
// 0x16E0 with `movs r1,#0xB7; lsls r1,r1,#5`, so the offset must stay a constant
// (symbol forms score 14/76).
// Next: permuter.
s32 sub_08043B90(void)
{
    struct Unk16E0 *p = gMainWorkPtr->unk16E0;

    if (p == 0)
        return -1;
    while (p->unk00 != 0)
    {
        if (sub_08073440((void *)p->unk00, gMainWorkPtr->unk16C8) == 0)
            return p->unk04;
        p++;
    }
    return 0;
}
