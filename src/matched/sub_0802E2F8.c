#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802e2f8
/* match-compiler: old_agbcc */
s32 sub_0802E2F8(u16 a, u16 b, s32 scale)
{
    s32 i;
    s32 value;

    for (i = 0; gData_08077AC0[i].unk00 > -1; i++)
    {
        if (gData_08077AC0[i].unk00 == (s16)a && gData_08077AC0[i].unk02 == (s16)b
         && gData_08077AC0[i].unk06 > 0)
        {
            value = _080740B0((gData_08077AC0[i].unk06 >> 1) * scale, 100);
            if (value > 0)
                return value;
            return 2;
        }
    }
    return 10;
}

