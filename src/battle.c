#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_0802BA4C */
// @ 0x0802ba4c
void BtlFreeUnk1694Obj(void)
{
    void *p;

    p = *(void **)gUnk_03000268;
    if (p != 0)
    {
        HeapFree(p);
        *(void **)gUnk_03000268 = 0;
    }
    gMainWorkPtr->unk1694 = 0;
}

/* fn: sub_0802C5DC */
// @ 0x0802c5dc
s32 BtlUnk1694FindAndMark(s8 a)
{
    s32 i;
    s8 val;

    val = (s8)a;
    if (gMainWorkPtr->unk1694 != NULL)
    {
        for (i = 0; i <= 0x7F; i++)
        {
            if ((s8)gMainWorkPtr->unk1694[i].group == val)
            {
                gMainWorkPtr->unk1694[i].slot = 1;
                return 1;
            }
        }
    }
    return 0;
}

/* fn: sub_0803019C */
// @ 0x0803019c

void BattleHudSlideStep(void);
void sub_0803D4C4(void);
void BeybladeEffectsPlace(void *a);
void FixedEaseStep(void *a);

struct Unk3019CWork
{
    u8 filler_00[0x328];
    u8 unk328[0x20];
    u8 filler_348[0x34];
    u8 unk37C[0x20];
    u8 filler_39C[0xDC];
    u8 unk478[0x2F8];
    u8 filler_770[0x19];
    u8 unk789;
    u8 filler_78A[6];
    u8 unk790[0x2F8];
    u8 filler_A88[0x19];
    u8 unkAA1;
    u8 filler_AA2[6];
    u8 unkAA8[0x18];
    u8 filler_AC0[8];
    void *unk0AC8[4];
    void *unk0AD8[4];
};

void BattleStepBeyblades(void)
{
    BattleHudSlideStep();
    sub_0803D4C4();
    BeybladeSpinStep(
        (struct Unk346C0 *)((struct Unk3019CWork *)gBattleWork)->unk478);
    BeybladeSpinStep(
        (struct Unk346C0 *)((struct Unk3019CWork *)gBattleWork)->unk790);
    BtlProjectToScreen(
        (struct Unk35D68Source *)((struct Unk3019CWork *)gBattleWork)->unk328,
        (struct Unk35D68State *)((struct Unk3019CWork *)gBattleWork)->unkAA8);
    BtlProjectToScreen(
        (struct Unk35D68Source *)((struct Unk3019CWork *)gBattleWork)->unk37C,
        (struct Unk35D68State *)((struct Unk3019CWork *)gBattleWork)->unkAA8);
    sub_080302A8(
        (struct Unk302A8 *)((struct Unk3019CWork *)gBattleWork)->unk328,
        (struct Unk302A8Src *)((struct Unk3019CWork *)gBattleWork)->unkAA8,
        (struct Unk302A8 *)((struct Unk3019CWork *)gBattleWork)->unk0AD8[0]);
    sub_080302A8(
        (struct Unk302A8 *)((struct Unk3019CWork *)gBattleWork)->unk37C,
        (struct Unk302A8Src *)((struct Unk3019CWork *)gBattleWork)->unkAA8,
        (struct Unk302A8 *)((struct Unk3019CWork *)gBattleWork)->unk0AD8[1]);
    BeybladeUpdate(
        (struct Unk346C0 *)((struct Unk3019CWork *)gBattleWork)->unk478,
        (u32)((struct Unk3019CWork *)gBattleWork)->unk790);
    BeybladeUpdate(
        (struct Unk346C0 *)((struct Unk3019CWork *)gBattleWork)->unk790,
        (u32)((struct Unk3019CWork *)gBattleWork)->unk478);
    BeybladeEffectsUpdate(
        (struct Unk35258 *)((struct Unk3019CWork *)gBattleWork)->unk478);
    BeybladeEffectsUpdate(
        (struct Unk35258 *)((struct Unk3019CWork *)gBattleWork)->unk790);
    BeybladeEffectsPlace(
        ((struct Unk3019CWork *)gBattleWork)->unk478);
    BeybladeEffectsPlace(
        ((struct Unk3019CWork *)gBattleWork)->unk790);
    ((struct Unk3019CWork *)gBattleWork)->unk789 = (u8)BeybladeCollisionResponse(
        (struct Unk346C0Inner *)((struct Unk3019CWork *)gBattleWork)->unk328,
        (struct Unk346C0Inner *)((struct Unk3019CWork *)gBattleWork)->unk37C);
    ((struct Unk3019CWork *)gBattleWork)->unkAA1 =
        ((struct Unk3019CWork *)gBattleWork)->unk789;
    MotionMidpoint(
        (struct Unk36264 *)((struct Unk3019CWork *)gBattleWork)->unkAA8,
        (struct Unk360BC *)((struct Unk3019CWork *)gBattleWork)->unk328,
        (struct Unk360BC *)((struct Unk3019CWork *)gBattleWork)->unk37C, 0x66);
    FixedEaseStep(
        ((struct Unk3019CWork *)gBattleWork)->unkAA8);
}

/* fn: sub_08030D4C */
// @ 0x08030d4c

void CleanBattleOverlays(void)
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

