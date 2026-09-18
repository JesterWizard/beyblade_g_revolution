#include "global.h"

// @ 0x08071f44
__attribute__((naked))
struct Unk71F84 *sub_08071F44(s32 a)
{
    asm(
        ".syntax unified\n"
        "push {r4, lr}\n"
        "adds r3, r0, #0x0\n"
        "ldr r0, _08071F6C @ =0x030040E4\n"
        "ldr r1, [r0, #0x00]\n"
        "ldr r0, _08071F70 @ =0x030040C4\n"
        "ldrb r2, [r0, #0x00]\n"
        "subs r2, #0x01\n"
        "movs r0, #0x01\n"
        "negs r0, r0\n"
        "cmp r2, r0\n"
        "beq _08071F7C\n"
        "adds r4, r0, #0x0\n"
        "_08071F5C:\n"
        "ldrb r0, [r1, #0x16]\n"
        "cmp r0, #0x00\n"
        "beq _08071F74\n"
        "ldr r0, [r1, #0x18]\n"
        "cmp r0, r3\n"
        "bne _08071F74\n"
        "adds r0, r1, #0x0\n"
        "b _08071F7E\n"
        "_08071F6C: .4byte 0x030040E4\n"
        "_08071F70: .4byte 0x030040C4\n"
        "_08071F74:\n"
        "adds r1, #0x28\n"
        "subs r2, #0x01\n"
        "cmp r2, r4\n"
        "bne _08071F5C\n"
        "_08071F7C:\n"
        "movs r0, #0x00\n"
        "_08071F7E:\n"
        "pop {r4}\n"
        "pop {r1}\n"
        "bx r1\n"
    );
}

