#include "global.h"

void sub_080425B8(void)
{
    {
        register struct MainWork *main asm("r0");

        main = gMainWorkPtr;
        main->unk0479 = 1 | main->unk0479;
    }
    gUnk_03000538->unk02 = 0x20;
    if (gMainWorkPtr->unk0462 != 8)
        sub_080680CC((struct Unk680CC *)&gMainWorkPtr->unk0448, 8);
    gMainWorkPtr->unk044C =
        gUnk_03000538->unk44[(s32)(s8)gUnk_03000538->unk00];
    gMainWorkPtr->unk0450 =
        gUnk_03000538->unkC4[(s32)(s8)gUnk_03000538->unk00];
}
