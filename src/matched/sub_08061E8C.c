#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08061e8c
void sub_08061E8C(struct Unk61E8C *obj, void *b, struct Unk61E8CSrc *src, u16 c, u16 d)
{
    u32 *sym = gData_080BB8BC;
    u32 size;
    struct Unk61E8CAlloc *alloc;
    void *inner;

    _08073C4C(0, obj, 0x28, (void *)*sym);
    obj->unk04 = b;
    obj->unk08 = src;
    obj->unk20 = src->unk04;
    obj->unk22 = src->unk05;
    obj->unk1C = c;
    obj->unk1E = d;
    size = 0x80;
    size <<= 2;
    alloc = HeapAlloc(size);
    obj->unk00 = alloc;
    if (alloc != 0) {
        inner = alloc->unk00;
        obj->unk0C = inner;
        _08073C4C(0, inner, size, (void *)*sym);
    }
}
