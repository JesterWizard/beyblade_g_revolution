#include "global.h"

// @ 0x080462d4
__attribute__((naked))
void sub_080462D4(void)
{
    asm(".syntax unified\npush {r4, r5, r6, lr}\nldr r0, _08046330 @ =0x03000198\nldr r1, [r0, #0x00]\nldr r2, _08046334 @ =0x0000184C\nadds r0, r1, r2\nldrb r0, [r0, #0x00]\nlsls r0, r0, #0x18\nasrs r0, r0, #0x18\ncmp r0, #0x00\nbeq _08046350\nadds r2, #0x01\nadds r0, r1, r2\nldrb r0, [r0, #0x00]\nlsls r0, r0, #0x18\nasrs r0, r0, #0x18\ncmp r0, #0x00\nbne _08046350\nmovs r5, #0x00\nldr r6, _08046338 @ =0x080979E4\nmovs r4, #0x00\n_080462FC:\nldr r0, _08046330 @ =0x03000198\nldr r1, [r0, #0x00]\nldr r2, _0804633C @ =0x000016B0\nadds r0, r1, r2\nadds r0, r0, r4\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nbeq _08046348\nadds r2, #0x04\nadds r0, r1, r2\nadds r2, r0, r4\nldr r0, [r2, #0x00]\ncmp r0, #0x00\nbne _08046344\nldr r2, _08046340 @ =0x000016B8\nadds r0, r1, r2\nadds r0, r0, r4\nldr r0, [r0, #0x00]\nlsls r0, r0, #0x02\nadds r0, r0, r6\nldr r1, [r0, #0x00]\nadds r0, r5, #0x0\nbl _08073C44\nb _08046348\n.byte 0x00, 0x00\n_08046330: .4byte 0x03000198\n_08046334: .4byte 0x0000184C\n_08046338: .4byte 0x080979E4\n_0804633C: .4byte 0x000016B0\n_08046340: .4byte 0x000016B8\n_08046344:\nsubs r0, #0x01\nstr r0, [r2, #0x00]\n_08046348:\nadds r4, #0x0C\nadds r5, #0x01\ncmp r5, #0x01\nble _080462FC\n_08046350:\npop {r4, r5, r6}\npop {r0}\nbx r0");
}
