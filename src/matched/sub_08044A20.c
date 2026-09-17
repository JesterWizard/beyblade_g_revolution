#include "global.h"

// @ 0x08044a20
__attribute__((naked))
void sub_08044A20(void)
{
    asm(".syntax unified\npush {r4, r5, r6, lr}\nldr r5, _08044A6C @ =0x03000198\nldr r1, [r5, #0x00]\nldr r0, _08044A70 @ =0x000017C4\nadds r4, r1, r0\nldr r2, [r4, #0x00]\nldr r3, _08044A74 @ =0xFFFFC000\ncmp r2, r3\nbeq _08044A48\nldr r6, _08044A78 @ =0x000017B4\nadds r0, r1, r6\nstr r2, [r0, #0x00]\nldr r0, _08044A7C @ =0x000017B8\nadds r2, r1, r0\nadds r6, #0x14\nadds r1, r1, r6\nldr r0, [r1, #0x00]\nstr r0, [r2, #0x00]\nstr r3, [r4, #0x00]\nstr r3, [r1, #0x00]\n_08044A48:\nldr r0, [r5, #0x00]\nldr r1, _08044A80 @ =0x0000044C\nadds r2, r0, r1\nldr r3, _08044A78 @ =0x000017B4\nadds r1, r0, r3\nldr r1, [r1, #0x00]\nstr r1, [r2, #0x00]\nmovs r6, #0x8A\nlsls r6, r6, #0x03\nadds r1, r0, r6\nldr r2, _08044A7C @ =0x000017B8\nadds r0, r0, r2\nldr r0, [r0, #0x00]\nstr r0, [r1, #0x00]\npop {r4, r5, r6}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_08044A6C: .4byte 0x03000198\n_08044A70: .4byte 0x000017C4\n_08044A74: .4byte 0xFFFFC000\n_08044A78: .4byte 0x000017B4\n_08044A7C: .4byte 0x000017B8\n_08044A80: .4byte 0x0000044C");
}
