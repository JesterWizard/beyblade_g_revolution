#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803ddb0
/* match-compiler: old_agbcc */
// 40-byte row lookup: tbl[a - 1] is a pointer, indexed by gMainWorkPtr->unk1818.
// Same shape as sub_0803DDD8 (different table).
void *sub_0803DDB0(s32 a)
{
    u8 *tbl = gData_0807AEEC;
    u32 *row = (u32 *)(tbl + (a - 1) * 4);
    return (void *)*(u32 *)((u8 *)*row + gMainWorkPtr->unk1818 * 4);
}

