#include "global.h"

// @ 0x08034894
__attribute__((naked))
void sub_08034894(void)
{
    asm(".syntax unified\nadds r2, r0, #0x0\nmovs r1, #0xC3\nlsls r1, r1, #0x02\nadds r0, r2, r1\nldrb r0, [r0, #0x00]\ncmp r0, #0x00\nbne _080348CC\nldr r0, _080348BC @ =0x03003F60\nldrh r1, [r0, #0x00]\nldr r3, _080348C0 @ =0x00000302\nadds r0, r2, r3\nstrh r1, [r0, #0x00]\nldr r0, _080348C4 @ =0x03004060\nldrh r1, [r0, #0x00]\nsubs r3, #0x02\nadds r0, r2, r3\nstrh r1, [r0, #0x00]\nldr r0, _080348C8 @ =0x0300406C\nldrh r1, [r0, #0x00]\nb _080348DC\n_080348BC: .4byte 0x03003F60\n_080348C0: .4byte 0x00000302\n_080348C4: .4byte 0x03004060\n_080348C8: .4byte 0x0300406C\n_080348CC:\nldr r1, _080348E4 @ =0x00000302\nadds r0, r2, r1\nmovs r1, #0x00\nstrh r1, [r0, #0x00]\nmovs r3, #0xC0\nlsls r3, r3, #0x02\nadds r0, r2, r3\nstrh r1, [r0, #0x00]\n_080348DC:\nadds r3, #0x04\nadds r0, r2, r3\nstrh r1, [r0, #0x00]\nbx lr\n_080348E4: .4byte 0x00000302");
}
