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
 *   (lsl #24; lsr #24 before strb). Do not use `register` or `asm volatile`
 *   to force registers.
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
struct Unk310F0Inner2;
struct Unk705DC;
struct Unk312EC;
struct Unk346C0;
struct Unk361CCDst;

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

/* Nested presence chain checked by sub_08041E14. */
struct Unk41E14Node /* >= 0x14 */
{
    /* 00 */ u8 filler_00[0x10];
    /* 10 */ struct Unk41E14Node *unk10;
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
struct Unk68574 /* >= 0xdc */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u32 unk04;
    /* 08 */ u32 unk08;
    /* 0c */ u32 unk0C;
    /* 10 */ u8 filler_10[0x0A];
    /* 1a */ s16 unk1A; /* sub_0803559C */
    /* 1c */ u8 filler_1C[0x1E];
    /* 3a */ u8 unk3A; /* sub_08035258 */
    /* 3b */ u8 filler_3B[0x17];
    /* 52 */ s16 unk52; /* sub_080353A0 */
    /* 54 */ u8 filler_54[0x1C];
    /* 70 */ void *unk70; /* sub_0803531C */
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
    /* bc */ u16 unkBC; /* sub_0804188C */
    /* be */ u8 filler_BE[0x0A];
    /* c8 */ struct Unk41E14Node *unkC8;
    /* cc */ u8 filler_CC[8];
    /* d4 */ void *unkD4; /* sub_08041DB4 */
    /* d8 */ void *unkD8; /* sub_08041DB4 */
};

/* State initialized by sub_08067BB8. */
struct Unk67BB8 /* >= 0xc4 */
{
    /* 00 */ void *unk00;
    /* 04 */ s32 unk04;
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
    /* 10 */ u8 unk10;
    /* 11 */ u8 unk11;
    /* 12 */ u16 unk12;
    /* 14 */ u16 unk14;
    /* 16 */ u16 unk16;
    /* 18 */ u16 unk18;
    /* 1a */ u16 unk1A;
    /* 1c */ u16 unk1C;
    /* 1e */ u16 unk1E;
    /* 20 */ u16 unk20;
    /* 22 */ u16 unk22;
    /* 24 */ u8 filler_24[4];
    /* 28 */ u16 unk28;
    /* 2a */ u16 unk2A;
    /* 2c */ u16 unk2C;
    /* 2e */ u16 unk2E;
    /* 30 */ u8 unk30;
    /* 31 */ u8 unk31;
    /* 32 */ u8 filler_32[6];
    /* 38 */ u8 unk38;
    /* 39 */ u8 unk39;
    /* 3a */ u8 unk3A;
    /* 3b */ u8 unk3B;
    /* 3c */ u32 unk3C;
    /* 40 */ u32 unk40;
    /* 44 */ u32 unk44;
    /* 48 */ u32 unk48;
    /* 4c */ u32 unk4C;
    /* 50 */ u32 unk50;
    /* 54 */ u32 unk54;
    /* 58 */ u32 unk58;
    /* 5c */ u8 filler_5C[4];
    /* 60 */ u16 unk60;
    /* 62 */ u8 filler_62[2];
    /* 64 */ u32 unk64;
    /* 68 */ u32 unk68;
    /* 6c */ u32 unk6C;
    /* 70 */ u32 unk70;
    /* 74 */ s32 unk74;
    /* 78 */ u32 unk78;
    /* 7c */ u32 unk7C;
    /* 80 */ u32 unk80;
    /* 84 */ s32 unk84;
    /* 88 */ u32 unk88;
    /* 8c */ u8 unk8C;
    /* 8d */ u8 unk8D;
    /* 8e */ u8 filler_8E[2];
    /* 90 */ u32 unk90;
    /* 94 */ u32 unk94;
    /* 98 */ u8 unk98;
    /* 99 */ u8 filler_99[7];
    /* a0 */ u16 unkA0;
    /* a2 */ u16 unkA2;
    /* a4 */ u8 unkA4;
    /* a5 */ u8 unkA5;
    /* a6 */ u8 filler_A6[2];
    /* a8 */ u16 unkA8;
    /* aa */ u16 unkAA;
    /* ac */ u16 unkAC;
    /* ae */ u16 unkAE;
    /* b0 */ u32 unkB0;
    /* b4 */ u32 unkB4;
    /* b8 */ u32 unkB8;
    /* bc */ u16 unkBC;
    /* be */ u8 filler_BE[2];
    /* c0 */ u32 unkC0;
};

/* Source record copied into the sub_08067BB8 state. */
struct Unk67BB8Source /* >= 0x18 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u8 unk04;
    /* 05 */ u8 unk05;
    /* 06 */ u8 unk06;
    /* 07 */ u8 unk07;
    /* 08 */ u32 unk08;
    /* 0c */ u8 unk0C;
    /* 0d */ u8 filler_0D[7];
    /* 14 */ u32 unk14;
};

/* Three animation blocks and dispatch state. sub_08035258. */
struct Unk35258 /* >= 0x2c6 */
{
    /* 000 */ struct Unk346C0Inner *unk00;
    /* 004 */ u8 filler_04[0x18];
    /* 01c */ struct Unk68574 unk1C;
    /* 0f8 */ struct Unk68574 unkF8;
    /* 1d4 */ struct Unk68574 unk1D4;
    /* 2b0 */ u32 unk2B0;
    /* 2b4 */ u32 unk2B4;
    /* 2b8 */ u8 filler_2B8[0xD];
    /* 2c5 */ u8 unk2C5;
    /* 2c6 */ u8 filler_2C6[0x1E];
    /* 2e4 */ s32 unk2E4; /* sub_080353A0 */
    /* 2e8 */ s32 unk2E8; /* sub_080353A0 */
    /* 2ec */ s32 unk2EC; /* sub_080353A0 */
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
/* +0x1E: s16 baseline/anchor. sub_08062068. */
struct Unk62068 /* >= 0x20 */
{
    /* 00 */ u8 filler_00[0x1E];
    /* 1e */ s16 unk1E;
};

/* Entry referenced by Unk62044.unk0C[i]. sub_080620D4. */
struct Unk620D4Entry /* >= 0x10 */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
};

struct Unk62044 /* 0x28 (padded from >= 0x26) */
{
    /* 00 */ void *unk00;
    /* 04 */ u8 filler_04[8];
    /* 0c */ struct Unk620D4Entry **unk0C;
    /* 10 */ s32 unk10;
    /* 14 */ s32 unk14;
    /* 18 */ u8 filler_18[0xC];
    /* 24 */ u16 unk24;
};

