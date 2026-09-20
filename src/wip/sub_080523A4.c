#include "global.h"

// @ 0x080523a4
void sub_080523A4(struct Unk2F520 *a)
{
    struct Unk2F520 *r4;
    struct Unk2F520Inner *r1;
    u32 r2;
    s32 r0;
    u32 r3;

    r4 = a;
    sub_08061BE8();
    sub_0805264C(r4, 0);
    sub_0805264C(r4, 1);
    sub_0805264C(r4, 2);
    sub_0805264C(r4, 3);
    sub_0805264C(r4, 4);
    sub_0805264C(r4, 5);

    r1 = r4->unk288;
    r3 = 0x2D5;
r2 = (u32)r4 + r3;
    r0 = 0;
    r0 = *(s8 *)(r2 + r0);
    r0 <<= 12;
    r3 = 0xB0;
    r3 <<= 6;
    r0 += r3;
    r1->unk0C = r0;

    r1 = r4->unk28C;
    r0 = 0;
    r0 = *(s8 *)(r2 + r0);
    r0 <<= 12;
    r0 += r3;
    r1->unk0C = r0;
}

