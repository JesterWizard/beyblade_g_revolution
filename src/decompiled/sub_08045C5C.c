#include "global.h"
#include "ram_map.h"

// Debounce gBtlInputMask. 0xFC00 clears the hold; otherwise unk1778
// counts down before the current mask is accepted.
u32 sub_08045C5C(u32 a, u32 b)
{
    u32 addr;
    vu16 *mask;
    u32 sentinel;
    u32 sample;
    struct MainWork **workLoc;
    struct MainWork *work;
    s32 *timer;
    s32 held;

    addr = gBtlInputMask;
    sentinel = 0xFC;
    sentinel <<= 8;
    sample = *(vu16 *)addr;
    mask = (vu16 *)addr;
    if (sample == sentinel)
    {
        gMainWorkPtr->unk1778 = 0;
        gMainWorkPtr->unk1774 = 0;
        return 0;
    }
    workLoc = gMainWorkPtrLoc;
    work = *workLoc;
    timer = &work->unk1778;
    held = *timer;
    if (held != 0)
    {
        *timer = held - 1;
        return 0;
    }
    if (work->unk1774 == *mask)
        *timer = b;
    else
        *timer = a;
    (*workLoc)->unk1774 = *mask;
    return *mask;
}
