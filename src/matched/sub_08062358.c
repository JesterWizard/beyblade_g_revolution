#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08062358
// Frame-list animation tick: when the frame timer runs out, advances to the
// next frame (looping for mode 1, stopping for mode 2 at the -1 terminator)
// and pushes the current frame to the attached text entry.
void sub_08062358(struct Unk62634 *a)
{
    struct Unk62358Anim *anim;

    if (a == NULL || a->unk00 == NULL)
        return;
    if (--a->unk56 > 0)
        return;
    anim = a->unk00;
    switch (a->unk52)
    {
    case 1:
        if (anim[++a->unk50].unk02 == -1)
        {
            a->unk54 = anim[0].unk00;
            a->unk56 = anim[0].unk02;
            a->unk50 = 0;
        }
        else
        {
            a->unk54 = anim[a->unk50].unk00;
            a->unk56 = anim[a->unk50].unk02;
        }
        break;
    case 2:
        if (anim[++a->unk50].unk02 == -1)
        {
            a->unk54 = anim[a->unk50].unk00;
            a->unk00 = NULL;
        }
        else
        {
            a->unk54 = anim[a->unk50].unk00;
            a->unk56 = anim[a->unk50].unk02;
        }
        break;
    }
    if (a->unk08 != NULL)
        a->unk08->unk18 = a->unk54;
}

