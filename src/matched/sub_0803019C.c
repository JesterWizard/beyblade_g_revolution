#include "global.h"

// @ 0x0803019c

void sub_08030F38(void);
void sub_0803D4C4(void);
void sub_080353A0(void *a);
void sub_080361A8(void *a);

struct Unk3019CWork
{
    u8 filler_00[0x328];
    u8 unk328[0x20];
    u8 filler_348[0x34];
    u8 unk37C[0x20];
    u8 filler_39C[0xDC];
    u8 unk478[0x2F8];
    u8 filler_770[0x19];
    u8 unk789;
    u8 filler_78A[6];
    u8 unk790[0x2F8];
    u8 filler_A88[0x19];
    u8 unkAA1;
    u8 filler_AA2[6];
    u8 unkAA8[0x18];
    u8 filler_AC0[8];
    void *unk0AC8[4];
    void *unk0AD8[4];
};

void sub_0803019C(void)
{
    sub_08030F38();
    sub_0803D4C4();
    sub_080302E0(
        (struct Unk346C0 *)((struct Unk3019CWork *)gBattleWork)->unk478);
    sub_080302E0(
        (struct Unk346C0 *)((struct Unk3019CWork *)gBattleWork)->unk790);
    sub_08035D68(
        ((struct Unk3019CWork *)gBattleWork)->unk328,
        ((struct Unk3019CWork *)gBattleWork)->unkAA8);
    sub_08035D68(
        ((struct Unk3019CWork *)gBattleWork)->unk37C,
        ((struct Unk3019CWork *)gBattleWork)->unkAA8);
    sub_080302A8(
        (struct Unk302A8 *)((struct Unk3019CWork *)gBattleWork)->unk328,
        (struct Unk302A8Src *)((struct Unk3019CWork *)gBattleWork)->unkAA8,
        (struct Unk302A8 *)((struct Unk3019CWork *)gBattleWork)->unk0AD8[0]);
    sub_080302A8(
        (struct Unk302A8 *)((struct Unk3019CWork *)gBattleWork)->unk37C,
        (struct Unk302A8Src *)((struct Unk3019CWork *)gBattleWork)->unkAA8,
        (struct Unk302A8 *)((struct Unk3019CWork *)gBattleWork)->unk0AD8[1]);
    sub_080348E8(
        (struct Unk346C0 *)((struct Unk3019CWork *)gBattleWork)->unk478,
        (u32)((struct Unk3019CWork *)gBattleWork)->unk790);
    sub_080348E8(
        (struct Unk346C0 *)((struct Unk3019CWork *)gBattleWork)->unk790,
        (u32)((struct Unk3019CWork *)gBattleWork)->unk478);
    sub_0803531C(
        (struct Unk35258 *)((struct Unk3019CWork *)gBattleWork)->unk478);
    sub_0803531C(
        (struct Unk35258 *)((struct Unk3019CWork *)gBattleWork)->unk790);
    sub_080353A0(
        ((struct Unk3019CWork *)gBattleWork)->unk478);
    sub_080353A0(
        ((struct Unk3019CWork *)gBattleWork)->unk790);
    ((struct Unk3019CWork *)gBattleWork)->unk789 = (u8)sub_08035AE0(
        (struct Unk346C0Inner *)((struct Unk3019CWork *)gBattleWork)->unk328,
        (struct Unk346C0Inner *)((struct Unk3019CWork *)gBattleWork)->unk37C);
    ((struct Unk3019CWork *)gBattleWork)->unkAA1 =
        ((struct Unk3019CWork *)gBattleWork)->unk789;
    sub_08036264(
        (struct Unk36264 *)((struct Unk3019CWork *)gBattleWork)->unkAA8,
        (struct Unk360BC *)((struct Unk3019CWork *)gBattleWork)->unk328,
        (struct Unk360BC *)((struct Unk3019CWork *)gBattleWork)->unk37C, 0x66);
    sub_080361A8(
        ((struct Unk3019CWork *)gBattleWork)->unkAA8);
}