/* fn: sub_08030F38 */
// @ 0x08030f38
// While the AF0 object's unk0C is at most 0x7FF, adds 0x100 to unk0C of the
// AF0..AFC/B40/B44/BA4/BA8 objects and to unkBB0, and sets the B00/B20 banks
// to unkBB0. Then moves the B48/B4C pair's unk0C towards unkBAC by 0x100.
void BattleHudSlideStep(void)
{
    struct BattleWork *work;
    struct Sprite *e;
    s32 i;

    work = gData_03000290;
    e = work->unk0AE8.fields.unkAF0;
    if (e != NULL && (s32)e->unk0C <= 0x7FF)
    {
        e->unk0C += 0x100;
        if (work->unk0AE8.fields.unkAF4 != NULL)
            work->unk0AE8.fields.unkAF4->unk0C += 0x100;
        if (gData_03000290->unk0AE8.fields.unkAF8 != NULL)
            gData_03000290->unk0AE8.fields.unkAF8->unk0C += 0x100;
        if (gData_03000290->unk0AE8.fields.unkAFC != NULL)
            gData_03000290->unk0AE8.fields.unkAFC->unk0C += 0x100;
        if (gData_03000290->unk0AE8.fields.unkB40 != NULL)
            gData_03000290->unk0AE8.fields.unkB40->unk0C += 0x100;
        if (gData_03000290->unk0AE8.fields.unkB44 != NULL)
            gData_03000290->unk0AE8.fields.unkB44->unk0C += 0x100;
        if (gData_03000290->unkBA4 != NULL)
            gData_03000290->unkBA4->unk0C += 0x100;
        if (gData_03000290->unkBA8 != NULL)
            gData_03000290->unkBA8->unk0C += 0x100;
        gData_03000290->hudY += 0x100;
        for (i = 0; i < 8; i++)
        {
            if (gData_03000290->unk0AE8.fields.unkB00[i] != NULL)
                gData_03000290->unk0AE8.fields.unkB00[i]->unk0C = gData_03000290->hudY;
            if (gData_03000290->unk0AE8.fields.unkB20[i] != NULL)
                gData_03000290->unk0AE8.fields.unkB20[i]->unk0C = gData_03000290->hudY;
        }
    }

    {
        struct BattleWork *battle;
        struct Sprite *lead;
        s32 delta;
        s32 step;

        battle = gData_03000290;
        lead = battle->unk0AE8.fields.unkB48;
        if (lead != NULL && lead->unk0C != battle->hudLeadTargetY)
        {
            delta = battle->hudLeadTargetY - lead->unk0C;
            step = 0x100;
            if (delta > step)
                delta = step;
            if (delta < step) /* BUG: meant -step */
                delta = -step;
            lead->unk0C += delta;
            if (battle->unk0AE8.fields.unkB4C != NULL)
                battle->unk0AE8.fields.unkB4C->unk0C += delta;
        }
    }
}

/* fn: sub_0803114C */
// @ 0x0803114c
// Lays out a row of entries: sub_0803139C fills up to 8 of them for `key`, then
// each non-NULL one gets x = base stepping by -0x900 (mode 0 starts from the far
// end so the row ends at base) and y = BattleWork.unkBB0.
void BattleHudDigitsLayout(struct Sprite **entries, u32 key, u32 base, u32 modeArg)
{
    u8 mode = modeArg;
    s32 count = 0;
    s32 i = 0;
    s32 value;

    count = DigitSpritesSetValue(entries, key, 8, (void *)0x0810B208, count);
    if (mode == 0)
    {
        for (value = base + (count - 1) * 0x900; i < count; i++)
        {
            if (entries[i] != NULL)
            {
                entries[i]->unk08 = value;
                entries[i]->unk0C = gBattleWork->hudY;
            }
            value -= 0x900;
        }
    }
    else
    {
        for (value = base; i < count; i++)
        {
            if (entries[i] != NULL)
            {
                entries[i]->unk08 = value;
                entries[i]->unk0C = gBattleWork->hudY;
            }
            value -= 0x900;
        }
    }
}

/* fn: sub_080314FC */
// @ 0x080314FC
// Sets battle-work field @ +0x118 to 0x3C (battle init path).
void BtlSetTimer118(void)
{
    gBattleWork->unk118 = 0x3C;
}

/* fn: sub_08032908 */
// @ 0x08032908
// Battle teardown: free work buffers, release pooled objects and entries.
void BattleTeardown(void)
{
    s32 i;

    GlyphTextFree(&gBattleWork->boostMeterText);
    GlyphTextFree(&gBattleWork->powerMeterText);
    if (gBattleWork->unk00 != 0)
    {
        HeapFree(gBattleWork->unk00);
        gBattleWork->unk00 = 0;
    }
    if (gBattleWork->unk04 != 0)
    {
        HeapFree(gBattleWork->unk04);
        gBattleWork->unk04 = 0;
    }
    CleanBattleOverlays();
    if (gBattleWork->unk324 != 0)
    {
        BtlObjPoolFree(gBattleWork->unk324);
        gBattleWork->unk324 = 0;
    }
    if (gBattleWork->unk1F0C != 0)
    {
        BtlObjPoolFree(gBattleWork->unk1F0C);
        gBattleWork->unk1F0C = 0;
    }
    for (i = 0; i <= 3; i++)
    {
        if (gBattleWork->unk0AC8[i] != 0)
        {
            BtlObjPoolFree(gBattleWork->unk0AC8[i]);
            gBattleWork->unk0AC8[i] = 0;
        }
    }
    for (i = 0; i <= 3; i++)
    {
        if (gBattleWork->unk0AD8[i] != 0)
        {
            BtlObjPoolFree(gBattleWork->unk0AD8[i]);
            gBattleWork->unk0AD8[i] = 0;
        }
    }
    for (i = 0; i <= 0x2F; i++)
        sub_08062238(&gBattleWork->unk0BCC[i]);
    for (i = 0; i <= 0x17; i++)
    {
        if (gMainWorkPtr->unk07A4[i] != 0)
        {
            BtlObjPoolFree(gMainWorkPtr->unk07A4[i]);
            gMainWorkPtr->unk07A4[i] = 0;
        }
    }
    for (i = 0; i <= 3; i++)
        BtlReleaseEntry(&gBattleWork->unk023C[i]);
    GlyphTextFree(&gBattleWork->unk2FC);
    GlyphTextFree(&gBattleWork->unk013C.fields.unk14C);
    GlyphTextFree(&gBattleWork->unk013C.fields.unk174);
    _08073C40((void *)gData_080BB888[0]);
}

