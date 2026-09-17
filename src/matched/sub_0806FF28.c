#include "global.h"

// @ 0x0806ff28
__attribute__((naked))
void sub_0806FF28(void)
{
    asm(".syntax unified\nadds r3, r0, #0x0\nldrb r0, [r3, #0x19]\ncmp r0, #0x00\nbne _0806FF4E\nldr r2, [r3, #0x00]\nldr r1, [r3, #0x04]\ncmp r2, #0x00\nbeq _0806FF3C\nstr r1, [r2, #0x04]\nb _0806FF40\n_0806FF3C:\nldr r0, _0806FF50 @ =0x030040B8\nstr r1, [r0, #0x00]\n_0806FF40:\ncmp r1, #0x00\nbeq _0806FF46\nstr r2, [r1, #0x00]\n_0806FF46:\nldr r1, _0806FF54 @ =0x030040A8\nldr r0, [r1, #0x00]\nstr r0, [r3, #0x04]\nstr r3, [r1, #0x00]\n_0806FF4E:\nbx lr\n_0806FF50: .4byte 0x030040B8\n_0806FF54: .4byte 0x030040A8");
}
