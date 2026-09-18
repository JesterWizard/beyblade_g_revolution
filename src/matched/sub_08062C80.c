#include "global.h"

// @ 0x08062c80
__attribute__((naked))
void sub_08062C80(void)
{
    asm(
        ".syntax unified\n"
        "push {r4, r5, lr}\n"
        "bl sub_080674B4\n"
        "bl sub_080608D4\n"
        "ldr r1, _08062CBC @ =0x04000050\n"
        "movs r0, #0xFF\n"
        "strh r0, [r1, #0x00]\n"
        "adds r1, #0x04\n"
        "movs r0, #0x1F\n"
        "strh r0, [r1, #0x00]\n"
        "ldr r4, _08062CC0 @ =0x080BB8BC\n"
        "movs r1, #0xA0\n"
        "lsls r1, r1, #0x13\n"
        "movs r5, #0x80\n"
        "lsls r5, r5, #0x02\n"
        "ldr r3, [r4, #0x00]\n"
        "movs r0, #0x00\n"
        "adds r2, r5, #0x0\n"
        "bl _08073C4C\n"
        "ldr r1, _08062CC4 @ =0x05000200\n"
        "ldr r3, [r4, #0x00]\n"
        "movs r0, #0x00\n"
        "adds r2, r5, #0x0\n"
        "bl _08073C4C\n"
        "pop {r4, r5}\n"
        "pop {r0}\n"
        "bx r0\n"
        "_08062CBC: .4byte 0x04000050\n"
        "_08062CC0: .4byte 0x080BB8BC\n"
        "_08062CC4: .4byte 0x05000200\n"
    );
}

