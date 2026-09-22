#include "global.h"

void sub_08070604(
    struct Unk7069C *dst, void *a, void *b, s32 c,
    s32 d, s32 e, s32 f);
void sub_0807179C(struct Unk7069C *a);
s32 sub_08033158(s32 a, s32 b);
void sub_08070C98(struct Unk70C98 *a, s32 b, s32 c);
void sub_0803484C(struct Unk3484C *a);
void sub_080312EC(struct Unk312EC *a);
void sub_08033188(void);

struct Unk33188Entry
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
    u16 unk10;
    u16 unk12;
    u32 unk14;
};

struct Unk33188State
{
    u32 unk00;
    u8 filler_04[0x64];
};

void sub_08033188(void)
{
    struct Unk33188State state;
    struct Unk33188Entry entries[2];
    struct Unk33188Entry *asset;
    u16 input_mask;
    u16 unknown_keys;
    u16 held_snapshot;
    u16 current_keys;
    u16 keys_new;
    s32 target;
    s32 moving;
    s32 i;
    s32 delta;
    s32 step;

    target = 0;
    moving = 0;
    i = 0;
    input_mask = *(u16 *)gBtlInputMask;
    unknown_keys = *(u16 *)0x03004064;
    held_snapshot = *(u16 *)gBtlKeysHeld;
    current_keys = held_snapshot;
    keys_new = *(u16 *)gBtlKeysNew;
    sub_08070604(
        (struct Unk7069C *)&state, (void *)0x082BF600,
        (void *)0x080B72F3, -0xF0, 0x50, 0xF0, 2);
    sub_08070AD4(
        (struct Unk7069C *)&state,
        ((void **)0x080780EC)[gMainWorkPtr->unk1818], 0);
    sub_0807179C((struct Unk7069C *)&state);
    sub_080312EC((struct Unk312EC *)gBattleWork->unkB84);
    sub_080312EC((struct Unk312EC *)gBattleWork->unkB94);
    sub_0803484C((struct Unk3484C *)((u8 *)gBattleWork + 0x478));
    sub_0803484C((struct Unk3484C *)((u8 *)gBattleWork + 0x790));

    for (; i < 2; i++)
    {
        asset = (struct Unk33188Entry *)
            sub_0806A954(((u8 *)0x08078100)[i]);
        entries[i].unk00 = asset->unk00;
        entries[i].unk04 = asset->unk04;
        entries[i].unk08 = asset->unk08;
        entries[i].unk0C = asset->unk0C;
        entries[i].unk10 = asset->unk10;
        entries[i].unk12 = asset->unk12;
        entries[i].unk14 = asset->unk14;
    }

    sub_0806A6F8();
    for (;;)
    {
        VBlankIntrWait();
        sub_0806A6F8();
        delta = target - (s32)state.unk00;
        if (delta != 0)
        {
            step = sub_08033158(delta, 0x10);
            sub_0807179C((struct Unk7069C *)&state);
            sub_08070C98(
                (struct Unk70C98 *)&state, (s16)step, 0);
            sub_0807179C((struct Unk7069C *)&state);
        }
        _08073C40(*(void **)0x080BB888);
        if ((s32)state.unk00 == target)
        {
            if (moving != 0)
                break;
            current_keys = *(u16 *)gBtlKeysHeld;
            if ((current_keys & 1) != 0 || (current_keys & 8) != 0)
            {
                moving = 1;
                target = -0xC800;
            }
        }
    }

    BtlReleaseEntry((struct Unk7069C *)&state);
    VBlankIntrWait();
    for (i = 0; i < 2; i++)
    {
        asset = (struct Unk33188Entry *)
            sub_0806A954(((u8 *)0x08078100)[i]);
        asset->unk00 = entries[i].unk00;
        asset->unk04 = entries[i].unk04;
        asset->unk08 = entries[i].unk08;
        asset->unk0C = entries[i].unk0C;
        asset->unk10 = entries[i].unk10;
        asset->unk12 = entries[i].unk12;
        asset->unk14 = entries[i].unk14;
    }
    *(u16 *)gBtlInputMask = input_mask;
    *(u16 *)0x03004064 = unknown_keys;
    *(u16 *)gBtlKeysHeld = held_snapshot;
    *(u16 *)gBtlKeysNew = keys_new;
}
