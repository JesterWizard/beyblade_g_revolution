#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08042784
// Push {a, cursor x, cursor y} onto the 32-slot history ring at *gUnk_03000538
// while recording is enabled (MainWork.unk182C).
void sub_08042784(u32 a)
{
    struct Unk0538 *ring = gUnk_03000538;
    s32 i = (s8)ring->unk01;
    struct MainWork *work = gMainWorkPtr;

    if (work->unk182C != 0)
    {
        ring->unk04[i] = a;
        ring->unk44[i] = work->unk0370;
        ring->unkC4[i] = work->unk0374;
        i++;
        ring->unk01 = i & 0x1F;
    }
}

