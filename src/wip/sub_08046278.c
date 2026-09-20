#include "global.h"

// @ 0x08046278
void sub_08046278(void)
{
    struct MainWork **mainPtr;
    u32 zero;
    u32 minusOne;
    u32 offset;
    u32 slot00;
    u32 slot04;
    u32 slot08;
    s32 count;
    struct MainWork *w;

    mainPtr = gMainWorkPtrLoc;
    slot00 = 0x16B0;
    minusOne = (u32)-1;
    offset = 0;
    zero = 0;
    slot04 = 0x16B4;
    slot08 = 0x16B8;
    count = 1;
    do
    {
        w = *mainPtr;
        *(u32 *)((u8 *)w + slot00 + offset) = zero;
        *(u32 *)((u8 *)w + slot04 + offset) = minusOne;
        *(u32 *)((u8 *)w + slot08 + offset) = minusOne;
        offset += 0x0C;
        count--;
    } while (count >= 0);
}
