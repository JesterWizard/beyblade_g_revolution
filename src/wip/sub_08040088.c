#include "global.h"

// @ 0x08040088
#include "global.h"

// @ 0x08040088
void sub_08040088(struct MainWork *a)
{
    register struct Unk40088Target **targetSlot;
    register struct Unk40088Target *target;
    register s32 *counter;

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
                register struct Unk40088Target *target2;
                register u16 mask;
                register u16 value;

                target2 = *targetSlot;
                mask = 3;
                value = target2->unk18;
                mask &= value;
                target2->unk18 = mask;
            }
        }
    }
}

