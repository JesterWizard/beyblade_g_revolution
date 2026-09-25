#include "global.h"

// @ 0x08062358
/* Advance Unk62634 animation frame when the per-frame timer expires. */
void sub_08062358(struct Unk62634 *a)
{
    struct Unk62358Anim *anim;
    struct Unk705DC *target;
    s16 index;

    if (a == NULL || a->unk00 == NULL)
        return;

    a->unk56--;
    if ((s16)a->unk56 > 0)
        return;

    anim = (struct Unk62358Anim *)a->unk00;
    if (a->unk52 == 1)
    {
        a->unk50++;
        if (anim[(s16)a->unk50].unk02 == -1)
        {
            a->unk54 = anim[0].unk00;
            a->unk56 = anim[0].unk02;
            a->unk50 = 0;
        }
        else
        {
            index = (s16)a->unk50;
            a->unk54 = anim[index].unk00;
            a->unk56 = anim[index].unk02;
        }
    }
    else if (a->unk52 == 2)
    {
        a->unk50++;
        if (anim[(s16)a->unk50].unk02 == -1)
        {
            a->unk54 = anim[(s16)a->unk50].unk00;
            a->unk00 = NULL;
        }
        else
        {
            index = (s16)a->unk50;
            a->unk54 = anim[index].unk00;
            a->unk56 = anim[index].unk02;
        }
    }

    target = a->unk08;
    if (target != NULL)
        target->unk18 = a->unk54;
}
