#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

/* fn: sub_08033084 */
// @ 0x08033084

void PaletteAnimFrameCopy(struct Unk726E0 *a, void *dst, s32 idx);

void BtlPaletteFadeStep(struct Unk726E0 *a, u32 flag)
{
    struct Unk726E0 *dst;
    struct BattleWork **loc;
    struct BattleWork *w;
    s32 value;

    dst = a;
    flag <<= 24;
    if (flag != 0)
    {
        loc = gBattleWorkPtrLoc;
        w = *loc;
        w->fadeLevel += w->fadeStep;
        value = w->fadeLevel;
        if (value > 0x7FF)
        {
            value = 0x800;
            w->fadeActive = 0;
        }
        if (value <= 0)
        {
            value = 0;
            (*loc)->fadeActive = 0;
        }
        PaletteAnimFrameCopy(dst, (void *)0x05000000, value >> 8);
    }
}

/* fn: sub_080330F4 */
// @ 0x080330f4
void BtlPaletteFadeStart(s32 a)
{
    gBattleWork->fadeStep = a;
    gBattleWork->fadeActive = 1;
    if (a >= 0)
        gBattleWork->fadeLevel = 0;
    else
        gBattleWork->fadeLevel = 0x800;
}

/* fn: sub_0804438C */
// @ 0x0804438c
// Brightness fade over 11 steps: mode -1 lowers the level by 16 per step;
// mode 1 raises it by 16 per step (capped at 0xB8) while restoring DISPCNT.
void ScreenBrightnessFade(s8 mode)
{
    s32 i;
    s32 value;
    s16 level;

    TextSetActiveObject((struct Unk617C4 *)0x08119204, 0x080B7429);
    *(vu16 *)0x050001FE = 0;
    switch (mode)
    {
    case -1:
        i = 0;
        while (i <= 10)
        {
            value = sub_08060394();
            if (value > 0)
            {
                level = value - 0x10;
                if (level < 0)
                    level = 0;
                SfxSetMasterVolume(level);
            }
            sub_08061D00((u16)i, 0x0F);
            sub_08052FC8();
            sub_08052FC8();
            sub_08052FC8();
            i++;
        }
        SfxSetMasterVolume(0);
        ScreenWhiteoutClearPalettes();
        break;
    case 1:
        FieldUpdateFrame(0);
        FieldUpdateFrame(0);
        FieldUpdateFrame(0);
        if (gMainWorkPtr->unk1834 == 1)
            sub_08042718();
        i = 10;
        while (i >= 0)
        {
            value = sub_08060394();
            if (value <= 0xB7)
            {
                level = value + 0x10;
                if (level > 0xB8)
                    level = 0xB8;
                SfxSetMasterVolume(level);
            }
            sub_08061D00((u16)i, 0x0F);
            sub_08052FC8();
            sub_08052FC8();
            sub_08052FC8();
            REG_BLDCNT = 0;
            REG_BLDY = 0;
            REG_DISPCNT = gMainWorkPtr->unk0358;
            i--;
        }
        TextWindowClearActiveTiles();
        TextWindowLayout(1, 4, 0x1C, 0x10, 0x1BF);
        SfxSetMasterVolume(0xB8);
        break;
    }
}

/* fn: sub_08051BBC */
// @ 0x08051bbc
/* match-compiler: old_agbcc */
// Fade-in loop: steps the BLDALPHA weights (EVA down from 16, EVB up from 0)
// once per frame until EVA reaches 0.
void BlendFadeInLoop(void)
{
    struct MainWork **loc = gMainWorkPtrLoc;
    struct MainWork *work;

    work = *loc;
    work->unk17F0 = 0x10;
    work->unk17F2 = 0;
    do
    {
        struct MainWork *cur = *loc;
        cur->unk17F0--;
        cur->unk17F2++;
        REG_BLDCNT = 0x3748;
        REG_BLDALPHA = (cur->unk17F2 << 8) | cur->unk17F0;
        VBlankIntrWait();
        ((void (*)(void))gData_080BB888[0])();
        InputUpdate();
    } while ((*loc)->unk17F0 != 0);
}

