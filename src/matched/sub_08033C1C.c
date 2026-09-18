#include "global.h"

// @ 0x08033c1c
__attribute__((naked))
void sub_08033C1C(void)
{
    asm(".syntax unified\npush {lr}\nldr r1, _08033C38 @ =0x03000380\nldrb r0, [r1, #0x09]\ncmp r0, #0x01\nbne _08033C34\nmovs r0, #0x00\nstrb r0, [r1, #0x09]\nstrb r0, [r1, #0x0A]\nadds r0, r1, #0x0\nadds r0, #0x0C\nbl sub_080358CC\n_08033C34:\npop {r0}\nbx r0\n_08033C38: .4byte 0x03000380");
}
