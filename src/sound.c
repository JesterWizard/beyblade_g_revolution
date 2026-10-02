#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_0806013C */
// @ 0x0806013c
void BgmStop(void)
{
    s32 v;

    v = gMainWorkPtr->bgmHandle;
    if (v != -1)
    {
        SoundStop(v);
        gMainWorkPtr->bgmHandle = -1;
        gMainWorkPtr->bgmTrack = -1;
    }
}

/* fn: sub_080601C4 */
// @ 0x080601c4
void SfxPlayInSlot(u32 a, u32 b)
{
    if (gMainWorkPtr->sfxHandles[a] != -1)
        SoundStop(gMainWorkPtr->sfxHandles[a]);

    gMainWorkPtr->sfxHandles[a] = (s32)SoundPlayIndexed(a, b);
    SoundSetVolume(gMainWorkPtr->sfxHandles[a], gMainWorkPtr->sfxVolume);
}

/* fn: sub_08060220 */
// @ 0x08060220
void SfxStopSlot(u32 idx)
{
    s32 v;

    v = gMainWorkPtr->sfxHandles[idx];
    if (v != -1)
    {
        SoundStop(v);
        gMainWorkPtr->sfxHandles[idx] = -1;
    }
}

/* fn: sub_08060254 */
// @ 0x08060254
void SfxPlayVariant(u32 a, u32 b, u32 c)
{
    SfxPlayInSlot(a, b + ((gUnk_03000180.unk00 >> 4) & c));
}

/* fn: sub_080602C0 */
// @ 0x080602c0
void SfxSetMasterVolume(u8 a)
{
    SoundSetMasterVolume(a);
}

/* fn: sub_080603A4 */
// @ 0x080603a4
void BgmSetVolume(u16 a)
{
    s32 v;

    v = gMainWorkPtr->bgmHandle;
    if (v != -1)
        SoundSetVolume(v, a);
    gMainWorkPtr->bgmVolume = a;
}

/* fn: sub_08060428 */
// @ 0x08060428
void sub_08060428(void)
{
    SfxPlayInSlot(0xD, 0x38);
}

/* fn: sub_080717F0 */
// @ 0x080717f0
/* match-compiler: old_agbcc */
void SoundSetMasterVolume(u32 a)
{
    if (a > 0x100)
        a = 0x100;
    *(u16 *)gUnk_030000CC = a;
}

/* fn: sub_08071808 */
// @ 0x08071808
u16 SoundGetMasterVolume(void)
{
    return *(u16 *)gUnk_030000CC;
}

/* fn: sub_08071B4C */
// @ 0x08071b4c
void SoundHwStop(void)
{
    u32 w = (u32)gData_04000084;
    u32 z = 0;
    u32 keep;
    u32 n;
    u32 scaled;
    u32 *sym;
    void *ptr;

    *(vu16 *)w = z;
    w -= 2;
    *(vu16 *)w = z;
    w += 0x42;
    z = w;
    keep = 0;
    *(vu32 *)w = keep;
    w += 0x0C;
    *(vu32 *)w = keep;
    w += 0x34;
    *(vu32 *)w = keep;
    w -= 4;
    *(vu32 *)w = keep;
    sym = gData_080BB8BC;
    ptr = (void *)gData_030040DC[0];
    n = gData_0300410C[0];
    scaled = n << 1;
    scaled += 0x20;
    n += scaled;
    _08073C4C(0, ptr, n, (void *)*sym);
    gData_030000C0[0] = keep;
    (void)z;
}

/* fn: sub_08071BA0 */
// @ 0x08071ba0
void SoundHwStart(void)
{
    u32 buffer;
    vu32 *timer;
    u32 rate;

    REG_SOUNDCNT_X = 0x80;
    REG_SOUNDCNT_H = 0xB04;
    REG_DMA1SAD = buffer = gData_030040DC[0];
    REG_DMA1DAD = REG_ADDR_FIFO_A;
    REG_DMA1CNT = 0xB6000000;
    REG_TM1CNT = (*(u16 *)0x030040D8 - 2) | 0xC40000;
    timer = &REG_TM0CNT;
    rate = *(u32 *)0x03004100;
    *timer = (0x10000 - _080741EC(0x1000000, rate)) | 0x800000;
    *(u32 *)0x030000B8 = buffer;
    *(u32 *)0x030000BC = 0x10000 - gData_0300410C[0];
}

/* fn: sub_08071E04 */
// @ 0x08071e04
void SoundChannelInit(struct SoundChannel *p, void *a, u32 n)
{
    p->state = 1;
    p->data = (s32)a;
    p->unk14 = 0;
    p->unk17 = 0;
    p->volume = 0x100;
    p->cursor = (s32)((u8 *)a + 0x10);
    if (n > 0x7F)
        n = 0x7F;
    p->rate = (s32)(*(void ***)gUnk_030000C4)[n];
    p->unk0C = 0;
    p->list = 0;
    p->listIndex = 0;
    p->unk24 = 0;
}

