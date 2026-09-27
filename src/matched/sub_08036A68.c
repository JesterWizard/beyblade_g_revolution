#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08036a68
void sub_08036A68(struct Unk346C0 *a, s32 unused, u32 slot)
{
    void *buf0;
    void *buf1;
    void *buf2;

    buf0 = BtlObjTableAdd(0x80);
    buf1 = BtlObjTableAdd(0x80);
    buf2 = BtlObjTableAdd(0x80);
    sub_08037318(a, (u8)slot);
    sub_08061E8C((struct Unk61E8C *)&gBattleWork->unk013C.fields.unk14C, gData_080B72F3, (struct Unk61E8CSrc *)gData_082BF600, 0xB0, 0x150);
    sub_08073AEC(gData_080972A0[gMainWorkPtr->unk1818], buf0,
                 sub_08042B00(gData_030002A0[slot].unk00), 0x23, 0x80);
    sub_08073AEC(buf0, buf1, (void *)sub_0803DD88(gData_030002A0[slot].unk04), 0x40, 0x80);
    sub_08061EF8(&gBattleWork->unk013C.fields.unk14C, buf1, 0, 0x50, 0, 0xC8, 0);
    BtlObjTableRemove(buf0);
    BtlObjTableRemove(buf1);
    BtlObjTableRemove(buf2);
    sub_08037430();
}

