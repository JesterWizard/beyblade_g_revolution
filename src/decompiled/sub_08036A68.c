#include "global.h"

// @ 0x08036a68
// 58/240 (24.2%), compiled 232 vs retail 240 (8B short = ~4 instrs).
// Structure believed correct: 3x alloc(0x80) into p1/p2/p3 (p3 spilled to [sp,#0xC]),
// setup + 2 blit calls + 3 frees + final call. Likely divergence: retail keeps p1/p2
// in r9/r8 (high-reg prologue push {r5,r6,r7}) and retail spends 4 extra instrs
// preserving/reloading values; my C's live ranges let agbcc drop those moves.
// Next: permuter, or force the high-register live ranges (p3 stays in a stack slot).
void sub_08036A68(struct Unk346C0 *a, u32 b, u32 c)
{
    u8 *p1;
    u8 *p2;
    u8 *p3;

    p1 = sub_0807309C(0x80);
    p2 = sub_0807309C(0x80);
    p3 = sub_0807309C(0x80);
    sub_08037318(a, (u8)c);
    sub_08061E8C(gData_03000290 + 0x14C, (void *)0x080B72F3, (void *)0x082BF600, 0xB0, 0x150);
    sub_08073AEC((void *)*(u32 *)(0x080972A0 + gMainWorkPtr->unk1818 * 4), p1, sub_08042B00(*(u32 *)(gData_030002A0 + c * 0x2C)), 0x23, 0x80);
    sub_08073AEC(p1, p2, (void *)sub_0803DD88(*(u32 *)(gData_030002A0 + 4 + c * 0x2C)), 0x40, 0x80);
    sub_08061EF8(gData_03000290 + 0x14C, p2, 0, 0x50, 0, 0xC8, 0);
    sub_08073114(p1);
    sub_08073114(p2);
    sub_08073114(p3);
    sub_08037430();
}
