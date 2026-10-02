#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080415fc
// Per-frame step: runs the frame callback (unless unk0854 bit 0), then the phase
// callback for the current phase (unk0804), then the always-on callback.
void MainCallbacksRun(void)
{
    struct MainWork *work;

    if ((gMainWorkPtr->unk0854 & 1) == 0)
        ((void (*)(void))gData_080BB888[0])();

    work = gMainWorkPtr;
    switch (work->unk0804)
    {
    case 0:
        if (work->unk077C != 0)
            work->unk077C(&work->unk0530, work);
        break;
    case 1:
        if (work->unk0780 != 0)
            work->unk0780(&work->unk0530, work);
        MenuDispatchKeyHandlers(&gMainWorkPtr->unk0530);
        break;
    case 2:
        if (work->unk0784 != 0)
            work->unk0784(&work->unk0530, work);
        break;
    case 3:
        work->unk181C = 2;
        break;
    }
    if (gMainWorkPtr->unk0788 != 0)
        gMainWorkPtr->unk0788(&gMainWorkPtr->unk0530);
}

