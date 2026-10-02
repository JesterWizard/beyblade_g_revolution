#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_08060468 */
// @ 0x08060468
void WindowEffectCreate(void)
{
    void **slotA;
    void **slotB;
    void **fn;
    void *p;
    void *q;

    slotA = (void **)gUnk_03000750;
    *slotA = 0;
    slotB = (void **)gUnk_0300075C;
    *slotB = 0;
    p = HeapAlloc(0x18);
    *slotB = p;
    if (p != 0)
    {
        q = *(void **)p;
        *slotA = q;
        fn = (void **)0x080BB8BC;
        _08073C4C((void *)0, q, 0x18, *fn);
    }
}

/* fn: sub_080604A4 */
// @ 0x080604a4
void WindowEffectDestroy(void)
{
    void *p;

    p = *(void **)gUnk_0300075C;
    if (p != 0)
    {
        HeapFree(p);
        *(void **)gUnk_0300075C = 0;
        *(void **)gUnk_03000750 = 0;
    }
}

/* fn: sub_080604C8 */
// @ 0x080604c8
/* match-compiler: old_agbcc */
void WindowRegsApply(void)
{
    struct WindowRegs *p = *(struct WindowRegs **)gUnk_03000750;
    u32 w;

    w = p->win0Left;
    w <<= 8;
    w |= p->win0Right;
    p->win0H = w;
    p->win1H = (p->win1Left << 8) | p->win1Right;
    p->win0V = (p->win0Top << 8) | p->win0Bottom;
    if (1)
    {
        if (p)
        {
            p->win1V = (p->win1Top << 8) | p->win1Bottom;
            p->winIn = (p->win1In << 8) | p->win0In;
            p->winOut = (p->objWinIn << 8) | p->outside;
            *(vu16 *)gData_04000040 = (u16)w;
            w = (u32)gData_04000042;
            *(u16 *)w = p->win1H;
            w += 2;
            *(u16 *)w = p->win0V;
            w += 2;
            *(u16 *)w = p->win1V;
            w += 2;
            *(u16 *)w = p->winIn;
            w += 2;
        }
        else
        {
            p->win1V = (p->win1Top << 8) | p->win1Bottom;
            p->winIn = (p->win1In << 8) | p->win0In;
            p->winOut = (p->objWinIn << 8) | p->outside;
            *(vu16 *)gData_04000040 = (u16)w;
            w = (u32)gData_04000042;
            *(u16 *)w = p->win1H;
            w += 2;
            *(u16 *)w = p->win0V;
            w += 2;
            *(u16 *)w = p->win1V;
            w += 2;
            *(u16 *)w = p->winIn;
            w += 2;
        }
    }
    *(u16 *)w = p->winOut;
}

/* fn: sub_080608D4 */
// @ 0x080608d4
void WindowRegsClear(void)
{
    u16 *p;
    u16 z;

    p = (u16 *)0x04000040;
    z = 0;
    *p = z;
    p++;
    *p = z;
    p++;
    *p = z;
    p++;
    *p = z;
    p++;
    *p = z;
    p++;
    *p = z;
}

/* fn: sub_080691E4 */
// @ 0x080691e4
// Sprite dimensions for OAM shape/size bits (b >> 14): with flags bit 0 a
// square of 2^(size+4) pixels, else the fixed wide/tall table. Stores the
// log2 width/height in unk5F/unk60 and returns the tile byte count.
u32 OamShapeToSize(struct Unk691E4 *a, u16 b, u16 flags)
{
    s32 size;
    s32 shape;
    u32 result;

    size = b >> 14;
    shape = size;
    if (flags & 1)
    {
        result = 1 << (size * 2 + 8);
        size += 4;
        a->unk5F = size;
        a->unk60 = size;
    }
    else
    {
        switch (shape)
        {
        case 0:
            result = 0x800;
            a->unk5F = 5;
            a->unk60 = 5;
            break;
        case 1:
            result = 0x1000;
            a->unk5F = 6;
            a->unk60 = 5;
            break;
        case 2:
            result = 0x1000;
            a->unk5F = 5;
            a->unk60 = 6;
            break;
        case 3:
            result = 0x2000;
            a->unk5F = 6;
            a->unk60 = 6;
            break;
        }
    }
    return result;
}

