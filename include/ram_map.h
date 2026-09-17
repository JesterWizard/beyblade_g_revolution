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
#define gMainWorkPtr (*(struct MainWork **)0x03000198)
#define gBattleWork (*(struct BattleWork **)0x03000290)

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
