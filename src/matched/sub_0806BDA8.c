#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806bda8
/* match-compiler: old_agbcc */
void *sub_0806BDA8(struct Unk6BDA8 *a, u32 i)
{
    void **t = a->unk114;

    if (t == 0)
        return 0;
    return t[i];
}

