#include "global.h"

void sub_08057274(void)
{
    register struct MainWork **main_loc asm("r4");
    struct MainWork *main;

    main_loc = gMainWorkPtrLoc;
    main = *main_loc;
    switch (main->unk1810)
    {
    case 0x40:
        if (main->unk0386 != 5)
            sub_080680CC((struct Unk680CC *)&main->unk036C, 5);
        main->unk039D = 2 & main->unk039D;
        break;
    case 0x20:
        if (main->unk0386 != 5)
            sub_080680CC((struct Unk680CC *)&main->unk036C, 5);
        main->unk039D = 1 | main->unk039D;
        break;
    case 0x80:
        if (main->unk0386 != 6)
            sub_080680CC((struct Unk680CC *)&main->unk036C, 6);
        main->unk039D = 0;
        break;
    case 0x100:
        if (main->unk0386 != 7)
            sub_080680CC((struct Unk680CC *)&main->unk036C, 7);
        main->unk039D = 0;
        break;
    }
}
