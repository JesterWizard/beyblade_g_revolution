#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08035020
/* match-compiler: old_agbcc */
// Reset the +0x2CC state word to "7" (keeping the +0x2FC payload a caller passes
// only on a real transition) and invalidate the +0x2F8 companion, except in the
// three "leave alone" states. Retail's comparison chain is
// `cmp #2; blt / cmp #3; ble / cmp #6; beq` — SIGNED branches, so the switch
// subject must be s32: with the u32 field agbcc emits blo/bls instead of blt/ble.
void sub_08035020(struct Unk346C0 *a, u32 b)
{
    switch ((s32)a->unk2CC)
    {
    case 2:
    case 3:
    case 6:
        break;
    default:
        if (a->unk2CC != 7)
        {
            a->unk2CC = 7;
            a->unk2FC = b;
        }
        a->unk2F8 = -1;
        break;
    }
}

