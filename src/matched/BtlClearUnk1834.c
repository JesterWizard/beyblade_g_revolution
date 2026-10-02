#include "global.h"

// @ 0x080433f4
void BtlClearUnk1834(void)
{
    gMainWorkPtr->unk1834 = 0;
    gMainWorkPtr->unk1808 &= 0xFFFFFDFF;
}

