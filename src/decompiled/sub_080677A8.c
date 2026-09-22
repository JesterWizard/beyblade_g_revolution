/* match-compiler: old_agbcc */
#include "global.h"

u32 sub_080677A8(u32 arg0, void *arg1v)
{
    u16 *arg1;
    u16 x;
    u16 buf[4];
    u16 *p;
    s32 i;

    arg1 = (u16 *)arg1v;
    x = (u16)arg0;
    if (x >= (*(struct Unk09B0 **)gUnk_030009B0)->unk04)
        return 0x80FF;

    sub_08067584(x, buf);

    p = buf;
    for (i = 0; i <= 3; i++)
    {
        if (*arg1 != *p)
            return 0x8000;
        p++;
        arg1++;
    }

    return 0;
}
