#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08051578
void sub_08051578(u32 a, s32 b, u32 c)
{
    u32 t;

    sub_080617C4((struct Unk617C4 *)gData_080D79CC, (u32)gData_080B7429);
    t = (u32)b << 4;
    TextSetCursor(0, t + 0x8);
    TextDrawAlign((void *)gData_083A85A4, TextGetAreaWidth() >> 1, 0);
    TextSetCursor(0, t + 0x10);
    TextDrawAlign((void *)gData_083A85A4, TextGetAreaWidth() >> 1, 0);
    sub_080617C4((struct Unk617C4 *)gData_082BCD00, (u32)gData_080B738E);
    TextSetCursor(0, t + 0x8);
    TextDrawAlign((void *)c, TextGetAreaWidth() >> 1, 0);
}

