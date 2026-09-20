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
#undef gUnk_030002A0
#undef gUnk_0300047C
#undef gUnk_03000798
#undef gUnk_030003CC
#undef gUnk_03000554
#undef gUnk_03000558
#undef gUnk_03000538
#undef gUnk_03000610
#undef gUnk_03000600
#undef gUnk_03000630
#undef gUnk_03000654
#undef gUnk_03000658
#undef gUnk_03000660
#define gMainWorkPtrLoc ((struct MainWork **)0x03000198)
#define gBattleWorkPtrLoc ((struct BattleWork **)0x03000290)
#define gMainWorkPtr (*(struct MainWork **)0x03000198)
#define gBattleWork (*(struct BattleWork **)0x03000290)
#define gBtlObjListHeadLoc ((struct BtlObjNode **)0x030040A8)
#define gBtlObjListTailLoc ((struct BtlObjNode **)0x030040B8)
#define gUnk_03000180 (*(struct Unk0180 *)0x03000180)
#define gUnk_0300026C (*(struct Unk026C **)0x0300026C)
#define gUnk_030002A0 (*(struct Unk002A0 *)0x030002A0)
#define gUnk_0300047CLoc ((struct Unk047C **)0x0300047C)
#define gUnk_0300047C (*(struct Unk047C **)0x0300047C)
#define gUnk_03000798 (*(struct Unk0798 **)0x03000798)
#define gUnk_030003CC (*(struct Unk3CC **)0x030003CC)
#define gUnk_03000554 (*(struct Unk0554 **)0x03000554)
#define gUnk_03000538 (*(struct Unk0538 **)0x03000538)
#define gUnk_03000558 (*(struct Unk0558 **)0x03000558)
#define gUnk_03000558Loc ((u32 *)0x03000558)
#define gUnk_03000610 (*(struct Unk0610 *)0x03000610)
#define gUnk_03000600 (*(struct Unk0600 *)0x03000600)
#define gUnk_03000630 (*(struct Unk473F8 **)0x03000630)
#define gUnk_03000654 (*(s16 *)0x03000654)
#define gUnk_03000658 (*(struct Unk4AAF0 ***)0x03000658)
#define gUnk_03000660 (*(struct Unk4AAF0 **)0x03000660)

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
