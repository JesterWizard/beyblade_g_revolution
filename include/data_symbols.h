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
extern u8 gData_080BB748[];
extern s16 gData_08091204[];
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
extern u32 gData_03000198[];
extern u8 gData_03000290[];
extern u8 gData_030002A0[];
extern void *gData_03000508[];
extern u32 gData_03000534[];
extern u16 gData_03000504[];
extern u8 gData_03000770[];
extern u32 gData_03000794[];
extern struct Unk0798 *gData_03000798;

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

extern u8 gData_030040E4[];
extern u8 gData_030040C4[];
extern u8 gData_030000C8[];
extern u8 gData_083D2578[];

extern u8 gData_03000634[];
extern u8 gData_0300063C[];

#endif // GUARD_DATA_SYMBOLS_H
extern u8 gData_030040A8[];
extern u8 gData_030040B8[];
