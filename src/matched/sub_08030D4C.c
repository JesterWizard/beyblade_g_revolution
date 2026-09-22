#include "global.h"

// @ 0x08030d4c

void sub_08030D4C(void)
{
    s32 i;

    i = 0;
    DebugPrint((void *)0x0833C318, (void *)0x0833C334);
    if (gBattleWork->unk0AE8.fields.unkAF0 != 0)
    {
        BtlObjPoolFree(gBattleWork->unk0AE8.fields.unkAF0);
        gBattleWork->unk0AE8.fields.unkAF0 = 0;
    }
    if (gBattleWork->unk0AE8.fields.unkAF4 != 0)
    {
        BtlObjPoolFree(gBattleWork->unk0AE8.fields.unkAF4);
        gBattleWork->unk0AE8.fields.unkAF4 = 0;
    }
    if (gBattleWork->unk0AE8.fields.unkAF8 != 0)
    {
        BtlObjPoolFree(gBattleWork->unk0AE8.fields.unkAF8);
        gBattleWork->unk0AE8.fields.unkAF8 = 0;
    }
    if (gBattleWork->unk0AE8.fields.unkAFC != 0)
    {
        BtlObjPoolFree(gBattleWork->unk0AE8.fields.unkAFC);
        gBattleWork->unk0AE8.fields.unkAFC = 0;
    }
    if (gBattleWork->unkBA4 != 0)
    {
        BtlObjPoolFree(gBattleWork->unkBA4);
        gBattleWork->unkBA4 = 0;
    }
    if (gBattleWork->unkBA8 != 0)
    {
        BtlObjPoolFree(gBattleWork->unkBA8);
        gBattleWork->unkBA8 = 0;
    }
    if (gBattleWork->unk0AE8.fields.unkB48 != 0)
    {
        BtlObjPoolFree(gBattleWork->unk0AE8.fields.unkB48);
        gBattleWork->unk0AE8.fields.unkB48 = 0;
    }
    if (gBattleWork->unk0AE8.fields.unkB4C != 0)
    {
        BtlObjPoolFree(gBattleWork->unk0AE8.fields.unkB4C);
        gBattleWork->unk0AE8.fields.unkB4C = 0;
    }
    if (gBattleWork->unk0AE8.fields.unkB50 != 0)
    {
        BtlObjPoolFree(gBattleWork->unk0AE8.fields.unkB50);
        gBattleWork->unk0AE8.fields.unkB50 = 0;
    }
    if (gBattleWork->unk0AE8.fields.unkB40 != 0)
    {
        BtlObjPoolFree(gBattleWork->unk0AE8.fields.unkB40);
        gBattleWork->unk0AE8.fields.unkB40 = 0;
    }
    if (gBattleWork->unk0AE8.fields.unkB44 != 0)
    {
        BtlObjPoolFree(gBattleWork->unk0AE8.fields.unkB44);
        gBattleWork->unk0AE8.fields.unkB44 = 0;
    }
    for (i = 0; i <= 7; i++)
    {
        if (gBattleWork->unk0AE8.fields.unkB00[i] != 0)
        {
            BtlObjPoolFree(gBattleWork->unk0AE8.fields.unkB00[i]);
            gBattleWork->unk0AE8.fields.unkB00[i] = 0;
        }
    }
    for (i = 0; i <= 7; i++)
    {
        if (gBattleWork->unk0AE8.fields.unkB20[i] != 0)
        {
            BtlObjPoolFree(gBattleWork->unk0AE8.fields.unkB20[i]);
            gBattleWork->unk0AE8.fields.unkB20[i] = 0;
        }
    }
}

