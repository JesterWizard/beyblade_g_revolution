#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080419b0
// Take the next free object from the gData_03000534 pool (at most 0x20 live),
// initialise it through sub_08067BB8, and append it to the gData_03000480
// list (kept NULL-terminated).
struct Actor *SceneObjSpawn(u32 a, u32 b, u32 c, u32 d)
{
    if (gData_03000534 == NULL || gData_03000504 > 0x1F)
        return NULL;
    AnimObjCreate((struct Unk67BB8 *)&gData_03000534[gData_03000504], (struct Unk67BB8Source *)b, a, c, d, 0, -1);
    gData_03000534[gData_03000504].unkBC = ~d;
    gData_03000480[gData_03000504] = &gData_03000534[gData_03000504];
    gData_03000480[gData_03000504 + 1] = NULL;
    return &gData_03000534[gData_03000504++];
}

