#include "global.h"

// @ 0x08062d24
__attribute__((naked))
void sub_08062D24(void)
{
    asm(
        ".syntax unified\n"
        "lsls r0, r0, #0x18\n"
        "movs r2, #0xA0\n"
        "lsls r2, r2, #0x13\n"
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
    );
}