/* *gUnk_030008D0. 16-slot pointer pool + used-bitmask. sub_08062A74, sub_08062AF8, sub_08062B9C. */
struct Unk62A74 /* >= 0x42 */
{
    /* 00 */ void *unk00[16];
    /* 40 */ u16 unk40;
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

/* Linked entry with a position word pair. sub_08038F30. */
struct Unk38F30Entry /* >= 0x10 */
{
    /* 00 */ u8 filler_00[0x0C];
    /* 0c */ s32 unk0C;
};

struct Unk30D4CResourceFields /* 0x6c */
{
    /* 00 */ u32 filler_00[2];
    /* 08 */ struct Unk705DC *unkAF0;
    /* 0c */ struct Unk705DC *unkAF4;
    /* 10 */ struct Unk705DC *unkAF8;
    /* 14 */ struct Unk705DC *unkAFC;
    /* 18 */ struct Unk705DC *unkB00[8];
    /* 38 */ struct Unk705DC *unkB20[8];
    /* 58 */ struct Unk705DC *unkB40;
    /* 5c */ struct Unk705DC *unkB44;
    /* 60 */ struct Unk705DC *unkB48;
    /* 64 */ struct Unk705DC *unkB4C;
    /* 68 */ struct Unk705DC *unkB50;
};

union Unk30D4CResource /* 0x6c */
{
    s32 words[0x1B];
    struct Unk30D4CResourceFields fields;
};

/* IWRAM state at 0x030002A0. sub_08031204. */
struct Unk002A0Record /* 0x2c */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
    /* 10 */ u8 filler_10[8];
    /* 18 */ u32 unk18;
    /* 1c */ s8 unk1C; /* sub_08038F30 */
    /* 1d */ u8 filler_1D[0x0B];
    /* 28 */ void *unk28;
};

struct Unk002A0 /* >= 0xb0 */
{
    /* 00 */ struct Unk002A0Record records[4];
};

struct Unk013CFields /* 0x60 */
{
    /* 00 */ s32 values[4];
    /* 10 */ struct Unk62044 unk14C;
    /* 38 */ struct Unk62044 unk174;
};

union Unk013C /* 0x60 */
{
    s32 values[0x18];
    struct Unk013CFields fields;
};

/* Per-entry state at BattleWork +0x0BCC. sub_0803D4C4, sub_08062238. */
/* RGB555 triplet (r,g,b bytes, top 5 bits used). sub_08062D50. */
struct Unk62D50 /* >= 0x03 */
{
    /* 00 */ u8 unk00;
    /* 01 */ u8 unk01;
    /* 02 */ u8 unk02;
};

struct Unk62634 /* >= 0x64 */
{
    /* 00 */ void *unk00;
    /* 04 */ struct Unk6225CSource *unk04;
    /* 08 */ struct Unk705DC *unk08;
    /* 0c */ u8 filler_0C[0xC];
    /* 18 */ u32 unk18;
    /* 1c */ s32 unk1C;
    /* 20 */ s32 unk20;
    /* 24 */ s32 unk24;
    /* 28 */ s32 unk28;
    /* 2c */ u8 filler_2C[4];
    /* 30 */ s32 unk30;
    /* 34 */ s32 unk34;
    /* 38 */ s32 unk38;
    /* 3c */ s32 unk3C;
    /* 40 */ s32 unk40;
    /* 44 */ u8 filler_44[0x1C];
    /* 60 */ u8 unk60;
    /* 61 */ u8 filler_61[3];
};

struct Unk6225CSource /* >= 0x14 */
{
    /* 00 */ u8 filler_00[0x0C];
    /* 0C */ s32 unk0C;
    /* 10 */ s32 unk10;
};

/* Moving object updated by sub_0806225C. */
struct Unk6225C /* >= 0x61 */
{
    /* 00 */ void *unk00;
    /* 04 */ struct Unk6225CSource *unk04;
    /* 08 */ struct Unk705DC *unk08;
    /* 0C */ u8 filler_0C[0x0C];
    /* 18 */ u32 unk18;
    /* 1C */ s32 unk1C;
    /* 20 */ s32 unk20;
    /* 24 */ s32 unk24;
    /* 28 */ s32 unk28;
    /* 2C */ u8 filler_2C[4];
    /* 30 */ s32 unk30;
    /* 34 */ s32 unk34;
    /* 38 */ s32 unk38;
    /* 3C */ s32 unk3C;
    /* 40 */ s32 unk40;
    /* 44 */ u8 filler_44[0x1C];
    /* 60 */ u8 unk60;
};

struct Unk62988 /* >= 0x05 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u8 unk04;
};

struct Unk632F8 /* 0x328 */
{
    /* 000 */ u8 filler_000[0x24C];
    /* 24C */ void *unk24C;
    /* 250 */ void *unk250;
    /* 254 */ void *unk254;
    /* 258 */ void *unk258;
    /* 25C */ u8 filler_25C[0x78];
    /* 2D4 */ u8 unk2D4;
    /* 2D5 */ u8 filler_2D5[0x4F];
    /* 324 */ u32 unk324;
};

struct Unk65560Source /* 0x08 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
};

struct Unk65560 /* >= 0x2D6 */
{
    /* 000 */ u8 filler_000[0x274];
    /* 274 */ struct Unk705DC *unk274[24];
    /* 2D4 */ s8 filler_2D4;
    /* 2D5 */ s8 unk2D5;
};

struct Unk66224Object /* >= 0x28 */
{
    /* 00 */ void *unk00;
    /* 04 */ void *callbacks[7];
    /* 20 */ s32 unk20;
    /* 24 */ s32 unk24;
};

struct Unk66224Entry /* 0x1C */
{
    /* 00 */ struct Unk66224Object *unk00;
    /* 04 */ u8 filler_04[0x10];
    /* 14 */ s32 unk14;
    /* 18 */ u8 filler_18[4];
};

struct Unk66224RefTarget /* >= 0x0B */
{
    /* 00 */ u8 filler_00[0x0A];
    /* 0A */ u8 unk0A;
};

struct Unk66224Ref /* >= 0x04 */
{
    /* 00 */ struct Unk66224RefTarget *unk00;
};

struct Unk66224 /* >= 0x70 */
{
    /* 00 */ s32 unk00;
    /* 04 */ s32 unk04;
    /* 08 */ u8 filler_08[4];
    /* 0C */ s32 unk0C;
    /* 10 */ u8 filler_10[4];
    /* 14 */ s32 unk14;
    /* 18 */ u8 filler_18[0x10];
    /* 28 */ struct Unk66224Entry *unk28;
    /* 2C */ struct Unk66224Ref *unk2C;
    /* 30 */ u8 filler_30[0x0C];
    /* 3C */ u16 unk3C;
    /* 3E */ u8 filler_3E[2];
    /* 40 */ struct Unk7069C unk40;
};

struct Unk66FB8Table /* 0x10 */
{
    /* 00 */ u8 filler_00[0x0C];
    /* 0C */ void *unk0C;
};

/* Rotation angle state at BattleWork +0xAA8. */
struct Unk30638AA8 /* >= 0x18 */
{
    /* 00 */ s32 unk00;
    /* 04 */ s32 unk04;
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
    /* 10 */ s32 unk10;
    /* 14 */ s32 unk14;
};

