#include "global.h"

// @ 0x0806b724
__attribute__((naked))
void sub_0806B724(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, lr}\n"
        "adds r4, r0, #0x0\n"
        "adds r5, r2, #0x0\n"
        "movs r2, #0x00\n"
        "ldrb r0, [r4, #0x00]\n"
        "adds r4, #0x01\n"
        "cmp r0, #0x00\n"
        "beq _0806B756\n"
        "ldr r6, _0806B760 @ =0x080BB748\n"
        "_0806B736:\n"
        "movs r3, #0x05\n"
        "cmp r0, #0x20\n"
        "beq _0806B74C\n"
        "adds r0, r0, r6\n"
        "ldrb r0, [r0, #0x00]\n"
        "adds r3, r5, #0x0\n"
        "cmp r1, #0x00\n"
        "beq _0806B74C\n"
        "adds r0, r1, r0\n"
        "ldrb r0, [r0, #0x00]\n"
        "subs r3, r3, r0\n"
        "_0806B74C:\n"
        "adds r2, r2, r3\n"
        "ldrb r0, [r4, #0x00]\n"
        "adds r4, #0x01\n"
        "cmp r0, #0x00\n"
        "bne _0806B736\n"
        "_0806B756:\n"
        "adds r0, r2, #0x0\n"
        "pop {r4, r5, r6}\n"
        "pop {r1}\n"
        "bx r1\n"
        ".byte 0x00, 0x00\n"
        "_0806B760: .4byte 0x080BB748\n"
    );
}

