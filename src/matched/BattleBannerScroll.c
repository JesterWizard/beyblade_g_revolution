#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08033188
union Unk33188Text
{
    struct Unk70604 hdr;
    u8 raw[0x68];
};

// Banner scroll: save input state and the two gData_08078100 records, slide
// the language banner text in until A or START is pressed (then slide it out
// to -0xC800), and restore everything.
void BattleBannerScroll(void)
{
    union Unk33188Text text;
    struct Unk6A954 saved[2];
    u32 mask;
    u32 keys64;
    u32 held;
    u32 keysNew;
    s32 done;
    s32 target;
    s32 i;
    s32 delta;
    struct Unk6A954 *slot;

    done = 0;
    target = 0;
    i = 0;
    mask = *(u16 *)gBtlInputMask;
    keys64 = *(u16 *)gUnk_03004064;
    held = gBtlKeysHeldU16;
    keysNew = *(u16 *)gBtlKeysNew;
    Unk70604Init(&text.hdr, (struct Unk70604Src *)0x082BF600, 0x080B72F3, -0xF0, 0x50, 0xF0, 2);
    TextGroupSetString((struct TextGroup *)&text, gData_080780EC[gMainWorkPtr->language], 0);
    sub_0807179C((struct Unk7179C *)&text);
    PaletteHighlightRestore((struct Unk312EC *)gBattleWork->rowHighlightA);
    PaletteHighlightRestore((struct Unk312EC *)gBattleWork->rowHighlightB);
    sub_0803484C((struct Unk3484C *)gBattleWork->battlerStates);
    sub_0803484C((struct Unk3484C *)&gBattleWork->battlerStates[0x318]);
    for (; i <= 1; i++)
    {
        slot = sub_0806A954(gData_08078100[i]);
        saved[i].unk00 = slot->unk00;
        saved[i].unk04 = slot->unk04;
        saved[i].unk08 = slot->unk08;
        saved[i].unk0C = slot->unk0C;
        saved[i].unk10 = slot->unk10;
        saved[i].unk12 = slot->unk12;
        saved[i].unk14 = slot->unk14;
    }
    InputUpdate();
    while (!done || text.hdr.unk00 != target)
    {
        VBlankIntrWait();
        InputUpdate();
        delta = target - text.hdr.unk00;
        if (delta != 0)
        {
            delta = sub_08033158(delta, 0x10);
            sub_0807179C((struct Unk7179C *)&text);
            TextGroupMoveBy((struct Unk70C98 *)&text, (s16)delta, 0);
            sub_0807179C((struct Unk7179C *)&text);
        }
        ((void (*)(void))gData_080BB888[0])();
        if (!done && text.hdr.unk00 == target)
        {
            if (gData_03004060 & 1)
                done = 1;
            if (gData_03004060 & 8)
                done = 1;
            if (done)
                target = -0xC800;
        }
    }
    BtlReleaseEntry((struct TextGroup *)&text);
    VBlankIntrWait();
    for (i = 0; i <= 1; i++)
    {
        slot = sub_0806A954(gData_08078100[i]);
        slot->unk00 = saved[i].unk00;
        slot->unk04 = saved[i].unk04;
        slot->unk08 = saved[i].unk08;
        slot->unk0C = saved[i].unk0C;
        slot->unk10 = saved[i].unk10;
        slot->unk12 = saved[i].unk12;
        slot->unk14 = saved[i].unk14;
    }
    gData_03003F60 = mask;
    gData_03004064 = keys64;
    gData_03004060 = held;
    gData_0300406C = keysNew;
}

