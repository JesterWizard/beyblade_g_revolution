#include "global.h"

// @ 0x08035624
__attribute__((naked))
void sub_08035624(struct Unk346C0 *a, u32 type_arg, s32 delta_arg)
{
    asm(".syntax unified\npush {r4, r5, lr}\nadds r3, r0, #0x0\nlsls r1, r1, #0x18\nlsrs r4, r1, #0x18\nadds r5, r4, #0x0\nldr r0, [r3, #0x00]\nldr r0, [r0, #0x00]\nlsls r2, r2, #0x18\nasrs r2, r2, #0x18\nldrh r0, [r0, #0x22]\nadds r1, r0, r2\ncmp r4, #0x01\nbeq _0803565A\ncmp r4, #0x01\nbgt _08035648\ncmp r4, #0x00\nbeq _0803564E\nb _08035690\n_08035648:\ncmp r5, #0x02\nbeq _08035676\nb _08035690\n_0803564E:\nadds r4, r3, #0x0\nadds r4, #0xD8\nstrh r1, [r4, #0x00]\nadds r2, r3, #0x0\nadds r2, #0xD4\nb _08035666\n_0803565A:\nmovs r0, #0xDA\nlsls r0, r0, #0x01\nadds r4, r3, r0\nstrh r1, [r4, #0x00]\nsubs r0, #0x04\nadds r2, r3, r0\n_08035666:\nldr r0, [r2, #0x00]\ncmp r0, #0x00\nbeq _08035690\nlsls r1, r1, #0x10\nlsrs r1, r1, #0x10\nbl sub_08070468\nb _08035690\n_08035676:\nmovs r0, #0xA4\nlsls r0, r0, #0x02\nadds r4, r3, r0\nstrh r1, [r4, #0x00]\nsubs r0, #0x04\nadds r2, r3, r0\nldr r0, [r2, #0x00]\ncmp r0, #0x00\nbeq _08035690\nlsls r1, r1, #0x10\nlsrs r1, r1, #0x10\nbl sub_08070468\n_08035690:\npop {r4, r5}\npop {r0}\nbx r0");
}
