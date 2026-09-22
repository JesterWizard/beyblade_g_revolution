#include "global.h"

// @ 0x080507b8

void sub_080507B8(u8 *data)
{
    u32 value;

    if (gUnk_030006B8 == 0)
    {
        BgMapSetPaletteBankRun(0x10, 0x0F, 9, 0x1A);
        BgMapSetPaletteBankRun(0x11, 0x0F, 9, 0x1A);
        value = (u32)((s8)data[0x2D5] + 0x10);
        value = (value << 16) >> 16;
        BgMapSetPaletteBankRun(value, 0x0E, 9, 0x1A);
    }
    else
    {
        BgMapSetPaletteBankRun(6, 0x0F, 0x0A, 0x18);
        BgMapSetPaletteBankRun(8, 0x0F, 0x0A, 0x18);
        BgMapSetPaletteBankRun(0x0A, 0x0F, 0x0A, 0x18);
        BgMapSetPaletteBankRun(0x0C, 0x0F, 0x0A, 0x18);
        BgMapSetPaletteBankRun(0x0E, 0x0F, 0x0A, 0x18);
        value = (u32)((s32)(s8)data[0x2D5] << 17) + 0x60000;
        value >>= 16;
        BgMapSetPaletteBankRun(value, 0x0E, 0x0A, 0x18);
    }
}

