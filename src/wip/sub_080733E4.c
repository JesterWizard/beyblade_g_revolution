#include "global.h"

// @ 0x080733e4
s32 sub_080733E4(u8 *a, u8 *b, s32 c)
{
    s32 i;
    u8 *end;
    u8 ch;

    if (a == NULL)
        return -1;
    if (b == NULL)
        return -1;

    while (*b != 0)
    {
        b++;
        c--;
    }

    if (c <= 0)
        return -1;

    end = b + c - 1;

    for (i = 0; ; i++)
    {
        if (i >= c)
        {
            *end = 0;
            ch = a[i];
        }
        else
        {
            ch = a[i];
            if (ch != '\n')
                b[i] = ch;
        }

        if (ch == 0)
            break;
    }

    return i - 1;
}
