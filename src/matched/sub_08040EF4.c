#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08040ef4
/* match-compiler: old_agbcc */
s32 GetPlayerKeyedWord(void *key)
{
    s32 i;

    for (i = 0; gData_0808B2E4[i].unk00 != -1; i++)
    {
        if (gData_0808B2E4[i].unk00 == (u32)key)
            return ((u32 *)gData_0808B2E4[i].unk04)[gMainWorkPtr->language];
    }
    return 0;
}

