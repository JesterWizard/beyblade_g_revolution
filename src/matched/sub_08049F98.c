#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08049f98
#include "global.h"

// @ 0x08049f98
void sub_08049F98(u32 a, s32 b, u32 c)
{
    u32 t;

    sub_080617C4((struct Unk617C4 *)gData_080D79CC, (u32)gData_080B7429);
    t = (u32)b << 4;
    sub_080615EC(0, t + 0x8);
    sub_0806171C((void *)gData_083A734C, sub_08061784() >> 1, 0);
    sub_080615EC(0, t + 0x10);
    sub_0806171C((void *)gData_083A734C, sub_08061784() >> 1, 0);
    sub_080617C4((struct Unk617C4 *)gData_082BCD00, (u32)gData_080B738E);
    sub_080615EC(0, t + 0x8);
    sub_0806171C((void *)c, sub_08061784() >> 1, 0);
}

