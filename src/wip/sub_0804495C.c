#include "global.h"

// @ 0x0804495c
#include "global.h"

/* match-flags: -fprologue-bugfix */

void sub_0804495C(void)
{
    u32 table;
    s32 idx;
    u16 *src;
    u16 *dst;
    s32 n;
    u16 tmp;

    table = 0x08094E00;
    idx = gMainWorkPtr->unk181F;
    idx <<= 2;
    idx = idx + table;
    src = *(u16 **)idx;
    dst = (u16 *)0x050001C0;
    n = 0x1F;
    do
    {
        tmp = *src;
        *dst = tmp;
        src++;
        dst++;
        n--;
    } while (n >= 0);
}
