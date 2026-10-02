#include "global.h"

// @ 0x0807069c
void TextGroupClear(struct TextGroup *a)
{
    BtlObjPoolReleaseChain(&a->glyphs);
    a->penX = 0;
}

