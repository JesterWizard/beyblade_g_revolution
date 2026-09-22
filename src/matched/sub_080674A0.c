#include "global.h"

// @ 0x080674a0
/* BIOS SWI 0x06: quotient of num/den in r0, remainder in r1. */
s32 Div(s32 num, s32 den)
{
    asm("swi 6");
    return num;
}

