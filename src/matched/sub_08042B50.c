#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08042b50
void *sub_08042B50(u32 i)
{
    u32 *t = gData_080910E8;

    if (t[i] == 0)
        DebugPrint((void *)0x083A2CD0, i);
    return (void *)t[i];
}

