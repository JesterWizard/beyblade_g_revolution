#include "global.h"

// @ 0x08044a20
void sub_08044A20(void)
{
    if (gMainWorkPtr->unk17C4 != 0xFFFFC000)
    {
        gMainWorkPtr->unk17B4 = gMainWorkPtr->unk17C4;
        gMainWorkPtr->unk17B8 = gMainWorkPtr->unk17C8;
        gMainWorkPtr->unk17C4 = 0xFFFFC000;
        gMainWorkPtr->unk17C8 = 0xFFFFC000;
    }

    gMainWorkPtr->unk044C = gMainWorkPtr->unk17B4;
    gMainWorkPtr->unk0450 = gMainWorkPtr->unk17B8;
}

