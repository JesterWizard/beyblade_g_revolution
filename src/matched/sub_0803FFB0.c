#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803ffb0
#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

// @ 0x0803ffb0
/* match-compiler: old_agbcc */
void sub_0803FFB0(struct MainWork *a, s32 b)
{
    struct MainWork *main;
    s32 ypos;
    s32 v;
    u8 *base;
    u32 off;
    void *str;
    u32 t0;
    u16 t1;
    u16 t2;
    s32 x;
    struct Unk40088Target **slot;

    main = gMainWorkPtr;
    if (main->unk1829 == 0)
        return;

    b = b - 1;
    v = 1;
    if (b <= 1)
        v = b;
    ypos = (v << 4) + 0x74;
    if (main->unk184F != 0)
        ypos = 0x8F;

    base = (u8 *)gUnk_0300047C;
    b = b << 2;
    off = 0x81;
    off <<= 4;
    base = base + off;
    str = *(void **)(base + b);

    t0 = sub_08061A98();
    t1 = sub_08061AA8();
    t2 = sub_080617B4();
    x = sub_08073988((const u8 *)str, (const u8 *)t0, t1, t2);
    x = (x >> 1) + 0x79;

    slot = &a->unk0274;
    if (*slot != 0)
    {
        BtlObjPoolFree(*slot);
        *slot = 0;
    }
    *slot = BtlObjPoolAlloc(0);

    sub_0806FF58(*slot, (void *)0x08118CF0, x << 8, ypos << 8, 1, 0, 0, 0);
    TextEntrySetPaletteBank((struct Unk705DC *)*slot, 2);

    a->unk0304 = 4;
}

