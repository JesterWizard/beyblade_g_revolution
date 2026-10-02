#include "global.h"

// @ 0x08062044
void GlyphTextFree(struct GlyphText *a)
{
    if (a != 0)
    {
        GlyphTextReleaseSprites(a);
        if (a->heapBlock != 0)
        {
            HeapFree(a->heapBlock);
            a->heapBlock = 0;
        }
        a->sprites = 0;
    }
}

