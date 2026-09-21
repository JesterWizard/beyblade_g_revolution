/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x0803e3c0
s32 sub_0803E3C0(struct Unk3E328 *a)
{
    const u8 *t1 = (const u8 *)0x0807BDB8;
    u32 i1 = a->unk1E * 4;
    u32 v1;
    u32 v2;

    v1 = t1[i1 + 2];
    v2 = ((const u8 *)0x0807BB80)[(s8)a->unk20 * 4 + 2];
    v1 += v2;
    v1 += ((const u8 *)0x0807B6F0)[a->unk1D * 4 + 2];
    return _080741EC(v1, 3) - 1;
}
