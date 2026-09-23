#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08061c48
#include "global.h"

void Unk770FreeLastSlot(void)
{
    s32 i;
    struct Unk0770 *base;

    i = gData_03000794[0] - 1;
    if (i < 0)
        return;
    gData_03000794[0] = i;
    base = (struct Unk0770 *)gData_03000770;
    if (base[i].unk00 != 0)
    {
        BtlObjFree(base[i].unk00);
        base[gData_03000794[0]].unk00 = 0;
    }
}
