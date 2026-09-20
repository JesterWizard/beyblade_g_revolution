#include "global.h"

// @ 0x08069894
void sub_08069894(void)
{
    register u32 r0 asm("r0");
    register u32 r1 asm("r1");
    u8 i;

    r0 = gUnk_03000108;
    r1 = 0;
    *(s8 *)r0 = (s8)r1;
    asm("" : "+r"(r0), "+r"(r1) : : "memory");
    r0 = gUnk_030001B0;
    asm("" : "+r"(r0));
    *(s8 *)r0 = (s8)r1;
    r1 = gUnk_030001A8;
    asm("" : "+r"(r1));
    r0 = 0x20;
    *(s8 *)r1 = (s8)r0;

    for (i = 0; i <= 3; i++)
    {
        *sub_08069908(i) = 0;
        *sub_08069948(i) = 0;
    }

    sub_08069A60(2, 0, 0x100, 0x100);
    sub_08069A60(3, 0, 0x100, 0x100);
}

