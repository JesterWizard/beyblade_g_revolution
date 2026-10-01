#include "global.h"

// @ 0x080426a4

void sub_080426A4(void)
{
    gMainWorkPtr->unk0479 = 0;
    gUnk_03000538->facing = 0x100;
    if (gMainWorkPtr->unk0462 != 0x0B)
        BtlEntitySelectByKeyDefault((struct Unk680CC *)&gMainWorkPtr->unk0448, 0x0B);
    gMainWorkPtr->unk044C =
        gUnk_03000538->x[(s32)(s8)gUnk_03000538->readIndex];
    gMainWorkPtr->unk0450 =
        gUnk_03000538->y[(s32)(s8)gUnk_03000538->readIndex];
}

