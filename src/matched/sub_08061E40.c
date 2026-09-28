#include "global.h"

// @ 0x08061e40

/* match-flags: -fprologue-bugfix */

void TextTypewriterRestart(struct Unk61E40 *a)
{
    if (a != 0)
    {
        a->unk10 = 0;
        a->unk0A = 0;
        a->unk15 = 0;
        a->unk04 = 0;
    }
}


