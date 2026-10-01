#include "global.h"

// @ 0x08042540

void sub_08042540(void)
{
    u8 *addr;
    u32 mask;
    u32 value;

    addr = &gMainWorkPtr->unk0479;
    mask = 2;
    value = *addr;
    mask &= value;
    *addr = (u8)mask;
    gUnk_03000538->facing = 0x40;
    if (gMainWorkPtr->unk0462 != 8)
        BtlEntitySelectByKeyDefault((struct Unk680CC *)&gMainWorkPtr->unk0448, 8);
    gMainWorkPtr->unk044C =
        gUnk_03000538->x[(s32)(s8)gUnk_03000538->readIndex];
    gMainWorkPtr->unk0450 =
        gUnk_03000538->y[(s32)(s8)gUnk_03000538->readIndex];
}

