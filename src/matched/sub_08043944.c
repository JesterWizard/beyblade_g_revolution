#include "global.h"

// @ 0x08043944
__attribute__((naked))
void sub_08043944(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "lsls r0, r0, #0x18\n"
        "lsls r1, r1, #0x18\n"
        "lsrs r3, r1, #0x18\n"
        "lsls r2, r2, #0x18\n"
        "lsrs r4, r2, #0x18\n"
        "cmp r0, #0x00\n"
        "bne _08043968\n"
        "ldr r0, _08043970 @ =0x03000554\n"
        "ldr r2, [r0, #0x00]\n"
        "adds r1, r2, #0x0\n"
        "adds r1, #0x08\n"
        "adds r1, r1, r3\n"
        "adds r0, r4, #0x0\n"
        "ldrb r3, [r1, #0x00]\n"
        "orrs r0, r3\n"
        "strb r0, [r1, #0x00]\n"
        "strb r0, [r2, #0x02]\n"
        "_08043968:\n"
        "pop {r4}\n"
        "pop {r0}\n"
        "bx r0\n"
        ".byte 0x00, 0x00\n"
        "_08043970: .4byte 0x03000554\n"
    );
}

