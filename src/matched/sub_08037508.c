#include "global.h"

// @ 0x08037508
#define gBattleWork37508 (*(*(struct Unk37508Work **)gBattleWorkPtrLoc))

void sub_08037508(void)
{
    sub_08062BF0(5);
    sub_08032908();
    sub_08032604();
    sub_08036190(&gBattleWork37508.unkAA8, 0xEBB0, 0x10000, 0xFFFF2E00);
    sub_080361CC(&gBattleWork37508.unkAA8, &gBattleWork37508.unk08);
    sub_080361CC(&gBattleWork37508.unkAA8, &gBattleWork37508.unk90);
    sub_08068EC0(&gBattleWork37508.unk08);
    sub_08068EC0(&gBattleWork37508.unk90);
    sub_08035238((struct Unk35258 *)&gBattleWork37508.unk478);
    sub_08035238((struct Unk35258 *)&gBattleWork37508.unk790);
    sub_08034568(&gBattleWork37508.unk478);
    sub_08034568(&gBattleWork37508.unk790);
    sub_08031294(&gBattleWork37508.unkB84);
    sub_08031294(&gBattleWork37508.unkB94);
    gBattleWork37508.unk128 = -1;
    gBattleWork37508.unk1FA0 = -1;
    gBattleWork37508.unk1F9C = -1;
    sub_08033574();
    BtlClearState();
    sub_08033A5C(&gBattleWork37508.unk2094);
    sub_0803403C(&gBattleWork37508.unk20A4);
    sub_08033F48(&gBattleWork37508.unk20A4);
    BtlSetTimer118();
    sub_08062C38(5);
    sub_0803114C(&gBattleWork37508.unkAE8.unkB00, 0, 0x1900, 0);
    sub_0803114C(&gBattleWork37508.unkAE8.unkB20, 0, 0xD400, 1);
    gBattleWork37508.unk144 = 0;
    gBattleWork37508.unk148 = 0;
    gMainWorkPtr->unk1824 = 8;
    gBattleWork37508.unk12C = 3;
    REG_BLDCNT = 0x0448;
    REG_BLDALPHA = 0x070B;
    gBattleWork37508.unk130 = 0;
    gBattleWork37508.unk131 = 0;
    gBattleWork37508.unk132 = 0;
    gBattleWork37508.unk1F6C = 0;
    gBattleWork37508.unk1F72 = 0;
    gBattleWork37508.unk1F70 = 0;
    gBattleWork37508.unk1F6B = 0;
    gBattleWork37508.unk1F6E = 0;
    gBattleWork37508.unk1F6F = 0;
}

