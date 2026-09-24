#include "global.h"
#include "ram_map.h"

// @ 0x0806a3a4
/* match-compiler: old_agbcc */
void *HeapAlloc(u32 size)
{
    struct Unk6A4D8Node *node;
    void *buffer;
    void **current;
    u32 current_value;
    s32 *payload;
    s32 *next_payload;
    u32 pool;
    u32 neg;

    current = &gUnk_03000B30;
    current_value = (u32)*current;
    pool = 0x03003F50;
    if (current_value == 0)
    {
        *current = *(void **)pool;
        gUnk_03000B3C = current_value;
        buffer = (void *)0x03000B34;
        gUnk_03000B34 = *(u32 *)buffer;
        gUnk_03000B38 = current_value;
    }
    buffer = sub_0806A580(*(void **)pool, 0x60);
    if (buffer == 0)
        DebugPrint((void *)0x083D1B00, (void *)size);
    node = sub_0806A4D8(
        (void *)(size + 8),
        (void *)gUnk_03000B34,
        0xFE << 10,
        *current,
        buffer,
        current);
    if (node != 0)
    {
        gUnk_03000B3C++;
        node->unk04 -= 8;
        payload = node->unk00;
        next_payload = payload + 1;
        node->unk00 = next_payload;
        neg = 1;
        neg = -neg;
        *payload = (s32)neg;
        next_payload = (s32 *)((u32)next_payload + node->unk04);
        *next_payload = (s32)neg;
    }
    return node;
}
