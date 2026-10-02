#include "global.h"

// @ 0x08067634
u16 EepromWriteBlock(u32 a, u32 b)
{
    return EepromWriteBlockEx(a, (const u16 *)b, 1);
}

