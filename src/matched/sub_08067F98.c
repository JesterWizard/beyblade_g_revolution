#include "global.h"

// @ 0x08067f98
__attribute__((naked))
void sub_08067F98(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "lsls r1, r1, #0x10\n"
        "lsrs r3, r1, #0x10\n"
        "ldr r2, [r0, #0x00]\n"
        "ldr r1, [r2, #0x18]\n"
        "adds r2, r2, r1\n"
        "movs r1, #0x00\n"
        "ldrh r0, [r0, #0x28]\n"
        "cmp r1, r0\n"
        "bcs _08067FC0\n"
        "_08067FAC:\n"
        "ldrh r4, [r2, #0x00]\n"
        "cmp r4, r3\n"
        "bne _08067FB6\n"
        "adds r0, r2, #0x0\n"
        "b _08067FC2\n"
        "_08067FB6:\n"
        "ldrh r4, [r2, #0x02]\n"
        "adds r2, r4, r2\n"
        "adds r1, #0x01\n"
        "cmp r1, r0\n"
        "bcc _08067FAC\n"
        "_08067FC0:\n"
        "movs r0, #0x00\n"
        "_08067FC2:\n"
        "pop {r4}\n"
        "pop {r1}\n"
        "bx r1\n"
    );
}

