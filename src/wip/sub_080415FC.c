#include "global.h"

void sub_080415FC(void)
{
    struct MainWork *main;

    if ((gMainWorkPtr->unk0854 & 1) == 0)
        _08073C40(*(void **)0x080BB888);

    main = gMainWorkPtr;
    switch (main->unk0804)
    {
    case 0:
        if (main->unk077C != 0)
            _08073C48((void *)&main->unk0530, main, main->unk077C);
        break;
    case 1:
        if (main->unk0780 != 0)
            _08073C48((void *)&main->unk0530, main, main->unk0780);
        sub_080411EC((void *)&main->unk0530);
        break;
    case 2:
        if (main->unk0784 != 0)
            _08073C48((void *)&main->unk0530, main, main->unk0784);
        break;
    case 3:
        main->unk181C = 2;
        break;
    }
    if (main->unk0788 != 0)
        _08073C44((void *)&main->unk0530, main->unk0788);
}
