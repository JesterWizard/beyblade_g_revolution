#include "global.h"

// @ 0x0802e210
s8 BitBeastLevel(void)
{
    struct Unk42E78 *p;

    p = sub_08042E78(gUnk_0300026C->unk4E);
    return ExpBracket(p->bitBeastExp);
}

