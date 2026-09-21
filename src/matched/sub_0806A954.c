#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806a954
/* match-compiler: old_agbcc */
void *sub_0806A954(u8 a)
{
    if (a > 9)
        return 0;
    return (u8 *)gUnk_03003F70 + a * 24;
}

