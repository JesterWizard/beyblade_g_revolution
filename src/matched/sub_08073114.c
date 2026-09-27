#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08073114
void BtlObjTableRemove(void *a)
{
    struct BtlObj **table;
    u32 i;

    table = gData_03004150;
    if (table == 0)
        return;
    for (i = 0; i < gData_03004154; i++)
    {
        if (table[i] != 0 && table[i]->next == a)
        {
            HeapFree(table[i]);
            table[i] = 0;
            gData_03004158--;
            break;
        }
    }
    if (i == gData_03004154)
        DebugPrint(gData_083D2690);
}

