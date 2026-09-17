#include "global.h"

// @ 0x08031c98
__attribute__((naked))
void sub_08031C98(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nldr r1, _08031CBC @ =0x03000290\nldr r1, [r1, #0x00]\nmovs r2, #0xC3\nlsls r2, r2, #0x02\nadds r4, r0, r2\nldrb r2, [r4, #0x00]\nlsls r0, r2, #0x02\nldr r5, _08031CC0 @ =0x0000208C\nadds r3, r1, r5\nadds r1, r3, r0\nldr r0, [r1, #0x00]\ncmp r0, #0x00\nblt _08031CC4\nsubs r0, #0x01\nstr r0, [r1, #0x00]\nb _08031D20\n.byte 0x00, 0x00\n_08031CBC: .4byte 0x03000290\n_08031CC0: .4byte 0x0000208C\n_08031CC4:\nldr r7, _08031D08 @ =0x030002A0\nmovs r6, #0x2C\nadds r1, r2, #0x0\nmuls r1, r6\nadds r5, r7, #0x0\nadds r5, #0x0C\nadds r1, r1, r5\nldr r0, [r1, #0x00]\nsubs r0, #0x01\nstr r0, [r1, #0x00]\nldrb r2, [r4, #0x00]\nadds r1, r2, #0x0\nmuls r1, r6\nadds r0, r1, r5\nldr r0, [r0, #0x00]\ncmp r0, #0x32\nbgt _08031D0C\nlsls r0, r2, #0x02\nadds r0, r3, r0\nmovs r1, #0x1E\nstr r1, [r0, #0x00]\nldrb r1, [r4, #0x00]\nadds r0, r1, #0x0\nmuls r0, r6\nadds r0, r0, r5\nldr r0, [r0, #0x00]\ncmp r0, #0x14\nbgt _08031D20\nlsls r0, r1, #0x02\nadds r0, r3, r0\nmovs r1, #0x0A\nstr r1, [r0, #0x00]\nb _08031D20\n.byte 0x00, 0x00\n_08031D08: .4byte 0x030002A0\n_08031D0C:\nlsls r2, r2, #0x02\nadds r2, r3, r2\nadds r0, r7, #0x0\nadds r0, #0x18\nadds r0, r1, r0\nldr r1, [r0, #0x00]\nlsls r0, r1, #0x02\nadds r0, r0, r1\nlsls r0, r0, #0x01\nstr r0, [r2, #0x00]\n_08031D20:\nbl sub_080320CC\nbl sub_08031204\npop {r4, r5, r6, r7}\npop {r0}\nbx r0");
}
