#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0804a438
void sub_0804A438(u8 *a, s32 b, u32 c)
{
    u32 t;

    if (b == *(s8 *)(a + 0x2D5))
        TextSetPaletteBank(0x0E);
    else
        TextSetPaletteBank(0x0F);
    sub_080617C4((struct Unk617C4 *)gData_080D79CC, (u32)gData_080B7429);
    t = (u32)b << 4;
    TextSetCursor(0, t + 0x8);
    TextDrawAlign((void *)gData_083A7404, TextGetAreaWidth() >> 1, 0);
    TextSetCursor(0, t + 0x10);
    TextDrawAlign((void *)gData_083A7404, TextGetAreaWidth() >> 1, 0);
    sub_080617C4((struct Unk617C4 *)gData_082BCD00, (u32)gData_080B738E);
    TextSetCursor(0, t + 0x8);
    TextDrawAlign((void *)c, TextGetAreaWidth() >> 1, 0);
}

