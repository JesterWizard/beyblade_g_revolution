#include "global.h"

void sub_080473F8(void)
{
    void *pool;
    void **temp;
    s32 i;

    temp = sub_0806A3A4(0x48);
    *(void ***)gUnk_03000638 = temp;
    *(void **)gUnk_03000630 = pool = *temp;
    ((struct Unk473F8 *)pool)->unk44 = 0x1C20;

    for (i = 0; i <= 0xF; i++)
    {
        (*(struct Unk473F8 **)gUnk_03000630)->unk00[i] = sub_0806FDD0(2);
        sub_0806FF58((*(struct Unk473F8 **)gUnk_03000630)->unk00[i], (void *)0x081193C0, 0, 1, 0, 0, 0xFFFFC000, 0xFFFFC000);
    }
}
