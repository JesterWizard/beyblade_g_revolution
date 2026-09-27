#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08042be8
s32 ExpBracket(s32 points)
{
    s32 i;

    for (i = 0; gData_080908BC[i].unk00 != -1; i++)
    {
        if (points >= gData_080908BC[i].unk04 && points < gData_080908BC[i + 1].unk04)
            return gData_080908BC[i].unk00;
    }
    return -1;
}

