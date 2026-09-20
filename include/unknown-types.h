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

struct Unk310F0Inner1;

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
    /* 00 */ u8 filler_00[4];
    /* 04 */ struct Unk310F0Inner1 *unk04;
    /* 08 */ u8 filler_08[0x2E8];
    /* 2f0 */ u32 unk2F0;
};

/* Packed u16s at +0x9a..+0xae. sub_08068574, sub_08068584, sub_08068558. */
struct Unk68574 /* >= 0xb4 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u32 unk04;
    /* 08 */ u32 unk08;
    /* 0c */ u32 unk0C;
    /* 10 */ u8 filler_10[0x64];
    /* 74 */ s32 unk74;
    /* 78 */ u32 unk78;
    /* 7c */ void *unk7C;
    /* 80 */ u8 filler_80[0x1A];
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
    /* b0 */ void *unkB0;
    /* b4 */ u8 filler_B4[4];
    /* b8 */ void *unkB8;
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

/* 0xC-stride records pointed to by gUnk_0300046C. sub_0803EDC8, sub_0803EDF0. */
struct Unk0C /* 0x0c */
{
    /* 00 */ u8 filler_00[3];
    /* 03 */ u8 unk03;
    /* 04 */ u8 filler_04[8];
};

/* Pointer at +0, word at +0xC. sub_08062044. */
struct Unk62044 /* 0x28 (padded from >= 0x26) */
{
    /* 00 */ void *unk00;
    /* 04 */ u8 filler_04[8];
    /* 0c */ void **unk0C;
    /* 10 */ s32 unk10;
    /* 14 */ s32 unk14;
    /* 18 */ u8 filler_18[0xC];
    /* 24 */ u16 unk24;
};

/* Halfword at +4, object at +0x14, pointer at +0x2C. sub_0807069C, sub_08070678. */
struct Unk7069C /* >= 0x30 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u16 unk04;
    /* 06 */ u8 filler_06[4];
    /* 0a */ u16 unk0A;
    /* 0c */ u8 filler_0C[8];
    /* 14 */ u8 unk14;
    /* 15 */ u8 filler_15[0x17];
    /* 2c */ struct Unk705CC *unk2C;
};

/* Battle work block (*gBattleWork). sub_080314FC, sub_08033530, sub_08033574. */
struct BattleWork /* >= 0x208A */
{
    /* 0000 */ u8 filler_00[0x118];
    /* 0118 */ u32 unk118;
    /* 011C */ u8 filler_011C[0x80];
    /* 019C */ struct Unk62044 unk19C[4]; /* sub_08038314 */
    /* 023C */ struct Unk7069C unk023C[4]; /* sub_08038D10 */
    /* 02FC */ u8 filler_02FC[0x1C94];
    /* 1F90 */ s32 unk1F90; /* sub_080330F4 */
    /* 1F94 */ s32 unk1F94; /* sub_080330F4 */
    /* 1F98 */ u8 unk1F98; /* sub_080330F4 */
    /* 1F99 */ u8 filler_1F99[0x13];
    /* 1FAC */ u8 unk1FAC;
    /* 1FAD */ u8 filler_1FAD[0x39];
    /* 1FE6 */ u8 unk1FE6;
    /* 1FE7 */ u8 filler_1FE7[0x35];
    /* 201C */ u32 unk201C;
    /* 2020 */ u8 filler_2020[0x68];
    /* 2088 */ u8 unk2088;
    /* 2089 */ u8 unk2089;
};

/* 4-byte records pointed to by MainWork.unk1694. sub_0802C62C. */
struct Unk1694 /* 0x04 */
{
    /* 00 */ s8 unk00;
    /* 01 */ u8 unk01;
    /* 02 */ u8 unk02;
    /* 03 */ s8 unk03;
};

/* Out-param for Unk1694 lookup. sub_0802C314 / 2C3DC / 2C4A4. */
struct Unk2C314 /* 0x0c */
{
    /* 00 */ s8 unk00;
    /* 01 */ u8 unk01;
    /* 02 */ u8 unk02;
    /* 03 */ s8 unk03;
    /* 04 */ s32 unk04;
    /* 08 */ struct Unk1694 *unk08;
};

/* {u32, u32} ROM table. sub_0802B994. */
struct Unk7709C /* 0x08 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
};

/* Stride-12 list from sub_0802B994. sub_0802B95C. */
struct Unk2B95C /* 0x0c */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ void *unk04;
    /* 08 */ u8 filler_08[4];
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

/* Per-slot record, 2 slots. sub_08046230. */
struct Unk16B0 /* 0x0c */
{
    /* 00 */ s32 unk00;
    /* 04 */ s32 unk04;
    /* 08 */ s32 unk08;
};

/* Per-slot record, 0x53 slots at MainWork+0x8D0. sub_0803E258. */
struct Unk8D0 /* 0x28 */
{
    /* 00 */ u8 filler_00[0x1C];
    /* 1C */ s8 unk1C;
    /* 1D */ u8 filler_1D[6];
    /* 23 */ u8 unk23; /* sub_0803e1f4 */
    /* 24 */ u8 filler_24[4];
};

