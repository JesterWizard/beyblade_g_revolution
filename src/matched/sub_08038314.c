#include "global.h"

// @ 0x08038314
__attribute__((naked))
void sub_08038314(void)
{
    asm(".syntax unified\npush {r4, lr}\nadds r2, r0, #0x0\nadds r3, r1, #0x0\nmovs r0, #0xC1\nlsls r0, r0, #0x02\nadds r1, r2, r0\nldr r0, [r1, #0x00]\nsubs r0, #0x01\nstr r0, [r1, #0x00]\ncmp r0, #0x00\nble _08038336\nldr r1, _08038378 @ =0x03004060\nmovs r0, #0x03\nldrh r1, [r1, #0x00]\nands r0, r1\ncmp r0, #0x00\nbeq _08038370\n_08038336:\nmovs r1, #0xBF\nlsls r1, r1, #0x02\nadds r0, r2, r1\nstr r3, [r0, #0x00]\nldr r4, _0803837C @ =0x03000290\nldr r0, [r4, #0x00]\nmovs r1, #0xCE\nlsls r1, r1, #0x01\nadds r0, r0, r1\nbl sub_08062044\nldr r0, [r4, #0x00]\nmovs r1, #0xE2\nlsls r1, r1, #0x01\nadds r0, r0, r1\nbl sub_08062044\nldr r0, [r4, #0x00]\nmovs r1, #0xF6\nlsls r1, r1, #0x01\nadds r0, r0, r1\nbl sub_08062044\nldr r0, [r4, #0x00]\nmovs r1, #0x85\nlsls r1, r1, #0x02\nadds r0, r0, r1\nbl sub_08062044\n_08038370:\npop {r4}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_08038378: .4byte 0x03004060\n_0803837C: .4byte 0x03000290");
}
