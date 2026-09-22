#include "global.h"

// @ 0x0806a3a4
void *BtlObjAlloc(u32 size)
{
    struct Unk6A4D8Node *node;
    void *buffer;
    void **current;
    u32 work;
    u32 current_value;
    s32 *payload;
    s32 *next_payload;
    u32 r0;
    u32 r1;
    u32 r2;
    u32 r3;

    work = size;
    current = &gUnk_03000B30;
    current_value = (u32)*current;
    r2 = 0x03003F50;
    if (current_value == 0)
    {
        *current = *(void **)r2;
        r0 = 0x03000B3C;
        *(u32 *)r0 = current_value;
r0 = 0x03000B38;
*(u32 *)r0 = current_value;
    }
    buffer = sub_0806A580(*(struct Unk6A580 **)r2, 0x60);
    if (buffer == 0)
        DebugPrint((void *)0x083D1B00, (void *)work);

    r0 = work + 8;
    r1 = gUnk_03000B34;
    r2 = 0xFE;
    r2 <<= 10;
    r3 = (u32)*current;
    node = sub_0806A4D8(
        (void *)r0,
        (void *)r1,
        r2,
        (void *)r3,
        buffer,
        current);
    if (node != 0)
    {
        gUnk_03000B3C++;
        node->unk04 -= 8;
        payload = node->unk00;
        next_payload = payload + 1;
        node->unk00 = next_payload;
        r2 = 1;
        r2 = -r2;
        *payload = (s32)r2;
        next_payload = (s32 *)((u32)next_payload + node->unk04);
        *next_payload = (s32)r2;
    }
    return node;
}