/* Root main-work arena (*gMainWorkPtr). */
struct MainWork /* >= 0x18B4 */
{
    /* 0000 */ u8 filler_0000[0x370];
    /* 0370 */ u32 unk0370;
    /* 0374 */ u32 unk0374;
    /* 0378 */ u8 filler_0378[0x34];
    /* 03AC */ u32 unk03AC;
    /* 03B0 */ u32 unk03B0;
    /* 03B4 */ u8 filler_03B4[0x70];
    /* 0424 */ struct Unk705DC *unk0424;
    /* 0428 */ u8 filler_0428[0x24];
    /* 044C */ u32 unk044C; /* sub_08044A20, sub_08042784 */
    /* 0450 */ u32 unk0450; /* sub_08042784 */
    /* 0454 */ u8 filler_0454[0x34];
    /* 0488 */ u32 unk0488; /* sub_080424E8 */
    /* 048C */ u32 unk048C; /* sub_080424E8 */
    /* 0490 */ u8 filler_0490[0x3D8];
    /* 0868 */ u32 unk0868;
    /* 086C */ u32 unk086C;
    /* 0870 */ u8 filler_0870[4];
    /* 0874 */ s16 unk0874;
    /* 0876 */ u8 filler_0876[2];
    /* 0878 */ s8 unk0878;
    /* 0879 */ u8 filler_0879[3];
    /* 087C */ u8 unk087C[0x53]; /* sub_0803E258 */
    /* 08CF */ u8 filler_08CF[1];
    /* 08D0 */ struct Unk8D0 unk08D0[0x53]; /* sub_0803E258 */
    /* 15C8 */ s8 unk15C8;
    /* 15C9 */ s8 unk15C9;
    /* 15CA */ s8 unk15CA;
    /* 15CB */ s8 unk15CB;
    /* 15CC */ s8 unk15CC;
    /* 15CD */ u8 filler_15CD[3];
    /* 15D0 */ s16 unk15D0;
    /* 15D2 */ s16 unk15D2;
    /* 15D4 */ u8 filler_15D4[0xB4];
    /* 1688 */ struct Unk1688Entry *unk1688;
    /* 168C */ void *unk168C;
    /* 1690 */ void *unk1690;
    /* 1694 */ struct Unk1694 *unk1694;
    /* 1698 */ u8 filler_1698[0x18];
    /* 16B0 */ struct Unk16B0 unk16B0[2]; /* sub_08046230 */
    /* 16C8 */ void *unk16C8;
    /* 16CC */ u8 filler_16CC[0x14];
    /* 16E0 */ struct Unk16E0 *unk16E0;
    /* 16E4 */ struct Unk16E0 *unk16E4;
    /* 16E8 */ u8 filler_16E8[0x20]; /* sub_0805D99C */
    /* 1708 */ u32 unk1708; /* sub_0805D99C */
    /* 170C */ s32 unk170C;
    /* 1710 */ s32 unk1710[27];
    /* 177C */ s32 unk177C;
    /* 1780 */ s32 unk1780;
    /* 1784 */ u8 filler_1784[4];
    /* 1788 */ u32 unk1788;
    /* 178C */ u8 filler_178C[0xC];
    /* 1798 */ u32 unk1798;
    /* 179C */ u32 unk179C;
    /* 17A0 */ u8 filler_17A0[0x14];
    /* 17B4 */ u32 unk17B4; /* sub_08044A20 */
    /* 17B8 */ u32 unk17B8; /* sub_08044A20 */
    /* 17BC */ u8 filler_17BC[8];
    /* 17C4 */ u32 unk17C4; /* sub_08044A20 */
    /* 17C8 */ u32 unk17C8; /* sub_08044A20 */
    /* 17CC */ u8 filler_17CC[0x2A];
    /* 17F6 */ s8 unk17F6; /* sub_080435D8 */
    /* 17F7 */ s8 unk17F7; /* sub_080435D8 */
    /* 17F8 */ u8 filler_17F8[8];
    /* 1800 */ u32 unk1800;
    /* 1804 */ u8 filler_1804[4];
    /* 1808 */ u32 unk1808;
    /* 180C */ u32 unk180C;
    /* 1810 */ u8 filler_1810[8];
    /* 1818 */ u8 unk1818;
    /* 1819 */ u8 unk1819;
    /* 181A */ u8 unk181A;
    /* 181B */ u8 filler_181B[1];
    /* 181C */ u8 unk181C; /* sub_0803fdd0, sub_0805d99c */
    /* 181D */ u8 filler_181D[2];
    /* 181F */ s8 unk181F;
    /* 1820 */ u8 filler_1820[0xC];
    /* 182C */ u8 unk182C; /* sub_08042784 */
    /* 182D */ u8 filler_182D[7];
    /* 1834 */ u8 unk1834;
    /* 1835 */ u8 filler_1835[3];
    /* 1838 */ u16 unk1838;
    /* 183A */ u16 unk183A;
    /* 183C */ u8 filler_183C[0x25];
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

/* Ring buffer at *gUnk_03000538 (32 slots). sub_080428C4, sub_08042784. */
struct Unk0538 /* >= 0x144 */
{
    /* 00 */ u8 unk00;
    /* 01 */ u8 unk01;
    /* 02 */ u8 filler_02[2];
    /* 04 */ u16 unk04[32];
    /* 44 */ u32 unk44[32];
    /* C4 */ u32 unkC4[32];
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
    /* 00 */ u8 filler_00[0x5C];
    /* 5c */ u8 unk5C;
    /* 5d */ u8 unk5D;
    /* 5e */ u8 filler_5E[0x2A];
    /* 88 */ void *unk88;
    /* 8c */ u32 unk8C;
    /* 90 */ u16 unk90;
    /* 92 */ u16 unk92;
    /* 94 */ u16 unk94;
    /* 96 */ u16 unk96;
    /* 98 */ u16 unk98;
    /* 9a */ u16 unk9A;
    /* 9c */ u16 unk9C;
    /* 9e */ u8 filler_9E[2];
    /* a0 */ u16 unkA0;
    /* a2 */ u16 unkA2;
};

/* Source object for sub_080617C4. */
struct Unk617C4 /* >= 0x0d */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u8 unk04;
    /* 05 */ u8 unk05;
    /* 06 */ u8 filler_06[6];
    /* 0c */ u8 unk0C;
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

/* Double-indirect table at +0x230, word at +0x310. sub_08066BC4. */
struct Unk66BC4 /* >= 0x314 */
{
    /* 000 */ u8 filler_00[0x230];
    /* 230 */ void ***unk230;
    /* 234 */ u8 filler_234[0xDC];
    /* 310 */ u32 unk310;
};

/* Flags at +0x14. sub_0806F430. */
struct Unk4084 /* >= 0x18 */
{
    /* 00 */ u8 filler_00[0x14];
    /* 14 */ u32 unk14;
};

/* Halfword table at +0x22. sub_08038638. */
struct Unk03CC /* >= 0x24 */
{
    /* 00 */ u8 filler_00[0x22];
    /* 22 */ s16 unk22[1];
};

/* Byte at +0x14. sub_08061BDC. */
struct Unk61BDC /* >= 0x15 */
{
    /* 00 */ u8 filler_00[0x14];
    /* 14 */ u8 unk14;
};

struct Unk705DC; /* word at +0x14. sub_08031300. */

/* Bytes + words + pointer. sub_08031294, sub_080312EC. */
struct Unk312EC /* >= 0x10 */
{
    /* 00 */ s8 unk00;
    /* 01 */ s8 unk01;
    /* 02 */ u8 filler_02[2];
    /* 04 */ s32 unk04;
    /* 08 */ u8 unk08;
    /* 09 */ u8 filler_09[3];
    /* 0c */ struct Unk705DC *unk0C;
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

/* Byte at +0x2C, pointer table at +0x30. sub_08033D90. */
struct Unk33F30Inner /* >= 0x34 */
{
    /* 00 */ u8 filler_00[0x2C];
    /* 2c */ u8 unk2C;
    /* 2d */ u8 filler_2D[3];
    /* 30 */ void **unk30;
};

/* Signed store + flag. sub_08033F30, sub_08033F48, sub_08034360, sub_0803403C. */
struct Unk33F30 /* >= 0x68 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
    /* 08 */ u8 unk08;
    /* 09 */ u8 unk09;
    /* 0a */ u8 unk0A;
    /* 0b */ u8 filler_0B;
    /* 0c */ u32 unk0C;
    /* 10 */ u8 filler_10[4];
    /* 14 */ s32 unk14;
    /* 18 */ u32 unk18;
    /* 1c */ struct Unk33F30Inner *unk1C;
    /* 20 */ u32 unk20;
    /* 24 */ u8 unk24;
    /* 25 */ u8 unk25;
    /* 26 */ u8 filler_26[2];
    /* 28 */ struct Unk33F30Inner *unk28;
    /* 2c */ u32 unk2C;
    /* 30 */ u8 unk30;
    /* 31 */ u8 unk31;
    /* 32 */ u8 unk32;
    /* 33 */ u8 unk33;
    /* 34 */ struct Unk62044 unk34;
    /* 5c */ u32 unk5C;
    /* 60 */ u32 unk60;
    /* 64 */ u32 unk64;
};

/* *gUnk_0300026C then +8, halfword at +0x18. sub_0802D8C4. */
struct Unk026CInner /* >= 0x1a */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ u32 unk08;
    /* 0c */ u32 unk0C;
    /* 10 */ u8 filler_10[8];
    /* 18 */ u16 unk18;
};

