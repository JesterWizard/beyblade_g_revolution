#include "global.h"

// @ 0x08044d8c
u32 sub_08044D8C(u32 *a)
{
    u32 sum = 0;
    u32 bound = 0x7D8;
    u32 *p = a + 1;
    u32 i = 1;

    do
    {
        sum += *p++;
        i++;
    } while (i < bound);

    return sum;
}

