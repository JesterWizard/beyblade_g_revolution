#include "global.h"

// @ 0x08031204

void sub_08031204(void)
{
    void *buffer;
    s16 angle;

    buffer = BtlObjTableAdd(0x10);
    angle = sub_08031124(gUnk_030002A0.records[0].unk0C, gBattleWork->unkBB4, 0x80);
    if (angle != -1 && gBattleWork->unk0AE8.fields.unkAF0 != 0)
        gBattleWork->unk0AE8.fields.unkAF0->unk18 = 0x80 - angle;
    angle = sub_08031124(gUnk_030002A0.records[1].unk0C, gBattleWork->unkBB8, 0x80);
    if (angle != -1 && gBattleWork->unk0AE8.fields.unkAF4 != 0)
        gBattleWork->unk0AE8.fields.unkAF4->unk18 = 0x80 - angle;
    BtlObjTableRemove(buffer);
}

