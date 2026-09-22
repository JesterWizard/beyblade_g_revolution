#include "global.h"

void sub_08032908(void)
{
    s32 i;
    struct Unk7069C *entry;

    sub_08062044(&gBattleWork->unk1F38);
    sub_08062044(&gBattleWork->unk1F10);
    if (gBattleWork->unk00 != 0)
    {
        BtlObjFree(gBattleWork->unk00);
        gBattleWork->unk00 = 0;
    }
    if (gBattleWork->unk04 != 0)
    {
        BtlObjFree(gBattleWork->unk04);
        gBattleWork->unk04 = 0;
    }
    sub_08030D4C();
    if (gBattleWork->unk324 != 0)
    {
        sub_0806FE84(gBattleWork->unk324);
        gBattleWork->unk324 = 0;
    }
    if (gBattleWork->unk1F0C != 0)
    {
        sub_0806FE84(gBattleWork->unk1F0C);
        gBattleWork->unk1F0C = 0;
    }
    for (i = 0; i <= 3; i++)
    {
        if (gBattleWork->unk0AC8[i] != 0)
        {
            sub_0806FE84(gBattleWork->unk0AC8[i]);
            gBattleWork->unk0AC8[i] = 0;
        }
    }
    for (i = 0; i <= 3; i++)
    {
        if (gBattleWork->unk0AD8[i] != 0)
        {
            sub_0806FE84(gBattleWork->unk0AD8[i]);
            gBattleWork->unk0AD8[i] = 0;
        }
    }
    for (i = 0; i <= 0x2F; i++)
        sub_08062238(&gBattleWork->unk0BCC[i]);
    for (i = 0; i <= 0x17; i++)
    {
        if (gMainWorkPtr->unk07A4[i] != 0)
        {
            sub_0806FE84(gMainWorkPtr->unk07A4[i]);
            gMainWorkPtr->unk07A4[i] = 0;
        }
    }
    entry = &gBattleWork->unk023C[0];
    for (i = 3; i >= 0; i--)
    {
        BtlReleaseEntry(entry);
        entry++;
    }
    sub_08062044(&gBattleWork->unk2FC);
    sub_08062044(&gBattleWork->unk013C.fields.unk14C);
    sub_08062044(&gBattleWork->unk013C.fields.unk174);
    _08073C40(*(void **)0x080BB888);
}
