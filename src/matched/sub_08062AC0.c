#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08062ac0
#include "global.h"
#include "data_symbols.h"

// @ 0x08062ac0
void sub_08062AC0(void)
{
    if (gUnk_030008D0 != 0)
    {
        _08073C4C(0, (void *)gUnk_030008D0, 0x44, (void *)gData_080BB8BC[0]);
        _08073C4C(0, (void *)gData_05000200, 0x200, (void *)gData_080BB8BC[0]);
    }
}

