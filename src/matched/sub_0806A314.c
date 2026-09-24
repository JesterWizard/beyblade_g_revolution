#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806a314
/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

void *sub_0806A314(struct Unk6A314 *state)
{
    struct Unk6A4D8Node *node;
    void *buffer;
    void **current;
    u32 current_value;
    s32 *payload;
    s32 *next_payload;
    u32 pool;
    u32 neg;

    current = &gUnk_03003F44;
    current_value = (u32)*current;
    pool = 0x03003F40;
    if (current_value == 0)
    {
        *current = *(void **)pool;
        gUnk_03003F48 = current_value;
        buffer = (void *)0x03000B40;
        *(u32 *)0x03000B40 = *(u32 *)buffer;
        gUnk_03003F4C = current_value;
    }
    buffer = sub_0806A580(*(void **)pool, 0x20);
    if (buffer == 0)
        DebugPrint((void *)0x083D1AC8, state);
    node = sub_0806A4D8(
        (void *)((u32)state + 8),
        (void *)0x03000B40,
        0xD0 << 6,
        *current,
        buffer,
        current);
    if (node != 0)
    {
        gUnk_03003F48++;
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

