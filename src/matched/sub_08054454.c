#include "global.h"

// @ 0x08054454
#include "global.h"

// @ 0x08054454
void sub_08054454(void)
{
    s32 i;

    if (*(struct Unk070C **)0x0300070C != 0)
    {
        for (i = 0; i <= 0xC; i++)
        {
            if ((*(struct Unk070C **)0x0300070C)->unk00[i] != 0)
            {
                sub_0806FE84((*(struct Unk070C **)0x0300070C)->unk00[i]);
                (*(struct Unk070C **)0x0300070C)->unk00[i] = 0;
            }
        }
        sub_08070678(&(*(struct Unk070C **)0x0300070C)->unk34);
    }
}

