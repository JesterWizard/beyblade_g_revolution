#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* match-flags: -O1 */
s32 sub_08067584(u32 addrArg, void *outArg)
{
    u16 buf[0x44];
    u16 *p;
    u16 *out = outArg;
    u16 addr = addrArg;
    u16 value;
    u8 i;
    u8 j;

    if (addr >= gUnk_030009B0->unk04)
        return 0x80FF;
    p = buf + gUnk_030009B0->unk08 + 1;
    for (i = 0; i < gUnk_030009B0->unk08; i++)
    {
        *p-- = addr;
        addr >>= 1;
    }
    *p-- = 1;
    *p = 1;
    sub_08067504(buf, (void *)0x0D000000, gUnk_030009B0->unk08 + 3);
    sub_08067504((void *)0x0D000000, buf, 0x44);
    p = &buf[4];
    out += 3;
    for (i = 0; i < 4; i++)
    {
        value = 0;
        for (j = 0; j < 16; j++)
        {
            value <<= 1;
            value |= *p++ & 1;
        }
        *out-- = value;
    }
    return 0;
}


