#include "global.h"

void sub_080429CC(void)
{
    struct Unk0538 *ring;
    struct MainWork *main;

    ring = gUnk_03000538;
    main = gMainWorkPtr;
    ring->unk02 = main->unk1810;
    switch (main->unk1828)
    {
    case 0:
        main->unk17B4 = main->unk036C + 0x2000;
        main->unk17B8 = main->unk0370;
        sub_080428F0(main->unk17B4, main->unk17B8, 0, 1);
        break;
    case 1:
        main->unk17B4 = main->unk036C - 0x1000;
        main->unk17B8 = main->unk0370;
        sub_080428F0(main->unk17B4, main->unk17B8, 1, 2);
        break;
    case 2:
        main->unk17B4 = main->unk036C;
        main->unk17B8 = main->unk0370 + 0x2000;
        sub_080428F0(main->unk17B4, main->unk17B8, 2, 4);
        break;
    case 3:
        main->unk17B4 = main->unk036C;
        main->unk17B8 = main->unk0374 - 0x1000;
        sub_080428F0(main->unk17B4, main->unk17B8, 3, 8);
        break;
    }
}
