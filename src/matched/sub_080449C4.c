#include "global.h"

// @ 0x080449c4
__attribute__((naked))
void sub_080449C4(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nadd sp, #-0x004\nldr r4, _08044A0C @ =0x03000198\nldr r3, [r4, #0x00]\nldr r2, _08044A10 @ =0x000017F0\nadds r1, r3, r2\nmovs r2, #0x00\nstrh r2, [r1, #0x00]\nldr r5, _08044A14 @ =0x000017F2\nadds r1, r3, r5\nstrh r2, [r1, #0x00]\nldr r1, _08044A18 @ =0x04000050\nstrh r2, [r1, #0x00]\nadds r1, #0x02\nstrh r2, [r1, #0x00]\nadds r1, #0x02\nstrh r2, [r1, #0x00]\nldr r1, _08044A1C @ =0x0000181B\nadds r3, r3, r1\nstrb r0, [r3, #0x00]\nldr r1, [r4, #0x00]\nmovs r2, #0xDB\nlsls r2, r2, #0x02\nadds r1, r1, r2\nmovs r0, #0x01\nstr r0, [sp, #0x000]\nmovs r0, #0x00\nmovs r2, #0x00\nmovs r3, #0x01\nbl sub_08043DB4\nadd sp, #0x004\npop {r4, r5}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_08044A0C: .4byte 0x03000198\n_08044A10: .4byte 0x000017F0\n_08044A14: .4byte 0x000017F2\n_08044A18: .4byte 0x04000050\n_08044A1C: .4byte 0x0000181B");
}
