#include "global.h"

void sub_08066224(struct Unk66224 *a, s32 index)
{
    register struct Unk66224Entry *current asm("r3");
    register struct Unk66224Entry *base asm("r1");
    register u16 flags asm("r4");
    struct Unk66224Entry *entry;
    struct Unk7069C *state;

    base = a->unk28;
    current = base + a->unk04;
    if (index < 0 || index >= a->unk00)
        return;
    flags = a->unk3C;
    if ((flags & 1) != 0)
        return;
    entry = base + index;
    current->unk14 = current->unk00->unk20;
    entry->unk14 = entry->unk00->unk24;
    a->unk14 = 0xFFFF - index * a->unk0C;
    a->unk04 = index;
    state = &a->unk40;
    sub_08070AD4(
        state,
        entry->unk00->callbacks[sub_08072F94()],
        a->unk2C->unk00->unk0A);
}
