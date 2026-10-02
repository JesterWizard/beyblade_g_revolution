#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08071ee4
/* match-compiler: old_agbcc */
// Same free-slot search as sub_08071E84, calling sub_08071E04 instead.
void *SoundPlay(void *a, u32 b)
{
    struct SoundChannel *e = *(struct SoundChannel **)gData_030040E4;
    s32 i;
    u32 id;

    for (i = *(u8 *)gData_030040C4 - 1; i != -1; i--)
    {
        if (e->state == 0)
        {
            SoundChannelInit(e, a, b);
            id = *(u32 *)gData_030000C8;
            e->handle = id;
            id++;
            *(u32 *)gData_030000C8 = id;
            return (void *)e->handle;
        }
        e++;
    }
    DebugPrint((void *)gData_083D2578);
    return (void *)-1;
}

