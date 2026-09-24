/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

s32 sub_0802D2C0(void)
{
    s8 **bases;
    s8 *table;
    struct MainWork *mw;
    s16 left;
    s16 right;

    bases = gData_0807741C;
    mw = gMainWorkPtr;
    table = bases[mw->unk15C8];
    table += (s32)mw->unk15CA * 16;
    left = mw->unk15D0;
    right = mw->unk15D2;
    if (left > right)
        _0802D058((u16)table[1]);
    else if (left < right)
        _0802D058(0);
}
