#include "global.h"

// @ 0x0803e374
__attribute__((naked))
s32 sub_0803E374(struct Unk3E328 *a)
{
    asm(
        ".syntax unified\n"
        "push {lr}\n"
        "adds r2, r0, #0x0\n"
        "ldr r0, _0803E3B4 @ =0x0807BDB8\n"
        "movs r1, #0x1E\n"
        "ldsb r1, [r2, r1]\n"
        "lsls r1, r1, #0x02\n"
        "adds r1, r1, r0\n"
        "ldr r3, _0803E3B8 @ =0x0807BB80\n"
        "adds r0, r2, #0x0\n"
        "adds r0, #0x20\n"
        "ldrb r0, [r0, #0x00]\n"
        "lsls r0, r0, #0x18\n"
        "asrs r0, r0, #0x18\n"
        "lsls r0, r0, #0x02\n"
        "adds r0, r0, r3\n"
        "ldrb r0, [r0, #0x01]\n"
        "ldrb r1, [r1, #0x01]\n"
        "adds r0, r0, r1\n"
        "ldr r3, _0803E3BC @ =0x0807B6F0\n"
        "movs r1, #0x1D\n"
        "ldsb r1, [r2, r1]\n"
        "lsls r1, r1, #0x02\n"
        "adds r1, r1, r3\n"
        "ldrb r1, [r1, #0x01]\n"
        "adds r0, r1, r0\n"
        "movs r1, #0x03\n"
        "bl _080741EC\n"
        "subs r0, #0x01\n"
        "pop {r1}\n"
        "bx r1\n"
        ".byte 0x00, 0x00\n"
        "_0803E3B4: .4byte 0x0807BDB8\n"
        "_0803E3B8: .4byte 0x0807BB80\n"
        "_0803E3BC: .4byte 0x0807B6F0\n"
    );
}

