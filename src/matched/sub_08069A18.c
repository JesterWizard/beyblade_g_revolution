#include "global.h"

// @ 0x08069a18
#include "global.h"

// @ 0x08069a18
void sub_08069A18(u8 a, u16 b, u16 c, u16 d, u16 e)
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

