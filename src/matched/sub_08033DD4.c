#include "global.h"

// @ 0x08033dd4
__attribute__((naked))
void sub_08033DD4(void)
{
    asm(".syntax unified\npush {r4, lr}\nldr r4, _08033E20 @ =0x03000380\nldr r1, [r4, #0x00]\nmovs r2, #0xC4\nlsls r2, r2, #0x02\nadds r0, r1, r2\nldrb r0, [r0, #0x00]\ncmp r0, #0x00\nbne _08033E2C\nsubs r2, #0x44\nadds r0, r1, r2\nldr r0, [r0, #0x00]\ncmp r0, #0x07\nbeq _08033E2C\nadds r2, #0x46\nadds r0, r1, r2\nldrb r0, [r0, #0x00]\ncmp r0, #0x00\nbne _08033E2C\nldrb r0, [r4, #0x0A]\ncmp r0, #0x00\nbeq _08033E24\nldrb r0, [r4, #0x09]\ncmp r0, #0x00\nbeq _08033E24\nadds r4, #0x0C\nadds r0, r4, #0x0\nbl sub_08035884\nadds r0, r4, #0x0\nbl sub_08035908\ncmp r0, #0x00\nbeq _08033E36\nbl sub_08033C1C\nb _08033E36\n.byte 0x00, 0x00\n_08033E20: .4byte 0x03000380\n_08033E24:\nadds r0, r4, #0x0\nbl sub_08033E3C\nb _08033E36\n_08033E2C:\nldrb r0, [r4, #0x09]\ncmp r0, #0x00\nbeq _08033E36\nbl sub_08033C1C\n_08033E36:\npop {r4}\npop {r0}\nbx r0");
}
