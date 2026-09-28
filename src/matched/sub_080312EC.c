#include "global.h"

// @ 0x080312ec
void PaletteHighlightRestore(struct Unk312EC *a)
{
    if (a->unk0C != 0)
        TextEntrySetPaletteBank(a->unk0C, (u8)a->unk01);
}

