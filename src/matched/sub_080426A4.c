#include "global.h"

// @ 0x080426a4

void sub_080426A4(void)
{
    gMainWorkPtr->unk0479 = 0;
    gUnk_03000538->unk02 = 0x100;
    if (gMainWorkPtr->unk0462 != 0x0B)
        Unk680CCSelectByKeyDefault((struct Unk680CC *)&gMainWorkPtr->unk0448, 0x0B);
    gMainWorkPtr->unk044C =
        gUnk_03000538->unk44[(s32)(s8)gUnk_03000538->unk00];
    gMainWorkPtr->unk0450 =
        gUnk_03000538->unkC4[(s32)(s8)gUnk_03000538->unk00];
}

