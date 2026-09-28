#include "global.h"

// @ 0x08069a18

void sub_08069A18(u8 a, s16 b, s16 c, s16 d, s16 e)
{
    volatile u16 *reg;

    switch (a)
    {
    case 2:
        reg = (volatile u16 *)0x04000020;
        break;
    case 3:
        reg = (volatile u16 *)0x04000030;
        break;
    default:
        return;
    }

    *reg = b;
    reg++;
    *reg = c;
    reg++;
    *reg = d;
    reg++;
    *reg = e;
}