/* fn: sub_080607BC */
// @ 0x080607bc
// Blend fade tick: writes BLDCNT/BLDY from the fade state and, every
// (unk09 + 1) frames, steps the BLDY level by unk02 (bouncing at 15, and
// resetting the step when the level returns to 0).
void BlendFadeTick(void)
{
    struct Unk0758 *state = gUnk_03000758;
    u32 mode = state->unk06;
    struct Unk0758 *fade;

    if (mode != 1)
        return;
    switch (state->unk07)
    {
    case 0:
        REG_BLDCNT = state->unk00;
        REG_BLDY = state->unk04;
        if (state->unk08 != 0)
        {
            state->unk08--;
            break;
        }
        state->unk08 = state->unk09;
        fade = gUnk_03000758;
        fade->unk04 += fade->unk02;
        if (fade->unk04 == 0x0F)
            fade->unk02 |= 0xFFFF;
        if (gUnk_03000758->unk04 == 0)
            gUnk_03000758->unk02 = mode;
        break;
    case 1:
        REG_BLDCNT = state->unk00;
        REG_BLDY = state->unk04;
        break;
    }
}

/* fn: sub_08062BF0 */
// @ 0x08062bf0

void FadeToWhite(u16 a)
{
    s16 b;
    void **src;

    b = 0;
    *(u16 *)0x04000050 = 0xFF;
    do
    {
        b = a + b;
        if (b > 0x1F)
        {
            b = 0x1F;
            a = 0;
        }
        *(u16 *)0x04000054 = b;
        VBlankIntrWait();
        src = (void **)0x080BB888;
        _08073C40(*src);
        SparklesUpdate();
    } while (b != 0x1F);
}

/* fn: sub_08062C38 */
// @ 0x08062c38
void FadeFromWhite(u16 arg0)
{
  u16 counter;
  s32 diff;
  counter = 0x1F;
  *((u16 *) 0x04000050) = 0xFF;
  do
  {
    counter = counter - arg0;
    diff = (s16) counter;
    if (diff < 0)
    {
      counter = 0;
      arg0 = 0;
    }
    *((u16 *) 0x04000054) = counter;
    VBlankIntrWait();
    _08073C40(*((void **) 0x080BB888));
    SparklesUpdate();
  }
  while (counter != 0);
}

/* fn: sub_08062C80 */
// @ 0x08062c80
void ScreenWhiteoutClearPalettes(void)
{
    void **src;

    VBlankIntrWait();
    WindowRegsClear();

    *(u16 *)0x04000050 = 0xFF;
    *(u16 *)0x04000054 = 0x1F;

    src = (void **)0x080BB8BC;
    _08073C4C(0, (void *)0x05000000, 0x200, *src);
    _08073C4C(0, (void *)0x05000200, 0x200, *src);
}

/* fn: sub_08065CD0 */
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
    BgScrollReset();
    handle = Lz77ImageBlit(scene, 0, s->unk00, 0, 1);
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
        InputUpdate();
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

/* fn: sub_08072A38 */
// @ 0x08072a38
/* match-compiler: old_agbcc */
// Palette fade over job->unk08 rows: each colour fades toward (d, e, f) if
// its rough luminance is below c, else toward (g, h, i); the fade amount
// starts at 0 and grows by (4 * b / rows) / 1024 per row.
void PaletteFadeByLuma(struct Unk72A38 *job, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h, u32 i)
{
    s32 step;
    s32 t;
    s32 row;
    s32 col;
    u16 *src;
    u16 *dst;
    s32 r, gr, bl;
    s32 lum;
    u16 color;

    step = b;
    step = ((step << 10) >> 8) / job->unk08;
    t = 0;
    dst = job->unk0C;
    for (row = 0; row < job->unk08; row++)
    {
        src = &job->unk00[job->unk04];
        for (col = 0; col < job->unk06; col++)
        {
            color = *src;
            r = 0x1F;
            r &= color;
            gr = (color & 0x3E0) >> 5;
            bl = (color & 0x7C00) >> 10;
            lum = (r >> 2) + (gr >> 1) + (bl >> 1);
            if (lum > 31)
                lum = 31;
            if (lum < (s32)c)
            {
                r += ((s32)(d - r) * t) >> 10;
                gr += ((s32)(e - gr) * t) >> 10;
                bl += ((s32)(f - bl) * t) >> 10;
            }
            else
            {
                r += ((s32)(g - r) * t) >> 10;
                gr += ((s32)(h - gr) * t) >> 10;
                bl += ((s32)(i - bl) * t) >> 10;
            }
            if (r > 31)
                r = 31;
            if (gr > 31)
                gr = 31;
            if (bl > 31)
                bl = 31;
            *dst++ = r + (gr << 5) + (bl << 10);
            src++;
        }
        t += step;
    }
}
