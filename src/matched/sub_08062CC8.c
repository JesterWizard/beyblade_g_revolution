#include "global.h"

// @ 0x08062cc8
__attribute__((naked))
void sub_08062CC8(void)
{
    asm(
        ".syntax unified\n"
        "lsls r0, r0, #0x18\n"
        "ldr r2, _08062CF0 @ =0x05000200\n"
        "lsrs r0, r0, #0x17\n"
        "adds r0, r0, r2\n"
        "ldrh r2, [r0, #0x00]\n"
        "movs r3, #0x1F\n"
        "adds r0, r2, #0x0\n"
        "ands r0, r3\n"
        "strb r0, [r1, #0x00]\n"
        "movs r0, #0xF8\n"
        "lsls r0, r0, #0x02\n"
        "ands r0, r2\n"
        "lsrs r0, r0, #0x05\n"
        "strb r0, [r1, #0x01]\n"
        "movs r0, #0xF8\n"
        "lsls r0, r0, #0x07\n"
        "ands r2, r0\n"
        "lsrs r2, r2, #0x0A\n"
        "strb r2, [r1, #0x02]\n"
        "bx lr\n"
        "_08062CF0: .4byte 0x05000200\n"
    );
}

