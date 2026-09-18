#ifndef GUARD_RAM_MAP_H
#define GUARD_RAM_MAP_H

#include "gba/types.h"
#include "ram_map_pool.h"
#include "unknown-types.h"

/*
 * Hand-maintained symbols (see asm/ram_map_iwram.s).
 *
 * Pool header keeps address constants (needed by match_function.py, which
 * compares unlinked .text). Promoted pointer globals are typed dereference
 * macros so C can write `gMainWorkPtr->unk1800` instead of
 * `*(u32 *)((u8 *)*(u32 **)0x03000198 + 0x1800)`.
 */

#undef gMainWorkPtr
#undef gBattleWork
#undef gBtlObjListHead
#undef gBtlObjListTail
#undef gUnk_03000180
#undef gUnk_0300026C
#undef gUnk_0300047C
#undef gUnk_03000798
#define gMainWorkPtrLoc ((struct MainWork **)0x03000198)
#define gBattleWorkPtrLoc ((struct BattleWork **)0x03000290)
#define gMainWorkPtr (*(struct MainWork **)0x03000198)
#define gBattleWork (*(struct BattleWork **)0x03000290)
#define gBtlObjListHeadLoc ((struct BtlObjNode **)0x030040A8)
#define gBtlObjListTailLoc ((struct BtlObjNode **)0x030040B8)
#define gUnk_03000180 (*(struct Unk0180 *)0x03000180)
#define gUnk_0300026C (*(struct Unk026C **)0x0300026C)
#define gUnk_0300047C (*(struct Unk047C **)0x0300047C)
#define gUnk_03000798 (*(struct Unk0798 **)0x03000798)

#define gBattlerArena    0x03004060
#define gBattlerArenaEnd 0x0300416C

#define gBtlInputMask      0x03003F60
#define gBtlState          0x03003F64
#define gBtlKeysHeld       0x03004060
#define gBtlKeysNew        0x0300406C
#define gBtlKeyQueuePtr    0x03004070
#define gBtlKeyQueueCount  0x03004074
#define gBtlObjListHead (*(struct BtlObjNode **)0x030040A8)
#define gBtlObjListTail (*(struct BtlObjNode **)0x030040B8)
#define gBtlObjTable       0x03004150
#define gBtlObjTableCount  0x03004154
#define gBtlObjLiveCount   0x03004158
#define gBtlLookupBase     0x03004130
#define gBtlLookupPtr      0x03004148

extern char gNoCashPrintBuf[];

#endif /* GUARD_RAM_MAP_H */