/* Battle work block (*gBattleWork). sub_080314FC, sub_08033530, sub_08033574. */
struct BattleWork /* >= 0x208A */
{
    /* 0000 */ void *unk00;
    /* 0004 */ void *unk04;
    /* 0008 */ u8 filler_0008[0x48];
    /* 0050 */ u16 unk050;
    /* 0052 */ u16 unk052;
    /* 0054 */ u32 unk054;
    /* 0058 */ u32 unk058;
    /* 005c */ u8 filler_005C[0x34];
    /* 0090 */ u8 unk090[8];
    /* 0098 */ u8 filler_0098[0x40];
    /* 00d8 */ u16 unkD8;
    /* 00da */ u16 unkDA;
    /* 00dc */ u32 unkDC;
    /* 00e0 */ u32 unkE0;
    /* 00e4 */ u8 filler_00E4[0x34];
    /* 0118 */ u32 unk118;
    /* 011C */ u8 filler_011C[0x0C];
    /* 0128 */ s32 unk128; /* sub_08037508 */
    /* 012c */ u8 unk12C; /* sub_08037508 */
    /* 012d */ u8 filler_012D[2];
    /* 012f */ s8 unk12F; /* sub_08038F30 */
    /* 0130 */ u8 unk130;
    /* 0131 */ u8 unk131;
    /* 0132 */ u8 unk132;
    /* 0133 */ u8 unk133; /* sub_08037430 */
    /* 0134 */ u8 filler_0134[8];
    /* 013C */ union Unk013C unk013C;
    /* 019C */ struct Unk62044 unk19C[4]; /* sub_08038314 */
    /* 023C */ struct Unk7069C unk023C[4]; /* sub_08038D10 */
    /* 02FC */ struct Unk62044 unk2FC;
    /* 0324 */ struct Unk38F30Entry *unk324; /* sub_08038F30 */
    /* 0328 */ u8 filler_0328[0x18];
    /* 0340 */ s32 unk340;
    /* 0344 */ s32 unk344;
    /* 0348 */ u8 filler_0348[0x760];
    /* 0aa8 */ struct Unk30638AA8 unkAA8;
    /* 0ac0 */ u8 filler_0AC0[4];
    /* 0ac4 */ u32 unkAC4;
    /* 0ac8 */ void *unk0AC8[4];
    /* 0AD8 */ void *unk0AD8[4];
    /* 0AE8 */ union Unk30D4CResource unk0AE8;
    /* 0B54 */ void *unk0B54[4]; /* sub_08033878 */
    /* 0B64 */ u32 unk0B64;
    /* 0B68 */ u32 unk0B68;
    /* 0B6C */ u8 unk0B6C;
    /* 0B6D */ u8 filler_0B6D[3];
    /* 0B70 */ u32 unk0B70;
    /* 0B74 */ s32 unk0B74;
    /* 0B78 */ u32 unk0B78;
    /* 0B7C */ s32 unk0B7C;
    /* 0B80 */ u8 filler_0B80[4];
    /* 0B84 */ u8 unkB84[0x10];
    /* 0B94 */ u8 unkB94[0x10];
    /* 0BA4 */ void *unkBA4;
    /* 0BA8 */ void *unkBA8;
    /* 0BAC */ s32 unkBAC;
    /* 0BB0 */ s32 unkBB0;
    /* 0BB4 */ s32 unkBB4;
    /* 0BB8 */ s32 unkBB8;
    /* 0BBC */ u8 filler_0BBC[0x10];
    /* 0BCC */ struct Unk62634 unk0BCC[48]; /* sub_0803D4C4 */
    /* 1E8C */ u8 filler_1E8C[0x80];
    /* 1F0C */ void *unk1F0C;
    /* 1F10 */ struct Unk62044 unk1F10;
    /* 1F38 */ struct Unk62044 unk1F38;
    /* 1F60 */ u8 filler_1F60[0x13];
    /* 1F73 */ u8 unk1F73; /* sub_0803D51C */
    /* 1F74 */ u8 filler_1F74[8];
    /* 1F7C */ u8 unk1F7C;
    /* 1F7D */ u8 filler_1F7D[0x13];
    /* 1F90 */ s32 unk1F90; /* sub_080330F4 */
    /* 1F94 */ s32 unk1F94; /* sub_080330F4 */
    /* 1F98 */ u8 unk1F98; /* sub_080330F4 */
    /* 1F99 */ u8 filler_1F99[3];
    /* 1F9C */ s32 unk1F9C; /* sub_08037508 */
    /* 1FA0 */ s32 unk1FA0; /* sub_08037508 */
    /* 1FA4 */ u8 filler_1FA4[8];
    /* 1FAC */ u8 unk1FAC;
    /* 1FAD */ u8 filler_1FAD[0x39];
    /* 1FE6 */ u8 unk1FE6;
    /* 1FE7 */ u8 filler_1FE7[0x35];
    /* 201C */ u32 unk201C;
    /* 2020 */ u8 filler_2020[0x68];
    /* 2088 */ u8 unk2088;
    /* 2089 */ u8 unk2089;
    /* 208a */ u8 filler_208A[0x0A];
    /* 2094 */ void *unk2094;
    /* 208c */ s32 unk208C[4];
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
    /* 00 */ s16 unk00;
    /* 02 */ u8 filler_02[2];
    /* 04 */ void *unk04;
    /* 08 */ void *unk08;
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

/* Per-slot record, 2 slots. sub_08046230 (per-index), sub_08046278 (both). */
struct Unk16B0 /* 0x0c */
{
    /* 00 */ s32 unk00;
    /* 04 */ s32 unk04;
    /* 08 */ s32 unk08;
};

/* Counter at +0x18 of the target owned by MainWork +0x274. */
struct Unk40088Target /* >= 0x1a */
{
    /* 00 */ u8 filler_00[0x18];
    /* 18 */ u16 unk18;
};

/* Two-word ROM lookup entries used by sub_08040EF4. */
struct Unk40EF4 /* 0x08 */
{
    /* 00 */ u32 unk00;
    /* 04 */ void *unk04;
};

/* Object anchor at MainWork +0x448. */
struct Unk42718 /* >= 0x04 */
{
    /* 00 */ u8 filler_00[4];
};

/* Two-word descending range entries at 0x080908BC. */
struct Unk42BE8 /* 0x08 */
{
    /* 00 */ s32 unk00;
    /* 04 */ s32 unk04;
};

struct Unk442FC /* >= 0x88 */
{
    /* 00 */ u8 filler_00[0x84];
    /* 84 */ s32 unk84;
};

struct Unk442FCInput /* >= 0x18 */
{
    /* 00 */ u8 filler_00[0x14];
    /* 14 */ u16 unk14;
    /* 16 */ u16 unk16;
};

struct Unk0610 /* 0x20 */
{
    /* 00 */ u32 words[8];
};

struct Unk0600 /* 0x10 */
{
    /* 00 */ u8 bytes[16];
};

struct Unk45D3CEntry /* 0x1f60 */
{
    /* 0000 */ u8 filler_0000[0x0C];
    /* 000c */ u32 words[8];
    /* 002c */ u8 filler_002C[0x44];
    /* 0070 */ u8 bytes_70[16];
    /* 0080 */ u8 filler_0080[0x1EE0];
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

/* Flag at +8, pointers at +0/+4. sub_08045A84. */
struct Unk45A84 /* >= 0x0c */
{
    /* 00 */ void *unk00;
    /* 04 */ void *unk04;
    /* 08 */ u8 unk08;
};

/* Current menu entry selected by sub_0804AAF0. */
struct Unk4AAF0 /* >= 0x28 */
{
    /* 00 */ u8 filler_00[0x1D];
    /* 1D */ s8 unk1D;
    /* 1E */ s8 unk1E;
    /* 1F */ u8 unk1F;
    /* 20 */ u8 unk20;
    /* 21 */ s8 unk21;
    /* 22 */ u8 filler_22[4];
    /* 26 */ s16 unk26;
};

/* Menu callback table at 0x080995AC. */
struct Unk995AC /* 0x10 */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ void *unk08;
    /* 0C */ u8 filler_0C[4];
};

/* Event descriptor dispatched by sub_08056D68. */
struct Unk56D68 /* >= 0x10 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u16 unk04;
    /* 06 */ u8 filler_06[2];
    /* 08 */ u32 unk08;
    /* 0C */ u32 unk0C;
};

