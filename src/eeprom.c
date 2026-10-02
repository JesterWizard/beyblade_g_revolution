#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_080674BC */
// @ 0x080674bc
u32 EepromSetType(u32 a)
{
    int v;
    u32 r2;

    v = (u16)a;
    r2 = 0;
    if (v == 4)
        *((u32 *)0x030009B0) = 0x083A93C8;
    else if (v == 0x40)
        *((u32 *)0x030009B0) = 0x083A93D4;
    else
    {
        *((u32 *)0x030009B0) = 0x083A93C8;
        r2 = 1;
    }
    return r2;
}

/* fn: sub_08067504 */
// @ 0x08067504
/* match-flags: -O1 */
// EEPROM library (built at -O1): DMA3 transfer with interrupts off and the
// cartridge wait state (WAITCNT bits 8-10) set from the EEPROM config.
void EepromDmaTransfer(void *source, void *destination, u16 count)
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

/* fn: sub_08067584 */
// @ 0x08067584
/* match-flags: -O1 */
// EEPROM read: clock out the read command and the unk08-bit address at
// addr, then pack the 64 returned bits into four halfwords (last first).
// Returns 0x80FF if addr is past the chip size (unk04).
s32 EepromReadBlock(u32 addr, void *out)
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
    EepromDmaTransfer(buf, (void *)0x0D000000, gData_030009B0->unk08 + 3);
    EepromDmaTransfer((void *)0x0D000000, buf, 0x44);
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

/* fn: sub_08067634 */
// @ 0x08067634
u16 EepromWriteBlock(u32 a, u32 b)
{
    return EepromWriteBlockEx(a, (const u16 *)b, 1);
}

/* fn: sub_08067648 */
// @ 0x08067648
/* match-flags: -O1 */
// EEPROM library (built at -O1): write one 64-bit block. Clocks out the write
// command, the address and the four data halfwords (MSB first), then polls the
// chip's ready bit, giving up after 0x88 scanlines. Returns 0x80FF if address
// is past the chip size and 0xC001 on a timeout.
u16 EepromWriteBlockEx(u16 address, const u16 *data, u8 mode)
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

/* fn: sub_080677A8 */
// @ 0x080677a8

u32 EepromVerifyBlock(u32 a, void *b)
{
    u16 *arg1;
    u16 x;
    u16 buf[4];
    u16 *p;
    u8 i;
    u32 result;
    u16 va;
    u16 vb;

    arg1 = (u16 *)b;
    x = (u16)a;
    result = 0;
    if (x >= gUnk_030009B0->unk04)
        return 0x80FF;

    EepromReadBlock(x, buf);
    p = buf;
    i = 0;
    goto compare;
matched:
    i = (u8)(i + 1);
    if (i > 3)
        goto done;
compare:
    va = *arg1;
    vb = *p;
    p++;
    arg1++;
    if (va == vb)
        goto matched;
    result = 0x80;
    result <<= 8;
done:
    return result;
}
