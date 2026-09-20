#include "global.h"

// @ 0x08046278
void sub_08046278(void)
{
    register struct MainWork **mainPtr;
    register u32 zero;
    register u32 minusOne;
    register u32 offset;
    register u32 slot00;
    register u32 slot04;
    register u32 slot08;
    register s32 count;
    register struct MainWork *w;

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
