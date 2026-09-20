#include "global.h"

// @ 0x08043b58
#include "global.h"

/* match-flags: -fprologue-bugfix */

struct Unk447CC *sub_08043B58(void)
{
    register u32 key asm("r2");
    register struct Unk447CC *r1 asm("r1");
    register struct Unk447CC **r3 asm("r3");
    register u32 r0 asm("r0");

    key = gMainWorkPtr->unk1690->unk00;
    r0 = 0x08096794;
    r1 = *(struct Unk447CC **)r0;
    if (r1 != 0)
    {
        r3 = (struct Unk447CC **)(r0 + 4);
        do
        {
            r0 = (u32)r1->unk00;
            if (key == r0)
            {
                r0 = (u32)r1;
                goto done;
            }
            r1 = *r3++;
        } while (r1 != 0);
    }
    r0 = 0;
done:
    return (struct Unk447CC *)r0;
}

