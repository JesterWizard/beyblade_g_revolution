#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08051bbc
/* match-compiler: old_agbcc */
// Fade-in loop: steps the BLDALPHA weights (EVA down from 16, EVB up from 0)
// once per frame until EVA reaches 0.
void BlendFadeInLoop(void)
{
    struct MainWork **loc = gMainWorkPtrLoc;
    struct MainWork *work;

    work = *loc;
    work->unk17F0 = 0x10;
    work->unk17F2 = 0;
    do
    {
        struct MainWork *cur = *loc;
        cur->unk17F0--;
        cur->unk17F2++;
        REG_BLDCNT = 0x3748;
        REG_BLDALPHA = (cur->unk17F2 << 8) | cur->unk17F0;
        VBlankIntrWait();
        ((void (*)(void))gData_080BB888[0])();
        InputUpdate();
    } while ((*loc)->unk17F0 != 0);
}
