#include "global.h"

// @ 0x08033530
__attribute__((naked))
void sub_08033530(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nldr r5, _08033550 @ =0x03000290\nldr r1, [r5, #0x00]\nldr r2, _08033554 @ =0x00002088\nadds r0, r1, r2\nldrb r0, [r0, #0x00]\ncmp r0, #0x01\nbne _08033568\nsubs r2, #0x6C\nadds r0, r1, r2\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nbne _08033558\nbl sub_08033574\nb _08033568\n_08033550: .4byte 0x03000290\n_08033554: .4byte 0x00002088\n_08033558:\nldr r4, _08033570 @ =0x00001FAC\nadds r0, r1, r4\nbl sub_080686D8\nldr r0, [r5, #0x00]\nadds r0, r0, r4\nbl sub_08068418\n_08033568:\npop {r4, r5}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_08033570: .4byte 0x00001FAC");
}
