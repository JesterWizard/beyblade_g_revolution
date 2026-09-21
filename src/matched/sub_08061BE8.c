#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08061be8
void sub_08061BE8(void)
{
    u32 r0;
    u32 r1;
    struct Unk0798 *r2;
    u32 r3;
    struct Unk0798 **loc;
    struct Unk0770 *entry;
    void **handler_slot;

    r0 = gData_03000794[0] - 1;
    if ((s32)r0 < 0)
        return;

    r1 = (u32)gData_03000770;
    r0 <<= 3;
    entry = (struct Unk0770 *)(r0 + r1);
    handler_slot = (void **)entry->unk00;
    if (handler_slot == 0)
        return;

    loc = &gData_03000798;
    r2 = *loc;
    r0 = (u32)r2 + 0x5D;
    r0 = *(u8 *)r0;
    r1 = r0 << 14;
    r0 = 0xC0;
    r0 <<= 19;
    r1 += r0;
    r3 = (u32)gData_080BB8C0;
    r0 = (u32)*handler_slot;
    r2 = (struct Unk0798 *)((u32)r2 + 0x94);
    r2 = (struct Unk0798 *)(u32)*(u16 *)r2;
    r2 = (struct Unk0798 *)((u32)r2 << 5);
    r3 = *(u32 *)r3;
    _08073C4C((void *)r0, (void *)r1, (u32)r2, (void *)r3);

    r1 = (u32)*loc;
    r2 = (struct Unk0798 *)(u32)entry->unk04;
    r0 = r1 + 0x90;
    *(u16 *)r0 = (u16)(u32)r2;
    r0 = entry->unk06;
    r1 += 0x92;
    *(u16 *)r1 = (u16)r0;
}

