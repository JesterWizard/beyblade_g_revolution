#include "global.h"

// @ 0x08062068
__attribute__((naked))
void sub_08062068(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "adds r4, r1, #0x0\n"
        "cmp r2, #0x01\n"
        "beq _0806208A\n"
        "cmp r2, #0x01\n"
        "bcc _0806207A\n"
        "cmp r2, #0x02\n"
        "beq _08062084\n"
        "b _08062090\n"
        "_0806207A:\n"
        "movs r2, #0x1E\n"
        "ldsh r1, [r0, r2]\n"
        "lsrs r0, r4, #0x01\n"
        "subs r3, r1, r0\n"
        "b _08062090\n"
        "_08062084:\n"
        "movs r1, #0x1E\n"
        "ldsh r3, [r0, r1]\n"
        "b _08062090\n"
        "_0806208A:\n"
        "movs r2, #0x1E\n"
        "ldsh r0, [r0, r2]\n"
        "subs r3, r0, r4\n"
        "_08062090:\n"
        "adds r0, r3, #0x0\n"
        "pop {r4}\n"
        "pop {r1}\n"
        "bx r1\n"
    );
}

