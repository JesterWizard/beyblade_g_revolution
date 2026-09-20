#include "global.h"

void sub_08051BBC(void)
{
    register struct MainWork **main_loc asm("r5");
    register vu16 *bldy asm("r6");

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
        sub_080674B4();
        _08073C40(*(void **)0x080BB888);
        sub_0806A6F8();
    }
}
