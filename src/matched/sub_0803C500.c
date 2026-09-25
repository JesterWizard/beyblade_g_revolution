#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803c500
#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

void sub_0803C500(s32 a)
{
    struct BattleWork **btl_loc;
    struct BattleWork *btl;
    s32 remain;
    void *buf_a;
    void *buf_b;
    void **table;

    buf_a = BtlObjTableAdd(0x20);
    buf_b = BtlObjTableAdd(0x20);
    btl_loc = gBattleWorkPtrLoc;
    sub_08061E8C((struct Unk61E8C *)&(*btl_loc)->unk1F10, (void *)gData_080B72F3, (struct Unk61E8CSrc *)gData_082BF600, 0xF0, 0x78);
    remain = 0x64 - a;
    TextFormatInt(remain, buf_b, 0x20);
    table = gData_080971EC;
    sub_08073AEC(table[gMainWorkPtr->unk1818], buf_a, buf_b, 0x40, 0x20);
    sub_08061EF8(&(*btl_loc)->unk1F10, buf_a, 0, 0x3E, 0, 0xFFFF, 0);
    BtlObjTableRemove(buf_a);
    BtlObjTableRemove(buf_b);
    DebugPrint((void *)gData_0833C79C, remain);
    btl = *btl_loc;
    btl->unk1F74 = 0x64 - a;
}

