#include "global.h"

// @ 0x0803dd88
// 38/40 same-size (95%). Row lookup into the 40-byte-stride table at
// gData_0807A1F4 indexed by the u8 at gMainWorkPtr+0x1818. Splitting `off` into
// a local (rather than inlining the sum in the pointer expression) recovers the
// table-first ordering and the a*5<<3 shape.
// Remaining DIFF: retail loads the index with `ldrb r1,[r1]` and shifts into r2
// (`lsls r2,r1,#2`); agbcc loads it into r2 instead (`ldrb r2,[r1]`).
s32 sub_0803DD88(s32 a)
{
    u8 *base = gData_0807A1F4;
    u32 off = gMainWorkPtr->unk1818 * 4 + a * 40;

    return *(s32 *)(base + off);
}
