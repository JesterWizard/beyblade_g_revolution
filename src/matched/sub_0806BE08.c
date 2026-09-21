#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806be08
/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x0806be08
s32 sub_0806BE08(struct Unk6BE08 *a, u32 b)
{
    u32 i = (b - a->unk0C) >> 5;

    if (i < a->unk00->unk08)
        return i;
    return -1;
}

