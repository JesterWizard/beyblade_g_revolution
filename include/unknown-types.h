#ifndef GUARD_UNKNOWN_TYPES_H
#define GUARD_UNKNOWN_TYPES_H

#include "gba/types.h"

/*
 * Shared layouts for still-unnamed objects. Counterpart to unknown-functions.h.
 *
 * Rules (from the AW2BHR matching style):
 * - A struct here is a superset. Adding a field is fine; moving one is not.
 *   Offsets, member types, and sizeof are load-bearing — agbcc picks the
 *   instruction from the member type and the stride from the size.
 * - filler_XX is unexplored space; unkXX is a field something actually accesses.
 *   Narrowing a filler into a field is the normal way this grows.
 * - Prefer `a->unkA0 = v` over `*(u16 *)((u8 *)a + 0xa0) = v`.
 * - Do not mark stores volatile unless the ROM kept extra narrowing
 *   (lsl #24; lsr #24 before strb). Do not use asm volatile to force registers.
 * - merge structs only when two functions are shown to share an object.
 */

#ifndef MODERN
#define MODERN 0
#endif

#if !MODERN
#define STRUCT_PAD(from, to) unsigned char _pad_##from[(to) - (from)]
#else
#define STRUCT_PAD(from, to)
#endif

/* 6-byte header: u16, u16, u32. sub_080338E4. */
struct Unk338E4 /* 0x08 */
{
    /* 00 */ u16 unk00;
    /* 02 */ u16 unk02;
    /* 04 */ u32 unk04;
};

/* Word fields at +0/+4/+8/+0xc. sub_08035878, sub_080358CC. */
struct Unk35878 /* 0x10 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
    /* 08 */ u32 unk08;
    /* 0c */ u32 unk0C;
};

/* Store at +0x2f0. sub_080346A8. */
struct Unk346A8 /* >= 0x2f4 */
{
    /* 00 */ u8 filler_00[0x2f0];
    /* 2f0 */ u32 unk2F0;
};

/* Packed u16s at +0x9a..+0xa2. sub_08068574, sub_08068584. */
struct Unk68574 /* >= 0xa4 */
{
    /* 00 */ u8 filler_00[0x9a];
    /* 9a */ u16 unk9A;
    /* 9c */ u16 unk9C;
    /* 9e */ u16 unk9E;
    /* a0 */ u16 unkA0;
    /* a2 */ u16 unkA2;
};

/* Byte at +0x19. sub_080705CC, sub_080705D4. */
struct Unk705CC /* >= 0x1a */
{
    /* 00 */ u8 filler_00[0x19];
    /* 19 */ u8 unk19;
};

/* Shift byte at +6, addend at +0x10. sub_0806BB38. */
struct Unk6BB38 /* >= 0x14 */
{
    /* 00 */ u8 filler_00[6];
    /* 06 */ u8 unk06;
    /* 07 */ u8 filler_07[9];
    /* 10 */ u32 unk10;
};

/* Six-word init block. sub_08036190. */
struct Unk36190 /* 0x18 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
    /* 08 */ u32 unk08;
    /* 0c */ u32 unk0C;
    /* 10 */ u32 unk10;
    /* 14 */ u32 unk14;
};

/* Word at +0x18. sub_08062098. */
struct Unk62098 /* >= 0x1c */
{
    /* 00 */ u8 filler_00[0x18];
    /* 18 */ u32 unk18;
};

/* 0xC-stride records pointed to by gUnk_0300046C. sub_0803EDC8. */
struct Unk0C /* 0x0c */
{
    /* 00 */ u8 filler_00[0x0c];
};

/* Battle work block (*gBattleWork). sub_080314FC. */
struct BattleWork /* >= 0x11c */
{
    /* 000 */ u8 filler_00[0x118];
    /* 118 */ u32 unk118;
};

/* 4-byte records pointed to by MainWork.unk1694. sub_0802C62C. */
struct Unk1694 /* 0x04 */
{
    /* 00 */ s8 unk00;
    /* 01 */ u8 unk01;
    /* 02 */ u8 unk02;
    /* 03 */ s8 unk03;
};

/* 0x18-stride records pointed to by MainWork.unk1688. sub_08044EE8. */
struct Unk1688Entry /* 0x18 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
    /* 08 */ u32 unk08;
    /* 0c */ u8 filler_0C[4];
    /* 10 */ u16 unk10;
    /* 12 */ u16 unk12;
    /* 14 */ u16 unk14;
    /* 16 */ u16 unk16;
};

/* Root main-work arena (*gMainWorkPtr). */
struct MainWork /* >= 0x18B4 */
{
    /* 0000 */ u8 filler_0000[0x874];
    /* 0874 */ s16 unk0874;
    /* 0876 */ u8 filler_0876[0xE12];
    /* 1688 */ struct Unk1688Entry *unk1688;
    /* 168C */ void *unk168C;
    /* 1690 */ void *unk1690;
    /* 1694 */ struct Unk1694 *unk1694;
    /* 1698 */ u8 filler_1698[0x78];
    /* 1710 */ s32 unk1710[27];
    /* 177C */ s32 unk177C;
    /* 1780 */ s32 unk1780;
    /* 1784 */ u8 filler_1784[0x14];
    /* 1798 */ u32 unk1798;
    /* 179C */ u32 unk179C;
    /* 17A0 */ u8 filler_17A0[0x60];
    /* 1800 */ u32 unk1800;
    /* 1804 */ u8 filler_1804[4];
    /* 1808 */ u32 unk1808;
    /* 180C */ u8 filler_180C[0xC];
    /* 1818 */ u8 unk1818;
    /* 1819 */ u8 unk1819;
    /* 181A */ u8 filler_181A[0x1A];
    /* 1834 */ u8 unk1834;
    /* 1835 */ u8 filler_1835[0x2C];
    /* 1861 */ s8 unk1861[0x53];
};

struct BtlObjNode /* 0x08 */
{
    /* 00 */ struct BtlObjNode *next;
    /* 04 */ struct BtlObjNode *prev;
};

/* Battle object (node + flags). sub_0806FF28, sub_080705CC. */
struct BtlObj /* >= 0x1a */
{
    /* 00 */ struct BtlObjNode *next;
    /* 04 */ struct BtlObjNode *prev;
    /* 08 */ u8 filler_08[0x11];
    /* 19 */ u8 unk19;
};

/* Two-byte cursor at *gUnk_03000538. sub_080428C4. */
struct Unk0538 /* 0x02 */
{
    /* 00 */ u8 unk00;
    /* 01 */ u8 unk01;
};

struct Unk0630 /* >= 0x48 */
{
    /* 00 */ u8 filler_00[0x40];
    /* 40 */ u32 unk40;
    /* 44 */ u32 unk44;
};

#endif /* GUARD_UNKNOWN_TYPES_H */
