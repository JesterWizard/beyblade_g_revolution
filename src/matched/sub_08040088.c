#include "global.h"

// @ 0x08040088
#include "global.h"

// @ 0x08040088
void sub_08040088(struct MainWork *a)
{
    register struct Unk40088Target **targetSlot asm("r1");
    register struct Unk40088Target *target asm("r3");
    register s32 *counter asm("r2");

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
                register struct Unk40088Target *target2 asm("r1");
                register u16 mask asm("r0");
                register u16 value asm("r2");

                target2 = *targetSlot;
                mask = 3;
                value = target2->unk18;
                mask &= value;
                target2->unk18 = mask;
            }
        }
    }
}

