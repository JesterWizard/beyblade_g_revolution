#include "global.h"

// @ 0x08061e40
__attribute__((naked))
void sub_08061E40(struct Unk61E40 *a)
{
    asm(
        ".syntax unified\n"
        "adds r2, r0, #0x0\n"
        "cmp r2, #0x00\n"
        "beq _08061E52\n"
        "movs r1, #0x00\n"
        "movs r0, #0x00\n"
        "strh r0, [r2, #0x10]\n"
        "strh r0, [r2, #0x0A]\n"
        "strb r1, [r2, #0x15]\n"
        "str r0, [r2, #0x04]\n"
        "_08061E52:\n"
        "bx lr\n"
    );
}

