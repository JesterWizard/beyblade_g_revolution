#include "global.h"

// @ 0x080507b8

void sub_080507B8(u8 *data)
{
    u32 value;

    if (gUnk_030006B8 == 0)
    {
        sub_08061D68(0x10, 0x0F, 9, 0x1A);
        sub_08061D68(0x11, 0x0F, 9, 0x1A);
        value = (u32)((s8)data[0x2D5] + 0x10);
        value = (value << 16) >> 16;
        sub_08061D68(value, 0x0E, 9, 0x1A);
    }
    else
    {
        sub_08061D68(6, 0x0F, 0x0A, 0x18);
        sub_08061D68(8, 0x0F, 0x0A, 0x18);
        sub_08061D68(0x0A, 0x0F, 0x0A, 0x18);
        sub_08061D68(0x0C, 0x0F, 0x0A, 0x18);
        sub_08061D68(0x0E, 0x0F, 0x0A, 0x18);
        value = (u32)((s32)(s8)data[0x2D5] << 17) + 0x60000;
        value >>= 16;
        sub_08061D68(value, 0x0E, 0x0A, 0x18);
    }
}

