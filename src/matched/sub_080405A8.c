#include "global.h"

// @ 0x080405a8
__attribute__((naked))
void sub_080405A8(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, lr}\n"
        "ldr r3, _080405D8 @ =0x0300047C\n"
        "ldr r0, [r3, #0x00]\n"
        "ldr r2, _080405DC @ =0x0000080C\n"
        "adds r1, r0, r2\n"
        "movs r2, #0x00\n"
        "str r2, [r1, #0x00]\n"
        "ldr r1, _080405E0 @ =0x00000808\n"
        "adds r0, r0, r1\n"
        "str r2, [r0, #0x00]\n"
        "ldr r5, _080405E4 @ =0x000001FF\n"
        "adds r4, r3, #0x0\n"
        "movs r3, #0x01\n"
        "negs r3, r3\n"
        "_080405C4:\n"
        "ldr r0, [r4, #0x00]\n"
        "lsls r1, r2, #0x02\n"
        "adds r0, r0, r1\n"
        "str r3, [r0, #0x00]\n"
        "adds r2, #0x01\n"
        "cmp r2, r5\n"
        "ble _080405C4\n"
        "pop {r4, r5}\n"
        "pop {r0}\n"
        "bx r0\n"
        "_080405D8: .4byte 0x0300047C\n"
        "_080405DC: .4byte 0x0000080C\n"
        "_080405E0: .4byte 0x00000808\n"
        "_080405E4: .4byte 0x000001FF\n"
    );
}

