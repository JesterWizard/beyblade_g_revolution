#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080429cc
void sub_080429CC(void)
{
    struct CursorHistory *ring;
    struct MainWork *main;
    u32 x;
    u32 y;

    ring = gUnk_03000538;
    main = gMainWorkPtr;
    ring->facing = main->unk1810;
    switch (main->unk1828)
    {
    case 0:
        x = main->unk17B4 = main->unk0370 + 0x1000;
        y = main->unk17B8 = main->unk0374;
        sub_080428F0(x, y, 0, 1);
        break;
    case 1:
        x = main->unk17B4 = main->unk0370 - 0x1000;
        y = main->unk17B8 = main->unk0374;
        sub_080428F0(x, y, 1, 2);
        break;
    case 2:
        x = main->unk17B4 = main->unk0370;
        y = main->unk17B8 = main->unk0374 + 0x1000;
        sub_080428F0(x, y, 2, 4);
        break;
    case 3:
        x = main->unk17B4 = main->unk0370;
        y = main->unk17B8 = main->unk0374 - 0x1000;
        sub_080428F0(x, y, 3, 8);
        break;
    }
}

