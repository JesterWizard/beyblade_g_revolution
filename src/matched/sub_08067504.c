#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08067504
/* match-flags: -O1 */
// EEPROM library (built at -O1): DMA3 transfer with interrupts off and the
// cartridge wait state (WAITCNT bits 8-10) set from the EEPROM config.
void sub_08067504(void *source, void *destination, u16 count)
{
    u16 ime;
    u16 waitcnt;

    ime = REG_IME;
    REG_IME = 0;
    waitcnt = REG_WAITCNT;
    waitcnt &= 0xF8FF;
    waitcnt |= gUnk_030009B0->unk06;
    REG_WAITCNT = waitcnt;
    REG_DMA3SAD = (u32)source;
    REG_DMA3DAD = (u32)destination;
    REG_DMA3CNT = count | 0x80000000;
    while (REG_DMA3CNT_H & 0x8000)
        ;
    REG_IME = ime;
}
