#include "global.h"

void sub_08051BBC(void)
{
    struct MainWork **main_loc;
    vu16 *bldy;

    main_loc = gMainWorkPtrLoc;
    (*main_loc)->unk17F0 = 0x10;
    (*main_loc)->unk17F2 = 0;
    bldy = &REG_BLDY;
    while ((*main_loc)->unk17F0 != 0)
    {
        (*main_loc)->unk17F0--;
        (*main_loc)->unk17F2++;
        REG_BLDALPHA = 0x3748;
        *bldy = ((*main_loc)->unk17F2 << 8) | (*main_loc)->unk17F0;
        VBlankIntrWait();
        _08073C40(*(void **)0x080BB888);
        sub_0806A6F8();
    }
}
