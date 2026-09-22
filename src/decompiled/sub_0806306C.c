#include "global.h"
#include "data_symbols.h"

// @ 0x0806306c
void sub_0806306C(void)
{
    if (gUnk_030008DC != 0 && gUnk_030008D8 != 0 && gUnk_030008E0 != 0 && gUnk_030008D4 != 0)
    {
        _08073C4C(gUnk_030008DC, (void *)0x05000000, 0x200, (void *)gData_080BB8C0[0]);
        _08073C4C(gUnk_030008D8, (void *)gData_05000200, 0x200, (void *)gData_080BB8C0[0]);
        if (gUnk_030008E0 != 0)
        {
            sub_0806A434(gUnk_030008E0);
            gUnk_030008E0 = 0;
        }
        if (gUnk_030008D4 != 0)
        {
            sub_0806A434(gUnk_030008D4);
            gUnk_030008D4 = 0;
        }
        gUnk_030008DC = 0;
        gUnk_030008D8 = 0;
    }
}
