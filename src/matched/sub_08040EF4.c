#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08040ef4
/* match-compiler: old_agbcc */
s32 GetPlayerKeyedWord(void *key)
{
    s32 i;

    for (i = 0; gData_0808B2E4[i].key != -1; i++)
    {
        if (gData_0808B2E4[i].key == (u32)key)
            return ((u32 *)gData_0808B2E4[i].texts)[gMainWorkPtr->language];
    }
    return 0;
}

