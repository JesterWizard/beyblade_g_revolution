#include "global.h"

// @ 0x080424e8

void CursorFaceIdlePose(void);

// @ 0x080424e8
void sub_080424E8(void)
{
    struct MainWork *w = gMainWorkPtr;

    if (w->unk182C != 0)
    {
        w->unk0488 = 0;
        w->unk048C = 0;
        CursorFaceIdlePose();
        gMainWorkPtr->unk17B4 = gMainWorkPtr->unk044C;
        gMainWorkPtr->unk17B8 = gMainWorkPtr->unk0450;
    }
}

