#include "global.h"

// @ 0x0806105c
__attribute__((naked))
void sub_0806105C(void *a, u8 *s)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, lr}\n"
        "adds r6, r0, #0x0\n"
        "adds r5, r1, #0x0\n"
        "cmp r5, #0x00\n"
        "beq _08061082\n"
        "cmp r6, #0x00\n"
        "beq _08061082\n"
        "ldrb r1, [r5, #0x00]\n"
        "movs r4, #0x01\n"
        "cmp r1, #0x00\n"
        "beq _08061082\n"
        "_08061072:\n"
        "adds r0, r6, #0x0\n"
        "bl sub_08060E48\n"
        "adds r0, r5, r4\n"
        "ldrb r1, [r0, #0x00]\n"
        "adds r4, #0x01\n"
        "cmp r1, #0x00\n"
        "bne _08061072\n"
        "_08061082:\n"
        "pop {r4, r5, r6}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