/* Text/layout record used by sub_080610A8. */
struct Unk610A8 /* >= 0xA2 */
{
    /* 00 */ u8 filler_00[0x8C];
    /* 8C */ void *unk8C;
    /* 90 */ u16 unk90;
    /* 92 */ u8 filler_92[6];
    /* 98 */ u16 unk98;
    /* 9A */ u8 filler_9A[2];
    /* 9C */ u16 unk9C;
    /* 9E */ u8 filler_9E[2];
    /* A0 */ u16 unkA0;
    /* A2 */ u8 filler_A2[0x1E];
};

/* Tilemap selector used by sub_0806114C. */
struct Unk6114C /* >= 0x5D */
{
    /* 00 */ u8 filler_00[0x5C];
    /* 5C */ u8 unk5C;
    /* 5D */ u8 filler_5D;
};

/* Lookup record returned by sub_08041DB4; callback slot at +0xB8. */
struct Unk5E044Lookup /* >= 0xBC */
{
    /* 00 */ u8 filler_00[0xB8];
    /* B8 */ struct Unk705DC *unkB8;
};

/* Root main-work arena (*gMainWorkPtr). */
struct MainWork /* >= 0x18B4 */
{
    /* 0000 */ u8 filler_0000[0x274];
    /* 0274 */ struct Unk40088Target *unk0274;
    /* 0278 */ u8 filler_0278[0x8C];
    /* 0304 */ s32 unk0304;
    /* 0308 */ u8 filler_0308[0x50];
    /* 0358 */ u16 unk0358; /* sub_0804438C */
    /* 035A */ u8 filler_035A[0x12];
    /* 036C */ s32 unk036C;
    /* 0370 */ s32 unk0370;
    /* 0374 */ s32 unk0374;
    /* 0378 */ u8 filler_0378[0x0E];
    /* 0386 */ u16 unk0386;
    /* 0388 */ u8 filler_0388[0x15];
    /* 039D */ u8 unk039D;
    /* 039E */ u8 filler_039E[0xE];
    /* 03AC */ u32 unk03AC;
    /* 03B0 */ u32 unk03B0;
    /* 03B4 */ u8 filler_03B4[0x70];
    /* 0424 */ struct Unk705DC *unk0424;
    /* 0428 */ u8 filler_0428[0x20];
    /* 0448 */ struct Unk42718 unk0448;
    /* 044C */ u32 unk044C; /* sub_08044A20, sub_08042784 */
    /* 0450 */ u32 unk0450; /* sub_08042784 */
    /* 0454 */ u8 filler_0454[0x0E];
    /* 0462 */ u16 unk0462;
    /* 0464 */ u8 filler_0464[0x15];
    /* 0479 */ u8 unk0479;
    /* 047A */ u8 filler_047A[0x0E];
    /* 0488 */ u32 unk0488; /* sub_080424E8 */
    /* 048C */ u32 unk048C; /* sub_080424E8 */
    /* 0490 */ u8 filler_0490[0x70];
    /* 0500 */ struct Unk705DC *unk0500;
    /* 0504 */ u8 filler_0504[0x2C];
    /* 0530 */ u8 unk0530; /* sub_080415FC */
    /* 0531 */ u8 filler_0531[0x24B];
    /* 077c */ void *unk077C;
    /* 0780 */ void *unk0780;
    /* 0784 */ void *unk0784;
    /* 0788 */ void *unk0788;
    /* 078c */ u8 filler_078C[0x18];
    /* 07A4 */ struct Unk38F30Entry *unk07A4[0x18]; /* sub_08038F30 */
    /* 0804 */ u8 unk0804; /* sub_080415FC */
    /* 0805 */ u8 filler_0805[0x4F];
    /* 0854 */ u32 unk0854; /* sub_080415FC */
    /* 0858 */ u8 filler_0858[0x10];
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
    /* 15D4 */ u8 filler_15D4[8];
    /* 15DC */ u8 unk15DC[0xAC];
    /* 1688 */ struct Unk1688Entry *unk1688;
    /* 168C */ struct Unk45D3CEntry *unk168C;
    /* 1690 */ struct Unk1690 *unk1690;
    /* 1694 */ struct Unk1694 *unk1694;
    /* 1698 */ u8 filler_1698[0x18];
    /* 16B0 */ struct Unk16B0 unk16B0[2]; /* sub_08046230 */
    /* 16C8 */ void *unk16C8;
    /* 16CC */ u8 filler_16CC[8];
    /* 16D4 */ void *unk16D4;
    /* 16D8 */ u8 filler_16D8[8];
    /* 16E0 */ struct Unk16E0 *unk16E0;
    /* 16E4 */ struct Unk16E0 *unk16E4;
    /* 16E8 */ void *unk16E8;
    /* 16EC */ u8 filler_16EC[0x1C]; /* sub_0805D99C */
    /* 1708 */ u32 unk1708; /* sub_0805D99C */
    /* 170C */ s32 unk170C;
    /* 1710 */ s32 unk1710[27];
    /* 177C */ s32 unk177C;
    /* 1780 */ s32 unk1780;
    /* 1784 */ u8 filler_1784[4];
    /* 1788 */ u32 unk1788;
    /* 178C */ u8 filler_178C[8];
    /* 1794 */ s32 unk1794;
    /* 1798 */ u32 unk1798;
    /* 179C */ u32 unk179C;
    /* 17A0 */ u8 filler_17A0[0x14];
    /* 17B4 */ u32 unk17B4; /* sub_08044A20 */
    /* 17B8 */ u32 unk17B8; /* sub_08044A20 */
    /* 17BC */ u8 filler_17BC[8];
    /* 17C4 */ u32 unk17C4; /* sub_08044A20 */
    /* 17C8 */ u32 unk17C8; /* sub_08044A20 */
    /* 17CC */ u8 filler_17CC[0x18];
    /* 17E4 */ s16 unk17E4;
    /* 17E6 */ u8 filler_17E6[0x0A];
    /* 17F0 */ u16 unk17F0; /* sub_080449C4, sub_08051BBC — BLDY fade counter (down) */
    /* 17F2 */ u16 unk17F2; /* sub_080449C4, sub_08051BBC — BLDY fade counter (up) */
    /* 17F4 */ u8 filler_17F4[2];
    /* 17F6 */ s8 unk17F6; /* sub_080435D8 */
    /* 17F7 */ s8 unk17F7; /* sub_080435D8 */
    /* 17F8 */ u8 filler_17F8[4];
    /* 17FC */ s32 unk17FC;
    /* 1800 */ u32 unk1800;
    /* 1804 */ u8 filler_1804[4];
    /* 1808 */ u32 unk1808;
    /* 180C */ u32 unk180C;
    /* 1810 */ u32 unk1810;
    /* 1814 */ u8 filler_1814[4];
    /* 1818 */ u8 unk1818;
    /* 1819 */ u8 unk1819;
    /* 181A */ u8 unk181A;
    /* 181B */ u8 unk181B; /* sub_080449C4 */
    /* 181C */ u8 unk181C; /* sub_0803fdd0, sub_0805d99c */
    /* 181D */ u8 unk181D;
    /* 181E */ u8 filler_181E[1];
    /* 181F */ s8 unk181F;
    /* 1820 */ u8 filler_1820[4];
    /* 1824 */ u8 unk1824; /* sub_08037508 */
    /* 1825 */ u8 unk1825;
    /* 1826 */ u8 unk1826;
    /* 1827 */ u8 unk1827;
    /* 1828 */ u8 unk1828; /* sub_080429CC */
    /* 1829 */ u8 filler_1829[3];
    /* 182C */ u8 unk182C; /* sub_08042784 */
    /* 182D */ u8 filler_182D[6];
    /* 1833 */ u8 unk1833;
    /* 1834 */ u8 unk1834;
    /* 1835 */ u8 filler_1835[3];
    /* 1838 */ u16 unk1838;
    /* 183A */ u16 unk183A;
    /* 183C */ u8 filler_183C[0x10];
    /* 184C */ s8 unk184C; /* sub_080462D4 */
    /* 184D */ s8 unk184D; /* sub_080462D4 */
    /* 184E */ u8 filler_184E[7];
    /* 1855 */ s8 unk1855;
    /* 1856 */ u8 filler_1856[0x0B];
    /* 1861 */ s8 unk1861[0x53];
    /* 18B4 */ u8 filler_18B4[4];
    /* 18B8 */ struct Unk45A84 unk18B8;
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
    /* 02 */ u16 unk02;
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

/* Double-indirect table at +0x230, word at +0x310. sub_08066BC4. */
struct Unk66BC4 /* >= 0x314 */
{
    /* 000 */ u8 filler_00[0x230];
    /* 230 */ void ***unk230;
    /* 234 */ u8 filler_234[0xD0];
    /* 304 */ s32 unk304;
    /* 308 */ s32 unk308;
    /* 30C */ u8 filler_30C[4];
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
/* sub_0806DF38 output entry, 0x14 stride. sub_0806C78C. */
struct UnkDF38Entry /* >= 0x14 */
{
    /* 00 */ s32 *unk00;
    /* 04 */ s32 unk04;
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
    /* 10 */ void *unk10;
};

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
    /* 44 */ void *unk44;
    /* 48 */ u8 unk48;
    /* 49 */ u8 filler_49[3];
    /* 4c */ s16 unk4C;
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

/* Animation update state and its indexed callback table. sub_08068118. */
struct Unk68118 /* >= 0xc4 */
{
    /* 00 */ struct Unk68014 *unk00;
    /* 04 */ u8 filler_04[0x16];
    /* 1a */ s16 unk1A;
    /* 1c */ u16 unk1C;
    /* 1e */ u16 unk1E;
    /* 20 */ u8 filler_20[0x0E];
    /* 2e */ u16 unk2E;
    /* 30 */ u8 filler_30[0x90];
    /* c0 */ void *unkC0;
};

struct Unk68118Table /* >= 0x0a */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u16 unk04;
    /* 06 */ u8 filler_06[2];
    /* 08 */ u16 entries[1];
};

/* Record stream used by sub_08068598. */
struct Unk68598Record /* 0x08 */
{
    /* 00 */ u16 value;
    /* 02 */ u16 unk02;
    /* 04 */ u8 filler_04[4];
};

struct Unk68598Lookup /* >= 0x04 */
{
    /* 00 */ u16 unk00;
    /* 02 */ u16 values[1];
};

/* Playback state updated by sub_08068598. */
struct Unk68598 /* >= 0xc4 */
{
    /* 00 */ struct Unk68014 *unk00;
    /* 04 */ u8 filler_04[0x1C];
    /* 20 */ u16 unk20;
    /* 22 */ s16 unk22;
    /* 24 */ u8 unk24;
    /* 25 */ u8 filler_25[0x0D];
    /* 32 */ u8 unk32;
    /* 33 */ u8 unk33;
    /* 34 */ u16 unk34;
    /* 36 */ s16 unk36;
    /* 38 */ u8 filler_38[0x20];
    /* 58 */ u32 unk58;
    /* 5c */ u8 filler_5C[4];
    /* 60 */ u16 unk60;
    /* 62 */ u8 filler_62[0x36];
    /* 98 */ u8 unk98;
    /* 99 */ u8 filler_99[0x27];
    /* c0 */ void *unkC0;
};

struct Unk68798Entry /* 0x10 */
{
    /* 00 */ s32 unk00;
    /* 04 */ s32 unk04;
    /* 08 */ void *unk08;
    /* 0c */ u8 filler_0C[4];
};

struct Unk68798 /* >= 0x7c */
{
    /* 00 */ u8 filler_00[0x74];
    /* 74 */ s32 unk74;
    /* 78 */ struct Unk68798Entry *unk78;
};

/* Bounds and bit shifts consumed by sub_08068988. */
struct Unk68988 /* >= 0x61 */
{
    /* 00 */ s32 unk00;
    /* 04 */ s32 unk04;
    /* 08 */ u8 filler_08[0x57];
    /* 5f */ u8 unk5F;
    /* 60 */ u8 unk60;
};

/* Motion accumulator advanced by sub_08068E54. */
struct Unk68E54 /* >= 0x65 */
{
    /* 00 */ u8 filler_00[0x14];
    /* 14 */ s32 unk14;
    /* 18 */ s32 unk18;
    /* 1c */ s32 unk1C;
    /* 20 */ s32 unk20;
    /* 24 */ s32 unk24;
    /* 28 */ u8 filler_28[0x2C];
    /* 54 */ s32 unk54;
    /* 58 */ s32 unk58;
    /* 5c */ u8 filler_5C[8];
    /* 64 */ u16 unk64;
    /* 66 */ u8 filler_66[0x22];
};

struct Unk691E4 /* >= 0x61 */
{
    /* 00 */ u8 filler_00[0x5F];
    /* 5f */ u8 unk5F;
    /* 60 */ u8 unk60;
};

struct Unk69DBC /* >= 0x74 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u8 filler_04[0x58];
    /* 5c */ u8 unk5C;
    /* 5d */ u8 filler_5D[2];
    /* 5f */ u8 unk5F;
    /* 60 */ u8 filler_60[0x10];
    /* 70 */ u8 *unk70;
};

