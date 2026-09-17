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

/* Root main-work arena (*gMainWorkPtr). sub_080628E4. */
struct MainWork /* >= 0x1819 */
{
    /* 0000 */ u8 filler_0000[0x1800];
    /* 1800 */ u32 unk1800;
    /* 1804 */ u8 filler_1804[0x14];
    /* 1818 */ u8 unk1818;
};

struct BtlObjNode
{
    struct BtlObjNode *next;
    struct BtlObjNode *prev;
};

#endif /* GUARD_UNKNOWN_TYPES_H */