struct Unk026C /* >= 0x50 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
    /* 08 */ struct Unk705DC *unk08;
    /* 0c */ struct Unk705DC *unk0C;
    /* 10 */ struct Unk705DC *unk10;
    /* 14 */ struct Unk705DC *unk14;
    /* 18 */ struct Unk705DC *unk18;
    /* 1c */ struct Unk705DC *unk1C;
    /* 20 */ struct Unk705DC *unk20;
    /* 24 */ struct Unk705DC *unk24;
    /* 28 */ struct Unk705DC *unk28;
    /* 2c */ struct Unk705DC *unk2C;
    /* 30 */ struct Unk705DC *unk30;
    /* 34 */ struct Unk705DC *unk34;
    /* 38 */ struct Unk705DC *unk38;
    /* 3c */ struct Unk705DC *unk3C;
    /* 40 */ struct Unk705DC *unk40;
    /* 44 */ u8 filler_44[4];
    /* 48 */ u8 unk48;
    /* 49 */ u8 filler_49[3];
    /* 4c */ u16 unk4C;
    /* 4e */ s16 unk4E;
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
struct Unk047C /* >= 0x834 */
{
    /* 000 */ void *unk00[0x200];
    /* 800 */ u32 unk800;
    /* 804 */ u8 filler_804[4];
    /* 808 */ u32 unk808;
    /* 80c */ u32 unk80C;
    /* 810 */ void *unk810[9];
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
    /* 00 */ u16 unk00;
    /* 02 */ u16 unk02;
    /* 04 */ u16 unk04;
    /* 06 */ u8 filler_06[2];
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

/* Walk key table at inner+unk18. sub_080680CC. */
struct Unk680CCRec /* >= 0x0a */
{
    /* 00 */ u16 unk00;
    /* 02 */ u16 unk02;
    /* 04 */ u8 filler_04[4];
    /* 08 */ u16 unk08;
};

struct Unk680CC /* >= 0x30 */
{
    /* 00 */ struct Unk68014 *unk00;
    /* 04 */ u8 filler_04[0x16];
    /* 1a */ u16 unk1A;
    /* 1c */ u16 unk1C;
    /* 1e */ u16 unk1E;
    /* 20 */ u8 filler_20[8];
    /* 28 */ u16 unk28;
    /* 2a */ u8 filler_2A[4];
    /* 2e */ u16 unk2E;
};

/* Halfword delta @ +0x1C, words @ +0x14/+0x18. sub_080361A8. */
struct Unk361A8 /* >= 0x1e */
{
    /* 00 */ u8 filler_00[0x14];
    /* 14 */ u32 unk14;
    /* 18 */ s32 unk18;
    /* 1c */ u16 unk1C;
};

/* Pointer + fields at +0x30..+0x4C. sub_080346C0. */
struct Unk346C0Inner /* >= 0x50 */
{
    /* 00 */ struct Unk705DC *unk00;
    /* 04 */ u8 filler_04[8];
    /* 0c */ s32 unk0C;
    /* 10 */ s32 unk10;
    /* 14 */ s32 unk14;
    /* 18 */ s32 unk18;
    /* 1c */ s32 unk1C;
    /* 20 */ s32 unk20;
    /* 24 */ u8 filler_24[0xC];
    /* 30 */ u32 unk30;
    /* 34 */ u32 unk34;
    /* 38 */ u8 filler_38[4];
    /* 3c */ s32 unk3C;
    /* 40 */ s32 unk40;
    /* 44 */ u8 filler_44[4];
    /* 48 */ u32 unk48;
    /* 4c */ u32 unk4C;
};

struct Unk346C0 /* >= 0x2f8 */
{
    /* 000 */ struct Unk346C0Inner *unk00;
    /* 004 */ struct Unk346C0Inner *unk04;
    /* 008 */ struct Unk35878 unk08;
    /* 018 */ u8 filler_18[0x2B4];
    /* 2cc */ u32 unk2CC;
    /* 2d0 */ u32 unk2D0;
    /* 2d4 */ u32 unk2D4;
    /* 2d8 */ u32 unk2D8;
    /* 2dc */ u32 unk2DC;
    /* 2e0 */ u32 unk2E0;
    /* 2e4 */ u32 unk2E4;
    /* 2e8 */ u32 unk2E8;
    /* 2ec */ u8 filler_2EC[8];
    /* 2f4 */ u32 unk2F4;
    /* 2f8 */ u32 unk2F8;
    /* 2fc */ u32 unk2FC;
    /* 300 */ u8 filler_300[0xC];
    /* 30c */ u8 unk30C;
    /* 30d */ u8 filler_30D[2];
    /* 30f */ u8 unk30F;
    /* 310 */ u8 unk310;
    /* 311 */ u8 unk311;
    /* 312 */ u8 filler_312[2];
    /* 314 */ u8 unk314;
};

/* Position + scaled velocity. sub_080360BC. */
struct Unk360BC /* >= 0x20 */
{
    /* 00 */ u8 filler_00[0xC];
    /* 0c */ s32 unk0C;
    /* 10 */ s32 unk10;
    /* 14 */ u8 filler_14[4];
    /* 18 */ s32 unk18;
    /* 1c */ s32 unk1C;
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
    /* 00 */ u8 filler_00[0xC];
    /* 0C */ void *unk0C; /* sub_0805d99c */
    /* 10 */ u8 filler_10[0x74];
    /* 80 */ void *unk80;
    /* 84 */ u8 unk84;
    /* 85 */ u8 filler_85[0xDF];
    /* 164 */ void *unk164;
};

/* Callback + heap slot. sub_08059D08. */
struct Unk59D08 /* >= 0x18 */
{
    /* 00 */ void *unk00;
    /* 04 */ void *unk04;
    /* 08 */ void *unk08;
    /* 0c */ void *unk0C;
    /* 10 */ u8 filler_10[4];
    /* 14 */ void *unk14;
};

/* CpuSet args at +0x80. sub_0806D958. */
struct Unk6D958Inner /* >= 0x08 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ void *unk04;
};

struct Unk6D958 /* >= 0x94 */
{
    /* 00 */ u8 filler_00[0x80];
    /* 80 */ void *unk80;
    /* 84 */ s32 unk84;
    /* 88 */ s32 unk88;
    /* 8c */ u8 filler_8C[4];
    /* 90 */ struct Unk6D958Inner *unk90;
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
struct Unk42E78 /* >= 0x04 */
{
    /* 00 */ s16 unk00;
    /* 02 */ u8 filler_02;
    /* 03 */ u8 unk03;
};

/* Lookup result. sub_080447CC. */
struct Unk447CC /* >= 0x1c */
{
    /* 00 */ void *unk00;
    /* 04 */ u8 filler_04[0x14];
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

/* Indexed byte-chain walk. sub_0806DEC8. */
struct UnkDEC8Head /* >= 0x08 */
{
    /* 00 */ u32 unk00;
    /* 04 */ s32 unk04;
};

struct UnkDEC8 /* >= 0x0c */
{
    /* 00 */ struct UnkDEC8Head *unk00;
    /* 04 */ u8 filler04[4];
    /* 08 */ u8 *unk08;
};

/* Linked list, halfword at +0x20. sub_0806FDB4. */
struct Unk6FDB4 /* >= 0x22 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ struct Unk6FDB4 *unk04;
    /* 08 */ u8 filler_08[0x18];
    /* 20 */ u16 unk20;
    /* 22 */ u16 unk22;
};

/* Byte at +0x18. sub_080703FC. */
struct Unk703FCInner /* >= 0x19 */
{
    /* 00 */ u8 filler_00[0x18];
    /* 18 */ u8 unk18;
};

struct Unk703FC /* >= 0x34 */
{
    /* 00 */ u8 filler_00[0x30];
    /* 30 */ struct Unk703FCInner *unk30;
};

/* Pointer table + count. sub_080720F0. */
struct Unk40D4 /* >= 0x10 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u32 unk04;
    /* 08 */ u8 filler_08[4];
    /* 0c */ void **unk0C;
};

/* Nested Unk7069C at +0x34. sub_08054558, sub_08054454. */
struct Unk070C /* >= 0x44 */
{
    /* 00 */ void *unk00[13];
    /* 34 */ struct Unk7069C unk34;
};

/* Fields at +0x224 / +0x348. sub_0806F174. */
struct Unk6F174 /* >= 0x34c */
{
    /* 000 */ u8 filler_00[0x224];
    /* 224 */ void *unk224;
    /* 228 */ u8 filler_228[0x120];
    /* 348 */ void *unk348;
};

/* Four pointers at 0x030005F0. sub_08043C28. */
struct Unk05F0 /* 0x10 */
{
    /* 00 */ void *unk00;
    /* 04 */ void *unk04;
    /* 08 */ void *unk08;
    /* 0c */ void *unk0C;
};

/* Stride-8 slot table at 0x03000770. sub_08061C48. */
struct Unk0770 /* 0x08 */
{
    /* 00 */ void *unk00;
    /* 04 */ u16 unk04;
    /* 06 */ u16 unk06;
};

/* Sprite/obj init. sub_080618A8. */
struct Unk618A8 /* >= 0x16 */
{
    /* 00 */ void *unk00;
    /* 04 */ u32 unk04;
    /* 08 */ u16 unk08;
    /* 0a */ u16 unk0A;
    /* 0c */ u16 unk0C;
    /* 0e */ u16 unk0E;
    /* 10 */ u16 unk10;
    /* 12 */ u16 unk12;
    /* 14 */ u8 unk14;
    /* 15 */ u8 unk15;
};


/* Nested byte at inner+0x21 / +0x24. sub_080310F0, sub_08031094. */
struct Unk310F0Inner2 /* >= 0x25 */
{
    /* 00 */ u8 filler_00[0x21];
    /* 21 */ s8 unk21;
    /* 22 */ u8 filler_22[2];
    /* 24 */ s8 unk24;
};

struct Unk310F0Inner1 /* >= 0x2c */
{
    /* 00 */ u8 filler_00[0x28];
    /* 28 */ struct Unk310F0Inner2 *unk28;
};

struct Unk310F0a /* >= 0x08 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ struct Unk310F0Inner1 *unk04;
};

struct Unk310F0b /* >= 0x1a */
{
    /* 00 */ u8 filler_00[0x18];
    /* 18 */ s16 unk18;
};

/* Pointer array at +0x220. sub_08041394. */
struct Unk41394 /* >= 0x240 */
{
    /* 000 */ u8 filler_00[0x220];
    /* 220 */ void *unk220[8];
};

/* Fields at +0xCC / +0xD0. sub_08062758. */
struct Unk62790Obj /* >= 0xd4 */
{
    /* 00 */ u8 filler_00[0xCC];
    /* CC */ u32 unkCC;
    /* D0 */ u32 unkD0;
};

/* Halfword stride blit. sub_080726E0. */
struct Unk726E0 /* >= 0x10 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u16 unk04;
    /* 06 */ u16 unk06;
    /* 08 */ s16 unk08;
    /* 0a */ u8 filler_0A[2];
    /* 0c */ void *unk0C;
};

