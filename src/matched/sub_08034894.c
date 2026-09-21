#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08034894
/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08034894
// Copy the three shadow scroll values into the +0x300..+0x304 working words when
// unk30C is clear, otherwise zero the same three. Plain `if/else` with the three
// stores spelled out in each arm matches; factoring the shared trailing store
// through a temporary makes agbcc re-order the pool and the tail (75/84).
void sub_08034894(struct Unk346C0 *a)
{
    if (a->unk30C == 0)
    {
        a->unk302 = *(u16 *)0x03003F60;
        a->unk300 = *(u16 *)0x03004060;
        a->unk304 = *(u16 *)0x0300406C;
    }
    else
    {
        a->unk302 = 0;
        a->unk300 = 0;
        a->unk304 = 0;
    }
}

