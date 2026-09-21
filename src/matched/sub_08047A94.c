#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08047a94
#include "global.h"

// @ 0x08047a94
void sub_08047A94(u8 *a, s32 b, u32 c)
{
    u32 t;

    if (b == *(s8 *)(a + 0x2D5))
        sub_08061610(0x0E);
    else
        sub_08061610(0x0F);
    sub_080617C4((struct Unk617C4 *)gData_080D79CC, (u32)gData_080B7429);
    t = (u32)b << 4;
    sub_080615EC(0, t + 0x28);
    sub_0806171C((void *)gData_083A6BE0, sub_08061784() >> 1, 0);
    sub_080615EC(0, t + 0x30);
    sub_0806171C((void *)gData_083A6BE0, sub_08061784() >> 1, 0);
    sub_080617C4((struct Unk617C4 *)gData_082BCD00, (u32)gData_080B738E);
    sub_080615EC(0, t + 0x28);
    sub_0806171C((void *)c, sub_08061784() >> 1, 0);
}

