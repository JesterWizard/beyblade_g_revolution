#include "global.h"

// @ 0x08046278
void sub_08046278(void)
{
    register struct MainWork **mainPtr asm("r8");
    register u32 zero asm("r9");
    register u32 minusOne asm("r4");
    register u32 offset asm("r2");
    register u32 slot00 asm("r12");
    register u32 slot04 asm("r6");
    register u32 slot08 asm("r5");
    register s32 count asm("r3");
    register struct MainWork *w asm("r0");

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
