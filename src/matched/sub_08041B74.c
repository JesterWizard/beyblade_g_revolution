#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08041b74
/* match-compiler: old_agbcc */
// Remove the live object bound to (a, b): free its unkC8 node, park it
// off-screen, and swap the last slot into its place.
void SceneObjDespawn(void *a, void *b)
{
    s16 i;
    struct Actor **slot;

    i = 0;
    if (gData_03000504 > 0)
    {
        for (; i < gData_03000504; i++)
        {
            slot = &gData_03000480[i];
            if (*slot != NULL && (*slot)->unkD4 == a && (*slot)->unkD8 == b)
            {
                if ((*slot)->unkC8 != NULL)
                {
                    TaskDestroy((struct Unk59D08 *)(*slot)->unkC8);
                    (*slot)->unkC8 = NULL;
                }
                SceneObjFreeResources(*slot);
                (*slot)->x = -0x4000;
                (*slot)->y = -0x4000;
                *slot = gData_03000480[--gData_03000504];
                gData_03000480[gData_03000504] = NULL;
                return;
            }
        }
    }
}

