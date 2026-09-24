#include "global.h"
#include "data_symbols.h"

void sub_0804AC3C(struct Unk2F520 *a)
{
    struct Unk2F520 *obj;
    u32 pal;
    u32 cur;
    u32 base;
    void **fn;

    obj = a;
    pal = *(u8 *)&obj->unk2D5;
    cur = *(u8 *)&obj->unk2FC;
    sub_08061BE8();
    sub_0804AAF0(obj);
    cur <<= 24;
    cur = (u32)((s32)cur >> 8);
    base = 0xE0;
    base <<= 11;
    cur += base;
    cur >>= 16;
    TextRowSetPaletteBank(cur, 0xF, 4, 0x19);
    pal <<= 24;
    pal = (u32)((s32)pal >> 8);
    base = 0xE0;
    base <<= 11;
    pal += base;
    pal >>= 16;
    TextRowSetPaletteBank(pal, 0xE, 4, 0x19);
    VBlankIntrWait();
    fn = (void **)gData_080BB888;
    _08073C40(*fn);
    sub_0804AE94();
}
