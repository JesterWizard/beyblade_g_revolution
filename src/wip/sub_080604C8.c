#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080604c8
/* match-compiler: old_agbcc */
void sub_080604C8(void)
{
    struct Unk604C8 *p = *(struct Unk604C8 **)gUnk_03000750;
    u32 w;

    w = p->unk00;
    w <<= 8;
    w |= p->unk02;
    p->unk08 = w;
    p->unk0A = (p->unk04 << 8) | p->unk06;
    p->unk0C = (p->unk01 << 8) | p->unk03;
    if (1)
    {
        if (p)
        {
            p->unk0E = (p->unk05 << 8) | p->unk07;
            p->unk14 = (p->unk11 << 8) | p->unk10;
            p->unk16 = (p->unk13 << 8) | p->unk12;
            *(vu16 *)gData_04000040 = (u16)w;
            w = (u32)gData_04000042;
            *(u16 *)w = p->unk0A;
            w += 2;
            *(u16 *)w = p->unk0C;
            w += 2;
            *(u16 *)w = p->unk0E;
            w += 2;
            *(u16 *)w = p->unk14;
            w += 2;
        }
        else
        {
            p->unk0E = (p->unk05 << 8) | p->unk07;
            p->unk14 = (p->unk11 << 8) | p->unk10;
            p->unk16 = (p->unk13 << 8) | p->unk12;
            *(vu16 *)gData_04000040 = (u16)w;
            w = (u32)gData_04000042;
            *(u16 *)w = p->unk0A;
            w += 2;
            *(u16 *)w = p->unk0C;
            w += 2;
            *(u16 *)w = p->unk0E;
            w += 2;
            *(u16 *)w = p->unk14;
            w += 2;
        }
    }
    *(u16 *)w = p->unk16;
}

