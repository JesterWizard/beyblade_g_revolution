#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803c5dc
#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

void sub_0803C5DC(s32 a)
{
    struct BattleWork **btl_loc;
    struct BattleWork *btl;
    s8 flag;
    void *buf_a;
    void *buf_b;
    void **table;

    flag = (*(btl_loc = gBattleWorkPtrLoc))->unk1F72;
    if (flag != 0)
        return;
    buf_a = BtlObjTableAdd(0x20);
    buf_b = BtlObjTableAdd(0x20);
    sub_08061E8C((struct Unk61E8C *)&(*btl_loc)->unk1F38, (void *)gData_080B72F3, (struct Unk61E8CSrc *)gData_082BF600, 0xF0, 0x78);
    TextFormatInt(a, buf_b, 0x20);
    table = gData_080971D8;
    sub_08073AEC(table[gMainWorkPtr->unk1818], buf_a, buf_b, 0x40, 0x20);
    sub_08061EF8(&(*btl_loc)->unk1F38, buf_a, 0, 0x4E, flag, 0xFFFF, flag);
    BtlObjTableRemove(buf_a);
    BtlObjTableRemove(buf_b);
    btl = *btl_loc;
    btl->unk1F76 = a;
    btl->unk1F72 = 1;
}

