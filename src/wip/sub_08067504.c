#include "global.h"

void sub_08067504(void *source, void *destination, u16 count)
{
    u16 ime;
    u16 waitcnt;
    register u16 busy_mask;

    ime = REG_IME;
    REG_IME = 0;
    waitcnt = REG_WAITCNT;
    waitcnt &= 0xF8FF;
    waitcnt |= gUnk_030009B0->unk06;
    REG_WAITCNT = waitcnt;
    REG_DMA3SAD = (u32)source;
    REG_DMA3DAD = (u32)destination;
    REG_DMA3CNT = (u32)count | 0x80000000;
    busy_mask = 0x8000;
    while ((REG_DMA3CNT_H & busy_mask) != 0)
        ;
    REG_IME = ime;
}
