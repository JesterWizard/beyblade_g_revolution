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
#undef gUnk_030006B8
#undef gUnk_03000674
#undef gUnk_03000678
#undef gUnk_0300069C
#undef gUnk_030006A0
#undef gUnk_030006A4
#undef gUnk_030006A8
#undef gUnk_03000758
#undef gUnk_03000770
#undef gUnk_03000794
#undef gUnk_030007A0
#undef gUnk_030007A4
#undef gUnk_030007B0
#undef gUnk_030008D0
#undef gUnk_030008D4
#undef gUnk_030008D8
#undef gUnk_030008DC
#undef gUnk_030008E0
#undef gUnk_030009A8
#undef gUnk_030009AC
#undef gUnk_030009B0
#undef gUnk_03000B40
#undef gUnk_03003F40
#undef gUnk_03003F44
#undef gUnk_03003F48
#undef gUnk_03003F4C
#undef gUnk_03000B30
#undef gUnk_03000B34
#undef gUnk_03000B38
#undef gUnk_03000B3C
#undef gUnk_03003F50
#undef gUnk_030040A4
#undef gUnk_030040AC
#undef gUnk_030040B4
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
#undef gUnk_03000638
#define gUnk_03000638 (*(void **)0x03000638)
#define gUnk_03000654 (*(s16 *)0x03000654)
#define gUnk_03000658 (*(struct Unk4AAF0 ***)0x03000658)
#define gUnk_03000660 (*(struct Unk4AAF0 **)0x03000660)
#define gUnk_030006B8 (*(u16 *)0x030006B8)
#define gUnk_03000674 (*(u32 *)0x03000674)
#define gUnk_03000678 (*(u32 *)0x03000678)
#define gUnk_0300069C (*(s32 *)0x0300069C)
#define gUnk_030006A0 (*(struct Unk4EBF0Entry **)0x030006A0)
#define gUnk_030006A4 (*(s32 *)0x030006A4)
#define gUnk_030006A8 (*(u32 *)0x030006A8)
#define gUnk_03000758Loc ((struct Unk0758 **)0x03000758)
#define gUnk_03000798Loc ((struct Unk0758 **)0x03000798)
#define gUnk_03000758 (*(struct Unk0758 **)0x03000758)
#define gUnk_03000770 ((struct Unk0770 *)0x03000770)
#define gUnk_03000794 (*(u32 *)0x03000794)
#define gUnk_030007A0 (*(u32 *)0x030007A0)
#define gUnk_030007A4 (*(void **)0x030007A4)
#define gUnk_030007B0 ((void *)0x030007B0)
#define gUnk_030008D0 (*(struct Unk62A74 **)0x030008D0)
#define gUnk_030008D4 (*(void **)0x030008D4)
#define gUnk_030008D8 (*(void **)0x030008D8)
#define gUnk_030008DC (*(void **)0x030008DC)
#define gUnk_030008E0 (*(void **)0x030008E0)
#define gUnk_030009A8 (*(u8 *)0x030009A8)
#define gUnk_030009AC (*(u8 **)0x030009AC)
#define gUnk_030009B0 (*(struct Unk09B0 **)0x030009B0)
#define gUnk_03000B40 ((void *)0x03000B40)
#define gUnk_03003F40 (*(void **)0x03003F40)
#define gUnk_03003F44 (*(void **)0x03003F44)
#define gUnk_03003F48 (*(u32 *)0x03003F48)
#define gUnk_03003F4C (*(u32 *)0x03003F4C)
#define gUnk_03000B30 (*(void **)0x03000B30)
#define gUnk_03000B34 (*(u32 *)0x03000B34)
#define gUnk_03000B38 (*(u32 *)0x03000B38)
#define gUnk_03000B3C (*(u32 *)0x03000B3C)
#define gUnk_03003F50 (*(void **)0x03003F50)
#define gUnk_030040A4 (*(struct Unk6FDB4 **)0x030040A4)
#define gUnk_030040AC (*(struct Unk6FDB4 **)0x030040AC)
#define gUnk_030040B4 (*(u32 *)0x030040B4)

#define gBattlerArena    0x03004060
#define gBattlerArenaEnd 0x0300416C

#define gBtlInputMask      0x03003F60
#define gBtlState          0x03003F64
#define gBtlKeysHeld       0x03004060
#define gBtlKeysHeldU16    (*(u16 *)0x03004060)
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
