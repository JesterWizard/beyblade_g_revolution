#include "global.h"

// @ 0x0802c62c
#include "global.h"

s32 sub_0802C62C(u8 a)
{
    s8 *p;
    s32 count;
    s32 i;
    s32 val;
    u32 *new_var;

    count = 0;
    new_var = (u32 *)0x03000198;
    p = *(s8 **)(*new_var + 0x1694);
    if (p != 0)
    {
        val = (s8)a;
        i = 0x7F;
        for (; i >= 0; i--)
        {
            if (p[3] == val)
                count++;
            p += 4;
        }
    }
    return count;
}

