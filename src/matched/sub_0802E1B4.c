#include "global.h"

// @ 0x0802e1b4
s8 sub_0802E1B4(s32 a)
{
    s32 x;
    s32 y;
    s32 z;
    s8 t;

    x = sub_08042BE8(a);
    y = sub_08042BB0(x);
    z = sub_08042B78(x);
    t = sub_08031124(z - a, z - y, 14);
    return 14 - t;
}

