#include "global.h"

void sub_08069894(void)
{
    u8 i;

    *(s8 *)gUnk_03000108 = 0;
    *(s8 *)gUnk_030001B0 = 0;
    *(s8 *)gUnk_030001A8 = 0x20;

    for (i = 0; i <= 3; i++)
    {
        *sub_08069908(i) = 0;
        *sub_08069948(i) = 0;
    }

    sub_08069A60(2, 0, 0x100, 0x100);
    sub_08069A60(3, 0, 0x100, 0x100);
}
