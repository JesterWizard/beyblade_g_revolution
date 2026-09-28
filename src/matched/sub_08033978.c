#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08033978
void sub_08033978(struct Unk33A5C *a, struct Unk346C0 *b, struct Unk346C0 *c, u8 d)
{
    a->unk00 = 1;
    a->unk04 = b;
    a->unk08 = c;
    sub_08034FF8((struct Unk34FF8 *)b, gData_08078158[d], (u32)c);
    sub_08034FF8((struct Unk34FF8 *)c, 0x08078E58, (u32)b);
    BtlSetMode1F90(0x80);
    sub_08035204(b, 0, 0xC, -1);
    b->unk08C = AnimDurationForKey(&b->unk1C, 0);
    b->unk2B0 = 0;
    b->unk2B4 = -1;
    b->unk2CC = 2;
    b->unk310 = 1;
    c->unk2CC = 6;
    b->unk310 = 1;
    sub_08060254(0xB, 0x38, d);
    a->unk0D = 0;
}

