#include "global.h"

// @ 0x080312d8

void PaletteHighlightEnd(struct Unk312EC *a)
{
    PaletteHighlightRestore(a);
    PaletteHighlightReset(a);
}

