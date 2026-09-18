#include "global.h"

// @ 0x08062c38
__attribute__((naked))
void sub_08062C38(u16 a)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, lr}\n"
        "lsls r0, r0, #0x10\n"
        "lsrs r5, r0, #0x10\n"
        "movs r4, #0x1F\n"
        "ldr r1, _08062C74 @ =0x04000050\n"
        "movs r0, #0xFF\n"
        "strh r0, [r1, #0x00]\n"
        "_08062C46:\n"
        "subs r0, r4, r5\n"
        "lsls r0, r0, #0x10\n"
        "lsrs r4, r0, #0x10\n"
        "cmp r0, #0x00\n"
        "bge _08062C54\n"
        "movs r4, #0x00\n"
        "movs r5, #0x00\n"
        "_08062C54:\n"
        "ldr r0, _08062C78 @ =0x04000054\n"
        "strh r4, [r0, #0x00]\n"
        "bl sub_080674B4\n"
        "ldr r0, _08062C7C @ =0x080BB888\n"
        "ldr r0, [r0, #0x00]\n"
        "bl _08073C40\n"
        "bl sub_080474AC\n"
        "cmp r4, #0x00\n"
        "bne _08062C46\n"
        "pop {r4, r5}\n"
        "pop {r0}\n"
        "bx r0\n"
        ".byte 0x00, 0x00\n"
        "_08062C74: .4byte 0x04000050\n"
        "_08062C78: .4byte 0x04000054\n"
        "_08062C7C: .4byte 0x080BB888\n"
    );
}

