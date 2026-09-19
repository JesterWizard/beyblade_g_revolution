#include "global.h"

// @ 0x080424e8
#include "global.h"

void sub_080427E8(void);

// @ 0x080424e8
void sub_080424E8(void)
{
    struct MainWork *w = gMainWorkPtr;

    if (w->unk182C != 0)
    {
        w->unk0488 = 0;
        w->unk048C = 0;
        sub_080427E8();
        gMainWorkPtr->unk17B4 = gMainWorkPtr->unk044C;
        gMainWorkPtr->unk17B8 = gMainWorkPtr->unk0450;
    }
}

