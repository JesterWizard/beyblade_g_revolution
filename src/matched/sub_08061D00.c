#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08061d00
/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"
#include "data_symbols.h"

void sub_08061D00(u32 a, u32 b)
{
    u32 lo;
    u32 shifted;
    u32 packed;
    struct Unk0798 **slot;
    struct Unk0798 *obj;
    void *src;
    u32 vram;
    u32 destA;
    u8 bankA;
    u8 bankB;
    void **cpu;

    lo = (u16)a;
    shifted = b << 28;
    packed = shifted >> 16;
    packed |= shifted;
    packed |= 0x80 << 3;

    slot = &gData_03000798;
    src = sub_0806BB38((struct Unk6BB38 *)(*slot)->unk88, lo);

    obj = *slot;
    bankA = obj->unk5C;
    destA = bankA << 11;
    vram = 0xC0;
    vram <<= 19;
    destA += vram;
    bankB = obj->unk5D;

    _08073C4C(src, (void *)((bankB << 14) + vram), 0x20, *(void **)gData_080BB8C0);

    cpu = (void **)gData_080BB8BC;
    _08073C4C((void *)packed, (void *)destA, 0x80 << 4, *cpu);
}

