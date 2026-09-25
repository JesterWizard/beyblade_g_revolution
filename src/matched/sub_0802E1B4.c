#include "global.h"

// @ 0x0802e1b4
s8 ExpBarFill(s32 points)
{
    s32 level;
    s32 base;
    s32 top;
    s8 fill;

    level = ExpBracket(points);
    base = ExpBracketBase(level);
    top = ExpBracketTop(level);
    fill = ScaleRatio(top - points, top - base, 14);
    return 14 - fill;
}

