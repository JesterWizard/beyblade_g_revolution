#include "global.h"

// @ 0x08040530
void MessageLinesFree(void)
{
    StringArrayFree(gUnk_0300047C->lines, 9);
}

