/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x0803e3c0
// MATCHED -> src/matched/sub_0803E3C0.c (old_agbcc)
// Byte 2 of the same 4-byte rows as sub_0803E374. Same discarded reads.
s32 sub_0803E3C0(struct Unk3E328 *a)
{
    const u8 *t1 = gData_0807BDB8;
    u32 i1 = a->unk1E * 4;
    u32 v1;
    u32 v2;

    v1 = ((struct Unk3E374Row *)(t1 + i1))->unk02;
    v2 = gData_0807BB80[(s8)a->unk20 * 4];
    v2 = ((struct Unk3E374Row *)(gData_0807BB80 + (s8)a->unk20 * 4))->unk02;
    v1 += v2;
    v2 = gData_0807B6F0[a->unk1D * 4];
    v1 += ((struct Unk3E374Row *)(gData_0807B6F0 + a->unk1D * 4))->unk02;
    return _080741EC(v1, 3) - 1;
}
