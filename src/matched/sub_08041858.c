#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08041858
void sub_08041858(void)
{
    sub_08041980();

    if (*gData_03000508 != 0)
    {
        sub_0806A434(*gData_03000508);
        *gData_03000508 = 0;
    }
    *gData_03000534 = 0;
    *gData_03000504 = 0;
}