/* fn: sub_0806FF58 */
// @ 0x0806ff58
/* match-compiler: old_agbcc */
// Initialise sprite `dst` from template `src` at (x, y): pack the OAM
// attribute words (shape/size from src->unk07; 16-colour flag and palette
// from src->unk0C; object mode + mosaic; flip; priority) and point unk28 at
// the template graphics.
// The `mode` temporary keeps agbcc from re-associating the 0x1000 constant.
void SpriteInitFromTemplate(struct Sprite *dst, struct Unk6FF58Src *src, u32 x, u32 y, u8 objMode, u8 priority, u8 flip, u16 h)
{
    s8 shapeSize;
    u8 palette;
    u32 mode;

    shapeSize = src->unk07;
    palette = src->unk0C;
    dst->unk2C = src;
    dst->unk1C = flip;
    dst->unk08 = x;
    dst->unk0C = y;
    dst->unk10 = ((shapeSize & 3) << 14) | ((~palette & 1) << 13) | (mode = ((objMode & 3) << 10) | 0x1000)
               | ((shapeSize & 0xC) << 28) | ((flip & 3) << 28);
    dst->unk14 = (((palette >> 1) & 0xF) << 12) | ((priority & 3) << 10);
    dst->unk28 = (u8 *)src + (src->unk1C != 0 ? src->unk1C : src->unk10);
    dst->unk16 = src->unk06;
    dst->unk18 = h;
    dst->unk1A = 0xFFFF;
    dst->unk1C = 0;
    dst->unk20 = 0;
    dst->unk24 = -1;
    dst->unk1E = 0;
}

/* fn: sub_08070354 */
// @ 0x08070354
/* match-compiler: old_agbcc */

void SpriteApplyAffine(struct Unk70354 *state, u16 b, u16 c, u8 d)
{
    u16 count = (u16)c;
    u8 mode = d;
    u32 flags;
    struct AffineObj *object;
    u32 value;

    object = state->unk30;
    flags = state->unk10;
    if (object != 0)
    {
        object = state->unk30 = BtlObjSetAffine(object, b, count, mode);
        if (object == 0)
        {
            flags &= 0xC1FFFCFF;
            flags |= (u32)(state->unk1C & 3) << 28;
        }
    }
    else
    {
        object = state->unk30 = BtlObjSetAffine(0, b, count, mode);
        if (object != 0)
        {
            flags &= 0xC1FFFDFF;
            value = object->unk08 & (0xF8 << 2);
            value <<= 20;
            value |= 0x80 << 1;
            flags |= value;
        }
    }
    if (object != 0)
    {
        if (object->angle != 0)
        {
            if (object->scaleX > 0xB0 || object->scaleY > 0xB0)
                flags |= 0x200;
            else
                flags &= 0xFFFFFDFF;
        }
        else
        {
            if (object->scaleX > 0x100 || object->scaleY > 0x100)
                flags |= 0x200;
            else
                flags &= 0xFFFFFDFF;
        }
    }
    state->unk10 = flags;
}

/* fn: sub_080705A4 */
// @ 0x080705a4
void SpriteSetObjMode(struct Sprite *a, s32 b)
{
    u32 t;
    u32 v;
    u32 mask;

    t = b << 24;
    v = a->unk10;
    v &= 0xFFFFF3FF;
    mask = 0xC0 << 18;
    mask &= t;
    mask >>= 14;
    a->unk10 = v | mask;
}

/* fn: sub_080705CC */
// @ 0x080705cc
void AffineObjLock(struct AffineObj *a)
{
    a->locked = 1;
}

/* fn: sub_080705D4 */
// @ 0x080705d4
void AffineObjUnlock(struct AffineObj *a)
{
    a->locked = 0;
}
