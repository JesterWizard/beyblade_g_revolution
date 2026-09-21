/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08043b58
// 38/54 (compiled 56 bytes). Look up `key` (the word at gMainWorkPtr->unk1690) in the
// NULL-terminated pointer array at 0x08096794 and return the first entry whose +0 word
// matches (0 if not found). Retail: ldr r0,=0x03000198 ... ldr r2,[r0] (KEY IN r2);
// ldr r0,=0x08096794; ldr r1,[r0]; cmp r1,#0; beq ret0; adds r3,r0,#4;
// loop: ldr r0,[r1]; cmp r2,r0; bne next; adds r0,r1,#0; b done;
// next: ldm r3!,{r1}; cmp r1,#0; bne loop; ret0: movs r0,#0.
//
// Reproduced exactly except for two things:
//   1. register colouring is swapped -- agbcc puts `key` in r3 and the array walker in
//      r2; retail has key in r2 and the walker in r3.
//   2. the walker costs 4 bytes instead of 2: agbcc emits `adds r2,#4; ldr r1,[r2]`
//      where retail has the single `ldm r3!,{r1}` (i.e. retail's walker really is a
//      `*p++`, and r3 is its register).
// All 24 declaration orders of key/tbl/p/i give the identical 38/54 / 56 bytes, so this
// is not a declaration-order case. `q`/`*q++` forms (post-increment walker) collapse to
// 48 bytes and 11/54 -- they change the whole shape. Next: permuter.
// Note: the sibling sub_08043B90 (parked) walks the same table -- this array (not a
// linked list) is the shared insight.
struct Unk447CC *sub_08043B58(void)
{
    u32 key = *(u32 *)gMainWorkPtr->unk1690;
    struct Unk447CC **tbl = (struct Unk447CC **)0x08096794;
    struct Unk447CC *p;
    u32 i = 0;

    p = tbl[0];
    while (p != 0)
    {
        if (key == (u32)p->unk00)
            return p;
        p = tbl[++i];
    }
    return 0;
}
