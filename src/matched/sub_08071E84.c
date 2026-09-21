#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08071e84
/* match-compiler: old_agbcc */
// Find the first free Unk71E84 slot (*gData_030040C4 slots at *gData_030040E4).
// `i != -1` must stay a compare against a materialised -1; plain agbcc folds the
// entry test to `cmp r0,#0`. `id` has to be a local so the counter increment
// reuses the value just stored into unk18.
void *sub_08071E84(void *a, u32 b)
{
    struct Unk71E84 *e = *(struct Unk71E84 **)gData_030040E4;
    s32 i;
    u32 id;

    for (i = *(u8 *)gData_030040C4 - 1; i != -1; i--)
    {
        if (e->unk16 == 0)
        {
            sub_08071E44(e, a, (s16 *)b);
            id = *(u32 *)gData_030000C8;
            e->unk18 = id;
            id++;
            *(u32 *)gData_030000C8 = id;
            return (void *)e->unk18;
        }
        e++;
    }
    sub_08067B98((void *)gData_083D2578);
    return (void *)-1;
}

