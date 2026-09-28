#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08067584
/* match-flags: -O1 */
// EEPROM read: clock out the read command and the unk08-bit address at
// addr, then pack the 64 returned bits into four halfwords (last first).
// Returns 0x80FF if addr is past the chip size (unk04).
s32 sub_08067584(u32 addr, void *out)
{
    u16 buf[0x44];
    u16 *p;
    u16 *dst;
    u16 a;
    u16 value;
    u8 i;
    u8 j;

    dst = out;
    a = addr;
    if (a >= gData_030009B0->unk04)
        return 0x80FF;
    // buf[0..1] is the read command; the address bits fill buf[2..n+1], MSB first.
    p = &buf[gData_030009B0->unk08 + 2] - 1;
    for (i = 0; i < gData_030009B0->unk08; i++)
    {
        *p-- = a;
        a >>= 1;
    }
    *p-- = 1;
    *p = 1;
    sub_08067504(buf, (void *)0x0D000000, gData_030009B0->unk08 + 3);
    sub_08067504((void *)0x0D000000, buf, 0x44);
    p = &buf[4];
    dst += 3;
    for (i = 0; i < 4; i++)
    {
        value = 0;
        for (j = 0; j < 16; j++)
        {
            value <<= 1;
            value |= *p++ & 1;
        }
        *dst-- = value;
    }
    return 0;
}

