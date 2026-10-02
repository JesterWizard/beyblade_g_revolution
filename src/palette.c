#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

/* fn: sub_08031294 */
// @ 0x08031294
/* match-compiler: old_agbcc */
// Set both byte flags to all-ones, then publish -1 in the +0x04 word and clear the
// +0x0C word / +0x08 byte. The two ORs must be written out inline with an explicit
// (u8) cast: a `u8 m = 0xFF;` local makes agbcc emit the `ldrb`/`orrs` pair in the
// opposite register order (5/28, and it adds a spurious stack frame).
void PaletteHighlightReset(struct Unk312EC *a)
{
    a->unk00 = (s8)((u8)a->unk00 | 0xFF);
    a->unk01 = (s8)((u8)a->unk01 | 0xFF);
    a->unk04 = -1;
    a->unk0C = 0;
    a->unk08 = 0;
}

/* fn: sub_080312B0 */
// @ 0x080312b0
/* match-compiler: old_agbcc */
void PaletteHighlightBegin(struct Unk312EC *a, struct Sprite *b, u8 c, s32 d)
{
    u16 val;
    u32 shifted;

    if (a->unk08 == 0 && b != NULL)
    {
        val = b->unk14;
        shifted = val >> 0xC;
        a->unk00 = c;
        a->unk01 = shifted;
        a->unk04 = d;
        a->unk0C = b;
        a->unk08 = 1;
    }
}

/* fn: sub_080312D8 */
// @ 0x080312d8

void PaletteHighlightEnd(struct Unk312EC *a)
{
    PaletteHighlightRestore(a);
    PaletteHighlightReset(a);
}

/* fn: sub_080312EC */
// @ 0x080312ec
void PaletteHighlightRestore(struct Unk312EC *a)
{
    if (a->unk0C != 0)
        TextEntrySetPaletteBank(a->unk0C, (u8)a->unk01);
}

/* fn: sub_08034414 */
// @ 0x08034414
void BtlPaletteRestoreBg(struct Unk33F30 *a)
{
    PaletteSnapshotRestoreBg();
}

/* fn: sub_08038438 */
// @ 0x08038438
/* match-compiler: old_agbcc */

// Acquire a palette slot for `palette`: find its table index, then either bump
// the refcount of the slot already holding it or claim the first free slot,
// copy the palette in and return the slot index (-1 if the pool is missing or
// full).
//
// The nested `do { } while (0)` wrappers are load-bearing. They add
// loop-depth weight so global alloc hands out r12/r8/r6/r7/r1/r2 as retail
// does, and they keep the two "found" blocks inside their loops (loop.c would
// otherwise move them out and hoist the gData_030003CC load).
s32 PaletteSlotAcquire(void *palette)
{
    s16 key;
    s16 i;

    key = 0;
    do { do { do {
    while (gData_08079068[(s16)key] != 0 && gData_08079068[(s16)key] != (u32)palette)
        key++;
    } while (0); } while (0); } while (0);
    if (gData_030003CC == NULL)
        return -1;
    i = 0;
    while (i < 16)
    {
        do { do { if ((s16)key == (s16)gData_030003CC->unk00[i])
        {
            gData_030003CC->unk22[i]++;
            return (s8)i;
        } } while (0); } while (0);
        do { do { i++; } while (0); } while (0);
    }
    for (i = 0; i < 16; i++)
    {
        do { if (((gData_030003CC->unk20 >> i) & 1) == 0)
        {
            gData_030003CC->unk00[i] = key;
            gData_030003CC->unk20 |= 1 << i;
            gData_030003CC->unk22[i] = 1;
            ((void (*)(u32, void *, u32))gData_080BB8C0[0])(gData_08079358[(s16)key], (void *)(0x05000200 + i * 32), 0x20);
            return (s8)i;
        } } while (0);
    }
    return -1;
}

