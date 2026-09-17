#include "global.h"

// @ 0x08042718
__attribute__((naked))
void sub_08042718(void)
{
    asm(".syntax unified\npush {r4, r5, r6, lr}\nldr r6, _0804276C @ =0x03000198\nldr r5, [r6, #0x00]\nldr r1, _08042770 @ =0x0000182C\nadds r0, r5, r1\nldrb r0, [r0, #0x00]\ncmp r0, #0x00\nbeq _08042764\nldr r0, _08042774 @ =0x000017B4\nadds r1, r5, r0\nldr r0, _08042778 @ =0x0000044C\nadds r3, r5, r0\nldr r0, [r3, #0x00]\nstr r0, [r1, #0x00]\nldr r0, _0804277C @ =0x000017B8\nadds r1, r5, r0\nmovs r0, #0x8A\nlsls r0, r0, #0x03\nadds r2, r5, r0\nldr r0, [r2, #0x00]\nstr r0, [r1, #0x00]\nldr r0, _08042780 @ =0xFFFFC000\nstr r0, [r3, #0x00]\nstr r0, [r2, #0x00]\nmovs r4, #0x89\nlsls r4, r4, #0x03\nadds r0, r5, r4\nbl sub_08068418\nldr r0, [r6, #0x00]\nadds r0, r0, r4\nmovs r1, #0x00\nbl sub_08067CE8\nldr r0, [r6, #0x00]\nadds r0, r0, r4\nbl sub_08068808\n_08042764:\npop {r4, r5, r6}\npop {r0}\nbx r0\n.byte 0x00, 0x00\n_0804276C: .4byte 0x03000198\n_08042770: .4byte 0x0000182C\n_08042774: .4byte 0x000017B4\n_08042778: .4byte 0x0000044C\n_0804277C: .4byte 0x000017B8\n_08042780: .4byte 0xFFFFC000");
}