/* Header + flag at +0x98. sub_08067F3C. */
struct Unk67F3C /* >= 0x99 */
{
    /* 00 */ struct Unk68014 *unk00;
    /* 04 */ u8 filler_04[0x94];
    /* 98 */ u8 unk98;
};

struct Unk705DC /* >= 0x1a */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ struct Unk705DC *unk04;
    /* 08 */ u32 unk08;
    /* 0c */ u32 unk0C;
    /* 10 */ u32 unk10;
    /* 14 */ u16 unk14;
    /* 16 */ u16 unk16;
    /* 18 */ u16 unk18;
};

/* 0x84-stride records. sub_0806F1A0. */
struct Unk6F1A0 /* 0x84 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u8 filler_04[0x80];
};

/* Linked Unk705DC list + flag. sub_080712CC. */
struct Unk712CC /* >= 0x20 */
{
    /* 00 */ u8 filler_00[0xE];
    /* 0e */ u8 unk0E;
    /* 0f */ u8 filler_0F[5];
    /* 14 */ struct Unk705DC *unk14;
    /* 18 */ u8 filler_18[4];
    /* 1c */ s32 unk1C;
};

/* DISPCNT copy + flags. sub_0806EE24. */
struct Unk6EE24 /* >= 0x35a */
{
    /* 000 */ u8 filler_00[0x355];
    /* 355 */ u8 unk355;
    /* 356 */ u8 unk356;
    /* 357 */ u8 filler_357;
    /* 358 */ u16 unk358;
};

