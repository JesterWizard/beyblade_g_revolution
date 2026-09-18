#include "global.h"

// @ 0x080674b0
s32 sub_080674B0(s32 a)
{
    asm("swi 8");
    return a;
}
