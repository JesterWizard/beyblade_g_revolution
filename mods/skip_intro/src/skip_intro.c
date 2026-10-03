#include "global.h"

/* Replaces the call that plays the six splash screens (0x08065C7C). The first
 * of them also verifies the save and loads its header and slot into memory
 * (SaveDataVerify, called from 0x08065D84), which the title menu needs to
 * recognise a save, so that part still has to run. */
void SkipIntro(void)
{
    SaveDataVerify();
}