/* sub_080302A8 */
struct Unk302A8Inner /* >= 0x10 */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
};

struct Unk302A8 /* >= 0x18 */
{
    /* 00 */ struct Unk302A8Inner *unk00;
    /* 04 */ u8 filler_04[4];
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
    /* 10 */ u8 filler_10[4];
    /* 14 */ s32 unk14;
};

struct Unk302A8Src /* >= 0x0c */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ s32 unk08;
};

/* sub_08030F00 */
struct Unk30F00Inner /* >= 0x34 */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
    /* 10 */ u8 filler_10[0x20];
    /* 30 */ struct Unk705DC *unk30;
};

struct Unk30F00Mid /* >= 0x04 */
{
    /* 00 */ struct Unk30F00Inner *unk00;
};

struct Unk30F00Src /* >= 0x04 */
{
    /* 00 */ struct Unk30F00Mid *unk00;
};

struct Unk30F00 /* >= 0x10 */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
};

/* Midpoint + scaled distance. sub_08036264. */
struct Unk36264 /* >= 0x0c */
{
    /* 00 */ s32 unk00;
    /* 04 */ s32 unk04;
    /* 08 */ s32 unk08;
};

struct Unk59C6C /* 0x3c */
{
    /* 00 */ void *unk00;
    /* 04 */ void *unk04;
    /* 08 */ void *unk08;
    /* 0c */ void *unk0C;
    /* 10 */ void *unk10;
    /* 14 */ u32 unk14;
    /* 18 */ void *unk18;
    /* 1c */ void *unk1C;
    /* 20 */ void *unk20;
    /* 24 */ void *unk24;
    /* 28 */ void *unk28;
    /* 2c */ void *unk2C;
    /* 30 */ void *unk30;
    /* 34 */ void *unk34;
    /* 38 */ void *unk38;
};

