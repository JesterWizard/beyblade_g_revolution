#include "global.h"

// @ 0x0803e440
__attribute__((naked))
void sub_0803E440(void)
{
    asm(".syntax unified\npush {r4, lr}\nmovs r2, #0x00\nmovs r1, #0x00\nldr r0, _0803E46C @ =0x03000198\nldr r0, [r0, #0x00]\nldr r4, _0803E470 @ =0x00001861\nadds r3, r0, r4\n_0803E44E:\nadds r0, r3, r1\nldrb r0, [r0, #0x00]\nlsls r0, r0, #0x18\nasrs r0, r0, #0x18\ncmp r0, #0x00\nble _0803E45C\nadds r2, #0x01\n_0803E45C:\nadds r1, #0x01\ncmp r1, #0x52\nble _0803E44E\nadds r0, r2, #0x0\npop {r4}\npop {r1}\nbx r1\n.byte 0x00, 0x00\n_0803E46C: .4byte 0x03000198\n_0803E470: .4byte 0x00001861");
}
