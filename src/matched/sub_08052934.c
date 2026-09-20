#include "global.h"

// @ 0x08052934
#include "global.h"

void sub_08052934(s32 arg0)
{
    u32 idx;
    register u32 r0 asm("r0");
    register u32 r1 asm("r1");

    idx = arg0;
    idx = (u8)idx << 4;
    sub_080615EC(0, idx + 8);
    sub_080617C4((struct Unk617C4 *)0x082BCD00, 0x080B738E);
    r0 = 0x080995AC;
    asm("" : "+r"(r0));
    r0 += 0xC;
    idx += r0;
    r0 = (u32)gMainWorkPtr;
    asm("" : "+r"(r0), "+r"(idx));
    r1 = 0x1818;
    r0 += r1;
    r1 = *(u32 *)idx;
    r0 = *(u8 *)r0;
    r0 <<= 2;
    r0 += r1;
    sub_0806171C(*(void **)r0, 0x24, 2);
}

