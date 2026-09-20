#define sub_0806A3A4 sub_0806A3A4_allocator_proto
#include "global.h"
#undef sub_0806A3A4

struct Unk6A4D8Node *sub_0806A3A4(struct Unk6A314 *state)
{
    register struct Unk6A4D8Node *node asm("r3");
    register void *buffer asm("r4");
    register void **current asm("r5");
    register struct Unk6A314 *work asm("r6");
    register u32 current_value asm("r1");
    register s32 *payload asm("r0");
    register s32 *next_payload asm("r1");
    register u32 reg2 asm("r2");

    work = state;
    current = &gUnk_03000B30;
    current_value = (u32)*current;
    reg2 = 0x03003F50;
    if (current_value == 0)
    {
        *current = *(void **)reg2;
        gUnk_03000B3C = current_value;
        gUnk_03000B38 = current_value;
    }
    buffer = sub_0806A580(*(struct Unk6A580 **)reg2, 0x60);
    if (buffer == 0)
        sub_08067B98((void *)0x083D1B00, work);
    node = sub_0806A4D8(
        (u8 *)work + 8,
        (void *)gUnk_03000B34,
        0x3F800,
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
        reg2 = -1;
        *payload = reg2;
        next_payload = (s32 *)((u8 *)next_payload + node->unk04);
        *next_payload = reg2;
    }
    return node;
}
