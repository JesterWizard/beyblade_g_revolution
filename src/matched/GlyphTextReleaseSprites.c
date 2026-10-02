#include "global.h"

// @ 0x0806209c

void GlyphTextReleaseSprites(struct GlyphText *a)
{
    s32 i;
    void *p;

    if (a == 0)
        return;
    if (a->sprites != 0)
    {
        i = 0;
        do
        {
            p = a->sprites[i];
            if (p == 0)
                break;
            BtlObjPoolFree(p);
            a->sprites[i] = 0;
            i++;
        } while (i <= 0x7F);
    }
    a->spritesInUse = 0;
}

