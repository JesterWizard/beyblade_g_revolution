/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080604c8
// 92/112 same-size. Packs 6 u8 pairs from *gUnk_03000750 into BGR555-ish u16
// fields, then mirrors them to the IO block at 0x04000040 (first from the live
// `w` register, the rest re-read from the struct). Remaining DIFF is the tail
// register split: retail keeps the IO cursor in r2 and loads values into r0;
// agbcc puts the cursor in r0 and values in r2.
void sub_080604C8(void)
{
    struct Unk604C8 *p = *(struct Unk604C8 **)gUnk_03000750;
    u16 w;
    u16 *out;

    w = (p->unk00 << 8) | p->unk02;
    p->unk08 = w;
    p->unk0A = (p->unk04 << 8) | p->unk06;
    p->unk0C = (p->unk01 << 8) | p->unk03;
    p->unk0E = (p->unk05 << 8) | p->unk07;
    p->unk14 = (p->unk11 << 8) | p->unk10;
    p->unk16 = (p->unk13 << 8) | p->unk12;
    *(vu16 *)gData_04000040 = w;
    out = (u16 *)gData_04000042;
    *out++ = p->unk0A;
    *out++ = p->unk0C;
    *out++ = p->unk0E;
    *out++ = p->unk14;
    *out = p->unk16;
}
