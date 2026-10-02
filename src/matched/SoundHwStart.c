#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08071ba0
void SoundHwStart(void)
{
    u32 buffer;
    vu32 *timer;
    u32 rate;

    REG_SOUNDCNT_X = 0x80;
    REG_SOUNDCNT_H = 0xB04;
    REG_DMA1SAD = buffer = gData_030040DC[0];
    REG_DMA1DAD = REG_ADDR_FIFO_A;
    REG_DMA1CNT = 0xB6000000;
    REG_TM1CNT = (*(u16 *)0x030040D8 - 2) | 0xC40000;
    timer = &REG_TM0CNT;
    rate = *(u32 *)0x03004100;
    *timer = (0x10000 - _080741EC(0x1000000, rate)) | 0x800000;
    *(u32 *)0x030000B8 = buffer;
    *(u32 *)0x030000BC = 0x10000 - gData_0300410C[0];
}


