#include "global.h"

s32 sub_08042390(struct Unk42390 *arg0)
{
    s32 y = arg0->unk04 >> 8;
    s32 x = arg0->unk08 >> 8;
    s32 py = (s32)gMainWorkPtr->unk0370 >> 8;
    s32 px = (s32)gMainWorkPtr->unk0374 >> 8;

    if (py >= y)
    {
        if (px >= x)
        {
            if (py - y <= 0xB)
                return 0;
            return 2;
        }
        else
        {
            if (py - y > 0xB)
                return 2;
            return 1;
        }
    }
    else
    {
        if (px >= x)
        {
            if (y - py <= 0xB)
                return 0;
            return 3;
        }
        else
        {
            if (y - py <= 0xB)
                return 1;
            return 3;
        }
    }
}
