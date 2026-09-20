#include "global.h"

// @ 0x080312b0
#include "global.h"

// @ 0x080312b0
__attribute__((naked))
void sub_080312B0(struct Unk312EC *a, struct Unk705DC *b, u8 c, s32 d)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, lr}\n"
        "adds r4, r0, #0x0\n"
        "lsls r2, r2, #0x18\n"
        "lsrs r2, r2, #0x18\n"
        "ldrb r0, [r4, #0x08]\n"
        "cmp r0, #0x00\n"
        "bne _080312D2\n"
        "cmp r1, #0x00\n"
        "beq _080312D2\n"
        "ldrh r5, [r1, #0x14]\n"
        "lsrs r0, r5, #0x0C\n"
        "strb r2, [r4, #0x00]\n"
        "strb r0, [r4, #0x01]\n"
        "str r3, [r4, #0x04]\n"
        "str r1, [r4, #0x0C]\n"
        "movs r0, #0x01\n"
        "strb r0, [r4, #0x08]\n"
        "_080312D2:\n"
        "pop {r4, r5}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}


