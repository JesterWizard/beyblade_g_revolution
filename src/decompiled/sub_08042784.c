#include "global.h"
#include "ram_map.h"

// @ 0x08042784
// 35/100 same-size. Retail keeps the ring pointer in r12 (`mov r12, r0`) across
// the whole body while still using r0 for the `ldsb` — agbcc will not allocate a
// plain local to r12 from any source shape tried (plain pointer local, reloaded
// field, address-taken). The rest of the body (index*2 / index*4 addressing into
// unk04/unk44/unkC4, the 0x370/0x374 sources, the `(i+1) & 0x1F` wrap) is right.
// Role: push {value, unk370, unk374} onto the 32-slot ring at *gUnk_03000538.
void sub_08042784(u16 a)
{
    struct Unk0538 *s = gUnk_03000538;
    s32 i = (s8)s->unk01;

    if (gMainWorkPtr->unk182C == 0)
        return;
    s->unk04[i] = a;
    s->unk44[i] = *(u32 *)((u8 *)gMainWorkPtr + 0x370);
    s->unkC4[i] = *(u32 *)((u8 *)gMainWorkPtr + 0x374);
    s->unk01 = (i + 1) & 0x1F;
}
