#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_0802D3F0 */
// @ 0x0802d3f0
void StatusHudFree(void)
{
    struct Sprite *q;
    void *slot;

    slot = *(void **)0x03000270;
    if (slot != 0)
    {
        q = gUnk_0300026C->marker;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->marker = 0;
        }
        q = gUnk_0300026C->unk0C;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->unk0C = 0;
        }
        q = gUnk_0300026C->unk10;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->unk10 = 0;
        }
        q = gUnk_0300026C->playerLevelTens;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->playerLevelTens = 0;
        }
        q = gUnk_0300026C->playerLevelOnes;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->playerLevelOnes = 0;
        }
        q = gUnk_0300026C->playerStrengthTens;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->playerStrengthTens = 0;
        }
        q = gUnk_0300026C->playerStrengthOnes;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->playerStrengthOnes = 0;
        }
        q = gUnk_0300026C->playerExpBar;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->playerExpBar = 0;
        }
        q = gUnk_0300026C->unk28;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->unk28 = 0;
        }
        q = gUnk_0300026C->unk2C;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->unk2C = 0;
        }
        q = gUnk_0300026C->bitBeastLevelTens;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->bitBeastLevelTens = 0;
        }
        q = gUnk_0300026C->bitBeastLevelOnes;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->bitBeastLevelOnes = 0;
        }
        q = gUnk_0300026C->bladeStrengthTens;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->bladeStrengthTens = 0;
        }
        q = gUnk_0300026C->bladeStrengthOnes;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->bladeStrengthOnes = 0;
        }
        q = gUnk_0300026C->bitBeastExpBar;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->bitBeastExpBar = 0;
        }
        slot = *(void **)0x03000270;
        if (slot != 0)
        {
            HeapFree(slot);
            *(void **)0x03000270 = 0;
        }
    }
}

/* fn: sub_0802D52C */
// @ 0x0802d52c
void sub_0802D52C(u32 a, s32 b)
{
    struct StatusHud *w;

    if (b != 0)
    {
        w = gUnk_0300026C;
        if (w->markerShown == 0)
        {
            w->marker->unk18 = (u16)a;
            w->marker->unk08 = gMainWorkPtr->unk0424->unk08 + 0xFFFFF800;
            w->marker->unk0C = gMainWorkPtr->unk0424->unk0C + 0xFFFFF800;
            TextEntrySetPaletteBank(w->marker, 2);
        }
    }
    else
    {
        gUnk_0300026C->marker->unk08 = 0xFFFFC000;
        gUnk_0300026C->marker->unk0C = 0xFFFFC000;
    }

    gUnk_0300026C->markerShown = b;
}

/* fn: sub_0802D598 */
// @ 0x0802d598

void StatusHudMarkerHide(void)
{
    struct Sprite *q;

    gUnk_0300026C->markerShown = 0;
    q = gUnk_0300026C->marker;
    q->unk08 = 0xFFFFC000;
    q->unk0C = 0xFFFFC000;
}

