#include "global.h"

// @ 0x080699c8
__attribute__((naked))
void sub_080699C8(void)
{
    asm(
        ".syntax unified\n"
        "adds r3, r1, #0x0\n"
        "lsls r0, r0, #0x18\n"
        "lsrs r0, r0, #0x18\n"
        "cmp r0, #0x02\n"
        "beq _080699D8\n"
        "cmp r0, #0x03\n"
        "beq _080699F4\n"
        "b _08069A08\n"
        "_080699D8:\n"
        "ldr r0, _080699E8 @ =0x04000028\n"
        "strh r3, [r0, #0x00]\n"
        "ldr r1, _080699EC @ =0x0400002A\n"
        "asrs r0, r3, #0x10\n"
        "strh r0, [r1, #0x00]\n"
        "ldr r0, _080699F0 @ =0x0400002C\n"
        "b _08069A00\n"
        ".byte 0x00, 0x00\n"
        "_080699E8: .4byte 0x04000028\n"
        "_080699EC: .4byte 0x0400002A\n"
        "_080699F0: .4byte 0x0400002C\n"
        "_080699F4:\n"
        "ldr r0, _08069A0C @ =0x04000038\n"
        "strh r3, [r0, #0x00]\n"
        "ldr r1, _08069A10 @ =0x0400003A\n"
        "asrs r0, r3, #0x10\n"
        "strh r0, [r1, #0x00]\n"
        "ldr r0, _08069A14 @ =0x0400003C\n"
        "_08069A00:\n"
        "strh r2, [r0, #0x00]\n"
        "adds r1, #0x04\n"
        "asrs r0, r2, #0x10\n"
        "strh r0, [r1, #0x00]\n"
        "_08069A08:\n"
        "bx lr\n"
        ".byte 0x00, 0x00\n"
        "_08069A0C: .4byte 0x04000038\n"
        "_08069A10: .4byte 0x0400003A\n"
        "_08069A14: .4byte 0x0400003C\n"
    );
}

