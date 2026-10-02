#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08037430
/* match-compiler: old_agbcc */
// Draw the name + count line (count capped at 3) into the battle text box
// unless MainWork.unk1808 bit 1 suppresses it.
void sub_08037430(void)
{
    void *text;
    void *num;

    text = StringAlloc(0x40);
    num = StringAlloc(0x40);
    if (!(gMainWorkPtr->unk1808 & 2))
    {
        if (gBattleWork->unk133 > 3)
            TextFormatInt(3, num, 0x40);
        else
            TextFormatInt(gBattleWork->unk133, num, 0x40);
        StringExpandDelim(gData_08096ECC[gMainWorkPtr->language], text, num, 0x23, 0x40);
        GlyphTextInit((struct Unk61E8C *)&gBattleWork->unk013C.fields.unk174, gData_080B72F3,
                     (struct Unk61E8CSrc *)gData_082BF600, 0xB0, 0x170);
        GlyphTextLayoutWrapped(&gBattleWork->unk013C.fields.unk174, text, 0, 0x28, 0, 0xC8, 0);
    }
    StringFree(text);
    StringFree(num);
}

