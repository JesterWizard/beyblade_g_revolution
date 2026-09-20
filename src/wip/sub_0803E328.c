#include "global.h"

// @ 0x0803e328
#include "global.h"

s32 sub_0803E328(struct Unk3E328 *a)
{
    register struct Unk3E328 *r2;
    register u32 r0;
    register s32 r1;
    register u32 r3;

    r2 = a;
    r0 = 0x0807BDB8;
r1 = r2->unk1E;
    r1 <<= 2;
    r1 += r0;
    r3 = 0x0807BB80;
r0 = (u32)r2;
    r0 += 0x20;
    r0 = *(u8 *)r0;
    r0 <<= 24;
    r0 = (u32)((s32)r0 >> 24);
    r0 <<= 2;
    r0 += r3;
    r0 = *(u8 *)r0;
    r1 = *(u8 *)r1;
    r0 += r1;
    r3 = 0x0807B6F0;
r1 = r2->unk1D;
    r1 <<= 2;
    r1 += r3;
    r1 = *(u8 *)r1;
    r0 = r1 + r0;
    return _080741EC(r0, 3) - 1;
}