/* fn: sub_08032DC4 */
// @ 0x08032dc4
void sub_080338E4(void *dst, void *src);
void sub_08032D5C(struct Unk346C0 *a, struct Unk346C0 *b);
void BattleBannerScroll(void);
void BattleScorePopupTick(void);
void BtlPaletteFadeStep(void *a, u32 b);
void BeybladeEffectsPlace(void *a);
void BattleHudSlideStep(void);
void sub_08033DD4(void);
void BtlKeyComboStep(struct Unk33958 *a, u16 b);
void BtlEffectStart(s32 a, s32 b, s32 c, s32 d);
void sub_08032DB8(struct Unk346C0 *a);
u8 sub_08033A94(u8 *a);
void FixedEaseStep(void *a);

/* match-compiler: old_agbcc */
// Battle main loop: run `frame + 1` frames of input, physics, drawing and the
// three combo checks; a combo hit re-arms the countdown to 60 frames.
void BtlFrameUpdate(
    s32 frame_arg, struct Unk346C0 *state_a_arg,
    struct Unk346C0 *state_b_arg)
{
    s32 frame;
    struct Unk346C0 *state_a;
    struct Unk346C0 *state_b;
    struct Unk33958 temp_a;
    struct Unk33958 temp_b;
    struct Unk33958 temp_c;

    state_a = state_a_arg;
    state_b = state_b_arg;
    frame = frame_arg;
    gBattleWork->randPhase = RandRange(0x100) << 8;
    sub_080338E4(&temp_a, (void *)0x0807811C);
    sub_080338E4(&temp_b, (void *)0x08078130);
    sub_080338E4(&temp_c, (void *)0x08078144);
    sub_08032D5C(state_a, state_b);
    if (frame >= 0)
    {
        do
        {
            VBlankIntrWait();
            TimerAdvance();
            InputUpdate();
            if ((gData_03004060 & 8) != 0)
                BattleBannerScroll();
            sub_080361CC(
                (struct Unk36190 *)&gBattleWork->unkAA8,
                (struct Unk361CCDst *)gBattleWork->filler_0008);
            sub_080361CC(
                (struct Unk36190 *)&gBattleWork->unkAA8,
                (struct Unk361CCDst *)gBattleWork->unk090);
            AffineBgUpdate(gBattleWork->filler_0008);
            AffineBgUpdate(gBattleWork->unk090);
            BtlProjectToScreen(
                (struct Unk35D68Source *)&gBattleWork->unk328,
                (struct Unk35D68State *)&gBattleWork->unkAA8);
            BtlProjectToScreen(
                (struct Unk35D68Source *)&gBattleWork->unk37C,
                (struct Unk35D68State *)&gBattleWork->unkAA8);
            sub_080302A8(
                (struct Unk302A8 *)&gBattleWork->unk328,
                (struct Unk302A8Src *)&gBattleWork->unkAA8,
                (struct Unk302A8 *)gBattleWork->unk0AD8[0]);
            sub_080302A8(
                (struct Unk302A8 *)&gBattleWork->unk37C,
                (struct Unk302A8Src *)&gBattleWork->unkAA8,
                (struct Unk302A8 *)gBattleWork->unk0AD8[1]);
            BeybladeEffectsUpdate((struct Unk35258 *)state_a);
            BeybladeEffectsUpdate((struct Unk35258 *)state_b);
            BeybladeEffectsPlace(state_a);
            BeybladeEffectsPlace(state_b);
            BattleHudSlideStep();
            sub_08030F00(
                (struct Unk30F00 *)gBattleWork->unk0AE8.fields.unkB50,
                (struct Unk30F00Src *)gBattleWork->battlerStates);
            BtlSceneObjUpdate();
            BattleScorePopupTick();
            BtlPaletteFadeStep(
                &gBattleWork->unk1F7C,
                gBattleWork->fadeActive);
            BeybladeSpinStep(state_a);
            BeybladeSpinStep(state_b);
            TextRowPulsePalette((struct Unk312EC *)gBattleWork->rowHighlightA);
            TextRowPulsePalette((struct Unk312EC *)gBattleWork->rowHighlightB);
            _08073C40((void *)gData_080BB888[0]);
            MotionMidpoint(
                (struct Unk36264 *)&gBattleWork->unkAA8,
                &gBattleWork->unk328,
                &gBattleWork->unk37C, 0x66);
            FixedEaseStep(&gBattleWork->unkAA8);
            BtlCaptureInput(state_a);
            if (state_a->unk30C == 1)
                sub_08033DD4();
            if (sub_08033A94((u8 *)&gBattleWork->unk2094) == 0)
            {
                BtlKeyComboStep(&temp_a, state_a->unk300);
                BtlKeyComboStep(&temp_b, state_a->unk300);
                BtlKeyComboStep(&temp_c, state_a->unk300);
                if ((u8)sub_08033958(&temp_a) != 0)
                {
                    sub_08033978(
                        (struct Unk33A5C *)&gBattleWork->unk2094, state_a, state_b, 0);
                    frame = 60;
                    BtlEffectStart(0x78, 0x50, 0, 3);
                }
                if ((u8)sub_08033958(&temp_b) != 0)
                {
                    sub_08033978(
                        (struct Unk33A5C *)&gBattleWork->unk2094, state_a, state_b, 1);
                    frame = 60;
                    BtlEffectStart(0x78, 0x50, 0, 3);
                }
                if ((u8)sub_08033958(&temp_c) != 0)
                {
                    sub_08033978(
                        (struct Unk33A5C *)&gBattleWork->unk2094, state_a, state_b, 2);
                    frame = 60;
                    BtlEffectStart(0x78, 0x50, 0, 3);
                }
            }
            frame--;
        } while (frame >= 0);
    }
    sub_08032DB8(state_a);
}

