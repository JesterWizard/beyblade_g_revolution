#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08042e78
/* match-compiler: old_agbcc */
void *BeybladeCollectionEntry(u32 i)
{
    if (i > 0x36)
        return 0;
    return (u8 *)*(u32 *)gUnk_03000540 + i * 48;
}

