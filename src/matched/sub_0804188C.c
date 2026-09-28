#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0804188c
/* match-compiler: old_agbcc */
// Per-frame update of the scene objects: tick each one, refresh its sort key
// (0xFFFF when unkD8 == 1, else ~(unk08 >> 8)) and re-claim its palette slot.
void SceneObjsUpdateAll(void)
{
    s16 i;
    u16 color;

    i = 0;
    if (gData_03000504 > 0)
    {
        ObjPaletteSlotsReleaseRange(3, 0x0F);
        while (i < gData_03000504)
        {
            SceneObjUpdate(gData_03000480[i]);
            if (gData_03000480[i]->unkB8 != NULL)
            {
                if (gData_03000480[i]->unkD8 == (void *)1)
                {
                    gData_03000480[i]->unkBC = 0xFFFF;
                    BtlObjListResort(gData_03000480[i]->unkB8, gData_03000480[i]->unkBC);
                }
                else
                {
                    gData_03000480[i]->unkBC = ~((s32)gData_03000480[i]->y >> 8);
                    BtlObjListResort(gData_03000480[i]->unkB8, gData_03000480[i]->unkBC);
                }
                if (gData_03000480[i]->unkD8 == NULL)
                    color = (s8)ScenePaletteAcquire(gData_080775CC, gData_03000480[i]->unkD4);
                else
                    color = (s8)ScenePaletteAcquire(gData_080779A8, gData_03000480[i]->unkD4);
                gData_03000480[i]->unk3A = (color << 1) | 1;
            }
            sub_08067CE8(gData_03000480[i++], 0);
        }
    }
}

