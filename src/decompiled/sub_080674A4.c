#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080674a4
s32 DivRemainder(s32 num, s32 den)
{
    s32 rem;

    asm("swi 6" : "+r"(num), "=r"(rem) : "r"(den));
    return rem;
}