/* fn: sub_080385DC */
// @ 0x080385dc
/* match-compiler: old_agbcc */
/* Release palette slots lo..hi: clear their in-use bits and reset key/refcount to 0xFFFF. */
void PaletteSlotsRelease(u16 lo, u16 hi)
{
    s32 i;
    struct Unk3CC *slots;

    for (i = lo; i <= hi; i++)
    {
        slots = gUnk_030003CC;
        slots->unk20 &= ~(1 << i);
        slots->unk00[i] |= 0xFFFF;
        slots->unk22[i] |= 0xFFFF;
    }
}

/* fn: sub_08038638 */
// @ 0x08038638
void PaletteSlotRefRelease(u16 a)
{
    u16 raw = gUnk_030003CC->unk22[a];

    if ((s16)gUnk_030003CC->unk22[a] > 0)
        gUnk_030003CC->unk22[a] = raw - 1;

    if ((s16)gUnk_030003CC->unk22[a] == 0)
        PaletteSlotsRelease(a, a);
}

/* fn: sub_08042B50 */
// @ 0x08042b50
void *BeybladeGetActorPalette(u32 i)
{
    u32 *t = gData_080910E8;

    if (t[i] == 0)
        DebugPrint((void *)0x083A2CD0, i);
    return (void *)t[i];
}

/* fn: sub_08062A74 */
// @ 0x08062a74
/* match-compiler: old_agbcc */
void ObjPalLoadSlot(u32 a, void *src)
{
    u32 r0;
    u32 r1;
    u32 r2;
    u32 r3;
    u32 r4;
    void *r5;
    u32 r6;

    r5 = src;
    a <<= 24;
    a >>= 24;
    r6 = (u32)&gUnk_030008D0;
    r1 = *(u32 *)r6;
    if (r1 == 0)
        goto done;
    r4 = 0x0F;
    r4 &= a;
    r1 += 0x40;
    r0 = 1;
    r0 <<= r4;
    r2 = *(u16 *)r1;
    r0 |= r2;
    *(u16 *)r1 = (u16)r0;
    r2 = 0x080BB8C0;
    r2 = 0x080BB8C0;
    r1 = (r4 << 5) + 0x05000200;
    r3 = *(u32 *)r2;
    r0 = (u32)r5;
    r2 = 0x20;
    _08073C4C((void *)r0, (void *)r1, r2, (void *)r3);
    r0 = *(u32 *)r6;
    r4 <<= 2;
    r0 += r4;
    *(void **)r0 = r5;
done:
    return;
}

/* fn: sub_08062AC0 */
// @ 0x08062ac0

// @ 0x08062ac0
void ObjPaletteSlotsReset(void)
{
    if (gUnk_030008D0 != 0)
    {
        _08073C4C(0, (void *)gUnk_030008D0, 0x44, (void *)gData_080BB8BC[0]);
        _08073C4C(0, (void *)gData_05000200, 0x200, (void *)gData_080BB8BC[0]);
    }
}

/* fn: sub_08062AF8 */
// @ 0x08062af8
/* match-compiler: old_agbcc */
// Find `table[key]` in the 16-slot palette pool, or claim a free slot, upload
// the 32-byte palette to OBJ palette RAM and return the slot index (-1 if full).
s32 ScenePaletteAcquire(void *table, void *key)
{
    void **slot;
    void *entry;
    s32 i;
    u32 one;
    struct Unk62A74 **loc;
    u16 mask;
    u8 *dst;

    if (table == 0)
        return -1;
    if (gUnk_030008D0 == 0)
        return -1;
    entry = ((void **)table)[(u32)key];

    slot = gUnk_030008D0->unk00;
    for (i = 0; i <= 0x0F; i++)
    {
        if (*slot == entry)
            return (s8)i;
        slot++;
    }

    i = 0;
    loc = &gUnk_030008D0;
    one = 1;
    dst = (u8 *)0x05000200;
    for (; i <= 0x0F; i++)
    {
        mask = (*loc)->unk40;
        if (((mask >> i) & one) == 0)
        {
            (*loc)->unk40 = mask | (one << i);
            if ((gMainWorkPtr->unk1808 & 0x800) == 0)
                _08073C4C(entry, dst, 0x20, (void *)gData_080BB8C0[0]);
            (*loc)->unk00[i] = entry;
            return (s8)i;
        }
        dst += 0x20;
    }
    return -1;
}

