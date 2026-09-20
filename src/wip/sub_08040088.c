#include "global.h"

// @ 0x08040088
void sub_08040088(struct MainWork *a)
{
    register struct Unk40088Target *target asm("r3");

    target = a->unk0274;
    if (target != 0)
    {
        a->unk0304--;
        if (a->unk0304 == 0)
        {
            a->unk0304 = 4;
            target->unk18++;
            target = a->unk0274;
            target->unk18 &= 3;
        }
    }
}