/* fn: sub_08033188 */
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

/* fn: sub_080333E4 */
// @ 0x080333e4
/* match-compiler: old_agbcc */

void sub_08068584(void *a, s32 b, s32 c);

void BtlEffectStart(void *arg, s32 x, s32 y, u8 mode)
{
    u16 id;

    if (mode > 4)
        return;
    if (gBattleWork->effectActive == 1 && (s8)gBattleWork->effectMode != mode)
        BtlEffectStop();
    if (gBattleWork->effectActive == 0)
    {
        id = PaletteSlotAcquire(gData_08078108[mode]);
        AnimObjCreate((struct AnimObj *)&gBattleWork->effectObj, gData_08078108[mode], 0, (s32)arg, x, y, -1);
        sub_08068584(&gBattleWork->effectObj, 0x20, 0x20);
        gBattleWork->effectFramesLeft = AnimDurationForKey(&gBattleWork->effectObj, 0);
        gBattleWork->unk1FE6 = (gBattleWork->unk1FE6 & 1) | (id << 1);
        gBattleWork->effectActive = 1;
    }
    else if ((s8)gBattleWork->effectMode == mode)
    {
        gBattleWork->effectFramesLeft += AnimDurationForKey(&gBattleWork->effectObj, 0);
    }
}

/* fn: sub_08033530 */
// @ 0x08033530
void BtlSceneObjUpdate(void)
{
    if (gBattleWork->effectActive == 1)
    {
        if (gBattleWork->effectFramesLeft == 0)
        {
            BtlEffectStop();
        }
        else
        {
            sub_080686D8(&gBattleWork->effectObj);
            SceneObjUpdate(&gBattleWork->effectObj);
        }
    }
}

/* fn: sub_08033574 */
// @ 0x08033574
/* match-compiler: old_agbcc */
void BtlEffectStop(void)
{
    struct BattleWork *w;
    u8 shifted;
    u8 *fieldPtr;

    w = gBattleWork;
    if (w->effectActive == 1)
    {
        fieldPtr = &w->unk1FE6;
        shifted = *fieldPtr >> 1;
        SceneObjFreeResources((struct Actor *)(fieldPtr - 0x3A));
        PaletteSlotRefRelease(shifted);
    }
    gBattleWork->effectMode = 0xFF;
    gBattleWork->effectActive = 0;
}

/* fn: sub_0803370C */
// @ 0x0803370c
/* match-compiler: old_agbcc */
// Tick the floating score digits (BattleWork+0xB54): count the shown value up
// towards its target by 4, lay the digits out right-to-left, ease y and x
// towards their targets, and clear the display once the timer runs out.
void BattleScorePopupTick(void)
{
    s32 count;
    s32 x;
    s32 i;

    if (gData_03000290->popupActive != 1)
        return;
    if (--gData_03000290->popupTimer >= 0)
    {
        if (gData_03000290->popupShown < gData_03000290->popupTarget)
        {
            gData_03000290->popupShown += 4;
            if (gData_03000290->popupShown > gData_03000290->popupTarget)
                gData_03000290->popupShown = gData_03000290->popupTarget;
        }
        count = DigitSpritesSetValue((struct Sprite **)gData_03000290->popupDigits, gData_03000290->popupShown, 4, gData_0810B4E0, 1);
        x = gData_03000290->popupX + (count - 1) * 0x700;
        for (i = 0; i < count; i++)
        {
            struct Sprite *digit = gData_03000290->popupDigits[i];

            if (digit != NULL)
            {
                digit->unk08 = x;
                digit->unk0C = gData_03000290->popupY;
            }
            x -= 0x700;
        }
        gData_03000290->popupY += (gData_03000290->popupTargetY - gData_03000290->popupY) >> 3;
        if (gData_03000290->popupSide == 1)
        {
            s32 cx = 0;
            s32 cy = 0;

            if (gData_03000290->unk0AE8.fields.unkB00[0] != NULL)
                sub_08031368(gData_03000290->unk0AE8.fields.unkB00, 8, (u32 *)&cx, (u32 *)&cy);
            gData_03000290->popupX += (cx - gData_03000290->popupX) >> 3;
        }
        else
        {
            s32 cx = 0;
            s32 cy = 0;

            if (gData_03000290->unk0AE8.fields.unkB20[0] != NULL)
                sub_08031368(gData_03000290->unk0AE8.fields.unkB20, 8, (u32 *)&cx, (u32 *)&cy);
            gData_03000290->popupX += (cx - gData_03000290->popupX) >> 3;
        }
    }
    else
    {
        BattleScorePopupClear();
    }
}

