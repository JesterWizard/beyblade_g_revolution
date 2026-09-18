#include "global.h"

// @ 0x08044D8C
__attribute__((naked))
void sub_08044D8C(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "movs r2, #0x00\n"
        "movs r4, #0xFB\n"
        "lsls r4, r4, #0x03\n"
        "adds r3, r0, #0x4\n"
        "movs r1, #0x01\n"
        "_08044D98:\n"
        "ldm r3!, {r0}\n"
        "adds r2, r2, r0\n"
        "adds r1, #0x01\n"
        "cmp r1, r4\n"
        "bcc _08044D98\n"
        "adds r0, r2, #0x0\n"
        "pop {r4}\n"
        "pop {r1}\n"
        "bx r1\n"
    );
}