/* fn: sub_08062B9C */
// @ 0x08062b9c
/* match-compiler: old_agbcc */

void ObjPaletteSlotsReleaseRange(u32 arg0, u32 arg1)
{
    s32 hi;
    s32 lo;
    s32 i;
    s32 tmp;
    struct Unk62A74 *slot;

    lo = arg0 & 0xF;
    hi = arg1 & 0xF;
    tmp = hi;
    if ((u32)lo > (u32)hi)
    {
        hi = lo;
        lo = tmp;
    }

    for (i = lo; i <= hi; i++)
    {
        slot = gUnk_030008D0;
        slot->unk40 &= ~(1 << i);
        slot->unk00[i] = 0;
    }
}

/* fn: sub_08062CC8 */
// @ 0x08062cc8
void ObjPaletteGetRgb(u32 idx, u8 *out)
{
    u32 shifted;
    u32 base;
    u16 color;
    u32 sh;
    u32 *p;

    shifted = idx << 24;
    base = 0x05000200;
    sh = 23;
    p = &shifted;
    shifted = *p >> sh;
    shifted = shifted + base;
    color = *(u16 *)shifted;
    out[0] = (u8)(color & 0x1F);
    out[1] = (u8)((color & 0x3E0) >> 5);
    out[2] = (u8)((color & 0x7C00) >> 10);
}

/* fn: sub_08062CF4 */
// @ 0x08062cf4
/* match-compiler: old_agbcc */

// @ 0x08062cf4
// Pack an RGB byte triple into BGR555 and store it as OBJ palette entry idx.
// The `pal` local hoisting the palette base is load-bearing: it keeps the base
// live across the packing so agbcc gives it r5 (retail) instead of loading it
// into a late scratch. old_agbcc is required for the r5/r6 split.
void ObjPaletteSetRgb(u8 idx, u8 *rgb)
{
    u16 *pal;
    u16 c;
    u32 mask;

    pal = gData_05000200;
    mask = 0x1F;
    c = (rgb[0] & mask) | ((rgb[1] & mask) << 5) | ((rgb[2] & mask) << 10);
    pal[idx] = c;
}

/* fn: sub_08062D24 */
// @ 0x08062d24
void BgPaletteGetRgb(u32 idx, u8 *out)
{
  u32 shifted = idx << 24;
  u32 *new_var;
  u32 base = 0x05000000;
  u16 color;
  shifted = shifted >> 23;
  new_var = &shifted;
  shifted = (*new_var) + base;
  color = *((u16 *) shifted);
  out[0] = color & 0x1F;
  out[1] = (color & 0x3E0) >> 5;
  out[2] = (color & 0x7C00) >> 10;
}

/* fn: sub_08062D50 */
// @ 0x08062d50

// @ 0x08062d50
/* match-compiler: old_agbcc */
// Pack an RGB byte triple into BGR555 and store it at BG palette entry idx.
// Same shape as sub_08062CF4: `pal` hoists the base (0x05000000 materialises as
// `movs r5,#0xA0; lsls r5,#0x13`) and `mask` gives the three 0x1F constants
// retail reuses. agbcc picks r6 for the base and r5 for the byte temp, so
// old_agbcc is required for the r5/r6 split.
void BgPaletteSetRgb(u8 idx, u8 *rgb)
{
    u16 *pal;
    u16 c;
    u32 mask;

    pal = (u16 *)0x05000000;
    mask = 0x1F;
    c = (rgb[0] & mask) | ((rgb[1] & mask) << 5) | ((rgb[2] & mask) << 10);
    pal[idx] = c;
}

/* fn: sub_08062D80 */
// @ 0x08062d80
void BgPaletteGetRgb(u32 idx, u8 *out);
void BgPaletteSetRgb(u32 idx, struct Unk62D50 *rgb);

