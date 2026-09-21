#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08071f44
/* match-compiler: old_agbcc */
// Find the first of *gData_030040C4 consecutive 0x28-byte records at *gData_030040E4
// whose +0x16 flag is set and whose +0x18 word equals `a`. The countdown is written
// `i != -1` (not `i >= 0`): retail materialises -1 once (`movs r0,#1; negs r0,r0`) and
// then compares the counter against a *register* holding it at both the entry guard and
// the back edge (`cmp r2,r0` / `cmp r2,r4`); `i >= 0` makes agbcc emit `cmp #0` plus a
// different loop shape (18/64).
// The two addresses MUST come from data_symbols.s: they are 0x20 apart, and with plain
// literals agbcc substitutes the second pool load with `subs r0, #0x20` (60 bytes,
// size mismatch). As symbols it emits two independent pool words like retail.
struct Unk71E84 *sub_08071F44(s32 a)
{
    struct Unk71E84 *p = *(struct Unk71E84 **)gData_030040E4;
    s32 i;

    for (i = *(u8 *)gData_030040C4 - 1; i != -1; i--)
    {
        if (p->unk16 != 0 && p->unk18 == a)
            return p;
        p++;
    }
    return 0;
}

