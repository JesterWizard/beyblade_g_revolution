#include "global.h"

// @ 0x08033dd4
#define sub_08035908(a) ((u32 (*)(struct Unk35878 *))sub_08035908)(a)

// @ 0x08033dd4
void sub_08033DD4(void)
{
    struct Unk0380 *p = (struct Unk0380 *)gUnk_03000380;
    struct Unk0380Target *t = p->unk00;

    if (t->unk310 == 0 && t->unk2CC != 7 && t->unk312 == 0)
    {
        if (p->unk0A != 0 && p->unk09 != 0)
        {
            sub_08035884(&p->unk0C);
            if (sub_08035908(&p->unk0C) != 0)
                sub_08033C1C();
        }
        else
        {
            sub_08033E3C((struct Unk33F30 *)p);
        }
        return;
    }

    if (p->unk09 != 0)
        sub_08033C1C();
}

