#include "global.h"

// @ 0x08047594
void sub_08047594(void)
{
    struct Unk473F8 **slot;
    s32 i;
    struct Unk474ACSlot *p;
    s32 v;

    slot = &gUnk_03000630;
    if (*slot != 0)
    {
        i = 0;
        v = -0x4000;
        do
        {
            p = (*slot)->unk00[i];
            p->unk08 = v;
            p->unk0C = v;
            i++;
        } while (i <= 0xF);
    }
}
