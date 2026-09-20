#include "global.h"

// @ 0x08062bf0
#include "global.h"

// @ 0x08062bf0
void sub_08062BF0(u16 a)
{
    s16 b;
    void **src;

    b = 0;
    *(u16 *)0x04000050 = 0xFF;
    do
    {
        b = a + b;
        if (b > 0x1F)
        {
            b = 0x1F;
            a = 0;
        }
        *(u16 *)0x04000054 = b;
        sub_080674B4();
        src = (void **)0x080BB888;
        _08073C40(*src);
        sub_080474AC();
    } while (b != 0x1F);
}

