#include "global.h"

// @ 0x08042718
void sub_08042718(void)
{
    struct MainWork *w;

    w = gMainWorkPtr;
    if (w->unk182C != 0)
    {
        w->unk17B4 = w->unk044C;
        w->unk17B8 = w->unk0450;
        w->unk044C = -0x4000;
        w->unk0450 = -0x4000;
        sub_08068418(&w->unk0448);
        sub_08067CE8(&gMainWorkPtr->unk0448, 0);
        sub_08068808((struct Unk68574 *)&gMainWorkPtr->unk0448);
    }
}

