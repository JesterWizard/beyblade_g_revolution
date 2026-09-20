#include "global.h"

void sub_08043420(void)
{
    struct MainWork *main;

    switch (gUnk_03000554->unk00)
    {
    case 0:
        main = gMainWorkPtr;
        if ((main->unk0374 >> 8) <= gUnk_03000554->unk06)
        {
            sub_08043638();
            break;
        }
        main->unk0374 -= 0x100;
        main->unk086C = main->unk0374;
        main->unk039D = 0;
        main->unk1810 = 0x80;
        if (main->unk0386 != 0x0A)
            sub_080680CC((struct Unk680CC *)&main->unk036C, 0x0A);
        break;
    case 1:
        main = gMainWorkPtr;
        if ((main->unk0374 >> 8) >= gUnk_03000554->unk06)
        {
            sub_08043638();
            break;
        }
        main->unk0374 += 0x100;
        main->unk086C = main->unk0374;
        main->unk039D = 0;
        main->unk1810 = 0x100;
        if (main->unk0386 != 0x0B)
            sub_080680CC((struct Unk680CC *)&main->unk036C, 0x0B);
        break;
    case 2:
        main = gMainWorkPtr;
        if ((main->unk0370 >> 8) >= gUnk_03000554->unk04)
        {
            sub_08043638();
            break;
        }
        main->unk0370 += 0x100;
        main->unk0868 = main->unk0370;
        main->unk039D = 1 | main->unk039D;
        main->unk1810 = 0x20;
        if (main->unk0386 != 8)
            sub_080680CC((struct Unk680CC *)&main->unk036C, 8);
        break;
    case 3:
        main = gMainWorkPtr;
        if ((main->unk0370 >> 8) <= gUnk_03000554->unk04)
        {
            sub_08043638();
            break;
        }
        main->unk0370 -= 0x100;
        main->unk0868 = main->unk0370;
        main->unk039D = 2 & main->unk039D;
        main->unk1810 = 0x40;
        if (main->unk0386 != 8)
            sub_080680CC((struct Unk680CC *)&main->unk036C, 8);
        break;
    }
}
