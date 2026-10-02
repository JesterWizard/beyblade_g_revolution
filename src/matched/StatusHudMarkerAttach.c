#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0805e044
// Snap the camera (sub_0802D898) to the sprite that owns `resource`: the
// three fixed HUD resources map to MainWork.unk0424/unk0500, anything else
// is looked up in the -1-terminated gData_080991D0 list via sub_08041DB4.
void sub_0805E044(void *resource)
{
    s32 i = 0;
    struct Sprite *entry;
    struct Unk5E044Lookup *lookup;

    if (resource == NULL || (gMainWorkPtr->unk1808 & 8) != 0)
        return;
    if (resource == (void *)0x08266DAC)
    {
        entry = gMainWorkPtr->unk0424;
        if (entry != NULL)
            sub_0802D898(entry->unk08, entry->unk0C);
        sub_0802D8C4(1);
        return;
    }
    if (resource == (void *)0x0827EA3C)
    {
        entry = gMainWorkPtr->unk0424;
        if (entry != NULL)
            sub_0802D898(entry->unk08, entry->unk0C);
        sub_0802D8C4(1);
        return;
    }
    if (resource == (void *)0x0826ADC8)
    {
        entry = gMainWorkPtr->unk0500;
        if (entry != NULL)
            sub_0802D898(entry->unk08, entry->unk0C);
        sub_0802D8C4(1);
        return;
    }
    for (; gData_080991D0[i] != (void *)-1; i++)
    {
        if (gData_080991D0[i] == resource)
        {
            lookup = ActorFindByIdSide(i, 0);
            if (lookup != NULL && lookup->unkB8 != NULL)
            {
                sub_0802D898(lookup->unkB8->unk08, lookup->unkB8->unk0C);
                sub_0802D8C4(1);
                return;
            }
        }
    }
}

