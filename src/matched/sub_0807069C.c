#include "global.h"

// @ 0x0807069c
void TextGroupClear(struct Unk7069C *a)
{
    BtlObjPoolReleaseChain(&a->unk14);
    a->unk0A = 0;
}

