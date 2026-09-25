#include "global.h"

// @ 0x0802d3f0
void sub_0802D3F0(void)
{
    struct Unk705DC *q;
    void *slot;

    slot = *(void **)0x03000270;
    if (slot != 0)
    {
        q = gUnk_0300026C->unk08;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->unk08 = 0;
        }
        q = gUnk_0300026C->unk0C;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->unk0C = 0;
        }
        q = gUnk_0300026C->unk10;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->unk10 = 0;
        }
        q = gUnk_0300026C->playerLevelTens;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->playerLevelTens = 0;
        }
        q = gUnk_0300026C->playerLevelOnes;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->playerLevelOnes = 0;
        }
        q = gUnk_0300026C->playerStrengthTens;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->playerStrengthTens = 0;
        }
        q = gUnk_0300026C->playerStrengthOnes;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->playerStrengthOnes = 0;
        }
        q = gUnk_0300026C->playerExpBar;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->playerExpBar = 0;
        }
        q = gUnk_0300026C->unk28;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->unk28 = 0;
        }
        q = gUnk_0300026C->unk2C;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->unk2C = 0;
        }
        q = gUnk_0300026C->bitBeastLevelTens;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->bitBeastLevelTens = 0;
        }
        q = gUnk_0300026C->bitBeastLevelOnes;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->bitBeastLevelOnes = 0;
        }
        q = gUnk_0300026C->bladeStrengthTens;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->bladeStrengthTens = 0;
        }
        q = gUnk_0300026C->bladeStrengthOnes;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->bladeStrengthOnes = 0;
        }
        q = gUnk_0300026C->bitBeastExpBar;
        if (q != 0)
        {
            BtlObjPoolFree(q);
            gUnk_0300026C->bitBeastExpBar = 0;
        }
        slot = *(void **)0x03000270;
        if (slot != 0)
        {
            HeapFree(slot);
            *(void **)0x03000270 = 0;
        }
    }
}

