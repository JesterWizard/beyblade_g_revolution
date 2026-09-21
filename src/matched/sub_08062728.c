#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08062728
/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08062728
// Zero `a->unk08` words starting at `a->unk04` (a do-while, so a zero count still
// writes one word -- matching retail, which has no entry guard).
// The zero must be its own local, initialised AFTER `i` but BEFORE the count and
// pointer: agbcc hoists `movs r3,#0` out of the loop, and only this declaration
// order makes it come before the two ldr's (`0021 0023 8268 4068` in retail).
// With the zero written inline (`*p++ = 0`) the mov lands after the loads (13/18),
// and with the zero declared first the two movs swap (16/18).
void sub_08062728(struct Unk62728 *a)
{
    u32 i = 0;
    u32 z = 0;
    u32 n = a->unk08;
    u32 *p = a->unk04;

    do
    {
        *p++ = z;
        i++;
    } while (i < n);
}