// Walk palette indices a..b. c == 0 adds d to each RGB byte and clamps at 31;
// c == 1 subtracts d and clamps at 0. Stores are batched before the clamps so
// the first sum stays in r1; `v0 <<= 24; v0 >>= 24` is the in-place sign extend.
void BgPaletteShiftRange(u8 a, u8 b, u8 c, u8 d)
{
    struct Unk62D50 rgb;
    s16 i;
    u8 idx;
    s32 v0;

    if (a >= b)
        goto done;
    if (c == 0)
        goto add;
    if (c == 1)
        goto sub;
    goto done;

add:
    for (i = a; i <= b; i++)
    {
        idx = (u8)i;
        BgPaletteGetRgb(idx, (u8 *)&rgb);
        v0 = rgb.unk00 + d;
        rgb.unk00 = v0;
        rgb.unk01 = d + rgb.unk01;
        rgb.unk02 = d + rgb.unk02;
        v0 <<= 24;
        v0 >>= 24;
        if (v0 > 31)
            rgb.unk00 = 31;
        if ((s8)rgb.unk01 > 31)
            rgb.unk01 = 31;
        if ((s8)rgb.unk02 > 31)
            rgb.unk02 = 31;
        BgPaletteSetRgb(idx, &rgb);
    }
    goto done;

sub:
    for (i = a; i <= b; i++)
    {
        idx = (u8)i;
        BgPaletteGetRgb(idx, (u8 *)&rgb);
        v0 = rgb.unk00 - d;
        rgb.unk00 = v0;
        rgb.unk01 = rgb.unk01 - d;
        rgb.unk02 = rgb.unk02 - d;
        v0 <<= 24;
        if (v0 < 0)
            rgb.unk00 = 0;
        if (((s32)rgb.unk01 << 24) < 0)
            rgb.unk01 = 0;
        if (((s32)rgb.unk02 << 24) < 0)
            rgb.unk02 = 0;
        BgPaletteSetRgb(idx, &rgb);
    }

done:
    return;
}

/* fn: sub_08062E88 */
// @ 0x08062e88
void ObjPaletteGetRgb(u32 idx, u8 *out);
void ObjPaletteSetRgb(u32 idx, struct Unk62D50 *rgb);

// Twin of sub_08062D80. Reads with sub_08062CC8 and writes with sub_08062CF4.
void ObjPaletteShiftRange(u8 a, u8 b, u8 c, u8 d)
{
    struct Unk62D50 rgb;
    s16 i;
    u8 idx;
    s32 v0;

    if (a >= b)
        goto done;
    if (c == 0)
        goto add;
    if (c == 1)
        goto sub;
    goto done;

add:
    for (i = a; i <= b; i++)
    {
        idx = (u8)i;
        ObjPaletteGetRgb(idx, (u8 *)&rgb);
        v0 = rgb.unk00 + d;
        rgb.unk00 = v0;
        rgb.unk01 = d + rgb.unk01;
        rgb.unk02 = d + rgb.unk02;
        v0 <<= 24;
        v0 >>= 24;
        if (v0 > 31)
            rgb.unk00 = 31;
        if ((s8)rgb.unk01 > 31)
            rgb.unk01 = 31;
        if ((s8)rgb.unk02 > 31)
            rgb.unk02 = 31;
        ObjPaletteSetRgb(idx, &rgb);
    }
    goto done;

sub:
    for (i = a; i <= b; i++)
    {
        idx = (u8)i;
        ObjPaletteGetRgb(idx, (u8 *)&rgb);
        v0 = rgb.unk00 - d;
        rgb.unk00 = v0;
        rgb.unk01 = rgb.unk01 - d;
        rgb.unk02 = rgb.unk02 - d;
        v0 <<= 24;
        if (v0 < 0)
            rgb.unk00 = 0;
        if (((s32)rgb.unk01 << 24) < 0)
            rgb.unk01 = 0;
        if (((s32)rgb.unk02 << 24) < 0)
            rgb.unk02 = 0;
        ObjPaletteSetRgb(idx, &rgb);
    }

done:
    return;
}

/* fn: sub_08062F90 */
// @ 0x08062f90
typedef void (*CpuCopyFunc)(const void *, void *, u32);

