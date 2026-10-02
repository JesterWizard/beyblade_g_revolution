#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08043420
/* match-compiler: old_agbcc */
// Steps the 24.8 position (unk0370/unk0374) one unit toward the target
// (unk04/unk06) along the direction in unk00 (0: -unk0374, 1: +unk0374,
// 2: +unk0370, 3: -unk0370), selecting that direction's animation; calls
// sub_08043638 once the target is reached.
void MapCursorMoveStep(void)
{
    struct Unk0554 *move = gUnk_03000554;

    switch (move->unk00)
    {
    case 0:
        if ((gMainWorkPtr->unk0374 >> 8) > move->unk06)
        {
            gMainWorkPtr->unk0374 -= 0x100;
            gMainWorkPtr->unk086C = gMainWorkPtr->unk0374;
            gMainWorkPtr->unk039D = 0;
            gMainWorkPtr->unk1810 = 0x80;
            if (gMainWorkPtr->unk0386 != 10)
                AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk036C, 10);
        }
        else
            sub_08043638();
        break;
    case 1:
        if ((gMainWorkPtr->unk0374 >> 8) < move->unk06)
        {
            gMainWorkPtr->unk0374 += 0x100;
            gMainWorkPtr->unk086C = gMainWorkPtr->unk0374;
            gMainWorkPtr->unk039D = 0;
            gMainWorkPtr->unk1810 = 0x100;
            if (gMainWorkPtr->unk0386 != 11)
                AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk036C, 11);
        }
        else
            sub_08043638();
        break;
    case 2:
        if ((gMainWorkPtr->unk0370 >> 8) < move->unk04)
        {
            gMainWorkPtr->unk0370 += 0x100;
            gMainWorkPtr->unk0868 = gMainWorkPtr->unk0370;
            gMainWorkPtr->unk039D |= 1;
            gMainWorkPtr->unk1810 = 0x20;
            if (gMainWorkPtr->unk0386 != 8)
                AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk036C, 8);
        }
        else
            sub_08043638();
        break;
    case 3:
        if ((gMainWorkPtr->unk0370 >> 8) > move->unk04)
        {
            gMainWorkPtr->unk0370 -= 0x100;
            gMainWorkPtr->unk0868 = gMainWorkPtr->unk0370;
            gMainWorkPtr->unk039D &= 2;
            gMainWorkPtr->unk1810 = 0x40;
            if (gMainWorkPtr->unk0386 != 8)
                AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk036C, 8);
        }
        else
            sub_08043638();
        break;
    }
}

