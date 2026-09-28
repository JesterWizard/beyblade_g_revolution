#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

// @ 0x08065cd0
/* match-compiler: old_agbcc */
// Shows a scene: loads it and its palette, fades in, then runs frames until
// the timer expires or (if skippable) a key is pressed once the fade is done,
// and optionally fades out.
void sub_08065CD0(struct Unk65CD0 *s, u16 fade, void *check)
{
    u8 scene[0x88];
    void *handle;
    s16 timer;
    bool32 done;

    done = FALSE;
    timer = s->unk08;
    sub_08069894();
    handle = sub_08065E0C(scene, 0, s->unk00, 0, 1);
    BgPaletteLoad(s->unk04);
    VBlankIntrWait();
    REG_DISPCNT = 0x1140;
    switch (s->unk0A)
    {
    case -1:
        REG_BLDCNT = 0xFF;
        break;
    case 0:
        REG_BLDCNT = 0;
        break;
    case 1:
        REG_BLDCNT = 0xBF;
        break;
    }
    do
    {
        if ((s16)fade > 0)
        {
            s32 v = (s16)fade - s->unk0C;

            fade = v;
            if ((s16)fade < 0)
                fade = 0;
        }
        REG_BLDY = fade;
        VBlankIntrWait();
        ((void (*)(void))gData_080BB888[0])();
        sub_0806A6F8();
        if (check != NULL)
        {
            SaveDataVerify();
            check = NULL;
        }
        if ((gData_03004060 & 0xB) && fade == 0 && s->unk12 == 1)
            done = TRUE;
        if (timer > -1)
        {
            if (--timer == 0)
                done = TRUE;
        }
    } while (!done);
    if (s->unk0E != 0)
    {
        if (s->unk0E == -1)
            REG_BLDCNT = 0xFF;
        else
            REG_BLDCNT = 0xBF;
        FadeToWhite(s->unk10);
    }
    HeapFree(handle);
}

