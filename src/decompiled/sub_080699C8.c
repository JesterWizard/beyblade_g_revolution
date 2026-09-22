#include "global.h"

// @ 0x080699c8
// 25/80, size mismatch. Retail sets two BG scroll register pairs per case and
// shares the tail: BG2 writes 0x04000028/2A/2C/2E, BG3 writes
// 0x04000038/3A/3C/3E, and both fall into the same `strh r2,[r0]; adds r1,#4;
// asrs r0,r2,#0x10; strh r0,[r1]` sequence (the +4 folds 0x2E into 0x2A's
// register). Plain if/else, pointer-base, and else-if forms all fail to produce
// that shared tail. Role: set BG2/BG3 scroll offsets from a packed s32 pair.
void sub_080699C8(u32 bg, s32 x, s32 y)
{
    u16 *p;

    if (bg == 2)
        p = (u16 *)0x04000028;
    else if (bg == 3)
        p = (u16 *)0x04000038;
    else
        return;
    p[0] = x;
    p[1] = x >> 16;
    p[2] = y;
    p[3] = y >> 16;
}
