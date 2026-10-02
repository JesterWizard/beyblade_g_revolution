#include "global.h"

// @ 0x0802e1ec
s8 ExpLevel(void)
{
    return ExpBracket(gMainWorkPtr->expPoints);
}

