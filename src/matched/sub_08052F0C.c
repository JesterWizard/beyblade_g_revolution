#include "global.h"

// @ 0x08052f0c
#include "global.h"

void sub_08052F0C(u8 *data)
{
    sub_08061D68(5, 0x0F, 8, 0x15);
    sub_08061D68(6, 0x0F, 8, 0x15);
    sub_08061D68(7, 0x0F, 8, 0x15);
    sub_08061D68(8, 0x0F, 8, 0x15);
    sub_08061D68(9, 0x0F, 8, 0x15);
    sub_08061D68(0x0A, 0x0F, 8, 0x15);
    sub_08061D68(0x0B, 0x0F, 8, 0x15);
    sub_08061D68(0x0C, 0x0F, 8, 0x15);
    sub_08061D68(0x0D, 0x0F, 8, 0x15);
    sub_08061D68(0x0E, 0x0F, 8, 0x15);
    sub_08061D68(
        (u32)(((s32)(s8)data[0x2D5] << 17) + 0x50000) >> 16,
        0x0E,
        8,
        0x15);
    sub_08061D68(
        (u32)(((s32)(s8)data[0x2D5] << 17) + 0x60000) >> 16,
        0x0E,
        8,
        0x15);
}

