#include "global.h"
#include "ram_map.h"
#include "battle.h"

u16 sub_08067648(u16 address, u32 data_arg, u32 mode_arg)
{
    u16 buffer[0x52];
    vu16 status;
    vu16 lastVcount;
    vu16 vcount;
    vu32 elapsed;
    const u16 *data = (const u16 *)data_arg;
    u8 mode = mode_arg;
    u16 result;
    u16 *ptr;
    u16 bits;
    u8 i;
    u8 j;

    if (address >= gUnk_030009B0->unk04)
        return 0x80FF;
    ptr = &buffer[gUnk_030009B0->unk08 + 0x42];
    *ptr-- = 0;
    for (i = 0; i < 4; i++)
    {
        bits = *data++;
        for (j = 0; j < 16; j++)
        {
            *ptr-- = bits;
            bits >>= 1;
        }
    }
    for (i = 0; i < gUnk_030009B0->unk08; i++)
    {
        *ptr-- = address;
        address >>= 1;
    }
    *ptr-- = 0;
    *ptr = 1;
    sub_08067504(buffer, (void *)0x0D000000, gUnk_030009B0->unk08 + 0x43);

    result = 0;
    status = 0;
    lastVcount = REG_VCOUNT;
    elapsed = 0;
    for (;;)
    {
        if (status == 0 && (*(vu16 *)0x0D000000 & 1))
        {
            status++;
            if (mode == 0)
                break;
        }
        vcount = REG_VCOUNT;
        if (vcount != lastVcount)
        {
            if (vcount > lastVcount)
                elapsed += vcount - lastVcount;
            else
                elapsed += vcount + 0xE4 - lastVcount;
            if (elapsed > 0x88)
            {
                if (status == 0 && !(*(vu16 *)0x0D000000 & 1))
                    result = 0xC001;
                break;
            }
            lastVcount = vcount;
        }
    }
    return result;
}
