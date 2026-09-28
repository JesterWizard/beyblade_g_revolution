#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08047624
/* match-compiler: old_agbcc */
// Count the pixel steps from the cursor (MainWork x/y >> 8) to the next
// 8-pixel boundary in direction `mode` (0 = -x, 1 = +x, 2 = -y, 3 = +y).
s32 CursorStepsToTile(u32 mode)
{
    u8 dir = mode;
    s32 x = gMainWorkPtr->unk0370 >> 8;
    s32 y = gMainWorkPtr->unk0374 >> 8;
    s32 steps = 0;
    s32 pos;

    switch (dir)
    {
    case 0:
        pos = x - 1;
        while ((pos & 7) != 0)
        {
            pos--;
            steps++;
        }
        return steps;
    case 1:
        pos = x + 1;
        while ((pos & 7) != 0)
        {
            pos++;
            steps++;
        }
        return steps;
    case 2:
        pos = y - 1;
        while ((pos & 7) != 0)
        {
            pos--;
            steps++;
        }
        return steps;
    case 3:
        pos = y + 1;
        while ((pos & 7) != 0)
        {
            pos++;
            steps++;
        }
        return steps;

    }
    // BUG: no return for other modes (r0 still holds y).
#ifdef BUGFIX
    return 0;
#endif
}

