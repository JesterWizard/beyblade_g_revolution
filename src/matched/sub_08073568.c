#include "global.h"

// @ 0x08073568
__attribute__((naked))
u8 sub_08073568(void **dest, u8 n)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, r7, lr}\n"
        "adds r7, r2, #0x0\n"
        "lsls r1, r1, #0x18\n"
        "lsrs r6, r1, #0x18\n"
        "cmp r0, #0x00\n"
        "beq _08073578\n"
        "cmp r7, #0x00\n"
        "bne _08073588\n"
        "_08073578:\n"
        "movs r0, #0x00\n"
        "b _080735A8\n"
        "_0807357C:\n"
        "ldr r0, _08073584 @ =0x083D26C0\n"
        "bl sub_08067B98\n"
        "b _080735A4\n"
        "_08073584: .4byte 0x083D26C0\n"
        "_08073588:\n"
        "movs r5, #0x00\n"
        "cmp r5, r6\n"
        "bcs _080735A4\n"
        "adds r4, r0, #0x0\n"
        "_08073590:\n"
        "adds r0, r7, #0x0\n"
        "bl sub_0807309C\n"
        "str r0, [r4, #0x00]\n"
        "cmp r0, #0x00\n"
        "beq _0807357C\n"
        "adds r4, #0x04\n"
        "adds r5, #0x01\n"
        "cmp r5, r6\n"
        "bcc _08073590\n"
        "_080735A4:\n"
        "lsls r0, r5, #0x18\n"
        "lsrs r0, r0, #0x18\n"
        "_080735A8:\n"
        "pop {r4, r5, r6, r7}\n"
        "pop {r1}\n"
        "bx r1\n"
    );
}