struct Unk6A4D8Node /* >= 0x10 */
{
    /* 00 */ s32 *unk00;
    /* 04 */ u32 unk04;
    /* 08 */ struct Unk6A4D8Node *unk08;
    /* 0c */ struct Unk6A4D8Node *unk0C;
};

struct Unk6A314 /* >= 0x08 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
};

struct Unk6A434 /* >= 0x10 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
    /* 08 */ struct Unk6A4D8Node *unk08;
    /* 0c */ struct Unk6A4D8Node *unk0C;
};

struct Unk6BC0CSource /* >= 0x1c */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u16 unk04;
    /* 06 */ u8 filler_06[0x0A];
    /* 10 */ u32 unk10;
    /* 14 */ u32 unk14;
    /* 18 */ u32 unk18;
};

struct Unk6BC0C /* >= 0x11a */
{
    /* 000 */ struct Unk6BC0CSource *unk00;
    /* 004 */ u8 *unk04;
    /* 008 */ u8 *unk08;
    /* 00c */ u8 *unk0C;
    /* 010 */ u32 unk10;
    /* 014 */ void *unk14[0x40];
    /* 114 */ u32 unk114;
    /* 118 */ u16 unk118;
};

struct Unk6C704 /* >= 0xa0 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ s32 unk04;
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
    /* 10 */ u8 filler_10[0x34];
    /* 44 */ s32 unk44;
    /* 48 */ u8 filler_48[0x38];
    /* 80 */ void *unk80;
    /* 84 */ void *unk84;
    /* 88 */ s32 unk88;
    /* 8c */ u8 filler_8C;
    /* 8d */ u8 unk8D;
    /* 8e */ u8 filler_8E[0x0C];
    /* 9a */ s16 unk9A;
    /* 9c */ s16 unk9C;
    /* 9e */ s16 unk9E;
};