/* Source blob + owner link for sub_08059C98. */
struct Unk59C98Src /* >= 0x24 */
{
    /* 00 */ void *unk00;
    /* 04 */ void *unk04;
    /* 08 */ void *unk08;
    /* 0c */ u32 unk0C;
    /* 10 */ void *unk10;
    /* 14 */ void *unk14;
    /* 18 */ void *unk18;
    /* 1c */ void *unk1C;
    /* 20 */ void *unk20;
};

struct Unk59C98Owner /* >= 0xcc */
{
    /* 00 */ u8 filler_00[0xC8];
    /* c8 */ struct Unk59C6C *unkC8;
};

/* Signed bytes + u8 into ROM tables. sub_0803E328 / 3E374 / 3E3C0. */
struct Unk3E328 /* >= 0x21 */
{
    /* 00 */ u8 filler_00[0x1D];
    /* 1d */ s8 unk1D;
    /* 1e */ s8 unk1E;
    /* 1f */ u8 filler_1F;
    /* 20 */ u8 unk20;
};

/* Callback at inner+8. sub_0806D748. */
struct Unk6D748Inner /* >= 0x0c */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ void *unk08;
};

struct Unk6D748 /* >= 0x98 */
{
    /* 00 */ u8 filler_00[0x94];
    /* 94 */ struct Unk6D748Inner *unk94;
};

