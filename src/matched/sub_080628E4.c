#include "global.h"

// @ 0x080628E4
// Stores into main work arena slot used by battle setup paths.
void sub_080628E4(u32 value)
{
    gMainWorkPtr->unk1800 = value;
}
