#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803c5dc
#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

void LaunchShowBoostMeter(s32 a)
{
    struct BattleWork **btl_loc;
    struct BattleWork *btl;
    s8 flag;
    void *buf_a;
    void *buf_b;
    void **table;

    flag = (*(btl_loc = gBattleWorkPtrLoc))->boostShown;
    if (flag != 0)
        return;
    buf_a = StringAlloc(0x20);
    buf_b = StringAlloc(0x20);
    GlyphTextInit((struct Unk61E8C *)&(*btl_loc)->boostMeterText, (void *)gData_080B72F3, (struct Unk61E8CSrc *)gData_082BF600, 0xF0, 0x78);
    TextFormatInt(a, buf_b, 0x20);
    table = gData_080971D8;
    StringExpandDelim(table[gMainWorkPtr->language], buf_a, buf_b, 0x40, 0x20);
    GlyphTextLayoutWrapped(&(*btl_loc)->boostMeterText, buf_a, 0, 0x4E, flag, 0xFFFF, flag);
    StringFree(buf_a);
    StringFree(buf_b);
    btl = *btl_loc;
    btl->boostValue = a;
    btl->boostShown = 1;
}

