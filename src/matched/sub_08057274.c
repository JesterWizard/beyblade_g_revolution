#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08057274
/* match-compiler: old_agbcc */
// Map the current input direction (MainWork.unk1810) to the cursor entity
// animation (keys 5/6/7) and update its facing flags.
void sub_08057274(void)
{
    switch (gMainWorkPtr->unk1810)
    {
    case 0x40:
        if (gMainWorkPtr->unk0386 != 5)
            BtlEntitySelectByKeyDefault((struct Unk680CC *)&gMainWorkPtr->unk036C, 5);
        gMainWorkPtr->unk039D &= 2;
        break;
    case 0x20:
        if (gMainWorkPtr->unk0386 != 5)
            BtlEntitySelectByKeyDefault((struct Unk680CC *)&gMainWorkPtr->unk036C, 5);
        gMainWorkPtr->unk039D |= 1;
        break;
    case 0x80:
        if (gMainWorkPtr->unk0386 != 6)
            BtlEntitySelectByKeyDefault((struct Unk680CC *)&gMainWorkPtr->unk036C, 6);
        gMainWorkPtr->unk039D = 0;
        break;
    case 0x100:
        if (gMainWorkPtr->unk0386 != 7)
            BtlEntitySelectByKeyDefault((struct Unk680CC *)&gMainWorkPtr->unk036C, 7);
        gMainWorkPtr->unk039D = 0;
        break;
    }
}

