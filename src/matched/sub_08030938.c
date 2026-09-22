#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08030938
#include "global.h"

// @ 0x08030938
// Blend two `sub_080674A0` (fixed-point multiply) results over the 0xB4 range and
// hand the pair of payload words from the inner struct to sub_080346C0.
// The `r1 = a->unk2F4` local is load-bearing: reading the field inline lets agbcc
// materialise 0x2D4 as a second `movs #0xB5; lsls #2` pair, while retail derives it
// from the 0x2D8 constant already in r1 (`subs r1, #4`). Binding the divisor to a
// named local first keeps r1 live across both struct reads and reproduces retail.
void sub_08030938(struct Unk346C0 *a)
{
    u32 r6;
    u32 r4;
    u32 r2;
    u32 r1;
    s32 r3;
    s32 r0;

    r6 = a->unk2D8;
    r4 = a->unk2D4;
    r2 = a->unk04->unk0C;
    r1 = a->unk2F4;
    r3 = Div((s32)(r4 * r2), (s32)r1);
    r0 = Div((s32)((0xB4 - r4) * r3), (s32)r4);
    r3 = 0xB4 - r0;
    sub_080346C0(a, a->unk00->unk30, a->unk00->unk34, r6, (u32)r3);
}