/* Stride-0x28 slot. sub_08071E84 / sub_08071EE4 / sub_08071E44. */
struct Unk71E84 /* 0x28 */
{
    /* 00 */ s32 unk00;
    /* 04 */ s32 unk04;
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
    /* 10 */ u16 unk10;
    /* 12 */ u8 filler_12[2];
    /* 14 */ u16 unk14;
    /* 16 */ u8 unk16;
    /* 17 */ u8 unk17;
    /* 18 */ u32 unk18;
    /* 1c */ void *unk1C;
    /* 20 */ void *unk20;
    /* 24 */ u16 unk24;
};

/* Flag + two Unk346C0 slots. sub_08033A5C. */
struct Unk33A5C /* >= 0x0c */
{
    /* 00 */ u8 unk00;
    /* 01 */ u8 filler_01[3];
    /* 04 */ struct Unk346C0 *unk04;
    /* 08 */ struct Unk346C0 *unk08;
};

/* 16-byte slot. sub_0806A580. */
struct Unk6A580 /* 0x10 */
{
    /* 00 */ void *unk00;
    /* 04 */ void *unk04;
    /* 08 */ u8 filler_08[8];
};

/* Byte at +6. sub_08060758. */
struct Unk0758 /* >= 0x07 */
{
    /* 00 */ u8 filler_00[6];
    /* 06 */ u8 unk06;
};

struct Unk6F8C4 /* >= 0x08 */
{
    /* 00 */ struct Unk6F8C4 *unk00;
    /* 04 */ struct Unk6F8C4 *unk04;
};

/* Destination of sub_080361CC's field copy/negate. */
struct Unk361CCDst /* >= 0x54 */
{
    /* 00 */ u8 filler_00[0x28];
    /* 28 */ s32 unk28;
    /* 2c */ u8 filler_2C[4];
    /* 30 */ s32 unk30;
    /* 34 */ s32 unk34;
    /* 38 */ u8 filler_38[0x10];
    /* 48 */ s16 unk48;
    /* 4a */ s16 unk4A;
    /* 4c */ s32 unk4C;
    /* 50 */ s32 unk50;
};

/* Sub-entry written by sub_08066AD4. */
struct Unk66AD4Entry
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
};

/* sub_08066AD4 */
struct Unk66AD4 /* >= 0x30c */
{
    /* 000 */ u8 filler_000[0x28C];
    /* 28c */ struct Unk66AD4Entry *unk28C;
    /* 290 */ u8 filler_290[0x74];
    /* 304 */ s32 unk304;
    /* 308 */ s32 unk308;
};

/* sub_080726A4 */
struct Unk726A4 /* >= 0x14 */
{
    /* 00 */ s32 unk00;
    /* 04 */ s16 unk04;
    /* 06 */ s16 unk06;
    /* 08 */ s16 unk08;
    /* 0a */ u8 filler_0A[2];
    /* 0c */ s32 unk0C;
    /* 10 */ s32 *unk10;
};

/* sub_0803593C */
struct Unk3593C /* >= 0x50 */
{
    /* 00 */ s32 unk00;
    /* 04 */ s32 unk04;
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
    /* 10 */ s32 unk10;
    /* 14 */ s32 unk14;
    /* 18 */ s32 unk18;
    /* 1c */ s32 unk1C;
    /* 20 */ s32 unk20;
    /* 24 */ s32 unk24;
    /* 28 */ s32 unk28;
    /* 2c */ s32 unk2C;
    /* 30 */ s32 unk30;
    /* 34 */ s32 unk34;
    /* 38 */ s32 unk38;
    /* 3c */ s32 unk3C;
    /* 40 */ s32 unk40;
    /* 44 */ s32 unk44;
    /* 48 */ s32 unk48;
    /* 4c */ s32 unk4C;
};