/* fn: sub_08071E44 */
// @ 0x08071e44
void SoundChannelInitFromList(struct SoundChannel *p, void *a, s16 *idx)
{
    s32 val;
    s32 zero;
    s32 one;
    s32 offset;

    offset = *idx;
    offset = offset << 2;
    offset = offset + (s32)a;
    val = *(s32 *)offset;
    zero = 0;
    one = 1;
    p->state = one;
    p->data = val;
    p->unk14 = zero;
    p->unk17 = 0;
    p->volume = 0x100;
    val += 0x10;
    p->cursor = val;
    p->rate = **(s32 **)0x030000C4;
    p->unk0C = zero;
    p->list = a;
    p->listIndex = idx;
    p->unk24 = one;
}

/* fn: sub_08071E84 */
// @ 0x08071e84
/* match-compiler: old_agbcc */
// Find the first free SoundChannel slot (*gData_030040C4 slots at *gData_030040E4).
// `i != -1` must stay a compare against a materialised -1; plain agbcc folds the
// entry test to `cmp r0,#0`. `id` has to be a local so the counter increment
// reuses the value just stored into unk18.
void *SoundPlayFromList(void *a, u32 b)
{
    struct SoundChannel *e = *(struct SoundChannel **)gData_030040E4;
    s32 i;
    u32 id;

    for (i = *(u8 *)gData_030040C4 - 1; i != -1; i--)
    {
        if (e->state == 0)
        {
            SoundChannelInitFromList(e, a, (s16 *)b);
            id = *(u32 *)gData_030000C8;
            e->handle = id;
            id++;
            *(u32 *)gData_030000C8 = id;
            return (void *)e->handle;
        }
        e++;
    }
    DebugPrint((void *)gData_083D2578);
    return (void *)-1;
}

/* fn: sub_08071EE4 */
// @ 0x08071ee4
/* match-compiler: old_agbcc */
// Same free-slot search as sub_08071E84, calling sub_08071E04 instead.
void *SoundPlay(void *a, u32 b)
{
    struct SoundChannel *e = *(struct SoundChannel **)gData_030040E4;
    s32 i;
    u32 id;

    for (i = *(u8 *)gData_030040C4 - 1; i != -1; i--)
    {
        if (e->state == 0)
        {
            SoundChannelInit(e, a, b);
            id = *(u32 *)gData_030000C8;
            e->handle = id;
            id++;
            *(u32 *)gData_030000C8 = id;
            return (void *)e->handle;
        }
        e++;
    }
    DebugPrint((void *)gData_083D2578);
    return (void *)-1;
}

/* fn: sub_08071F44 */
// @ 0x08071f44
/* match-compiler: old_agbcc */
// Find the first of *gData_030040C4 consecutive 0x28-byte records at *gData_030040E4
// whose +0x16 flag is set and whose +0x18 word equals `a`. The countdown is written
// `i != -1` (not `i >= 0`): retail materialises -1 once (`movs r0,#1; negs r0,r0`) and
// then compares the counter against a *register* holding it at both the entry guard and
// the back edge (`cmp r2,r0` / `cmp r2,r4`); `i >= 0` makes agbcc emit `cmp #0` plus a
// different loop shape (18/64).
// The two addresses MUST come from data_symbols.s: they are 0x20 apart, and with plain
// literals agbcc substitutes the second pool load with `subs r0, #0x20` (60 bytes,
// size mismatch). As symbols it emits two independent pool words like retail.
struct SoundChannel *SoundFindChannel(s32 a)
{
    struct SoundChannel *p = *(struct SoundChannel **)gData_030040E4;
    s32 i;

    for (i = *(u8 *)gData_030040C4 - 1; i != -1; i--)
    {
        if (p->state != 0 && p->handle == a)
            return p;
        p++;
    }
    return 0;
}

/* fn: sub_08071F84 */
// @ 0x08071f84
void SoundStop(s32 a)
{
    struct SoundChannel *p;

    p = SoundFindChannel(a);
    if (p != 0)
        p->state = 0;
}

/* fn: sub_08071F98 */
// @ 0x08071f98
void SoundPause(s32 a)
{
    struct SoundChannel *p;

    p = SoundFindChannel(a);
    if (p != 0)
        p->state = 2;
}

/* fn: sub_08071FAC */
// @ 0x08071fac

void SoundResume(s32 a)
{
    struct SoundChannel *p;

    p = SoundFindChannel(a);
    if (p != 0 && p->state == 2)
        p->state = 1;
}

/* fn: sub_08071FC8 */
// @ 0x08071fc8
void SoundSetVolume(s32 a, u32 b)
{
    struct SoundChannel *p;

    p = SoundFindChannel(a);
    if (p != 0)
    {
        if (b > 0x100)
            b = 0x100;
        p->volume = b;
    }
}

/* fn: sub_080720F0 */
// @ 0x080720f0
void *SoundPlayIndexed(u32 i, u32 b)
{
    struct Unk40D4 *p;

    p = *(struct Unk40D4 **)gUnk_030040D4;
    if (i < p->unk04)
        return SoundPlay(p->unk0C[i], b);
    return (void *)p->unk04;
}
