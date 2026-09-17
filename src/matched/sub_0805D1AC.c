#include "global.h"

// @ 0x0805d1ac
void sub_0805D1AC(void)
{
    struct Unk0748 *p;

    p = *(struct Unk0748 **)gUnk_03000748;
    if (p != 0 && p->unk80 != 0)
    {
        sub_08068418(&p->unk84);
        sub_08067CE8(&(*(struct Unk0748 **)gUnk_03000748)->unk84, 0);
    }
}