/* Pointed to by Unk41348.unk248. sub_08041348. */
struct Unk41348Inner /* >= 0x4e */
{
    /* 00 */ u8 filler_00[0x4A];
    /* 4a */ u16 unk4A;
    /* 4c */ u16 unk4C;
};

/* sub_08041348 */
struct Unk41348 /* >= 0x323 */
{
    /* 000 */ u8 filler_000[0x248];
    /* 248 */ struct Unk41348Inner *unk248;
    /* 24c */ u8 filler_24C[0x8B];
    /* 2d7 */ u8 unk2D7;
    /* 2d8 */ u8 filler_2D8[0x44];
    /* 31c */ u16 unk31C;
    /* 31e */ u16 unk31E;
    /* 320 */ u16 unk320;
    /* 322 */ u16 unk322;
};

/* sub_0802F520 */
struct Unk2F520Inner /* >= 0x10 */
{
    /* 00 */ u8 filler_00[0xC];
    /* 0c */ s32 unk0C;
};

struct Unk2F520 /* >= 0x2fd */
{
    /* 000 */ u8 filler_000[0x288];
    /* 288 */ struct Unk2F520Inner *unk288;
    /* 28c */ struct Unk2F520Inner *unk28C;
    /* 290 */ u8 filler_290[0x45];
    /* 2d5 */ s8 unk2D5;
    /* 2d6 */ u8 filler_2D6[0x26];
    /* 2fc */ s8 unk2FC;
};

/* Source object read by sub_08070604 (unk5 at +5). */
struct Unk70604Src /* >= 0x06 */
{
    /* 00 */ u8 filler_00[5];
    /* 05 */ u8 unk05;
};

/* sub_08070604 */
struct Unk70604 /* >= 0x2d */
{
    /* 00 */ s32 unk00;
    /* 04 */ s32 unk04;
    /* 08 */ s16 unk08;
    /* 0a */ s16 unk0A;
    /* 0c */ s16 unk0C;
    /* 0e */ u8 unk0E;
    /* 0f */ u8 unk0F;
    /* 10 */ u16 unk10;
    /* 12 */ u16 unk12;
    /* 14 */ s32 unk14;
    /* 18 */ s32 unk18;
    /* 1c */ s32 unk1C;
    /* 20 */ s32 unk20;
    /* 24 */ struct Unk70604Src *unk24;
    /* 28 */ u8 unk28;
    /* 29 */ u8 unk29;
    /* 2a */ s8 unk2A;
    /* 2b */ u8 unk2B;
    /* 2c */ s32 unk2C;
};

/* *gUnk_03000750. sub_080604C8. */
struct Unk604C8 /* >= 0x18 */
{
    /* 00 */ u8 unk00;
    /* 01 */ u8 unk01;
    /* 02 */ u8 unk02;
    /* 03 */ u8 unk03;
    /* 04 */ u8 unk04;
    /* 05 */ u8 unk05;
    /* 06 */ u8 unk06;
    /* 07 */ u8 unk07;
    /* 08 */ u16 unk08;
    /* 0a */ u16 unk0A;
    /* 0c */ u16 unk0C;
    /* 0e */ u16 unk0E;
    /* 10 */ u8 unk10;
    /* 11 */ u8 unk11;
    /* 12 */ u8 unk12;
    /* 13 */ u8 unk13;
    /* 14 */ u16 unk14;
    /* 16 */ u16 unk16;
};

/* Countdown word at +0x2FC, flag word at +0x304. sub_08038314. */
struct Unk38314 /* >= 0x308 */
{
    /* 000 */ u8 filler_000[0x2FC];
    /* 2FC */ u32 unk2FC;
    /* 300 */ u8 filler_300[4];
    /* 304 */ s32 unk304;
};

/* Palette-slot bookkeeping (*gUnk_030003CC). sub_08038438, sub_08038580, sub_080385DC, sub_08038638. */
struct Unk3CC /* >= 0x32 */
{
    /* 00 */ u16 unk00[16];
    /* 20 */ u16 unk20;
    /* 22 */ s16 unk22[16];
};

/* *gUnk_03000554 target: byte array at +0x08, u8 field at +0x02. sub_080435D8, sub_080436B0. */
struct Unk0554 /* >= 0x09 */
{
    /* 00 */ u8 filler_00[2];
    /* 02 */ u8 unk02;
    /* 03 */ u8 filler_03[5];
    /* 08 */ u8 unk08[0x7F];
};

/* Fixed-point (x.8) coordinate pair. sub_08042390. */
struct Unk42390 /* >= 0x0c */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ s32 unk04;
    /* 08 */ s32 unk08;
};

/* 62-entry ROM table @ 0x08075AB8, stride 0x1C. Key at +0x04, payload at +0x00.
 * sub_0802B930. */
struct Unk75AB8 /* 0x1c */
{
    /* 00 */ s32 unk00;
    /* 04 */ s16 unk04;
    /* 06 */ u8 filler_06[0x16];
};

#endif /* GUARD_UNKNOWN_TYPES_H */