/* fn: sub_08033878 */
// @ 0x08033878
void BattleScorePopupClear(void)
{
    s32 zero;

    zero = 0;
    gBattleWork->popupShown = zero;
    gBattleWork->popupTarget = zero;
    gBattleWork->popupActive = zero;
    gBattleWork->popupTargetY = zero;
    gBattleWork->popupTimer = zero;

    for (zero = 0; zero <= 3; zero++)
    {
        if (gBattleWork->popupDigits[zero] != 0)
        {
            BtlObjPoolFree(gBattleWork->popupDigits[zero]);
            gBattleWork->popupDigits[zero] = 0;
        }
    }
}

/* fn: sub_080338F0 */
// @ 0x080338f0
// Advances a key-combo tracker by one frame: `key` must match the next entry
// of the combo table within 60 frames of the previous one, or the combo resets.
// Completing the table sets the position to -1.
void BtlKeyComboStep(struct Unk33958 *a, u16 key)
{
    struct Unk338F0Table *table = a->unk04;
    u16 *keys = table->unk04;

    if (a->unk00 == table->unk00)
    {
        a->unk00 = -1;
        return;
    }
    if (a->unk00 == -1)
        return;
    if (a->unk02 == 0)
    {
        if (a->unk00 != 0)
            return;
    }
    else
        a->unk02--;
    if (key == keys[a->unk00])
    {
        a->unk02 = 60;
        a->unk00++;
    }
    else if (key != 0)
    {
        a->unk02 = 0;
        a->unk00 = 0;
    }
}

/* fn: sub_08034894 */
// @ 0x08034894
/* match-compiler: old_agbcc */
// Copy the three shadow scroll values into the +0x300..+0x304 working words when
// unk30C is clear, otherwise zero the same three. Plain `if/else` with the three
// stores spelled out in each arm matches; factoring the shared trailing store
// through a temporary makes agbcc re-order the pool and the tail (75/84).
void BtlCaptureInput(struct Unk346C0 *a)
{
    if (a->unk30C == 0)
    {
        a->unk302 = *(u16 *)0x03003F60;
        a->unk300 = *(u16 *)0x03004060;
        a->unk304 = *(u16 *)0x0300406C;
    }
    else
    {
        a->unk302 = 0;
        a->unk300 = 0;
        a->unk304 = 0;
    }
}

/* fn: sub_08035238 */
// @ 0x08035238
void BattleAnimStopAll(struct Unk35258 *a)
{
    BattleAnimStop(a, 0);
    BattleAnimStop(a, 1);
    BattleAnimStop(a, 2);
}

/* fn: sub_08035258 */
// @ 0x08035258
/* match-compiler: old_agbcc */
// Stops animation block `type` (0..2) if its active bit in unk2C5 is set:
// notifies sub_08038638, releases the block and clears the bit.
void BattleAnimStop(struct Unk35258 *a, u32 b)
{
    u8 type = b;

    switch (type)
    {
    case 0:
        if (a->unk2C5 & 1)
        {
            PaletteSlotRefRelease(a->unk1C.unk3A >> 1);
            SceneObjFreeResources(&a->unk1C);
            a->unk2B0 = 0;
            a->unk2B4 = 0;
            a->unk2C5 &= ~1;
        }
        break;
    case 1:
        if (a->unk2C5 & 2)
        {
            PaletteSlotRefRelease(a->unkF8.unk3A >> 1);
            SceneObjFreeResources(&a->unkF8);
            a->unk2C5 &= ~2;
        }
        break;
    case 2:
        if (a->unk2C5 & 4)
        {
            PaletteSlotRefRelease(a->unk1D4.unk3A >> 1);
            SceneObjFreeResources(&a->unk1D4);
            a->unk2C5 &= ~4;
        }
        break;
    }
}

