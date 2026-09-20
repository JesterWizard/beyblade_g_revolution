#include "global.h"

void sub_080427E8(void)
{
    register struct MainWork *main;

    main = gMainWorkPtr;
    if (main->unk182C == 0)
        return;
    switch (gUnk_03000538->unk02)
    {
    case 0x40:
        if (main->unk0462 != 5)
            sub_080680CC((struct Unk680CC *)&main->unk0448, 5);
        gMainWorkPtr->unk0479 = 2 & gMainWorkPtr->unk0479;
        break;
    case 0x20:
        if (main->unk0462 != 5)
            sub_080680CC((struct Unk680CC *)&main->unk0448, 5);
        gMainWorkPtr->unk0479 = 1 | gMainWorkPtr->unk0479;
        break;
    case 0x80:
        if (main->unk0462 != 6)
            sub_080680CC((struct Unk680CC *)&main->unk0448, 6);
        gMainWorkPtr->unk0479 = 0;
        break;
    case 0x100:
        if (main->unk0462 != 7)
            sub_080680CC((struct Unk680CC *)&main->unk0448, 7);
        gMainWorkPtr->unk0479 = 0;
        break;
    }
}
