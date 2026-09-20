#include "global.h"

void sub_08071BA0(void)
{
    register u32 source asm("r5");
    register u32 *timer0 asm("r4");
    register u8 *sound_io asm("r1");
    register u32 timer1 asm("r2");
    u32 value;

    sound_io = (u8 *)REG_ADDR_SOUNDCNT_X;
    *(volatile u16 *)sound_io = 0x80;
    sound_io -= 2;
    timer1 = 0xB04;
    value = timer1;
    *(volatile u16 *)sound_io = value;
    source = *(u32 *)gUnk_030040DC;
    *(volatile u32 *)(sound_io + 0x3A) = source;
    *(volatile u32 *)(sound_io + 0x3E) = (u32)REG_ADDR_FIFO_A;
    *(volatile u32 *)(sound_io + 0x42) = 0xB6000000;
    timer1 = (u32)REG_ADDR_TM1CNT;
    value = (*(u16 *)gUnk_030040D8 - 2) | 0xC40000;
    *(volatile u32 *)timer1 = value;
    timer0 = (u32 *)REG_ADDR_TM0CNT;
    value = _080741EC(0x1000000, *(u32 *)gUnk_03004100);
    value = (0x10000 - value) | 0x800000;
    *timer0 = value;
    *(u32 *)gUnk_030000B8 = source;
    *(u32 *)gUnk_030000BC = 0x10000 - *(u16 *)gUnk_0300410C;
}
