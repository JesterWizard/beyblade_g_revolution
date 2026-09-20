#include "global.h"

// @ 0x08062c38
#include "global.h"

void sub_08062C38(u16 arg0)
{
    u16 counter;
    s32 diff;

    counter = 0x1F;
    *(u16 *)0x04000050 = 0xFF;

    do
    {
        counter = counter - arg0;
        diff = (s16)counter;
        if (diff < 0)
        {
            counter = 0;
            arg0 = 0;
        }
        *(u16 *)0x04000054 = counter;
        sub_080674B4();
        _08073C40(*(void **)0x080BB888);
        sub_080474AC();
    } while (counter != 0);
}

