#include "global.h"

// @ 0x08069894
void sub_08069894(void)
{
    u32 a108;
    u32 a1b0;
    u32 a1a8;
    u8 i;
    u16 zero;
    u32 n;

    a108 = gUnk_03000108;
    a1b0 = gUnk_030001B0;
    a1a8 = gUnk_030001A8;
    *(s8 *)a108 = 0;
    *(s8 *)a1b0 = 0;
    *(s8 *)a1a8 = 0x20;

    i = 0;
    zero = 0;
    while (i <= 3)
    {
        *sub_08069908(i) = zero;
        *sub_08069948(i) = zero;
        i = (u8)(i + 1);
    }

    n = 0x80;
    n <<= 1;
    sub_08069A60(2, 0, n, n);
    sub_08069A60(3, 0, n, n);
}
