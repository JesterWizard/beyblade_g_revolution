#include "global.h"

// @ 0x08062bf0
__attribute__((naked))
void sub_08062BF0(u16 a)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, lr}\n"
        "lsls r0, r0, #0x10\n"
        "lsrs r5, r0, #0x10\n"
        "movs r4, #0x00\n"
        "ldr r1, _08062C2C @ =0x04000050\n"
        "movs r0, #0xFF\n"
        "strh r0, [r1, #0x00]\n"
        "_08062BFE:\n"
        "adds r0, r5, r4\n"
        "lsls r0, r0, #0x10\n"
        "lsrs r4, r0, #0x10\n"
        "asrs r0, r0, #0x10\n"
        "cmp r0, #0x1F\n"
        "ble _08062C0E\n"
        "movs r4, #0x1F\n"
        "movs r5, #0x00\n"
        "_08062C0E:\n"
        "ldr r0, _08062C30 @ =0x04000054\n"
        "strh r4, [r0, #0x00]\n"
        "bl sub_080674B4\n"
        "ldr r0, _08062C34 @ =0x080BB888\n"
        "ldr r0, [r0, #0x00]\n"
        "bl _08073C40\n"
        "bl sub_080474AC\n"
        "cmp r4, #0x1F\n"
        "bne _08062BFE\n"
        "pop {r4, r5}\n"
        "pop {r0}\n"
        "bx r0\n"
        "_08062C2C: .4byte 0x04000050\n"
        "_08062C30: .4byte 0x04000054\n"
        "_08062C34: .4byte 0x080BB888\n"
    );
}

