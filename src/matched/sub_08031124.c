#include "global.h"

// @ 0x08031124
s16 ScaleRatio(s32 a, s32 b, s32 c)
{
    if (b <= 0)
        return -1;
    if (a < 0)
        a = 0;
    if (a > b)
        a = b;
    return Div(a * c, b);
}

