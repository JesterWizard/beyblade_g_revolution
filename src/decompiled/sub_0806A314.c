#include "global.h"

struct Unk6A4D8Node *sub_0806A314(struct Unk6A314 *state)
{
    struct Unk6A4D8Node *node;
    void *buffer;
    void **current;
    struct Unk6A314 *work;
    s32 *payload;
    s32 *next_payload;
    u32 reg2;

    work = state;
    current = &gUnk_03003F44;
    reg2 = 0x03003F40;
    if (*current == 0)
    {
        *current = *(void **)reg2;
        gUnk_03003F48 = 0;
        gUnk_03003F4C = 0;
    }
    buffer = sub_0806A580(gUnk_03003F40, 0x20);
    if (buffer == 0)
        sub_08067B98((void *)0x083D1AC8, work);
    node = sub_0806A4D8(
        (u8 *)work + 8,
        gUnk_03000B40,
        0x3400,
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
        reg2 = -1;
        *payload = reg2;
        next_payload = (s32 *)((u8 *)next_payload + node->unk04);
        *next_payload = reg2;
    }
    return node;
}
