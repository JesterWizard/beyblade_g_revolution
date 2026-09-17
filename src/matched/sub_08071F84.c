#include "global.h"

// @ 0x08071f84
void sub_08071F84(s32 a)
{
    struct Unk71F84 *p;

    p = sub_08071F44(a);
    if (p != 0)
        p->unk16 = 0;
}

