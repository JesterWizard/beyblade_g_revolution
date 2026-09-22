#include "global.h"

// @ 0x08037430
void sub_08037430(void)
{
    void *first;
    void *r6;
    u32 r0;
    u32 r1;
    u32 r2;
    u32 r4;
    u32 r5;

    first = BtlObjTableAdd(0x40);
    r6 = BtlObjTableAdd(0x40);

    r0 = gMainWorkPtr->unk1808;
    r1 = 2;
    r0 &= r1;
    if (r0 != 0)
        goto cleanup;

    r0 = (u32)gBattleWork;
    r2 = 0x133;
    r0 += r2;
    r1 = *(u8 *)r0;
    if (r1 <= 3)
        goto use_count;
    r0 = 3;
    r1 = (u32)r6;
    r2 = 0x40;
    sub_080735DC((s32)r0, (void *)r1, r2);
    goto after_count;
use_count:
    r0 = *(u8 *)r0;
    r1 = (u32)r6;
    r2 = 0x40;
    sub_080735DC((s32)r0, (void *)r1, r2);
after_count:
    r1 = 0x08096ECC;
r0 = (u32)gMainWorkPtr;
    r2 = 0x1818;
    r0 += r2;
    r0 = *(u8 *)r0;
    r0 <<= 2;
    r0 += r1;
    r0 = *(u32 *)r0;
    r1 = 0x40;
    sub_08073AEC((void *)r0, first, r6, 0x23, r1);

    r5 = 0x03000290;
    r0 = *(u32 *)r5;
    r4 = 0xBA;
    r4 <<= 1;
    r0 += r4;
    r1 = 0x080B72F3;
    r2 = 0x082BF600;
    sub_08061E8C((void *)r0, (const void *)r1, (const void *)r2, 0xB0, 0x170);

    r0 = *(u32 *)r5;
    r0 += r4;
    sub_08061EF8((void *)r0, first, 0, 0x28, 0, 0xC8, 0);

cleanup:
    BtlObjTableRemove(first);
    BtlObjTableRemove(r6);
}

