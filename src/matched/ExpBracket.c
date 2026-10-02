#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08042be8
s32 ExpBracket(s32 points)
{
    s32 i;

    for (i = 0; gData_080908BC[i].level != -1; i++)
    {
        if (points >= gData_080908BC[i].minPoints && points < gData_080908BC[i + 1].minPoints)
            return gData_080908BC[i].level;
    }
    return -1;
}

