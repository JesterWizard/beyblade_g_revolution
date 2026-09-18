#include "global.h"

// @ 0x0806f430
__attribute__((naked))
void sub_0806F430(void)
{
    asm(
        ".syntax unified\n"
        "push {lr}\n"
        "ldr r0, _0806F444 @ =0x03004084\n"
        "ldr r0, [r0, #0x00]\n"
        "ldr r1, [r0, #0x14]\n"
        "movs r0, #0x08\n"
        "ands r0, r1\n"
        "cmp r0, #0x00\n"
        "beq _0806F448\n"
        "movs r0, #0x01\n"
        "b _0806F458\n"
        "_0806F444: .4byte 0x03004084\n"
        "_0806F448:\n"
        "movs r0, #0x10\n"
        "ands r1, r0\n"
        "cmp r1, #0x00\n"
        "bne _0806F456\n"
        "ldr r0, _0806F45C @ =0x083D2030\n"
        "bl sub_08067B98\n"
        "_0806F456:\n"
        "movs r0, #0x00\n"
        "_0806F458:\n"
        "pop {r1}\n"
        "bx r1\n"
        "_0806F45C: .4byte 0x083D2030\n"
    );
}

