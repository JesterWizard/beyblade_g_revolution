#include "global.h"

// @ 0x08041858
__attribute__((naked))
void sub_08041858(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "bl sub_08041980\n"
        "ldr r4, _08041880 @ =0x03000508\n"
        "ldr r0, [r4, #0x00]\n"
        "cmp r0, #0x00\n"
        "beq _0804186E\n"
        "bl sub_0806A434\n"
        "movs r0, #0x00\n"
        "str r0, [r4, #0x00]\n"
        "_0804186E:\n"
        "ldr r0, _08041884 @ =0x03000534\n"
        "movs r1, #0x00\n"
        "str r1, [r0, #0x00]\n"
        "ldr r0, _08041888 @ =0x03000504\n"
        "strh r1, [r0, #0x00]\n"
        "pop {r4}\n"
        "pop {r0}\n"
        "bx r0\n"
        ".byte 0x00, 0x00\n"
        "_08041880: .4byte 0x03000508\n"
        "_08041884: .4byte 0x03000534\n"
        "_08041888: .4byte 0x03000504\n"
    );
}
