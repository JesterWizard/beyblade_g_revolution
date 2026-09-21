#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806def4
/* match-compiler: old_agbcc */
s32 sub_0806DEF4(struct Unk6DEF4 *a, s32 b)
{
    s32 base = a->unk04;

    if (b < *a->unk00)
        return base + b * 16;
    return 0;
}

