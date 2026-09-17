#include "global.h"

// @ 0x0803d4c4
__attribute__((naked))
void sub_0803D4C4(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nmovs r6, #0x00\nldr r7, _0803D50C @ =0x03000290\n_0803D4CA:\nldr r1, [r7, #0x00]\nmovs r0, #0x64\nadds r4, r6, #0x0\nmuls r4, r0\nldr r2, _0803D510 @ =0x00000BD4\nadds r0, r1, r2\nadds r0, r0, r4\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nbeq _0803D500\nldr r0, _0803D514 @ =0x00000BCC\nadds r5, r4, r0\nadds r0, r1, r5\nbl sub_0806225C\nldr r2, [r7, #0x00]\nldr r1, _0803D518 @ =0x00000BF4\nadds r0, r2, r1\nadds r0, r0, r4\nldr r1, [r0, #0x00]\nmovs r0, #0xA0\nlsls r0, r0, #0x08\ncmp r1, r0\nble _0803D500\nadds r0, r2, r5\nbl sub_08062238\n_0803D500:\nadds r6, #0x01\ncmp r6, #0x2F\nble _0803D4CA\npop {r4, r5, r6, r7}\npop {r0}\nbx r0\n_0803D50C: .4byte 0x03000290\n_0803D510: .4byte 0x00000BD4\n_0803D514: .4byte 0x00000BCC\n_0803D518: .4byte 0x00000BF4");
}
