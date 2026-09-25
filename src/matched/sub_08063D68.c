#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08063d68
#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

// @ 0x08063d68
/* match-compiler: old_agbcc */
void sub_08063D68(struct MainWork *a, s32 b)
{
    s32 ypos;
    u8 *base;
    u32 off;
    void *str;
    u32 t0;
    u16 t1;
    u16 t2;
    s32 x;
    struct Unk40088Target **slot;
    void **srcLoc;
    void *src;
    void *graphic;
    void *dst;

    if (gMainWorkPtr->unk1829 == 0)
        return;

    b = b - 1;
    ypos = 0x84;
    if (b == 0)
        ypos = 0x74;

    base = *(u8 **)0x030008E4;
    b = b << 2;
    off = 0x98;
    off <<= 2;
    base = base + off;
    str = *(void **)(base + b);

    t0 = sub_08061A98();
    t1 = sub_08061AA8();
    t2 = sub_080617B4();
    x = TextMeasureWidth((const u8 *)str, (const u8 *)t0, t1, t2);
    x = (x >> 1) + 0x7A;

    slot = &a->unk0274;
    if (*slot != 0)
    {
        BtlObjPoolFree(*slot);
        *slot = 0;
    }
    *slot = BtlObjPoolAlloc(0);

    sub_0806FF58(*slot, (void *)0x08118CF0, x << 8, ypos << 8, 1, 0, 0, 0);

    a->unk0304 = 4;

    srcLoc = (void **)gData_080BB8C0;
    graphic = (void *)0x0826E320;
    dst = (void *)0x05000200;
    src = *srcLoc;
    _08073C4C(graphic, dst, 0x20, src);
}

