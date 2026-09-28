#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08067648
/* match-flags: -O1 */
// EEPROM library (built at -O1): write one 64-bit block. Clocks out the write
// command, the address and the four data halfwords (MSB first), then polls the
// chip's ready bit, giving up after 0x88 scanlines. Returns 0x80FF if address
// is past the chip size and 0xC001 on a timeout.
u16 sub_08067648(u16 address, const u16 *data, u8 mode)
{
    u16 buffer[0x52];
    vu16 status;
    vu16 lastVcount;
    vu16 vcount;
    vu32 elapsed;
    u16 result;
    u16 *ptr;
    u16 bits;
    u8 i;
    u8 j;

    if (address >= gData_030009B0->unk04)
        return 0x80FF;
    // Stop bit, then the data bits, address bits and the two command bits,
    // filled from the end of the stream.
    ptr = &buffer[gData_030009B0->unk08 + 0x43];
    ptr--;
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
    for (i = 0; i < gData_030009B0->unk08; i++)
    {
        *ptr-- = address;
        address >>= 1;
    }
    *ptr-- = 0;
    *ptr = 1;
    EepromDmaTransfer(buffer, (void *)0x0D000000, gData_030009B0->unk08 + 0x43);

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
            // VCOUNT wraps after 228 (0xE4) lines.
            if (vcount > lastVcount)
                elapsed += vcount - lastVcount;
            else
                elapsed += 0xE4 - lastVcount + vcount;
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

