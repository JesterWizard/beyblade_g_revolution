#include "global.h"

// @ 0x08066224
#include "global.h"

void sub_08066224(struct Unk66224 *a, s32 index)
{
    register struct Unk66224 *r6 asm("r6");
    register s32 r2 asm("r2");
    register s32 r1 asm("r1");
    register s32 r0 asm("r0");
    register struct Unk66224Entry *current asm("r3");
    register u32 obj asm("r4");
    register struct Unk7069C *state asm("r5");
    struct Unk66224Entry *entry;

    r6 = a;
    r2 = index;
    r1 = r6->unk04;
    r0 = r1 << 3;
    r0 -= r1;
    r0 <<= 2;
    r1 = (s32)r6->unk28;
    current = (struct Unk66224Entry *)(r1 + r0);
    if (r2 < 0)
        return;
    if (r2 >= r6->unk00)
        return;
    r0 = 1;
    obj = r6->unk3C;
    r0 &= obj;
    if (r0 != 0)
        return;
    r0 = r2 << 3;
    r0 -= r2;
    r0 <<= 2;
    entry = (struct Unk66224Entry *)(r1 + r0);
    current->unk14 = current->unk00->unk20;
    obj = (u32)entry->unk00;
    entry->unk14 = ((struct Unk66224Object *)obj)->unk24;
    r6->unk14 = 0xFFFF - r2 * r6->unk0C;
    r6->unk04 = r2;
    state = &r6->unk40;
    r0 = sub_08072F94();
    r0 <<= 2;
    obj += 4;
    obj += r0;
    r1 = *(s32 *)obj;
    sub_08070AD4(state, (void *)r1, r6->unk2C->unk00->unk0A);
}

