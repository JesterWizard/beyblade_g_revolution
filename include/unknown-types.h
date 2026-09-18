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

/* Packed u16s at +0x9a..+0xae. sub_08068574, sub_08068584, sub_08068558. */
struct Unk68574 /* >= 0xb4 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u32 unk04;
    /* 08 */ u32 unk08;
    /* 0c */ u32 unk0C;
    /* 10 */ u8 filler_10[0x8A];
    /* 9a */ u16 unk9A;
    /* 9c */ u16 unk9C;
    /* 9e */ u16 unk9E;
    /* a0 */ u16 unkA0;
    /* a2 */ u16 unkA2;
    /* a4 */ u8 filler_A4[4];
    /* a8 */ u16 unkA8;
    /* aa */ u16 unkAA;
    /* ac */ u16 unkAC;
    /* ae */ u16 unkAE;
    /* b0 */ u32 unkB0;
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

/* Battle work block (*gBattleWork). sub_080314FC, sub_08033530. */
struct BattleWork /* >= 0x2089 */
{
    /* 0000 */ u8 filler_00[0x118];
    /* 0118 */ u32 unk118;
    /* 011C */ u8 filler_011C[0x1E90];
    /* 1FAC */ u8 unk1FAC;
    /* 1FAD */ u8 filler_1FAD[0x6F];
    /* 201C */ u32 unk201C;
    /* 2020 */ u8 filler_2020[0x68];
    /* 2088 */ u8 unk2088;
};

/* 4-byte records pointed to by MainWork.unk1694. sub_0802C62C. */
struct Unk1694 /* 0x04 */
{
    /* 00 */ s8 unk00;
    /* 01 */ u8 unk01;
    /* 02 */ u8 unk02;
    /* 03 */ s8 unk03;
};

/* {u32, u32} ROM table. sub_0802B994. */
struct Unk7709C /* 0x08 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
};

/* {ptr, word} records. sub_08043B90, sub_08043BDC. */
struct Unk16E0 /* 0x08 */
{
    /* 00 */ void *unk00;
    /* 04 */ s32 unk04;
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
    /* 1698 */ u8 filler_1698[0x30];
    /* 16C8 */ void *unk16C8;
    /* 16CC */ u8 filler_16CC[0x14];
    /* 16E0 */ struct Unk16E0 *unk16E0;
    /* 16E4 */ struct Unk16E0 *unk16E4;
    /* 16E8 */ u8 filler_16E8[0x28];
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
    /* 181A */ u8 unk181A;
    /* 181B */ u8 filler_181B[4];
    /* 181F */ s8 unk181F;
    /* 1820 */ u8 filler_1820[0x14];
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

/* Byte at +0x16, halfword at +0x10. sub_08071F84, sub_08071FC8. */
struct Unk71F84 /* >= 0x17 */
{
    /* 00 */ u8 filler_00[0x10];
    /* 10 */ u16 unk10;
    /* 12 */ u8 filler_12[4];
    /* 16 */ u8 unk16;
};

/* *gUnk_03000798. sub_08061784 family, sub_080615EC. */
struct Unk0798 /* >= 0xa2 */
{
    /* 00 */ u8 filler_00[0x8C];
    /* 8c */ u32 unk8C;
    /* 90 */ u16 unk90;
    /* 92 */ u16 unk92;
    /* 94 */ u8 filler_94[4];
    /* 98 */ u16 unk98;
    /* 9a */ u8 filler_9A[2];
    /* 9c */ u16 unk9C;
    /* 9e */ u8 filler_9E[2];
    /* a0 */ u16 unkA0;
};

/* Stores at +0x18/+0x1c/+0x20, pointer at +8. sub_08062634, sub_08062238. */
struct Unk62634 /* >= 0x24 */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ void *unk08;
    /* 0c */ u8 filler_0C[0xC];
    /* 18 */ u32 unk18;
    /* 1c */ u32 unk1C;
    /* 20 */ u32 unk20;
};

/* Byte at +0x14. sub_08061BDC. */
struct Unk61BDC /* >= 0x15 */
{
    /* 00 */ u8 filler_00[0x14];
    /* 14 */ u8 unk14;
};

/* Halfword at +4, object at +0x14, pointer at +0x2C. sub_0807069C, sub_08070678. */
struct Unk7069C /* >= 0x30 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u16 unk04;
    /* 06 */ u8 filler_06[0xE];
    /* 14 */ u8 unk14;
    /* 15 */ u8 filler_15[0x17];
    /* 2c */ struct Unk705CC *unk2C;
};