// Snapshots BG and OBJ palette RAM into two freshly allocated 0x200-byte
// buffers, unless a snapshot is already held (see sub_0806306C).
void PaletteSnapshotSave(void)
{
    bool32 bgAllocated;

    if (gData_030008DC != NULL || gData_030008D8 != NULL
        || gData_030008E0 != NULL || gData_030008D4 != NULL)
        return;
    gData_030008E0 = HeapAlloc(0x200);
    gData_030008D4 = HeapAlloc(0x200);
    if ((bgAllocated = gData_030008E0 != NULL) || gData_030008D4 != NULL)
    {
        gData_030008DC = *gData_030008E0;
        gData_030008D8 = *gData_030008D4;
        ((CpuCopyFunc)gData_080BB8C0[0])((void *)0x05000000, gData_030008DC, 0x200);
        ((CpuCopyFunc)gData_080BB8C0[0])((void *)0x05000200, gData_030008D8, 0x200);
    }
}

/* fn: sub_0806306C */
// @ 0x0806306c

// @ 0x0806306c
void PaletteSnapshotRestore(void)
{
    u32 *d;

    if (gUnk_030008DC != 0 && gUnk_030008D8 != 0 && gUnk_030008E0 != 0 && gUnk_030008D4 != 0)
    {
        d = gData_080BB8C0;
        _08073C4C(gUnk_030008DC, (void *)0x05000000, 0x200, (void *)d[0]);
        _08073C4C(gUnk_030008D8, (void *)gData_05000200, 0x200, (void *)d[0]);
        if (gUnk_030008E0 != 0)
        {
            HeapFree(gUnk_030008E0);
            gUnk_030008E0 = 0;
        }
        if (gUnk_030008D4 != 0)
        {
            HeapFree(gUnk_030008D4);
            gUnk_030008D4 = 0;
        }
        gUnk_030008DC = 0;
        gUnk_030008D8 = 0;
    }
}

/* fn: sub_08063104 */
// @ 0x08063104

// @ 0x08063104
void PaletteSnapshotRestoreBg(void)
{
    void **slotA;
    void **slotB;
    void *srcA;
    u32 *d;

    slotA = &gUnk_030008DC;
    srcA = *slotA;
    if (srcA != 0)
    {
        slotB = &gUnk_030008E0;
        if (*slotB != 0)
        {
            d = gData_080BB8C0;
            _08073C4C(srcA, (void *)0x05000000, 0x200, (void *)d[0]);
            if (*slotB != 0)
            {
                HeapFree(*slotB);
                *slotB = 0;
            }
            *slotA = 0;
        }
    }
}

/* fn: sub_080679A4 */
// @ 0x080679a4
void BgPaletteLoad(void *src)
{
    void **cpuSet;
    u32 dst;
    u32 n;

    cpuSet = (void **)0x080BB8C0;
    dst = 0xA0;
    dst <<= 19;
    n = 0x80;
    n <<= 2;
    _08073C4C(src, (void *)dst, n, *cpuSet);
}

/* fn: sub_080679C0 */
// @ 0x080679c0
void ObjPaletteLoad(void *src)
{
    void **cpuSet;
    void *dst;
    u32 n;

    cpuSet = (void **)0x080BB8C0;
    dst = (void *)0x05000200;
    n = 0x80;
    n <<= 2;
    _08073C4C(src, dst, n, *cpuSet);
}

/* fn: sub_080726E0 */
// @ 0x080726e0
void PaletteAnimFrameCopy(struct Unk726E0 *a, void *dst, s32 idx)
{
    void *src;
    void **cpuSet;
    u16 width;

    if (idx < a->unk08)
    {
        cpuSet = (void **)0x080BB8C0;
        width = a->unk06;
        src = (void *)((u32)a->unk0C + idx * width * 2);
        a = (struct Unk726E0 *)(u32)a->unk04;
        _08073C4C(src, (void *)((u32)dst + (u32)a * 2), width * 2, *cpuSet);
    }
}
