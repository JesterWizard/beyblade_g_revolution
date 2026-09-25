#include "global.h"

void sub_0802DEA0(void)
{
    struct Unk026C *p = gUnk_0300026C;

    if (p->unk0C != 0)
    {
        p->unk0C->unk08 = 0xFFFFC000;
        p->unk0C->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->unk10 != 0)
    {
        p->unk10->unk08 = 0xFFFFC000;
        p->unk10->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->playerLevelTens != 0)
    {
        p->playerLevelTens->unk08 = 0xFFFFC000;
        p->playerLevelTens->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->playerLevelOnes != 0)
    {
        p->playerLevelOnes->unk08 = 0xFFFFC000;
        p->playerLevelOnes->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->playerStrengthTens != 0)
    {
        p->playerStrengthTens->unk08 = 0xFFFFC000;
        p->playerStrengthTens->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->playerStrengthOnes != 0)
    {
        p->playerStrengthOnes->unk08 = 0xFFFFC000;
        p->playerStrengthOnes->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->playerExpBar != 0)
    {
        p->playerExpBar->unk08 = 0xFFFFC000;
        p->playerExpBar->unk0C = 0xFFFFC000;
    }
    p = gUnk_0300026C;
    if (p->unk28 != 0)
    {
        p->unk28->unk08 = 0xF800;
        p->unk28->unk0C = 0xF800;
    }
    p = gUnk_0300026C;
    if (p->unk2C != 0)
    {
        p->unk2C->unk08 = 0xF800;
        p->unk2C->unk0C = 0xF800;
    }
    p = gUnk_0300026C;
    if (p->bitBeastExpBar != 0)
    {
        p->bitBeastExpBar->unk08 = 0xF800;
        p->bitBeastExpBar->unk0C = 0xF800;
    }
    p = gUnk_0300026C;
    if (p->bitBeastLevelTens != 0)
    {
        p->bitBeastLevelTens->unk08 = 0xF800;
        p->bitBeastLevelTens->unk0C = 0xF800;
    }
    p = gUnk_0300026C;
    if (p->bitBeastLevelOnes != 0)
    {
        p->bitBeastLevelOnes->unk08 = 0xF800;
        p->bitBeastLevelOnes->unk0C = 0xF800;
    }
    p = gUnk_0300026C;
    if (p->bladeStrengthTens != 0)
    {
        p->bladeStrengthTens->unk08 = 0xF800;
        p->bladeStrengthTens->unk0C = 0xF800;
    }
    p = gUnk_0300026C;
    if (p->bladeStrengthOnes != 0)
    {
        p->bladeStrengthOnes->unk08 = 0xF800;
        p->bladeStrengthOnes->unk0C = 0xF800;
    }

    p = gUnk_0300026C;
    if (p->unk28 != 0)
    {
        BtlObjPoolFree(p->unk28);
        gUnk_0300026C->unk28 = 0;
    }
    p = gUnk_0300026C;
    if (p->unk2C != 0)
    {
        BtlObjPoolFree(p->unk2C);
        gUnk_0300026C->unk2C = 0;
    }
    p = gUnk_0300026C;
    if (p->bitBeastLevelTens != 0)
    {
        BtlObjPoolFree(p->bitBeastLevelTens);
        gUnk_0300026C->bitBeastLevelTens = 0;
    }
    p = gUnk_0300026C;
    if (p->bitBeastLevelOnes != 0)
    {
        BtlObjPoolFree(p->bitBeastLevelOnes);
        gUnk_0300026C->bitBeastLevelOnes = 0;
    }
    p = gUnk_0300026C;
    if (p->bladeStrengthTens != 0)
    {
        BtlObjPoolFree(p->bladeStrengthTens);
        gUnk_0300026C->bladeStrengthTens = 0;
    }
    p = gUnk_0300026C;
    if (p->bladeStrengthOnes != 0)
    {
        BtlObjPoolFree(p->bladeStrengthOnes);
        gUnk_0300026C->bladeStrengthOnes = 0;
    }
    p = gUnk_0300026C;
    if (p->bitBeastExpBar != 0)
    {
        BtlObjPoolFree(p->bitBeastExpBar);
        gUnk_0300026C->bitBeastExpBar = 0;
    }

    VBlankIntrWait();
    _08073C40(*(void **)0x080BB888);

    gUnk_0300026C->unk48 = 0xFF;
    gMainWorkPtr->unk1838 |= 0xFFFF;
    gMainWorkPtr->unk183A |= 0xFFFF;
}
