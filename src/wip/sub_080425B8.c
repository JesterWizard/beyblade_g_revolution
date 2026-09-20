#include "global.h"

// @ 0x080425b8
#include "global.h"

void sub_080425B8(void)
{
    register u8 *addr;
    register u8 mask;
    register u8 value;

    addr = &gMainWorkPtr->unk0479;
    mask = 1;
    value = *addr;
    mask |= value;
    *addr = mask;
    gUnk_03000538->unk02 = 0x20;
    if (gMainWorkPtr->unk0462 != 8)
        sub_080680CC((struct Unk680CC *)&gMainWorkPtr->unk0448, 8);
    gMainWorkPtr->unk044C =
        gUnk_03000538->unk44[(s32)(s8)gUnk_03000538->unk00];
    gMainWorkPtr->unk0450 =
        gUnk_03000538->unkC4[(s32)(s8)gUnk_03000538->unk00];
}

