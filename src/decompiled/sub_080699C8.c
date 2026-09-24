/* match-flags: -fprologue-bugfix */
#include "global.h"

void sub_080699C8(u32 bg, s32 x, s32 y)
{
    switch ((u8)bg)
    {
    case 2:
        REG_BG2X_L = x;
        REG_BG2X_H = x >> 16;
        REG_BG2Y_L = y;
        REG_BG2Y_H = y >> 16;
        break;
    case 3:
        REG_BG3X_L = x;
        REG_BG3X_H = x >> 16;
        REG_BG3Y_L = y;
        REG_BG3Y_H = y >> 16;
        break;
    }
}
