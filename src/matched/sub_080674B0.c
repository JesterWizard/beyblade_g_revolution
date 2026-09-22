#include "global.h"

// @ 0x080674b0
s32 Sqrt(s32 a)
{
    asm("swi 8");
    return a;
}
