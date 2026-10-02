#include "global.h"

// @ 0x08071808
u16 SoundGetMasterVolume(void)
{
    return *(u16 *)gUnk_030000CC;
}