/* fn: sub_08035468 */
// @ 0x08035468
// Projects world point (x, y, z) through the battle camera (gBattleWork.unkAA8:
// position, screen centre, angle) and places the source's sprite there: depth
// scales the offset, the sprite offset (ox, oy) is rotated by camera - angle, and
// sub_08070354 gets the depth as scale and the relative angle.
void BtlPlaceSpriteAtWorld(void *source, s32 x, s32 y, s32 z, s32 ox, s32 oy, s32 angle)
{
    struct Unk70354 *obj = ((struct Unk35468Source *)source)->unkB8;
    struct Unk30638AA8 *cam = &gBattleWork->unkAA8;
    s32 sine;
    s32 cosine;
    s32 sx;
    s32 sy;
    s32 edge;
    s32 rx;
    s32 ry;
    s32 depth;

    if (obj == NULL)
        return;
    sine = gData_083C9544[((u32)cam->unk14 & 0xFFFF) >> 8];
    cosine = gData_083C9544[(((u32)cam->unk14 & 0xFFFF) >> 8) + 0x40];
    x -= cam->unk00;
    y -= cam->unk04;
    z -= cam->unk08;
    depth = z >> 8;
    x = (x * depth) >> 8;
    y = (y * depth) >> 8;
    sx = ((x * cosine) >> 8) + ((y * sine) >> 8) + cam->unk0C;
    sy = ((y * cosine) >> 8) - ((x * sine) >> 8) + cam->unk10;
    edge = (depth << 13) >> 8;
    sx -= edge;
    sy -= edge;
    if (depth < 0x100)
    {
        edge = ((0x100 - depth) << 13) >> 8;
        sx -= edge;
        sy -= edge;
    }
    cosine = gData_083C9544[(((u32)(cam->unk14 - angle) & 0xFFFF) >> 8) + 0x40];
    sine = gData_083C9544[((u32)(cam->unk14 - angle) & 0xFFFF) >> 8];
    rx = ((ox * cosine) >> 8) + ((oy * sine) >> 8);
    ry = ((oy * cosine) >> 8) - ((ox * sine) >> 8);
    rx = (rx * depth) >> 8;
    ry = (ry * depth) >> 8;
    obj->unk08 = sx - rx;
    obj->unk0C = sy - ry;
    SpriteApplyAffine(obj, depth, depth, (angle - cam->unk14) >> 8);
}

/* fn: sub_08035D68 */
// @ 0x08035d68
/* match-compiler: old_agbcc */
// Project `source` (world x/y/z) into screen space relative to camera `state`:
// rotate by the camera angle, scale by depth, then place and scale the
// source's sprite (sub_08070354 with the depth as zoom).
void BtlProjectToScreen(struct Unk35D68Source *source, struct Unk35D68State *state)
{
    s16 index;
    s32 sine;
    s32 cosine;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 x;
    s32 y;
    s32 flag;

    flag = 0;
    index = state->unk14 >> 8;
    sine = gData_083C9544[index];
    cosine = gData_083C9544[index + 0x40];
    dx = source->unk0C - state->unk00;
    dy = source->unk10 - state->unk04;
    dz = (source->unk14 - state->unk08) >> 8;
    dx = (dx * dz) >> 8;
    dy = (dy * dz) >> 8;
    x = ((dx * cosine) >> 8) + ((sine * dy) >> 8) + state->unk0C;
    y = ((dy * cosine) >> 8) - ((sine * dx) >> 8) + state->unk10;
    x -= source->unk04;
    y -= source->unk08;
    if (dz > 0x100)
    {
        x -= (source->unk04 * (dz - 0x100)) >> 8;
        y -= ((dz - 0x100) * source->unk08) >> 8;
    }
    source->unk00->unk08 = x;
    source->unk00->unk0C = y;
    if (source->unk00->unk30 != NULL)
        flag = source->unk00->unk30->angle;
    SpriteApplyAffine((struct Unk70354 *)source->unk00, dz, dz, flag);
}

/* fn: sub_0803715C */
// @ 0x0803715c
/* match-compiler: old_agbcc */
// score = experience-derived value of side b (0 = MainWork.expPoints, else
// gData_030002A0[b]) clamped to 20..100. Side a gets the score (divided by
// its unk24->unk04 when positive) and the other side a quarter; every total
// is capped at 0x3FFF. Returns the score.
s32 BtlApplyClampedScore(u8 a, u8 b)
{
    struct Unk3715C *slot;
    s32 score;
    s32 key;

    if (b == 0)
    {
        score = (s16)_080740B0(gData_03000198->expPoints, 10);
    }
    else
    {
        score = _080740B0(gData_030002A0[b].unk08, 10);
        gData_030002A0[b].unk28->unk26 += 5;
    }
    if (score <= 19)
        score = 20;
    if (score > 100)
        score = 100;

    if (a == 0)
    {
        key = sub_08042C3C((s8)_080672A8());
        if (gData_030002A0[b].unk24->unk04 > 0)
            score = Div(score, gData_030002A0[b].unk24->unk04);
        if (gData_03000198->expPoints < key || key == -1)
        {
            gData_03000198->expPoints += score;
            gData_030002A0[0].unk28->unk26 += 5;
        }
        else
        {
            score = RandRange(10) + 1;
        }
        if (gData_03000198->expPoints > 0x3FFF)
            gData_03000198->expPoints = 0x3FFF;
        slot = gData_030002A0[b].unk24;
        if (slot != NULL)
        {
            slot->unk00 += score >> 2;
            gData_030002A0[b].unk28->unk26 += 5;
            if (gData_030002A0[b].unk24->unk00 > 0x3FFF)
                gData_030002A0[b].unk24->unk00 = 0x3FFF;
        }
    }
    else
    {
        if (gData_030002A0[a].unk24 != NULL)
        {
            if (gData_030002A0[a].unk24->unk04 > 0)
                score = Div(score, gData_030002A0[a].unk24->unk04);
            gData_030002A0[a].unk24->unk00 += score;
            gData_030002A0[a].unk28->unk26 += 5;
            if (gData_030002A0[a].unk24->unk00 > 0x3FFF)
                gData_030002A0[a].unk24->unk00 = 0x3FFF;
        }
        gData_03000198->expPoints += score >> 2;
        gData_030002A0[0].unk28->unk26 += 5;
        if (gData_03000198->expPoints > 0x3FFF)
            gData_03000198->expPoints = 0x3FFF;
    }
    return score;
}

