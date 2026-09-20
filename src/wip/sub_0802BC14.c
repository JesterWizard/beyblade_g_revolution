#include "global.h"

// @ 0x0802bc14
s32 sub_0802BC14(u16 a)
{
    s32 count;
    s32 limit;
    struct Unk1694 *p;
    s32 i;
    s8 sa;

    sa = (s8)a;
    count = sub_0802C62C(sa);
    limit = _0802BA7C(sa);
    sub_08067B98((void *)0x0833BE30, (s16)a, count, limit);
    if (count >= limit)
        return 1;

    p = gMainWorkPtr->unk1694;
    if (p == NULL)
        return 1;

    for (i = 0; i <= 0x7F; i++, p++)
    {
        if (*(u32 *)p == 0xFF0000FF)
        {
            return 0;
        }
    }
    return 1;
}
