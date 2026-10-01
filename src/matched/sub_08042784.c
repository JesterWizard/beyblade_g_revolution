#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08042784
// Push {a, cursor x, cursor y} onto the 32-slot history ring at *gUnk_03000538
// while recording is enabled (MainWork.unk182C).
void CursorHistoryPush(u32 a)
{
    struct CursorHistory *ring = gUnk_03000538;
    s32 i = (s8)ring->writeIndex;
    struct MainWork *work = gMainWorkPtr;

    if (work->unk182C != 0)
    {
        ring->dir[i] = a;
        ring->x[i] = work->unk0370;
        ring->y[i] = work->unk0374;
        i++;
        ring->writeIndex = i & 0x1F;
    }
}

