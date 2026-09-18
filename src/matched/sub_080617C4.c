#include "global.h"

// @ 0x080617c4
__attribute__((naked))
void sub_080617C4(struct Unk617C4 *a, u32 b)
{
    asm(
        ".syntax unified\n"
        "adds r2, r0, #0x0\n"
        "movs r0, #0x01\n"
        "ldrb r3, [r2, #0x0C]\n"
        "ands r0, r3\n"
        "cmp r0, #0x00\n"
        "beq _080617F8\n"
        "ldr r0, _080617FC @ =0x03000798\n"
        "ldr r3, [r0, #0x00]\n"
        "adds r0, r3, #0x0\n"
        "adds r0, #0x88\n"
        "str r2, [r0, #0x00]\n"
        "adds r0, #0x04\n"
        "str r1, [r0, #0x00]\n"
        "ldrb r0, [r2, #0x04]\n"
        "adds r1, r3, #0x0\n"
        "adds r1, #0xA0\n"
        "strh r0, [r1, #0x00]\n"
        "ldrb r0, [r2, #0x05]\n"
        "adds r2, r3, #0x0\n"
        "adds r2, #0xA2\n"
        "strh r0, [r2, #0x00]\n"
        "ldrh r1, [r1, #0x00]\n"
        "lsrs r1, r1, #0x02\n"
        "adds r0, r3, #0x0\n"
        "adds r0, #0x9C\n"
        "strh r1, [r0, #0x00]\n"
        "_080617F8:\n"
        "bx lr\n"
        ".byte 0x00, 0x00\n"
        "_080617FC: .4byte 0x03000798\n"
    );
}

