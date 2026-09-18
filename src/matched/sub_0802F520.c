#include "global.h"

// @ 0x0802f520
__attribute__((naked))
void sub_0802F520(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nldr r2, _0802F578 @ =0x000002D5\nadds r1, r0, r2\nldrb r5, [r1, #0x00]\nmovs r1, #0xBF\nlsls r1, r1, #0x02\nadds r0, r0, r1\nmovs r4, #0x00\nldsb r4, [r0, r4]\nlsls r4, r4, #0x01\nadds r0, r4, #0x0\nadds r0, #0x0C\nmovs r1, #0x0F\nmovs r2, #0x04\nmovs r3, #0x19\nbl sub_08061D68\nadds r4, #0x0D\nadds r0, r4, #0x0\nmovs r1, #0x0F\nmovs r2, #0x04\nmovs r3, #0x19\nbl sub_08061D68\nlsls r5, r5, #0x18\nasrs r5, r5, #0x17\nadds r0, r5, #0x0\nadds r0, #0x0C\nmovs r1, #0x0E\nmovs r2, #0x04\nmovs r3, #0x19\nbl sub_08061D68\nadds r5, #0x0D\nadds r0, r5, #0x0\nmovs r1, #0x0E\nmovs r2, #0x04\nmovs r3, #0x19\nbl sub_08061D68\npop {r4, r5}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_0802F578: .4byte 0x000002D5");
}
