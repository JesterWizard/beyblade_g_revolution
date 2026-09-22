#include "global.h"

// @ 0x08049f98
void sub_08049F98(void *unused, u32 idx, void *out)
{
    struct Unk617C4 *base;
    u8 *p;
    u16 val;

    base = (struct Unk617C4 *)0x080D79CC;
    TextSetActiveObject(base, 0x080B7429);

    p = (u8 *)(idx << 4);
    p += 8;
    TextSetCursor(0, (u16)(u32)p);
    val = TextGetAreaWidth();
    TextDrawAlign((void *)0x083A734C, val, 0);

    p += 0x10;
    TextSetCursor(0, (u16)(u32)p);
    val = TextGetAreaWidth();
    TextDrawAlign((void *)0x083A734C, val, 0);

    base = (struct Unk617C4 *)0x082BCD00;
    TextSetActiveObject(base, 0x080B738E);

    TextSetCursor(0, (u16)(u32)(p - 0x10));
    val = TextGetAreaWidth();
    TextDrawAlign(out, val, 0);
}
