#include "global.h"

// @ 0x080442fc
__attribute__((naked))
void sub_080442FC(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nadd sp, #-0x004\nadds r5, r0, #0x0\nadds r7, r2, #0x0\nadds r6, r3, #0x0\nmovs r4, #0x00\ncmp r1, #0x00\nbeq _08044326\nldrh r4, [r1, #0x16]\nldr r0, _08044378 @ =0x08091208\nldrh r1, [r1, #0x14]\nldr r2, _0804437C @ =0x08091204\nmovs r3, #0x00\nldsh r2, [r2, r3]\nbl sub_0806F1A0\nldr r1, _08044380 @ =0x03000198\nldr r1, [r1, #0x00]\nldr r2, _08044384 @ =0x0000181B\nadds r1, r1, r2\nstrb r0, [r1, #0x00]\n_08044326:\nadds r0, r5, #0x0\nadds r0, #0x84\nldr r0, [r0, #0x00]\ncmp r0, #0x00\nblt _08044336\nadds r0, r5, #0x0\nbl sub_0806D958\n_08044336:\nldr r0, _08044380 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r3, _08044388 @ =0x00001690\nadds r2, r0, r3\nldr r1, _08044384 @ =0x0000181B\nadds r0, r0, r1\nldrb r3, [r0, #0x00]\nlsls r1, r3, #0x05\nadds r1, r1, r3\nlsls r1, r1, #0x02\nldr r0, _08044378 @ =0x08091208\nadds r1, r1, r0\nstr r1, [r2, #0x00]\nmovs r2, #0x82\nlsls r2, r2, #0x05\nlsls r4, r4, #0x10\nlsrs r3, r4, #0x10\nstr r6, [sp, #0x000]\nadds r0, r5, #0x0\nbl sub_08043C70\ncmp r7, #0x00\nbeq _08044370\nbl sub_08062A14\nasrs r2, r4, #0x10\nadds r1, r5, #0x0\nbl sub_0806C78C\n_08044370:\nadd sp, #0x004\npop {r4, r5, r6, r7}\npop {r0}\nbx r0\n_08044378: .4byte 0x08091208\n_0804437C: .4byte 0x08091204\n_08044380: .4byte 0x03000198\n_08044384: .4byte 0x0000181B\n_08044388: .4byte 0x00001690");
}
