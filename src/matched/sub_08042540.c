#include "global.h"

// @ 0x08042540
#include "global.h"

void sub_08042540(void)
{
    register u8 *addr asm("r1");
    register u32 mask asm("r0");
    register u32 value asm("r2");

    addr = &gMainWorkPtr->unk0479;
    mask = 2;
    value = *addr;
    mask &= value;
    *addr = (u8)mask;
    gUnk_03000538->unk02 = 0x40;
    if (gMainWorkPtr->unk0462 != 8)
        sub_080680CC((struct Unk680CC *)&gMainWorkPtr->unk0448, 8);
    gMainWorkPtr->unk044C =
        gUnk_03000538->unk44[(s32)(s8)gUnk_03000538->unk00];
    gMainWorkPtr->unk0450 =
        gUnk_03000538->unkC4[(s32)(s8)gUnk_03000538->unk00];
}

