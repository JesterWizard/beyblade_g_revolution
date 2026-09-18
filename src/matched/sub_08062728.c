#include "global.h"

// @ 0x08062728
__attribute__((naked))
void sub_08062728(struct Unk62728 *a)
{
    asm(
        ".syntax unified\n"
        "movs r1, #0x00\n"
        "movs r3, #0x00\n"
        "ldr r2, [r0, #0x08]\n"
        "ldr r0, [r0, #0x04]\n"
        "_08062730:\n"
        "stm r0!, {r3}\n"
        "adds r1, #0x01\n"
        "cmp r1, r2\n"
        "bcc _08062730\n"
        "bx lr\n"
    );
}

