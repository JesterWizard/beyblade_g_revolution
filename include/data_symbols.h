#ifndef GUARD_DATA_SYMBOLS_H
#define GUARD_DATA_SYMBOLS_H

// Absolute data-address symbols referenced by decompiled C.
//
// The retail build addressed these blocks through *symbols* rather than bare
// integer literals.  That is observable in the generated code: agbcc folds,
// substitutes and reschedules a literal address (for example turning a second
// pool load into `subs r0, #0x30`, or re-colouring the registers around a
// load), but it cannot do any of that to a symbol reference.  A handful of
// functions only reproduce retail when the table is a symbol, so use these
// names there instead of `(T *)0x08XXXXXX`.
//
// Values live in asm/data_symbols.s; tools/decomp/match_function.py reads that
// file and passes each value to the assembler with --defsym, so verification
// reproduces the original addressing.
//
// Naming: `gData_<8 hex digits>` — deliberately distinct from the numeric
// `gUnk_*` macros in ram_map_pool.h, which C that matches retail with literal
// addressing keeps using.

#include "unknown-types.h"

// ROM data
extern u32 gData_08091004[];
extern u32 gData_080910E8[];
extern u32 gData_080BB888[];
extern u32 gData_080BB8BC[];
extern u32 gData_080BB8C0[];
extern u32 gData_080BB644[];
extern u8 gData_080BB748[];
extern s16 gData_08091204[];
extern u16 gData_080908B4[];
extern u8 gData_08091208[];
extern u8 gData_0807B6F0[];
extern u8 gData_0807BB80[];
extern u8 gData_0807BDB8[];
extern u32 gData_0807B0C4[];
extern u32 gData_0807B6DC[];
extern u32 gData_0807BB6C[];
extern u32 gData_0807BDA4[];
extern u32 gData_08090FF0[];
extern u8 gData_080D79CC[];
extern u8 gData_080B7429[];
extern u8 gData_083A6BE0[];
extern u8 gData_082BCD00[];
extern u8 gData_080B738E[];

// IWRAM
extern struct MainWork *gData_03000198;
extern struct BattleWork *gData_03000290;
extern struct Unk3CC *gData_030003CC;
extern u16 gData_05000200[];
extern u32 gData_08079068[];
extern u32 gData_08079358[];
extern struct Unk002A0Record gData_030002A0[];
extern void *gData_03000508[];
extern struct Unk68574 *gData_03000534; /* pool of 0x20 objects, sub_080419B0 */
extern s16 gData_03000504;
extern void *gData_030003E0[];
extern struct Unk68574 *gData_03000480[];
extern u8 gData_03000770[];
extern u32 gData_03000794[];
extern struct Unk0798 *gData_03000798;
extern struct Unk09B0 *gData_030009B0;

extern u8 gData_083A7404[];
extern u8 gData_083A75A8[];
extern u8 gData_083A7DF8[];
extern u8 gData_083A7EE0[];
extern u8 gData_083A8424[];

extern u8 gData_083A734C[];
extern u8 gData_083A83F4[];
extern u8 gData_083A85A4[];
extern u8 gData_083A8724[];

extern u8 gData_0807AEEC[];
extern u8 gData_0807AEFC[];
extern u8 gData_04000010[];
extern u8 gData_04000012[];
extern u8 gData_04000014[];
extern u8 gData_04000016[];
extern u8 gData_04000018[];
extern u8 gData_0400001A[];
extern u8 gData_0400001C[];
extern u8 gData_0400001E[];
extern u8 gData_04000040[];
extern u8 gData_04000042[];

extern u8 gData_030040E4[];
extern u8 gData_030040C4[];
extern u8 gData_030000C8[];
extern u8 gData_083D2578[];
extern u8 gData_083D1D3C[];

extern u8 gData_03000634[];
extern u8 gData_0300063C[];

