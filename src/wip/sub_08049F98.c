#include "global.h"

// @ 0x08049f98
void sub_08049F98(void *unused, u32 idx, void *out)
{
    struct Unk617C4 *base;
    u8 *p;
    u16 val;

    base = (struct Unk617C4 *)0x080D79CC;
    sub_080617C4(base, 0x080B7429);

    p = (u8 *)(idx << 4);
    p += 8;
    sub_080615EC(0, (u16)(u32)p);
    val = sub_08061784();
    sub_0806171C((void *)0x083A734C, val, 0);

    p += 0x10;
    sub_080615EC(0, (u16)(u32)p);
    val = sub_08061784();
    sub_0806171C((void *)0x083A734C, val, 0);

    base = (struct Unk617C4 *)0x082BCD00;
    sub_080617C4(base, 0x080B738E);

    sub_080615EC(0, (u16)(u32)(p - 0x10));
    val = sub_08061784();
    sub_0806171C(out, val, 0);
}
