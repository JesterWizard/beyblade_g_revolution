#include "global.h"

// @ 0x08062a74
__attribute__((naked))
void sub_08062A74(u8 a, void *src)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, lr}\n"
        "adds r5, r1, #0x0\n"
        "lsls r0, r0, #0x18\n"
        "lsrs r0, r0, #0x18\n"
        "ldr r6, _08062AB4 @ =0x030008D0\n"
        "ldr r1, [r6, #0x00]\n"
        "cmp r1, #0x00\n"
        "beq _08062AAE\n"
        "movs r4, #0x0F\n"
        "ands r4, r0\n"
        "adds r1, #0x40\n"
        "movs r0, #0x01\n"
        "lsls r0, r4\n"
        "ldrh r2, [r1, #0x00]\n"
        "orrs r0, r2\n"
        "strh r0, [r1, #0x00]\n"
        "ldr r2, _08062AB8 @ =0x080BB8C0\n"
        "lsls r1, r4, #0x05\n"
        "ldr r0, _08062ABC @ =0x05000200\n"
        "adds r1, r1, r0\n"
        "ldr r3, [r2, #0x00]\n"
        "adds r0, r5, #0x0\n"
        "movs r2, #0x20\n"
        "bl _08073C4C\n"
        "ldr r0, [r6, #0x00]\n"
        "lsls r4, r4, #0x02\n"
        "adds r0, r0, r4\n"
        "str r5, [r0, #0x00]\n"
        "_08062AAE:\n"
        "pop {r4, r5, r6}\n"
        "pop {r0}\n"
        "bx r0\n"
        "_08062AB4: .4byte 0x030008D0\n"
        "_08062AB8: .4byte 0x080BB8C0\n"
        "_08062ABC: .4byte 0x05000200\n"
    );
}