extern u8 gData_030040A8[];
extern u8 gData_030040B8[];
extern u8 gData_080796DC[];
extern u8 gData_08097458[];
extern struct Unk8D0 gData_0807A1F4[]; /* 0x53 record templates, sub_0803DEC8 */
extern u8 gData_0833D1E0[];
extern u8 gData_0833D1F4[];
extern u8 gData_083A858C[];
extern u8 gData_083A8598[];
extern u32 gData_080969CC[];
extern u32 gData_080969E0[];
extern u8 gData_080995AC[];
extern u32 gData_08094E00[];
extern u16 gData_050001C0[];
extern u16 gData_04000084[];
extern u32 gData_030040DC[];
extern u16 gData_0300410C[];
extern u32 gData_030000C0[];
extern u8 gData_083D26F0[];
extern u8 gData_083D2708[];
extern u8 gData_083D2690[];
extern u8 gData_03000108[];
extern u8 gData_030001A8[];
extern u8 gData_030001B0[];
extern struct Unk473F8 *gData_03000630;
extern u32 gData_03000638[];
extern u32 *const gData_08094BB4[];
extern void *gData_080971D8[];
extern void *gData_080971EC[];
extern void *gData_080972A0[];
extern u8 gData_080B72F3[];
extern u8 gData_080B7258[];
extern u8 gData_082BF600[];
extern void *gData_08099710[];
extern struct Unk40EF4 gData_0808B2E4[];
extern struct Unk42BE8 gData_080908BC[];
extern u8 gData_083A2CF4[];
extern u8 gData_083A2D28[];
extern struct Unk447CC *gData_08096794[];
extern u8 gData_0833C79C[];
extern u8 gData_080BAF61[];
extern u8 gData_080BAF64[];
extern u8 gData_080BAF67[];
extern struct Unk65560Source gData_080BAF00[];
extern struct Unk66FB8Table gData_080BB110[];
extern s8 *gData_0807741C[];
extern u8 gData_0833BE30[];
extern s16 gData_083A9544[];
extern s16 gData_083C9544[];
extern u8 gData_083C97C4[];

// BtlObj table (IWRAM)
extern struct BtlObj **gData_03004150;
extern u8 gData_03004154;
extern u8 gData_03004158;

// Battle-object pool (IWRAM): active list, free list, free count
extern struct Unk6FDB4 *gData_030040A4;
extern struct Unk6FDB4 *gData_030040AC;
extern u32 gData_030040B4;

// Held-keys word (IWRAM, gBtlKeysHeld)
extern u16 gData_03004060;

// Record browser (IWRAM): cursor index, record table, current record
extern s16 gData_03000654;
extern struct Unk4AAF0 **gData_03000658;
extern struct Unk4AAF0 *gData_03000660;

// Part menu (sub_08039BD4): first visible row, cursor row, row table
extern s32 gData_03000400;
extern s32 gData_03000404;
extern struct Unk39BD4Row *gData_0300040C;

// Script VM context word (sub_08059DC8)
extern u32 gData_03000734;

// Name string table indexed by MainWork.unk1818 (sub_08037430)
extern void *gData_08096ECC[];

// Battle mode resource table indexed by (s8)_08032458() (sub_08032604)
extern struct Unk32604Mode gData_0807800C[];

// Battle mode resource pointers indexed by mode 0..4 (sub_080333E4)
extern void *gData_08078108[];

// (a, b) -> amount table, sub_0802E2F8
extern struct Unk2E2F8 gData_08077AC0[];

// Scene object pool (9 x 0xDC) and the scene index its tables are keyed by
// (sub_0804DB28)
extern u32 gData_03000694;
extern struct Unk68574 *gData_03000698;

// Per-scene tables indexed by gData_03000694 (sub_0804DB28)
extern struct Unk7BE04 gData_0807BE04[];
extern void *gData_080775CC[];
extern void *gData_080779A8[]; /* sub_0804188C */
extern void *gData_08098A20[];
extern void *gData_08098DF8[];
extern void *gData_080991D0[];

// Free-span allocator (IWRAM): sorted free list and spare-node list
// (sub_0806FBF8)
extern struct Unk6FBF8Span *gData_03004088;
extern struct Unk6FBF8Span *gData_03004098;

// 256 event flags (IWRAM), saved per slot by sub_08045D3C
extern struct Unk0610 gData_03000610;

// Battle-object sprite templates and their palette types, indexed 0..15
// (sub_08035054)
extern struct Unk67BB8Source *gData_080785C8[];
extern s8 gData_08078608[];

// Scrolling list state (sub_0802ECD8)
extern struct Unk2ECD8 *gData_03000278;

// Per-language item/category name tables indexed by MainWork.unk1818
// (sub_0802FA94)
extern u8 *gData_08096B5C[];
extern u8 *gData_08097084[];
extern u8 *gData_08097098[];
extern u8 *gData_080970AC[];
extern u8 *gData_080970C0[];
extern u8 *gData_080970D4[];
extern u8 *gData_080970E8[];
extern u8 *gData_080970FC[];
extern u8 *gData_08097110[];

// Input registers (IWRAM) saved/restored around sub_08033188
extern u16 gData_03003F60;
extern u16 gData_03004064;
extern u16 gData_0300406C;

// Per-language banner text and the two saved-slot ids (sub_08033188)
extern u8 *gData_080780EC[];
extern u32 gData_08078100[];

// Digit glyph table for the floating score (sub_0803370C)
extern u8 gData_0810B4E0[];

#endif // GUARD_DATA_SYMBOLS_H
