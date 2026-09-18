#include "global.h"

// @ 0x08042f4c
__attribute__((naked))
void sub_08042F4C(s32 a, s32 b, s16 c, s32 d)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, r6, r7, lr}\n"
        "add sp, #-0x008\n"
        "adds r6, r0, #0x0\n"
        "adds r4, r1, #0x0\n"
        "adds r7, r2, #0x0\n"
        "adds r5, r3, #0x0\n"
        "adds r0, r7, #0x0\n"
        "bl sub_08042E78\n"
        "adds r2, r0, #0x0\n"
        "cmp r2, #0x00\n"
        "beq _08042F8C\n"
        "movs r0, #0x00\n"
        "ldsh r3, [r2, r0]\n"
        "movs r0, #0x64\n"
        "muls r0, r5\n"
        "adds r0, r6, r0\n"
        "strh r0, [r2, #0x00]\n"
        "adds r0, r4, r5\n"
        "cmp r0, #0x00\n"
        "ble _08042F78\n"
        "adds r4, r0, #0x0\n"
        "_08042F78:\n"
        "strb r4, [r2, #0x03]\n"
        "ldr r0, _08042F94 @ =0x083A2CF4\n"
        "ldr r1, _08042F98 @ =0x083A2D28\n"
        "movs r4, #0x00\n"
        "ldsh r2, [r2, r4]\n"
        "str r2, [sp, #0x000]\n"
        "str r5, [sp, #0x004]\n"
        "adds r2, r7, #0x0\n"
        "bl sub_08067B98\n"
        "_08042F8C:\n"
        "add sp, #0x008\n"
        "pop {r4, r5, r6, r7}\n"
        "pop {r0}\n"
        "bx r0\n"
        "_08042F94: .4byte 0x083A2CF4\n"
        "_08042F98: .4byte 0x083A2D28\n"
    );
}

