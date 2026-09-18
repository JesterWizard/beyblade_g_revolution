#include "global.h"

// @ 0x08031368
__attribute__((naked))
void sub_08031368(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nadds r5, r0, #0x0\nadds r4, r2, #0x0\nsubs r2, r1, #0x1\ncmp r2, #0x00\nble _0803138E\nlsls r0, r2, #0x02\nadds r0, r0, r5\n_08031378:\nldr r1, [r0, #0x00]\ncmp r1, #0x00\nbeq _08031386\nldr r0, [r1, #0x08]\nstr r0, [r4, #0x00]\nldr r0, [r1, #0x0C]\nb _08031392\n_08031386:\nsubs r0, #0x04\nsubs r2, #0x01\ncmp r2, #0x00\nbgt _08031378\n_0803138E:\nmovs r0, #0x00\nstr r0, [r4, #0x00]\n_08031392:\nstr r0, [r3, #0x00]\npop {r4, r5}\npop {r0}\nbx r0");
}
