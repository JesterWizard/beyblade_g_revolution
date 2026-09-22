/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803ddb0
// MATCHED -> src/matched/sub_0803DDB0.c (old_agbcc)
// Same shape as sub_0803DDD8 (table 0x0807AEEC).
void *sub_0803DDB0(s32 a)
{
    u8 *tbl = gData_0807AEEC;
    u32 *row = (u32 *)(tbl + (a - 1) * 4);
    return (void *)*(u32 *)((u8 *)*row + gMainWorkPtr->unk1818 * 4);
}
