#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806306c
#include "global.h"
#include "data_symbols.h"

// @ 0x0806306c
void sub_0806306C(void)
{
    u32 *d;

    if (gUnk_030008DC != 0 && gUnk_030008D8 != 0 && gUnk_030008E0 != 0 && gUnk_030008D4 != 0)
    {
        d = gData_080BB8C0;
        _08073C4C(gUnk_030008DC, (void *)0x05000000, 0x200, (void *)d[0]);
        _08073C4C(gUnk_030008D8, (void *)gData_05000200, 0x200, (void *)d[0]);
        if (gUnk_030008E0 != 0)
        {
            BtlObjFree(gUnk_030008E0);
            gUnk_030008E0 = 0;
        }
        if (gUnk_030008D4 != 0)
        {
            BtlObjFree(gUnk_030008D4);
            gUnk_030008D4 = 0;
        }
        gUnk_030008DC = 0;
        gUnk_030008D8 = 0;
    }
}

