#include "global.h"

// @ 0x08042630

void sub_08042630(void)
{
    gMainWorkPtr->unk0479 = 0;
    gUnk_03000538->unk02 = 0x80;
    if (gMainWorkPtr->unk0462 != 0x0A)
        sub_080680CC((struct Unk680CC *)&gMainWorkPtr->unk0448, 0x0A);
    gMainWorkPtr->unk044C =
        gUnk_03000538->unk44[(s32)(s8)gUnk_03000538->unk00];
    gMainWorkPtr->unk0450 =
        gUnk_03000538->unkC4[(s32)(s8)gUnk_03000538->unk00];
}

