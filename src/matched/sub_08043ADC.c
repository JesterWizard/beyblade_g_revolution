#include "global.h"

// @ 0x08043adc
void sub_08043ADC(void)
{
    struct Unk68574 **slot;
    struct Unk68574 **saved;
    s32 n;
    s32 off;

    slot = (struct Unk68574 **)gUnk_0300054C;
    if (*slot != 0)
    {
        saved = slot;
        off = 0;
        n = 7;
        do
        {
            sub_08068808((struct Unk68574 *)((u8 *)*saved + off));
            off += 0xDC;
            n--;
        } while (n >= 0);
    }
    if (*(void **)gUnk_03000550 != 0)
    {
        HeapFree(*(void **)gUnk_03000550);
        *(void **)gUnk_03000550 = 0;
    }
    *(struct Unk68574 **)gUnk_0300054C = 0;
}

