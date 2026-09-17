#include "global.h"

// @ 0x08045c5c
__attribute__((naked))
void sub_08045C5C(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nadds r7, r0, #0x0\nadds r5, r1, #0x0\nldr r0, _08045C88 @ =0x03003F60\nmovs r1, #0xFC\nlsls r1, r1, #0x08\nadds r4, r0, #0x0\nldrh r0, [r4, #0x00]\ncmp r0, r1\nbne _08045C98\nldr r0, _08045C8C @ =0x03000198\nldr r0, [r0, #0x00]\nldr r2, _08045C90 @ =0x00001778\nadds r1, r0, r2\nmovs r2, #0x00\nstr r2, [r1, #0x00]\nldr r1, _08045C94 @ =0x00001774\nadds r0, r0, r1\nstr r2, [r0, #0x00]\nmovs r0, #0x00\nb _08045CDA\n.byte 0x00, 0x00\n_08045C88: .4byte 0x03003F60\n_08045C8C: .4byte 0x03000198\n_08045C90: .4byte 0x00001778\n_08045C94: .4byte 0x00001774\n_08045C98:\nldr r0, _08045CB0 @ =0x03000198\nldr r3, [r0, #0x00]\nldr r2, _08045CB4 @ =0x00001778\nadds r1, r3, r2\nldr r2, [r1, #0x00]\nadds r6, r0, #0x0\ncmp r2, #0x00\nbeq _08045CB8\nsubs r0, r2, #0x1\nstr r0, [r1, #0x00]\nmovs r0, #0x00\nb _08045CDA\n_08045CB0: .4byte 0x03000198\n_08045CB4: .4byte 0x00001778\n_08045CB8:\nldr r2, _08045CC8 @ =0x00001774\nadds r0, r3, r2\nldr r0, [r0, #0x00]\nldrh r2, [r4, #0x00]\ncmp r0, r2\nbne _08045CCC\nstr r5, [r1, #0x00]\nb _08045CCE\n_08045CC8: .4byte 0x00001774\n_08045CCC:\nstr r7, [r1, #0x00]\n_08045CCE:\nldr r0, [r6, #0x00]\nldr r1, _08045CE0 @ =0x00001774\nadds r0, r0, r1\nldrh r1, [r4, #0x00]\nstr r1, [r0, #0x00]\nldrh r0, [r4, #0x00]\n_08045CDA:\npop {r4, r5, r6, r7}\npop {r1}\nbx r1\n_08045CE0: .4byte 0x00001774");
}
