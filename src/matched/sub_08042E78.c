#include "global.h"

// @ 0x08042e78
__attribute__((naked))
void *sub_08042E78(s16 i)
{
    asm(
        ".syntax unified\n"
        "adds r2, r0, #0x0\n"
        "cmp r2, #0x36\n"
        "bhi _08042E90\n"
        "ldr r0, _08042E8C @ =0x03000540\n"
        "lsls r1, r2, #0x01\n"
        "adds r1, r1, r2\n"
        "lsls r1, r1, #0x04\n"
        "ldr r0, [r0, #0x00]\n"
        "adds r0, r0, r1\n"
        "b _08042E92\n"
        "_08042E8C: .4byte 0x03000540\n"
        "_08042E90:\n"
        "movs r0, #0x00\n"
        "_08042E92:\n"
        "bx lr\n"
    );
}

