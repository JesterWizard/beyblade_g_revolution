#include "global.h"

// @ 0x08031294
__attribute__((naked))
void sub_08031294(struct Unk312EC *a)
{
    asm(
        ".syntax unified\n"
        "movs r1, #0xFF\n"
        "ldrb r2, [r0, #0x00]\n"
        "orrs r2, r1\n"
        "strb r2, [r0, #0x00]\n"
        "ldrb r2, [r0, #0x01]\n"
        "orrs r1, r2\n"
        "strb r1, [r0, #0x01]\n"
        "movs r1, #0x01\n"
        "negs r1, r1\n"
        "str r1, [r0, #0x04]\n"
        "movs r1, #0x00\n"
        "str r1, [r0, #0x0C]\n"
        "strb r1, [r0, #0x08]\n"
        "bx lr\n"
    );
}

