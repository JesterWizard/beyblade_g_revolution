#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08036a68
void sub_08036A68(struct Unk346C0 *a, s32 unused, u32 slot)
{
    void *buf0;
    void *buf1;
    void *buf2;

    buf0 = StringAlloc(0x80);
    buf1 = StringAlloc(0x80);
    buf2 = StringAlloc(0x80);
    sub_08037318(a, (u8)slot);
    GlyphTextInit((struct Unk61E8C *)&gBattleWork->unk013C.fields.unk14C, gData_080B72F3, (struct Unk61E8CSrc *)gData_082BF600, 0xB0, 0x150);
    StringExpandDelim(gData_080972A0[gMainWorkPtr->language], buf0,
                 BeybladeGetName(gData_030002A0[slot].unk00), 0x23, 0x80);
    StringExpandDelim(buf0, buf1, (void *)GetBeybladeNameWithIndex(gData_030002A0[slot].unk04), 0x40, 0x80);
    GlyphTextLayoutWrapped(&gBattleWork->unk013C.fields.unk14C, buf1, 0, 0x50, 0, 0xC8, 0);
    StringFree(buf0);
    StringFree(buf1);
    StringFree(buf2);
    sub_08037430();
}

