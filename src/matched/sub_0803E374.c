#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803e374
/* match-compiler: old_agbcc */
// Byte 1 of the 4-byte rows at gData_0807BDB8 / gData_0807BB80 / gData_0807B6F0.
// The discarded `v2 = table[index]` reads hoist each pool load above the index
// math (`ldr r3,=table` before `movs r1,#imm`). Dropping either one misses.
s32 sub_0803E374(struct Unk3E328 *a)
{
    const u8 *t1 = gData_0807BDB8;
    u32 i1 = a->unk1E * 4;
    u32 v1;
    u32 v2;

    v1 = ((struct Unk3E374Row *)(t1 + i1))->unk01;
    v2 = gData_0807BB80[(s8)a->unk20 * 4];
    v2 = ((struct Unk3E374Row *)(gData_0807BB80 + (s8)a->unk20 * 4))->unk01;
    v1 += v2;
    v2 = gData_0807B6F0[a->unk1D * 4];
    v1 += ((struct Unk3E374Row *)(gData_0807B6F0 + a->unk1D * 4))->unk01;
    return _080741EC(v1, 3) - 1;
}

