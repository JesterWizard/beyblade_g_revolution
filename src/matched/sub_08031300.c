#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08031300
void TextRowPulsePalette(struct Unk312EC *a)
{
    struct Unk705DC *p;
    u32 bank;

    if (a->unk08 == 0)
        return;
    if (a->unk04 >= 0)
    {
        a->unk04--;
        p = a->unk0C;
        if (p == NULL)
            return;
        bank = p->unk14 >> 12;
        if ((a->unk04 & 5) == 0)
        {
            if (bank == a->unk01)
                bank = a->unk00;
            else
                bank = a->unk01;
            TextEntrySetPaletteBank(p, (u8)bank);
        }
    }
    else
    {
        sub_080312D8(a);
    }
}

