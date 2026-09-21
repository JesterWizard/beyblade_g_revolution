#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080717f0
/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x080717f0
void sub_080717F0(u32 a)
{
    if (a > 0x100)
        a = 0x100;
    *(u16 *)gUnk_030000CC = a;
}