/* Bytes + words + pointer. sub_08031294, sub_080312EC. */
struct Unk312EC /* >= 0x10 */
{
    /* 00 */ u8 unk00;
    /* 01 */ u8 unk01;
    /* 02 */ u8 filler_02[2];
    /* 04 */ s32 unk04;
    /* 08 */ u32 unk08;
    /* 0c */ void *unk0C;
};

/* Word count + dest. sub_08062728. */
struct Unk62728 /* >= 0x0c */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u32 *unk04;
    /* 08 */ u32 unk08;
};

/* ldrsh at +0, pointer at +4. sub_08033958. */
struct Unk33958 /* >= 0x08 */
{
    /* 00 */ s16 unk00;
    /* 02 */ u8 filler_02[2];
    /* 04 */ s32 *unk04;
};

/* Clear fields if non-NULL. sub_08061E40. */
struct Unk61E40 /* >= 0x16 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u32 unk04;
    /* 08 */ u8 filler_08[2];
    /* 0a */ u16 unk0A;
    /* 0c */ u8 filler_0C[4];
    /* 10 */ u16 unk10;
    /* 12 */ u8 filler_12[3];
    /* 15 */ u8 unk15;
};

/* Compare **a vs b, then base + (b<<4). sub_0806DEF4. */
struct Unk6DEF4 /* >= 0x08 */
{
    /* 00 */ s32 *unk00;
    /* 04 */ s32 unk04;
};

/* Pointer at +0, word at +0xC. sub_08062044. */
struct Unk62044 /* >= 0x10 */
{
    /* 00 */ void *unk00;
    /* 04 */ u8 filler_04[8];
    /* 0c */ u32 unk0C;
};

/* Signed store + flag. sub_08033F30, sub_08033F48, sub_08034360, sub_0803403C. */
struct Unk33F30 /* >= 0x68 */
{
    /* 00 */ u8 filler_00[0x14];
    /* 14 */ s32 unk14;
    /* 18 */ u32 unk18;
    /* 1c */ u8 unk1C;
    /* 1d */ u8 filler_1D[3];
    /* 20 */ u32 unk20;
    /* 24 */ u8 unk24;
    /* 25 */ u8 unk25;
    /* 26 */ u8 filler_26[2];
    /* 28 */ u32 unk28;
    /* 2c */ u32 unk2C;
    /* 30 */ u8 unk30;
    /* 31 */ u8 unk31;
    /* 32 */ u8 unk32;
    /* 33 */ u8 unk33;
    /* 34 */ struct Unk62044 unk34;
    /* 44 */ u8 filler_44[0x18];
    /* 5c */ u32 unk5C;
    /* 60 */ u32 unk60;
    /* 64 */ u32 unk64;
};

/* *gUnk_0300026C then +8, halfword at +0x18. sub_0802D8C4. */
struct Unk026CInner /* >= 0x1a */
{
    /* 00 */ u8 filler_00[0x18];
    /* 18 */ u16 unk18;
};

struct Unk026C /* >= 0x50 */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ struct Unk026CInner *unk08;
    /* 0c */ u8 filler_0C[0x42];
    /* 4e */ u16 unk4E;
};

/* Free pointer at +0x10. sub_08072CC0. */
struct Unk72CC0 /* >= 0x14 */
{
    /* 00 */ u8 filler_00[0x10];
    /* 10 */ void *unk10;
};

/* IWRAM triple at 0x03000180. sub_08067890. */
struct Unk0180 /* 0x0c */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
    /* 08 */ u32 unk08;
};

/* Byte at +0x5E. sub_08069C14. */
struct Unk69C14 /* >= 0x5f */
{
    /* 00 */ u8 filler_00[0x5E];
    /* 5e */ u8 unk5E;
};

/* Word at +0x800, count at +0x80C, pointer table at +0. sub_080400C0, sub_080405E8, sub_08040530. */
struct Unk047C /* >= 0x814 */
{
    /* 000 */ void *unk00[0x200];
    /* 800 */ u32 unk800;
    /* 804 */ u8 filler_804[8];
    /* 80c */ u32 unk80C;
    /* 810 */ u32 unk810;
};

/* Stride-4 u16 table. sub_0802B8BC. */
struct Unk0264 /* 0x04 */
{
    /* 00 */ u16 unk00;
    /* 02 */ u16 unk02;
};

/* Bytes at +0x34/+0x35 from gUnk_03000970. */
struct Unk0970 /* >= 0x36 */
{
    /* 00 */ u8 filler_00[0x34];
    /* 34 */ u8 unk34;
    /* 35 */ u8 unk35;
};

