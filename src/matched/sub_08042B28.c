#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08042b28
void *sub_08042B28(u32 i)
{
    u32 *t = gData_08091004;

    if (t[i] == 0)
        DebugPrint((void *)0x083A2CD0, i);
    return (void *)t[i];
}