/* fn: sub_0802D6D4 */
// @ 0x0802d6d4
void StatusHudCreate(void)
{
    struct Sprite *resource;
    struct StatusHud *w;

    resource = BtlObjPoolAlloc(2);
    gUnk_0300026C->marker = resource;
    SpriteInitFromTemplate(
        resource, (void *)0x080D63CC,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    TextEntrySetPaletteBank(gUnk_0300026C->marker, 2);

    gUnk_0300026C->unk0C = BtlObjPoolAlloc(0);
    gUnk_0300026C->unk10 = BtlObjPoolAlloc(0);
    gUnk_0300026C->playerLevelTens = BtlObjPoolAlloc(0);
    gUnk_0300026C->playerLevelOnes = BtlObjPoolAlloc(0);
    gUnk_0300026C->playerStrengthTens = BtlObjPoolAlloc(0);
    gUnk_0300026C->playerStrengthOnes = BtlObjPoolAlloc(0);
    gUnk_0300026C->playerExpBar = BtlObjPoolAlloc(0);

    SpriteInitFromTemplate(
        gUnk_0300026C->unk0C, (void *)0x08266DAC,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    SpriteInitFromTemplate(
        gUnk_0300026C->unk10, (void *)0x080D6618,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0,
        gMainWorkPtr->language);
    SpriteInitFromTemplate(
        gUnk_0300026C->playerLevelTens, (void *)0x080D6B68,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    SpriteInitFromTemplate(
        gUnk_0300026C->playerLevelOnes, (void *)0x080D6B68,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    SpriteInitFromTemplate(
        gUnk_0300026C->playerStrengthTens, (void *)0x080D6B68,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    SpriteInitFromTemplate(
        gUnk_0300026C->playerStrengthOnes, (void *)0x080D6B68,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    SpriteInitFromTemplate(
        gUnk_0300026C->playerExpBar, (void *)0x080D6D50,
        0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);

    TextEntrySetPaletteBank(gUnk_0300026C->unk0C, 2);
    TextEntrySetPaletteBank(gUnk_0300026C->unk10, 2);
    TextEntrySetPaletteBank(gUnk_0300026C->playerLevelTens, 2);
    TextEntrySetPaletteBank(gUnk_0300026C->playerLevelOnes, 2);
    TextEntrySetPaletteBank(gUnk_0300026C->playerStrengthTens, 2);
    TextEntrySetPaletteBank(gUnk_0300026C->playerStrengthOnes, 2);
    TextEntrySetPaletteBank(gUnk_0300026C->playerExpBar, 2);

    w = gUnk_0300026C;
    w->markerShown = 0;
    w->unk4C = 0xFFFF;
    w->unk04 = 0;
    w->unk48 = 0xFF;
}

/* fn: sub_0802D898 */
// @ 0x0802d898
void sub_0802D898(s32 a, s32 b)
{
    struct StatusHud *p;
    struct Sprite *q;

    p = gUnk_0300026C;
    q = p->marker;
    if (q != 0)
    {
        q->unk08 = a + 0xFFFFF800;
        q->unk0C = b + 0xFFFFF800;
        p->markerShown = 1;
    }
}

/* fn: sub_0802D8C4 */
// @ 0x0802d8c4
/* match-flags: -fprologue-bugfix */

void sub_0802D8C4(u16 a)
{
    u32 r1;
    struct Sprite *r0;

    r1 = a;
    r0 = gUnk_0300026C->marker;
    if (r0 != 0)
        r0->unk18 = r1;
}

/* fn: sub_0802D8DC */
// @ 0x0802d8dc
void HudRefreshStats(void)
{
    struct StatusHud *p;
    struct Unk310F0b *tens;
    struct Unk310F0b *ones;
    struct Unk42E78 *row;
    s8 t;

    _0802D9A8();
    p = gUnk_0300026C;
    if (p->unk0C != 0)
    {
        HudWriteDigits((struct Unk310F0b *)p->playerStrengthTens, (struct Unk310F0b *)p->playerStrengthOnes, gMainWorkPtr->strength);
        tens = (struct Unk310F0b *)gUnk_0300026C->playerLevelTens;
        ones = (struct Unk310F0b *)gUnk_0300026C->playerLevelOnes;
        t = ExpLevel();
        HudWriteDigits(tens, ones, t);
        if (gUnk_0300026C->playerExpBar != 0)
        {
            t = ExpBarFill(gMainWorkPtr->expPoints);
            gUnk_0300026C->playerExpBar->unk18 = t;
        }
    }
    p = gUnk_0300026C;
    if (p->unk28 != 0)
    {
        row = (struct Unk42E78 *)BeybladeCollectionEntry(p->unk4E);
        p = gUnk_0300026C;
        HudWriteDigits((struct Unk310F0b *)p->bladeStrengthTens, (struct Unk310F0b *)p->bladeStrengthOnes, (s8)row->strength);
        tens = (struct Unk310F0b *)gUnk_0300026C->bitBeastLevelTens;
        ones = (struct Unk310F0b *)gUnk_0300026C->bitBeastLevelOnes;
        t = BitBeastLevel();
        HudWriteDigits(tens, ones, t);
        if (gUnk_0300026C->bitBeastExpBar != 0)
        {
            t = ExpBarFill(row->bitBeastExp);
            gUnk_0300026C->bitBeastExpBar->unk18 = t;
        }
    }
}

/* fn: sub_0802E18C */
// @ 0x0802e18c
void HudWriteDigits(struct Unk310F0b *tens, struct Unk310F0b *ones, s32 value)
{
    if (value <= 99)
    {
        tens->shown = Div(value, 10);
        ones->shown = DivRemainder(value, 10);
    }
}

/* fn: sub_0802E1B4 */
// @ 0x0802e1b4
s8 ExpBarFill(s32 points)
{
    s32 level;
    s32 base;
    s32 top;
    s8 fill;

    level = ExpBracket(points);
    base = ExpBracketBase(level);
    top = ExpBracketTop(level);
    fill = ScaleRatio(top - points, top - base, 14);
    return 14 - fill;
}

/* fn: sub_080310F0 */
// @ 0x080310f0
void BarSetFillFromPercent(struct Unk310F0a *a, struct Unk310F0b *b)
{
    s32 v;

    if (b == 0)
        return;
    if (a->unk04 == 0)
        return;
    v = ScaleRatio(a->unk04->unk28->unk24, 100, 182);
    if ((s16)v != -1)
        b->shown = v;
}

/* fn: sub_0803139C */
// @ 0x0803139c

s32 DigitSpritesSetValue(struct Sprite **array, s32 value, s32 count, void *table, u8 withPoint)
{
    s32 index;
    s32 quotient;
    s32 digits;
    u16 palette;
    s32 digit;

    digits = 0;
    index = digits;

    while (value != 0 && index < count)
    {
        quotient = Div(value, 10);
        digit = value - quotient * 10;
        if (array[index] == NULL)
        {
            array[index] = BtlObjPoolAlloc(0x1C2);
            if (array[index] != NULL)
            {
                palette = PaletteSlotAcquire(table);
                SpriteInitFromTemplate(array[index], table, 0, 0, 0, 0, 0, (u16)(index - 0x30));
                if (array[index] != NULL)
                    TextEntrySetPaletteBank(array[index], (u8)palette);
            }
        }
        if (array[index] != NULL)
            array[index]->unk18 = digit;
        value = quotient;
        index++;
    }
    if (withPoint == 1)
    {
        if (array[index] == NULL)
        {
            array[index] = BtlObjPoolAlloc(0x1C2);
            if (array[index] != NULL)
            {
                palette = PaletteSlotAcquire(table);
                SpriteInitFromTemplate(array[index], table, 0, 0, 0, 0, 0, (u16)(index - 0x30));
                if (array[index] != NULL)
                    TextEntrySetPaletteBank(array[index], (u8)palette);
            }
        }
        if (array[index] != NULL)
            array[index]->unk18 = 10;
        index++;
    }
    digits = index;
    for (; index < count; index++)
    {
        if (array[index] != NULL)
        {
            PaletteSlotRefRelease((array[index]->unk14 & 0xF000) >> 12);
            BtlObjPoolFree(array[index]);
            array[index] = NULL;
        }
    }
    return digits;
}

/* fn: sub_080416C4 */
// @ 0x080416c4
/* match-compiler: old_agbcc */
// Build the four HUD digit/bar sprites from the descriptor at a->unk248 and
// enable the matching BG layers.
void HudBuildDigitSprites(struct MenuState *a)
{
    struct Unk4109CInput *desc;
    u16 dispFlags;
    s32 i;
    u8 *walk;
    void *src;

    desc = a->unk248;
    dispFlags = 0;
    HeapFreeSlots8((struct Unk41394 *)a);
    BgScrollReset();
    for (i = 0, walk = (u8 *)a; i <= 3; i++)
    {
        src = desc->unk30[i];
        if (src != NULL)
        {
            a->unk220[i] = Lz77ImageBlit(walk, i, src, 0, 0);
            dispFlags |= gData_080908B4[i];
        }
        walk += 0x88;
    }
    if (desc->unk40 != NULL)
        BgPaletteLoad(desc->unk40);
    if (desc->unk44 != NULL)
        ObjPaletteLoad(desc->unk44);
    VBlankIntrWait();
    REG_DISPCNT = dispFlags | 0x1040;
    BgSetPriorities(0, 1, 2, 3);
}

/* fn: sub_080593A4 */
// @ 0x080593a4
void SegmentedBarRebuild(struct SegmentedBar *a)
{
    s32 i;
    s32 last;
    s32 count;

    for (i = 0; i <= 7; i++)
    {
        if (a->segments[i] != NULL)
        {
            BtlObjPoolFree(a->segments[i]);
            a->segments[i] = NULL;
        }
    }
    count = (a->endAnchor->x >> 8) - ((a->startAnchor->x + a->startOffset) >> 8);
    last = DivRemainder(count, 32);
    count >>= 5;
    if (last > 24)
        last = 24;
    for (i = 0; i <= count; i++)
    {
        if (i == 0)
        {
            a->segments[0] = BtlObjPoolAlloc(10);
            SpriteInitFromTemplate(a->segments[0], (void *)0x0810E628, a->startAnchor->x + a->startOffset, a->endAnchor->y, 0, 0, 0, (u16)last);
            TextEntrySetPaletteBank(a->segments[0], 9);
            if (i < count)
                a->segments[0]->unk18 = 24;
        }
        else
        {
            a->segments[i] = BtlObjPoolAlloc(10);
            SpriteInitFromTemplate(a->segments[i], (void *)0x081178B0, a->startAnchor->x + a->startOffset + (i << 13), a->endAnchor->y, 0, 0, 0, (u16)last);
            TextEntrySetPaletteBank(a->segments[i], 9);
            if (i < count)
                a->segments[i]->unk18 = 24;
        }
    }
}

/* fn: sub_0805E044 */
// @ 0x0805e044
// Snap the camera (sub_0802D898) to the sprite that owns `resource`: the
// three fixed HUD resources map to MainWork.unk0424/unk0500, anything else
// is looked up in the -1-terminated gData_080991D0 list via sub_08041DB4.
void sub_0805E044(void *resource)
{
    s32 i = 0;
    struct Sprite *entry;
    struct Unk5E044Lookup *lookup;

    if (resource == NULL || (gMainWorkPtr->unk1808 & 8) != 0)
        return;
    if (resource == (void *)0x08266DAC)
    {
        entry = gMainWorkPtr->unk0424;
        if (entry != NULL)
            sub_0802D898(entry->unk08, entry->unk0C);
        sub_0802D8C4(1);
        return;
    }
    if (resource == (void *)0x0827EA3C)
    {
        entry = gMainWorkPtr->unk0424;
        if (entry != NULL)
            sub_0802D898(entry->unk08, entry->unk0C);
        sub_0802D8C4(1);
        return;
    }
    if (resource == (void *)0x0826ADC8)
    {
        entry = gMainWorkPtr->unk0500;
        if (entry != NULL)
            sub_0802D898(entry->unk08, entry->unk0C);
        sub_0802D8C4(1);
        return;
    }
    for (; gData_080991D0[i] != (void *)-1; i++)
    {
        if (gData_080991D0[i] == resource)
        {
            lookup = ActorFindByIdSide(i, 0);
            if (lookup != NULL && lookup->unkB8 != NULL)
            {
                sub_0802D898(lookup->unkB8->unk08, lookup->unkB8->unk0C);
                sub_0802D8C4(1);
                return;
            }
        }
    }
}
