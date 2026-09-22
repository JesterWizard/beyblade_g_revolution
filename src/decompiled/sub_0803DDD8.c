/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803ddd8
// MATCHED -> src/matched/sub_0803DDD8.c (old_agbcc)
// 40-byte row lookup: tbl[a - 1] is a pointer, indexed by gMainWorkPtr->unk1818.
// `tbl` must be a local (re-using the symbol twice folds the pool load); the
// dereference stays inline as `*row` so old_agbcc hoists `ldr r1,=tbl` above
// `subs r0,#1` like retail.
void *sub_0803DDD8(s32 a)
{
    u8 *tbl = gData_0807AEFC;
    u32 *row = (u32 *)(tbl + (a - 1) * 4);
    return (void *)*(u32 *)((u8 *)*row + gMainWorkPtr->unk1818 * 4);
}