/* Word at +0x114 from gUnk_030007B0. sub_08062A1C. */
struct Unk07B0 /* >= 0x118 */
{
    /* 000 */ u8 filler_00[0x114];
    /* 114 */ u32 unk114;
};

/* Header + 8-byte records. sub_08068014. */
struct Unk68014Rec /* 0x08 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
};

struct Unk68014 /* >= 0x28 */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ u32 unk08;
    /* 0c */ u8 filler_0C[0xC];
    /* 18 */ u32 unk18;
    /* 1c */ u8 filler_1C[4];
    /* 20 */ struct Unk68014Rec unk20[1];
};

/* Pointer + fields at +0x30..+0x4C. sub_080346C0. */
struct Unk346C0Inner /* >= 0x50 */
{
    /* 00 */ u8 filler_00[0x30];
    /* 30 */ u32 unk30;
    /* 34 */ u32 unk34;
    /* 38 */ u8 filler_38[0x10];
    /* 48 */ u32 unk48;
    /* 4c */ u32 unk4C;
};

struct Unk346C0 /* >= 0x04 */
{
    /* 00 */ struct Unk346C0Inner *unk00;
};

/* Word at +0xC, then *a +8. sub_0806BE08. */
struct Unk6BE08Inner /* >= 0x0c */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ u32 unk08;
};

struct Unk6BE08 /* >= 0x10 */
{
    /* 00 */ struct Unk6BE08Inner *unk00;
    /* 04 */ u8 filler_04[8];
    /* 0c */ u32 unk0C;
};

/* Unk35878 at +8, flags at +0x18. sub_08034FF8, sub_08034FDC. */
struct Unk34FF8 /* >= 0x1a */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ struct Unk35878 unk08;
    /* 18 */ u8 unk18;
    /* 19 */ u8 unk19;
};

/* Slot list at +4. sub_080626B8. */
struct Unk626B8 /* >= 0x0c */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u32 *unk04;
    /* 08 */ u32 unk08;
};

/* Flag at +8, pointers at +0/+4. sub_08045A84. */
struct Unk45A84 /* >= 0x0c */
{
    /* 00 */ void *unk00;
    /* 04 */ void *unk04;
    /* 08 */ u8 unk08;
};

/* 16 pointer slots. sub_08047594. */
struct Unk47594 /* >= 0x10 */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ u32 unk08;
    /* 0c */ u32 unk0C;
};

/* Nested block at +0x80. sub_0805D1AC, sub_0805DA70. */
struct Unk0748 /* >= 0x168 */
{
    /* 00 */ u8 filler_00[0x80];
    /* 80 */ void *unk80;
    /* 84 */ u8 unk84;
    /* 85 */ u8 filler_85[0xDF];
    /* 164 */ void *unk164;
};

/* IWRAM object at 0x03000380. sub_08033C1C. */
struct Unk0380 /* >= 0x1c */
{
    /* 00 */ u8 filler_00[9];
    /* 09 */ u8 unk09;
    /* 0a */ u8 unk0A;
    /* 0b */ u8 filler_0B;
    /* 0c */ struct Unk35878 unk0C;
};

/* Table row returned by sub_08042E78. */
struct Unk42E78 /* >= 0x02 */
{
    /* 00 */ s16 unk00;
};

/* Lookup result. sub_080447CC. */
struct Unk447CC /* >= 0x1c */
{
    /* 00 */ u8 filler_00[0x18];
    /* 18 */ void *unk18;
};

/* Pointer + byte at +0x2D0. sub_0803484C. */
struct Unk3484C /* >= 0x2d1 */
{
    /* 000 */ void *unk00;
    /* 004 */ u8 filler_04[0x2CC];
    /* 2d0 */ u8 unk2D0;
};

/* Position pair. sub_08070C98. */
struct Unk70C98 /* >= 0x08 */
{
    /* 00 */ s32 unk00;
    /* 04 */ s32 unk04;
};

/* Pointer table at +0x114. sub_0806BDA8. */
struct Unk6BDA8 /* >= 0x118 */
{
    /* 000 */ u8 filler_00[0x114];
    /* 114 */ void **unk114;
};

/* Linked list, halfword at +0x20. sub_0806FDB4. */
struct Unk6FDB4 /* >= 0x22 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ struct Unk6FDB4 *unk04;
    /* 08 */ u8 filler_08[0x18];
    /* 20 */ u16 unk20;
};

#endif /* GUARD_UNKNOWN_TYPES_H */