struct Unk6EE48Entry /* 0x18 */
{
    /* 00 */ void *unk00;
    /* 04 */ u8 filler_04[0x14];
};

struct Unk6EE48Table /* >= 0x74 */
{
    /* 00 */ u8 filler_00[0x14];
    /* 14 */ struct Unk6EE48Entry entries[4];
};

struct Unk6EE48 /* >= 0x355 */
{
    /* 000 */ struct Unk68E54 motion[4];
    /* 220 */ struct Unk6EE48Table *unk220;
    /* 224 */ void *unk224;
    /* 228 */ u8 filler_228[0x11C];
    /* 344 */ void *unk344;
    /* 348 */ u8 filler_348[0x0C];
    /* 354 */ u8 unk354;
};

struct Unk6FE84 /* >= 0x34 */
{
    /* 00 */ struct Unk6FE84 *unk00;
    /* 04 */ struct Unk6FE84 *unk04;
    /* 08 */ u8 filler_08[0x0E];
    /* 16 */ u16 unk16;
    /* 18 */ u8 filler_18[8];
    /* 20 */ u16 unk20;
    /* 22 */ u8 filler_22[2];
    /* 24 */ s32 unk24;
    /* 28 */ u8 filler_28[8];
    /* 30 */ void *unk30;
};

struct Unk70354Object /* >= 0x1A */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ u32 unk08;
    /* 0C */ u8 filler_0C[8];
    /* 14 */ u16 unk14;
    /* 16 */ u16 unk16;
    /* 18 */ u8 unk18;
};

