#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803e328
/* match-compiler: old_agbcc */

s32 sub_0803E328(struct Unk3E328 *a)
{
    const u8 *t1 = gData_0807BDB8;
    u32 i1 = a->unk1E * 4;
    u32 v1;
    u32 v2;

    v1 = t1[i1 + 0];
    v2 = gData_0807BB80[(s8)a->unk20 * 4 + 0];
    v1 += v2;
    v1 += gData_0807B6F0[a->unk1D * 4 + 0];
    return _080741EC(v1, 3) - 1;
}

