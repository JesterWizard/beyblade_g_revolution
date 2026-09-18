#include "global.h"

// @ 0x08062d50
__attribute__((naked))
void sub_08062D50(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, lr}\n"
        "lsls r0, r0, #0x18\n"
        "movs r5, #0xA0\n"
        "lsls r5, r5, #0x13\n"
        "movs r3, #0x1F\n"
        "adds r4, r3, #0x0\n"
        "ldrb r2, [r1, #0x00]\n"
        "ands r4, r2\n"
        "adds r2, r3, #0x0\n"
        "ldrb r6, [r1, #0x01]\n"
        "ands r2, r6\n"
        "lsls r2, r2, #0x05\n"
        "orrs r4, r2\n"
        "ldrb r1, [r1, #0x02]\n"
        "ands r3, r1\n"
        "lsls r3, r3, #0x0A\n"
        "orrs r4, r3\n"
        "lsrs r0, r0, #0x17\n"
        "adds r0, r0, r5\n"
        "strh r4, [r0, #0x00]\n"
        "pop {r4, r5, r6}\n"
        "pop {r0}\n"
        "bx r0\n"
    );
}

