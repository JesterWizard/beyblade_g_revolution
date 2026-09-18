#include "global.h"

// @ 0x08034810
__attribute__((naked))
void sub_08034810(struct Unk346C0 *a, u32 b)
{
    asm(
        ".syntax unified\n"
        "push {lr}\n"
        "adds r2, r0, #0x0\n"
        "adds r3, r1, #0x0\n"
        "ldr r0, [r2, #0x00]\n"
        "cmp r0, #0x00\n"
        "beq _08034848\n"
        "ldr r0, [r0, #0x00]\n"
        "ldrh r0, [r0, #0x14]\n"
        "lsrs r1, r0, #0x0C\n"
        "movs r0, #0x05\n"
        "ands r0, r3\n"
        "cmp r0, #0x00\n"
        "bne _08034848\n"
        "movs r3, #0xB4\n"
        "lsls r3, r3, #0x02\n"
        "adds r0, r2, r3\n"
        "ldr r0, [r0, #0x00]\n"
        "cmp r1, r0\n"
        "bne _0803483A\n"
        "movs r1, #0x0F\n"
        "b _0803483C\n"
        "_0803483A:\n"
        "adds r1, r0, #0x0\n"
        "_0803483C:\n"
        "ldr r0, [r2, #0x00]\n"
        "ldr r0, [r0, #0x00]\n"
        "lsls r1, r1, #0x18\n"
        "lsrs r1, r1, #0x18\n"
        "bl sub_080705DC\n"
        "_08034848:\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

