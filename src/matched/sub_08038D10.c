#include "global.h"

// @ 0x08038d10
__attribute__((naked))
void sub_08038D10(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nmov r7, r8\npush {r7}\nadds r7, r0, #0x0\nmovs r5, #0x00\nldr r0, _08038D44 @ =0x030003E0\nmov r8, r0\nldr r6, _08038D48 @ =0x03000290\nmovs r4, #0x8F\nlsls r4, r4, #0x02\n_08038D24:\nmovs r1, #0xBF\nlsls r1, r1, #0x02\nadds r0, r7, r1\nldr r0, [r0, #0x00]\nadds r0, r0, r5\nlsls r0, r0, #0x02\nadd r0, r8\nldr r1, [r0, #0x00]\ncmp r1, #0x00\nbeq _08038D4C\nldr r0, [r6, #0x00]\nadds r0, r0, r4\nmovs r2, #0x01\nbl sub_08070AD4\nb _08038D54\n_08038D44: .4byte 0x030003E0\n_08038D48: .4byte 0x03000290\n_08038D4C:\nldr r0, [r6, #0x00]\nadds r0, r0, r4\nbl sub_08070678\n_08038D54:\nadds r4, #0x30\nadds r5, #0x01\ncmp r5, #0x03\nble _08038D24\npop {r3}\nmov r8, r3\npop {r4, r5, r6, r7}\npop {r0}\nbx r0");
}
