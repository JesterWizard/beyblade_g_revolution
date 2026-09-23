#include "global.h"

// @ 0x08043638
void sub_08043638(void)
{
    gMainWorkPtr->unk0868 = gMainWorkPtr->unk0370;
    gMainWorkPtr->unk086C = gMainWorkPtr->unk0374;
    gMainWorkPtr->unk039D = 0;
    gMainWorkPtr->unk1810 = 0x100;

    gUnk_03000554->unk01 = 0;
    sub_080436B0();

    if (gUnk_03000554->unk01 == 1)
        sub_08043420();
    else
        Unk680CCSelectByKeyDefault((struct Unk680CC *)&gMainWorkPtr->unk036C, 7);
}

