#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802dea0
/* match-compiler: old_agbcc */
// gUnk_0300026C read through a volatile pointer: retail re-reads it for every
// entry, even across stores that cannot alias it.
#define HUD_PTR (*(struct StatusHud *volatile *)0x0300026C)

// Tears down the HUD: moves every HUD text entry off-screen (player entries to
// -0x4000, bit-beast/blade entries to 0xF800), frees the second group, waits a
// frame and runs the frame callback, then resets unk48 and MainWork unk1838/183A.
void sub_0802DEA0(void)
{
    struct Sprite *e;
    struct Sprite *obj;
    struct MainWork *work;

    e = HUD_PTR->unk0C;
    if (e != NULL)
    {
        e->unk08 = -0x4000;
        e->unk0C = -0x4000;
    }
    e = HUD_PTR->unk10;
    if (e != NULL)
    {
        e->unk08 = -0x4000;
        e->unk0C = -0x4000;
    }
    e = HUD_PTR->playerLevelTens;
    if (e != NULL)
    {
        e->unk08 = -0x4000;
        e->unk0C = -0x4000;
    }
    e = HUD_PTR->playerLevelOnes;
    if (e != NULL)
    {
        e->unk08 = -0x4000;
        e->unk0C = -0x4000;
    }
    e = HUD_PTR->playerStrengthTens;
    if (e != NULL)
    {
        e->unk08 = -0x4000;
        e->unk0C = -0x4000;
    }
    e = HUD_PTR->playerStrengthOnes;
    if (e != NULL)
    {
        e->unk08 = -0x4000;
        e->unk0C = -0x4000;
    }
    e = HUD_PTR->playerExpBar;
    if (e != NULL)
    {
        e->unk08 = -0x4000;
        e->unk0C = -0x4000;
    }
    e = HUD_PTR->unk28;
    if (e != NULL)
    {
        e->unk08 = 0xF800;
        e->unk0C = 0xF800;
    }
    e = HUD_PTR->unk2C;
    if (e != NULL)
    {
        e->unk08 = 0xF800;
        e->unk0C = 0xF800;
    }
    e = HUD_PTR->bitBeastExpBar;
    if (e != NULL)
    {
        e->unk08 = 0xF800;
        e->unk0C = 0xF800;
    }
    e = HUD_PTR->bitBeastLevelTens;
    if (e != NULL)
    {
        e->unk08 = 0xF800;
        e->unk0C = 0xF800;
    }
    e = HUD_PTR->bitBeastLevelOnes;
    if (e != NULL)
    {
        e->unk08 = 0xF800;
        e->unk0C = 0xF800;
    }
    e = HUD_PTR->bladeStrengthTens;
    if (e != NULL)
    {
        e->unk08 = 0xF800;
        e->unk0C = 0xF800;
    }
    e = HUD_PTR->bladeStrengthOnes;
    if (e != NULL)
    {
        e->unk08 = 0xF800;
        e->unk0C = 0xF800;
    }
    obj = HUD_PTR->unk28;
    if (obj != NULL)
    {
        BtlObjPoolFree(obj);
        HUD_PTR->unk28 = NULL;
    }
    obj = HUD_PTR->unk2C;
    if (obj != NULL)
    {
        BtlObjPoolFree(obj);
        HUD_PTR->unk2C = NULL;
    }
    obj = HUD_PTR->bitBeastLevelTens;
    if (obj != NULL)
    {
        BtlObjPoolFree(obj);
        HUD_PTR->bitBeastLevelTens = NULL;
    }
    obj = HUD_PTR->bitBeastLevelOnes;
    if (obj != NULL)
    {
        BtlObjPoolFree(obj);
        HUD_PTR->bitBeastLevelOnes = NULL;
    }
    obj = HUD_PTR->bladeStrengthTens;
    if (obj != NULL)
    {
        BtlObjPoolFree(obj);
        HUD_PTR->bladeStrengthTens = NULL;
    }
    obj = HUD_PTR->bladeStrengthOnes;
    if (obj != NULL)
    {
        BtlObjPoolFree(obj);
        HUD_PTR->bladeStrengthOnes = NULL;
    }
    obj = HUD_PTR->bitBeastExpBar;
    if (obj != NULL)
    {
        BtlObjPoolFree(obj);
        HUD_PTR->bitBeastExpBar = NULL;
    }
    VBlankIntrWait();
    ((void (*)(void))gData_080BB888[0])();
    HUD_PTR->unk48 = 0xFF;
    work = gMainWorkPtr;
    work->unk1838 |= 0xFFFF;
    work->unk183A |= 0xFFFF;
}
