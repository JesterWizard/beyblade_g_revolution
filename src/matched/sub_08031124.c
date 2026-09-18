#include "global.h"

// @ 0x08031124
s16 sub_08031124(s32 a, s32 b, s32 c)
{
    if (b <= 0)
        return -1;
    if (a < 0)
        a = 0;
    if (a > b)
        a = b;
    return sub_080674A0(a * c, b);
}

