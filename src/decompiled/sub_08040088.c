#include "global.h"

// @ 0x08040088
/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x08040088
void sub_08040088(struct MainWork *a)
{
    struct Unk40088Target **targetSlot;
    struct Unk40088Target *target;
    s32 *counter;

    targetSlot = &a->unk0274;
    target = *targetSlot;
    if (target != 0)
    {
        counter = &a->unk0304;
        (*counter)--;
        if (*counter == 0)
        {
            *counter = 4;
            target->unk18++;
            {
                struct Unk40088Target *target2;
                u16 mask;
                u16 value;

                target2 = *targetSlot;
                mask = 3;
                value = target2->unk18;
                mask &= value;
                target2->unk18 = mask;
            }
        }
    }
}