struct Unk70354 /* >= 0x34 */
{
    /* 00 */ u8 filler_00[0x10];
    /* 10 */ u32 unk10;
    /* 14 */ u8 filler_14[8];
    /* 1C */ u16 unk1C;
    /* 1E */ u8 filler_1E[0x12];
    /* 30 */ struct Unk70354Object *unk30;
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
struct Unk346C0Inner /* >= 0x54 */
{
    /* 00 */ struct Unk705DC *unk00;
    /* 04 */ u8 filler_04[8];
    /* 0c */ s32 unk0C;
    /* 10 */ s32 unk10;
    /* 14 */ s32 unk14;
    /* 18 */ s32 unk18;
    /* 1c */ s32 unk1C;
    /* 20 */ s32 unk20;
    /* 24 */ u8 filler_24[4];
    /* 28 */ struct Unk310F0Inner2 *unk28;
    /* 2c */ s32 unk2C;
    /* 30 */ u32 unk30;
    /* 34 */ u32 unk34;
    /* 38 */ s32 unk38;
    /* 3c */ s32 unk3C;
    /* 40 */ s32 unk40;
    /* 44 */ u8 filler_44[4];
    /* 48 */ u32 unk48;
    /* 4c */ u32 unk4C;
    /* 50 */ u8 filler_50[2];
    /* 52 */ s16 unk52; /* sub_080353A0 */
};

/* Position, velocity, and angle state. sub_08035984. */
struct Unk35984 /* >= 0x54 */
{
    /* 00 */ u8 filler_00[0x0C];
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
    /* 34 */ u8 filler_34[8];
    /* 3c */ s32 unk3C;
    /* 40 */ s32 unk40;
    /* 44 */ s32 unk44;
    /* 48 */ s32 unk48;
    /* 4c */ s32 unk4C;
    /* 50 */ u8 filler_50[2];
    /* 52 */ s16 unk52;
};

struct Unk346C0 /* >= 0x2f8 */
{
    /* 000 */ struct Unk346C0Inner *unk00;
    /* 004 */ struct Unk346C0Inner *unk04;
    /* 008 */ struct Unk35878 unk08;
    /* 018 */ u8 unk18; /* sub_08034568 */
    /* 019 */ u8 unk19;
    /* 01a */ u8 filler_1A[2];
    /* 01c */ u32 unk1C; /* sub_080348E8 */
    /* 020 */ u8 filler_20[0x6C];
    /* 08c */ u32 unk08C; /* sub_080348E8 */
    /* 090 */ u8 filler_90[0x44];
    /* 0d4 */ struct Unk705DC *unkD4; /* sub_08035624 */
    /* 0d8 */ u16 unkD8; /* sub_08035624 */
    /* 0da */ u16 unkDA; /* sub_08035624 */
    /* 0dc */ u8 filler_DC[0xD4];
    /* 1b0 */ struct Unk705DC *unk1B0; /* sub_08035624 */
    /* 1b4 */ u16 unk1B4; /* sub_08035624 */
    /* 1b6 */ u8 filler_1B6[0xD6];
    /* 28c */ struct Unk705DC *unk28C; /* sub_08035624 */
    /* 290 */ u16 unk290; /* sub_08035624 */
    /* 292 */ u8 filler_292[0x1E];
    /* 2b0 */ u32 unk2B0; /* sub_08034568 */
    /* 2b4 */ u32 unk2B4; /* sub_08034568 */
    /* 2b8 */ u32 unk2B8;
    /* 2bc */ u32 unk2BC;
    /* 2c0 */ s32 unk2C0;
    /* 2c4 */ u8 unk2C4; /* sub_08034568 */
    /* 2c5 */ u8 unk2C5;
    /* 2c6 */ u8 filler_2C6[2];
    /* 2c8 */ u32 unk2C8; /* sub_08034568 */
    /* 2cc */ u32 unk2CC;
    /* 2d0 */ u32 unk2D0;
    /* 2d4 */ u32 unk2D4;
    /* 2d8 */ u32 unk2D8;
    /* 2dc */ u32 unk2DC;
    /* 2e0 */ u32 unk2E0;
    /* 2e4 */ u32 unk2E4;
    /* 2e8 */ u32 unk2E8;
    /* 2ec */ u32 unk2EC; /* sub_08034568 */
    /* 2f0 */ u32 unk2F0; /* sub_08034568 */
    /* 2f4 */ u32 unk2F4;
    /* 2f8 */ u32 unk2F8;
    /* 2fc */ u32 unk2FC;
    /* 300 */ u16 unk300; /* sub_08034568 */
    /* 302 */ u16 unk302; /* sub_08034568 */
    /* 304 */ u16 unk304; /* sub_08034568 */
    /* 306 */ u8 filler_306[6];
    /* 30c */ u8 unk30C;
    /* 30d */ u8 unk30D; /* sub_08034568 */
    /* 30e */ u8 unk30E; /* sub_08034568 */
    /* 30f */ u8 unk30F;
    /* 310 */ u8 unk310;
    /* 311 */ u8 unk311;
    /* 312 */ u8 unk312; /* sub_08034568 */
    /* 313 */ u8 unk313; /* sub_08034568 */
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

/* 16 pointer slots. sub_08047594. */
struct Unk47594 /* >= 0x10 */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ u32 unk08;
    /* 0c */ u32 unk0C;
};

struct Unk474ACSlot /* >= 0x1a */
{
    /* 00 */ u8 filler_00[8];
    /* 08 */ s32 unk08;
    /* 0c */ s32 unk0C;
    /* 10 */ u8 filler_10[8];
    /* 18 */ u16 unk18;
};

/* *gUnk_03000630. 16-slot pool + counters. sub_080473F8, sub_0804745C, sub_080474AC. */
struct Unk473F8 /* >= 0x48 */
{
    /* 00 */ struct Unk474ACSlot *unk00[16];
    /* 40 */ s32 unk40;
    /* 44 */ s32 unk44;
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

/* Target object referenced by the IWRAM object at 0x03000380. */
struct Unk0380Target /* >= 0x313 */
{
    /* 000 */ u8 filler_00[0x2CC];
    /* 2cc */ u32 unk2CC;
    /* 2d0 */ u8 filler_2D0[0x40];
    /* 310 */ u8 unk310;
    /* 311 */ u8 filler_311;
    /* 312 */ u8 unk312;
};

/* IWRAM object at 0x03000380. sub_08033C1C. */
struct Unk0380 /* >= 0x1c */
{
    /* 00 */ struct Unk0380Target *unk00;
    /* 04 */ u8 filler_04[5];
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
    /* 04 */ void *unk04;
    /* 08 */ void *unk08;
    /* 0c */ void *unk0C;
    /* 10 */ void **unk10;
    /* 14 */ void *unk14;
    /* 18 */ void *unk18;
    /* 1c */ void *unk1C;
    /* 20 */ void *unk20;
    /* 24 */ void *unk24;
    /* 28 */ u32 unk28;
};

struct Unk1690 /* >= 0x78 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u8 filler_04[0x70];
    /* 74 */ u8 unk74;
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

struct Unk38F30Slot /* 0x30 */
{
    /* 00 */ struct Unk70C98 position;
    /* 08 */ u8 filler_08[0x28];
};

/* Pointer table at +0x114. sub_0806BDA8. */
struct Unk6BDA8 /* >= 0x118 */
{
    /* 000 */ u8 filler_00[0x114];
    /* 114 */ void **unk114;
};

/* Item, 0xDC stride (struct is wider; only unk70 known). sub_0806B3E8. */
struct Unk6B3E8Item /* >= 0xdc, stride 0xdc */
{
    /* 00 */ u8 filler_00[0x70];
    /* 70 */ s32 unk70;
    /* 74 */ u8 filler_74[0x68];
};

/* String cursor + item array. sub_0806B3E8. */
struct Unk6B3E8 /* >= 0x14 */
{
    /* 00 */ struct Unk6B3E8Item *unk00;
    /* 04 */ u8 unk04;
    /* 05 */ u8 filler_05[0xB];
    /* 10 */ const u8 *unk10;
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
    /* 00 */ struct Unk6FDB4 *unk00;
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
    /* 00 */ u8 filler_00[0x1F];
    /* 1f */ u8 unk1F;
    /* 20 */ u8 filler_20;
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

/* Local state assembled by sub_08040F4C. */
struct Unk40F4C /* >= 0x328 */
{
    /* 000 */ u8 filler_000[0x240];
    /* 240 */ void *unk240;
    /* 244 */ void *unk244;
    /* 248 */ void *unk248;
    /* 24c */ void *unk24C;
    /* 250 */ void *unk250;
    /* 254 */ void *unk254;
    /* 258 */ void *unk258;
    /* 25c */ void *unk25C;
    /* 260 */ void *unk260;
    /* 264 */ void *unk264;
    /* 268 */ void *unk268;
    /* 26c */ void *unk26C;
    /* 270 */ void *unk270;
    /* 274 */ void *unk274;
    /* 278 */ u8 filler_278[0x5C];
    /* 2d4 */ u8 unk2D4;
    /* 2d5 */ u8 filler_2D5[2];
    /* 2d7 */ u8 unk2D7;
    /* 2d8 */ u8 filler_2D8[1];
    /* 2d9 */ u8 unk2D9;
    /* 2da */ u8 filler_2DA[0x42];
    /* 31c */ u16 unk31C;
    /* 31e */ u16 unk31E;
    /* 320 */ u16 unk320;
    /* 322 */ u16 unk322;
    /* 324 */ u32 unk324;
};

/* Source descriptor copied into Unk40F4C by sub_0804109C. */
struct Unk4109CInput /* >= 0x4f */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
    /* 08 */ u32 unk08;
    /* 0c */ u32 unk0C;
    /* 10 */ u32 unk10;
    /* 14 */ u32 unk14;
    /* 18 */ u32 unk18;
    /* 1c */ u32 unk1C;
    /* 20 */ u32 unk20;
    /* 24 */ u32 unk24;
    /* 28 */ u32 unk28;
    /* 2c */ u32 unk2C;
    /* 30 */ u8 filler_30[0x18];
    /* 48 */ u16 unk48;
    /* 4a */ u16 unk4A;
    /* 4c */ u16 unk4C;
    /* 4e */ u8 unk4E;
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

/* *gUnk_030009B0. Count at +0x04. sub_080677A8. */
struct Unk09B0 /* >= 0x06 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ u16 unk04;
    /* 06 */ u16 unk06;
    /* 08 */ u8 unk08;
};

/* sub_08067F98 reuses struct Unk680CC / Unk68014 / Unk680CCRec (see sub_080680CC). */

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
    /* 1a */ u8 filler_1A[8];
    /* 22 */ u16 unk22; /* sub_08035624, sub_08070468 */
    /* 24 */ u8 filler_24[0xC];
    /* 30 */ struct Unk705DC *unk30;
};

/* 0x84-stride records. sub_0806F1A0. */
struct Unk6F1A0 /* 0x84 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u8 filler_04[0x80];
};

/* Linked node, swap fields at +8/+c/+18/+24. sub_0807179C. */
struct Unk7179CNode /* 0x34 */
{
    /* 00 */ struct Unk7179CNode *unk00;
    /* 04 */ struct Unk7179CNode *unk04;
    /* 08 */ u32 unk08;
    /* 0c */ u32 unk0C;
    /* 10 */ u8 filler_10[8];
    /* 18 */ u16 unk18;
    /* 1a */ u8 filler_1A[6];
    /* 20 */ u8 filler_20[4];
    /* 24 */ u32 unk24;
    /* 28 */ u8 filler_28[0xC];
};

/* Node pair + count. sub_0807179C. */
struct Unk7179C /* >= 0x20 */
{
    /* 00 */ u8 filler_00[0x14];
    /* 14 */ struct Unk7179CNode *unk14;
    /* 18 */ struct Unk7179CNode *unk18;
    /* 1c */ s32 unk1C;
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

/* Same signed table indices as Unk3E328, with byte-offset table reads. */
struct Unk3E374 /* >= 0x21 */
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

/* Flag + two Unk346C0 slots. sub_08033978, sub_08033A5C. */
struct Unk33A5C /* >= 0x0e */
{
    /* 00 */ u8 unk00;
    /* 01 */ u8 filler_01[3];
    /* 04 */ struct Unk346C0 *unk04;
    /* 08 */ struct Unk346C0 *unk08;
    /* 0c */ u8 filler_0C;
    /* 0d */ u8 unk0D;
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
    /* 00 */ u16 unk00;
    /* 02 */ u16 unk02;
    /* 04 */ s16 unk04;
    /* 06 */ u8 unk06;
    /* 07 */ u8 unk07;
    /* 08 */ u8 unk08;
    /* 09 */ u8 unk09;
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
    /* 00 */ u8 unk00; /* sub_08043420 */
    /* 01 */ u8 unk01;
    /* 02 */ u8 unk02;
    /* 03 */ u8 filler_03;
    /* 04 */ s16 unk04; /* sub_08043420 */
    /* 06 */ s16 unk06; /* sub_08043420 */
    /* 08 */ u8 unk08[0x7F];
};

/* Runtime records selected by sub_080436B0. */
struct Unk436B0Entry /* >= 0x3c */
{
    /* 00 */ u8 filler_00;
    /* 01 */ u8 unk01;
    /* 02 */ u8 filler_02[0x32];
    /* 34 */ s16 unk34;
    /* 36 */ s16 unk36;
    /* 38 */ s16 unk38;
    /* 3a */ s16 unk3A;
};

struct Unk0558 /* >= 0x14 */
{
    /* 00 */ u8 filler_00[4];
    /* 04 */ struct Unk436B0Entry *unk04;
    /* 08 */ struct Unk436B0Entry *unk08;
    /* 0c */ struct Unk436B0Entry *unk0C;
    /* 10 */ struct Unk436B0Entry *unk10;
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

/* Source record copied into an Unk59AE0Node. sub_08059AE0. */
struct Unk59AE0Src /* >= 0x24 */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
    /* 08 */ u32 unk08;
    /* 0c */ u32 unk0C;
    /* 10 */ u32 unk10;
    /* 14 */ u32 unk14;
    /* 18 */ u32 unk18;
    /* 1c */ u32 unk1C;
    /* 20 */ u32 unk20;
};

/* Freelist node type pointed to by gUnk_03000730. sub_08059AE0. */
struct Unk59AE0Node /* 0x3c */
{
    /* 00 */ u32 unk00;
    /* 04 */ u32 unk04;
    /* 08 */ u32 unk08;
    /* 0c */ u32 unk0C;
    /* 10 */ u32 unk10;
    /* 14 */ u32 unk14;
    /* 18 */ u32 unk18;
    /* 1c */ u32 unk1C;
    /* 20 */ u32 unk20;
    /* 24 */ u32 unk24;
    /* 28 */ struct Unk59AE0Src *unk28;
    /* 2c */ u32 unk2C;
    /* 30 */ u32 unk30;
    /* 34 */ u32 unk34;
    /* 38 */ u32 unk38;
};

/* Two output nodes and table indices. sub_08038D68. */
struct Unk38D68 /* >= 0x304 */
{
    /* 000 */ u8 filler_000[0x28C];
    /* 28c */ struct Unk705DC *unk28C;
    /* 290 */ struct Unk705DC *unk290;
    /* 294 */ u8 filler_294[0x68];
    /* 2fc */ s32 unk2FC;
    /* 300 */ s32 unk300;
};

struct Unk37508Resource /* 0x6c */
{
    /* 00 */ u8 filler_00[0x18];
    /* 18 */ u8 unkB00[0x20];
    /* 38 */ u8 unkB20[0x20];
    /* 58 */ u8 filler_58[0x14];
};

/* Overlay for the initialization fields used by sub_08037508. */
struct Unk37508Work /* >= 0x210c */
{
    /* 0000 */ u8 filler_0000[8];
    /* 0008 */ struct Unk361CCDst unk08;
    /* 005c */ u8 filler_005C[0x34];
    /* 0090 */ struct Unk361CCDst unk90;
    /* 00e4 */ u8 filler_00E4[0x44];
    /* 0128 */ s32 unk128;
    /* 012c */ u8 unk12C;
    /* 012d */ u8 filler_012D[3];
    /* 0130 */ u8 unk130;
    /* 0131 */ u8 unk131;
    /* 0132 */ u8 unk132;
    /* 0133 */ u8 unk133;
    /* 0134 */ u8 filler_0134[8];
    /* 013c */ u8 filler_013C[8];
    /* 0144 */ s32 unk144;
    /* 0148 */ s32 unk148;
    /* 014c */ u8 filler_014C[0x32C];
    /* 0478 */ struct Unk346C0 unk478;
    /* 0790 */ struct Unk346C0 unk790;
    /* 0aa8 */ struct Unk36190 unkAA8;
    /* 0ac0 */ u8 filler_0AC0[0x28];
    /* 0ae8 */ struct Unk37508Resource unkAE8;
    /* 0b54 */ u8 filler_0B54[0x30];
    /* 0b84 */ struct Unk312EC unkB84;
    /* 0b94 */ struct Unk312EC unkB94;
    /* 0ba4 */ u8 filler_0BA4[0x13C7];
    /* 1f6b */ u8 unk1F6B;
    /* 1f6c */ u8 unk1F6C;
    /* 1f6d */ u8 filler_1F6D;
    /* 1f6e */ u8 unk1F6E;
    /* 1f6f */ u8 unk1F6F;
    /* 1f70 */ u8 unk1F70;
    /* 1f71 */ u8 filler_1F71;
    /* 1f72 */ u8 unk1F72;
    /* 1f73 */ u8 filler_1F73[0x29];
    /* 1f9c */ s32 unk1F9C;
    /* 1fa0 */ s32 unk1FA0;
    /* 1fa4 */ u8 filler_1FA4[0xF0];
    /* 2094 */ struct Unk33A5C unk2094;
    /* 20a0 */ u8 filler_20A0[4];
    /* 20a4 */ struct Unk33F30 unk20A4;
};

#endif /* GUARD_UNKNOWN_TYPES_H */
