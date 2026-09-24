#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803e2ac
/* match-compiler: old_agbcc */
#include "global.h"
#include "data_symbols.h"

s32 sub_0803E2AC(struct Unk3E328 *a)
{
    const u8 *t1;
    u32 i1;
    u32 v1;
    u32 v2;
    s32 red;
    s32 green;
    s32 blue;

    if (a == 0)
        return 0;

    t1 = gData_0807BDB8;
    i1 = a->unk1E * 4;
    red = ((struct Unk3E374Row *)(t1 + i1))->unk00;
    v2 = gData_0807BB80[(s8)a->unk20 * 4];
    red += ((struct Unk3E374Row *)(gData_0807BB80 + (s8)a->unk20 * 4))->unk00;

    green = ((struct Unk3E374Row *)(t1 + i1))->unk01;
    v2 = gData_0807BB80[(s8)a->unk20 * 4];
    green += ((struct Unk3E374Row *)(gData_0807BB80 + (s8)a->unk20 * 4))->unk01;

    blue = ((struct Unk3E374Row *)(t1 + i1))->unk02;
    v2 = gData_0807BB80[(s8)a->unk20 * 4];
    blue += ((struct Unk3E374Row *)(gData_0807BB80 + (s8)a->unk20 * 4))->unk02;

    v2 = gData_0807B6F0[a->unk1D * 4];
    red += ((struct Unk3E374Row *)(gData_0807B6F0 + a->unk1D * 4))->unk00;
    green += ((struct Unk3E374Row *)(gData_0807B6F0 + a->unk1D * 4))->unk01;
    blue += ((struct Unk3E374Row *)(gData_0807B6F0 + a->unk1D * 4))->unk02;

    if (red > 8)
        return 0;
    if (green > 8)
        return 1;
    if (green > 5 && blue > 5)
        return 2;
    return 3;
}

