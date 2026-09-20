#include "global.h"

// @ 0x08071ba0
void sub_08071BA0(void)
{
    u32 r0;
    u32 r1;
    u32 r2;
    u32 r4;
    u32 r5;

    r1 = REG_ADDR_SOUNDCNT_X;
    r0 = 0x80;
    *(vu16 *)r1 = (u16)r0;
    r1 -= 2;
    r2 = 0xB04;
    r0 = r2;
*(vu16 *)r1 = (u16)r0;
    r1 += 0x3A;
    r0 = gUnk_030040DC;
    r5 = *(u32 *)r0;
    *(vu32 *)r1 = r5;
r1 += 4;
    r0 = REG_ADDR_FIFO_A;
    *(vu32 *)r1 = r0;
r1 += 4;
    r0 = 0xB6;
    r0 <<= 24;
    *(vu32 *)r1 = r0;
    r2 = REG_ADDR_TM1CNT;
    r0 = gUnk_030040D8;
    r0 = *(u16 *)r0;
    r0 -= 2;
    r1 = 0xC4;
    r1 <<= 16;
    r0 |= r1;
    *(vu32 *)r2 = r0;
    r4 = REG_ADDR_TM0CNT;
    r0 = gUnk_03004100;
    r1 = *(u32 *)r0;
    r0 = 0x80;
    r0 <<= 17;
    r0 = (u32)_080741EC(r0, r1);
    r2 = 0x80;
    r2 <<= 9;
    r0 = r2 - r0;
    r1 = 0x80;
    r1 <<= 16;
    r0 |= r1;
    *(vu32 *)r4 = r0;
    r0 = gUnk_030000B8;
    *(u32 *)r0 = r5;
    r1 = gUnk_030000BC;
    r0 = gUnk_0300410C;
    r0 = *(u16 *)r0;
    r2 -= r0;
    *(u32 *)r1 = r2;
}

