#include "global.h"
#include "ram_map.h"

void sub_0802DCDC(void *arg)
{
    struct MainWork *main;
    struct Unk026C *p;
    struct Unk42E78 *row;
    struct Unk310F0b *tens;
    struct Unk310F0b *ones;
    u32 flags;
    u32 x;
    u32 y;
    s16 current;
    s8 t;
    u32 *palette;

    main = gMainWorkPtr;
    flags = main->unk1808;
    if (flags & 4)
        return;
    if (flags & 0x1000)
        return;
    main->unk1808 = flags | 0x1000;
    current = main->unk1838;
    if (current == -1)
        return;
    p = gUnk_0300026C;
    if ((s8)p->unk48 == -1)
    {
        p->unk4C = current;
        p->unk4E = main->unk183A;
        p->unk48 = 0;
        gUnk_0300026C->unk04 = 1;
        gUnk_0300026C->unk44 = arg;
        gMainWorkPtr->unk16D4 = sub_08042B00(gUnk_0300026C->unk4E);
        return;
    }
    if (current == p->unk4C || (s8)p->unk48 != 2)
        return;

    row = (struct Unk42E78 *)sub_08042E78((s16)main->unk183A);
    p = gUnk_0300026C;
    x = p->unk28->unk08;
    y = p->unk28->unk0C;
    main = gMainWorkPtr;
    p->unk4C = main->unk1838;
    p->unk4E = main->unk183A;
    p->unk44 = arg;
    gMainWorkPtr->unk16D4 = sub_08042B00(p->unk4E);
    if (gUnk_0300026C->unk28 != NULL)
    {
        BtlObjPoolFree(gUnk_0300026C->unk28);
        gUnk_0300026C->unk28 = NULL;
    }
    gUnk_0300026C->unk28 = BtlObjPoolAlloc(1);
    sub_0806FF58(gUnk_0300026C->unk28, sub_08042B28(gUnk_0300026C->unk4E), x, y, 0, 1, 1, 0);
    palette = gData_080BB8C0;
    _08073C4C(sub_08042B50(gUnk_0300026C->unk4E), (void *)0x05000380, 0x20, (void *)*palette);
    TextEntrySetPaletteBank(gUnk_0300026C->unk28, 0x0C);
    HudWriteDigits((struct Unk310F0b *)gUnk_0300026C->bladeStrengthTens, (struct Unk310F0b *)gUnk_0300026C->bladeStrengthOnes, (s8)row->strength);
    tens = (struct Unk310F0b *)gUnk_0300026C->bitBeastLevelTens;
    ones = (struct Unk310F0b *)gUnk_0300026C->bitBeastLevelOnes;
    t = BitBeastLevel();
    HudWriteDigits(tens, ones, t);
    t = ExpBarFill(row->bitBeastExp);
    gUnk_0300026C->bitBeastExpBar->unk18 = t;
}