/* fn: sub_0803D51C */
// @ 0x0803d51c
/* match-compiler: old_agbcc */
// Retail compiled this caller against a (s8, s8, s16) prototype of
// sub_0802C55C, whose definition takes (u16, u8, s16): the arguments are
// passed sign-extended. The cast reproduces that call (still a direct bl).
#define FreeSlotSigned ((void (*)(s32, s32, s32))CollectionFreeSlot)

// For the CollectionEntry entries found by sub_0802C314(3, 1) and (2, 1): subtracts
// (unk00 + MainWork.strength) from the entry's unk02 and frees the entry once
// it drops to 0 or below. Returns 1 if either entry was freed.
s32 BattlePartsApplyWear(void)
{
    struct CollectionLookup out;
    s32 result = 0;

    if (gMainWorkPtr->unk1808 & 0x10000)
        return 0;
    CollectionFindByGroupSlot(3, 1, &out);
    out.entry->value -= out.kind + gMainWorkPtr->strength;
    if ((s8)out.entry->value <= 0)
    {
        gUnk_030002A0.records[0].unk0C = result;
        gBattleWork->wornOutA = 1;
        result = 1;
        FreeSlotSigned((s8)out.kind, (s8)out.group, (s16)out.index);
        if (BtlUnk1694FindAndMark(out.group) == 0)
            gBattleWork->unk1F73 = result;
    }
    CollectionFindByGroupSlot(2, 1, &out);
    out.entry->value -= out.kind + gMainWorkPtr->strength;
    if ((s8)out.entry->value <= 0)
    {
        gUnk_030002A0.records[0].unk0C = 0;
        gBattleWork->wornOutB = 1;
        result = 1;
        FreeSlotSigned((s8)out.kind, (s8)out.group, (s16)out.index);
        if (BtlUnk1694FindAndMark(out.group) == 0)
            gBattleWork->unk1F73 = result;
    }
    return result;
}

/* fn: sub_0803E440 */
// @ 0x0803e440
s32 BtlCountLiveSlots(void)
{
    s32 count;
    s32 i;
    s8 *p;

    count = 0;
    i = 0;
    p = gMainWorkPtr->unk1861;
    while (i <= 0x52)
    {
        if (p[i] > 0)
            count++;
        i++;
    }
    return count;
}

/* fn: sub_080433F4 */
// @ 0x080433f4
void BtlClearUnk1834(void)
{
    gMainWorkPtr->unk1834 = 0;
    gMainWorkPtr->unk1808 &= 0xFFFFFDFF;
}

/* fn: sub_08043B90 */
// @ 0x08043b90
/* match-compiler: old_agbcc */
// Walk MainWork.unk16E0 ({ptr,s32} records) until sub_08073440(entry->unk00,
// unk16C8) returns 0, then return entry->unk04. Null list -> -1.
s32 BtlFindUnk16E0(void)
{
    struct Unk16E0 *node = gMainWorkPtr->unk16E0;

    if (node == 0)
        return -1;
    while (node->unk00 != 0)
    {
        if (StringCompare(node->unk00, gMainWorkPtr->unk16C8) == 0)
            return node->unk04;
        node++;
    }
    // BUG: no return when the list is exhausted; r0 still holds the 0 from
    // the loop test, so callers see 0.
#ifdef BUGFIX
    return 0;
#endif
}

/* fn: sub_08043BDC */
// @ 0x08043bdc
void *BtlFindUnk16E4(void)
{
    struct Unk16E0 *p;

    p = gMainWorkPtr->unk16E4;
    if (p == 0)
        return 0;
    while (p->unk00 != 0)
    {
        if (StringCompare(p->unk00, gMainWorkPtr->unk16C8) == 0)
            return (void *)p->unk04;
        p++;
    }
    return 0;
}

/* fn: sub_08044EE8 */
// @ 0x08044ee8
void BtlClearUnk1688Entry(s32 idx)
{
    struct Unk1688Entry *p;

    p = &gMainWorkPtr->unk1688[idx];
    p->unk04 = 0;
    p->unk00 = 0;
    p->unk08 = 0;
    p->unk10 = 0;
    p->unk12 = 0;
    p->unk14 = 0;
    p->unk16 = 0;
}

/* fn: sub_08046230 */
// @ 0x08046230
void BtlResetUnk16B0(s32 a)
{
    if ((u32)a > 1)
        return;

    if (gMainWorkPtr->unk16B0[a].unk00 == 1)
    {
        gMainWorkPtr->unk16B0[a].unk00 = 0;
        gMainWorkPtr->unk16B0[a].unk04 = -1;
        gMainWorkPtr->unk16B0[a].unk08 = -1;
    }
}

/* fn: sub_08046278 */
// @ 0x08046278
// Reset both unk16B0 slots to {0, -1, -1} (unconditional form of BtlResetUnk16B0).
void BtlInitUnk16B0Slots(void)
{
    s32 i;

    for (i = 0; i < 2; i++)
    {
        gData_03000198->unk16B0[i].unk00 = 0;
        gData_03000198->unk16B0[i].unk04 = -1;
        gData_03000198->unk16B0[i].unk08 = -1;
    }
}

/* fn: sub_080603E0 */
// @ 0x080603e0
void BtlSetAllUnk1710(u16 a)
{
    s16 i;

    i = 0;
    do
    {
        SoundSetVolume(gMainWorkPtr->sfxHandles[i], a);
        i++;
    } while (i <= 0x18);
    gMainWorkPtr->sfxVolume = a;
}

/* fn: sub_0806C388 */
// @ 0x0806c388
/* match-compiler: old_agbcc */
// Build the collision quadtree over [x0, x1] x [y0, y1]: collect the mesh
// edges whose (16px-padded) bounds touch the box, and split into four
// children while more than unk3C edges touch it and it is at least 128px
// square; otherwise make it a leaf listing those edges (NULL if none).
typedef u8 (*EdgeFilter)(struct Unk6C388Mesh *, struct Unk6C388Edge *);

struct Unk6C388Node *CollisionQuadtreeBuild(struct Unk6C388Tree *t, struct Unk6C388Node *n, s32 x0, s32 y0, s32 x1, s32 y1, EdgeFilter filter)
{
    struct Unk6C388Mesh *mesh;
    struct Unk6C388Edge *e;
    struct Unk6C388Vert *verts;
    struct Unk6C388Vert *a, *b;
    s32 w, h;
    s32 i;
    s32 count;
    s32 start;
    s32 full;
    s32 minX, maxX, minY, maxY, tmp;
    u16 flags;
    s32 midX, midY;

    mesh = t->unk10;
    e = mesh->unk0C;
    verts = mesh->unk04;
    count = 0;
    start = t->unk3A;
    full = 0;
    n->unk18 = x0;
    n->unk20 = x1;
    n->unk1C = y0;
    n->unk24 = y1;
    w = x1 - x0;
    h = y1 - y0;
    for (i = 0; i < mesh->unk00->unk08; e++, i++)
    {
        a = &verts[e->unk00];
        b = &verts[e->unk04];
        if (e->unk11 & 8)
            continue;
        if (filter != NULL && !filter(mesh, e))
            continue;
        if (e->unk00 < 0 || e->unk04 < 0)
            continue;
        minX = a->unk00;
        minY = a->unk04;
        maxX = b->unk00;
        maxY = b->unk04;
        if (minX > maxX)
        {
            tmp = maxX;
            maxX = minX;
            minX = tmp;
        }
        if (minY > maxY)
        {
            tmp = maxY;
            maxY = minY;
            minY = tmp;
        }
        minX -= 16;
        maxX += 16;
        minY -= 16;
        maxY += 16;
        flags = 0;
        if (minX >= x0 && minX <= x1)
            flags = 1;
        if (maxX >= x0 && maxX <= x1)
            flags |= 1;
        if (minY >= y0 && minY <= y1)
            flags |= 2;
        if (maxY >= y0 && maxY <= y1)
            flags |= 2;
        if (minX <= x0 && maxX >= x1 && (flags & 2))
            flags = 3;
        if (minY <= y0 && maxY >= y1 && (flags & 1))
            flags = 3;
        if (minX <= x0 && maxX >= x1 && minY <= y0 && maxY >= y1)
        {
            flags = 3;
            full++;
        }
        if (flags == 3)
        {
            if (start < t->unk40)
            {
                t->unk30[start] = e;
                start++;
            }
            else
            {
                DebugPrint((void *)0x083D1EE8);
            }
            count++;
        }
    }
    if (count > t->unk3C && full < t->unk3C && w > 0x7F && h > 0x7F)
    {
        midX = x0 + ((x1 - x0) >> 1);
        midY = y0 + ((y1 - y0) >> 1);
        n->unk10 = NULL;
        n->unk14 = 0;
        n->unk28 = 0;
        n->unk2A = 0;
        if (t->unk38 + 4 >= t->unk3E)
            DebugPrint((void *)0x083D1F14);
        n->unk00 = &t->unk2C[t->unk38++];
        n->unk04 = &t->unk2C[t->unk38++];
        n->unk08 = &t->unk2C[t->unk38++];
        n->unk0C = &t->unk2C[t->unk38++];
        n->unk00 = CollisionQuadtreeBuild(t, n->unk00, x0, y0, midX, midY, filter);
        n->unk04 = CollisionQuadtreeBuild(t, n->unk04, midX, y0, x1, midY, filter);
        n->unk08 = CollisionQuadtreeBuild(t, n->unk08, x0, midY, midX, y1, filter);
        n->unk0C = CollisionQuadtreeBuild(t, n->unk0C, midX, midY, x1, y1, filter);
        return n;
    }
    n->unk28 = count;
    n->unk2A = 0;
    n->unk14 = 0;
    n->unk10 = &t->unk30[t->unk3A];
    t->unk3A = start;
    if (count > 32)
        DebugPrint((void *)0x083D1F5C, count, 32);
    if (count == 0)
        return NULL;
    return n;
}

/* fn: sub_08070678 */
// @ 0x08070678
void BtlReleaseEntry(struct TextGroup *a)
{
    struct AffineObj *p;

    BtlObjPoolReleaseChain(&a->glyphs);
    p = a->affine;
    if (p != 0)
    {
        AffineObjUnlock(p);
        BtlObjListMoveToHead((struct BtlObj *)a->affine);
        a->affine = 0;
    }
}
