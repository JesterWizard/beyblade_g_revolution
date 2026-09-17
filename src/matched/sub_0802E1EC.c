#include "global.h"

// @ 0x0802e1ec
__attribute__((naked))
void sub_0802E1EC(void)
{
    asm(".syntax unified\npush {lr}\nldr r0, _0802E208 @ =0x03000198\nldr r0, [r0, #0x00]\nldr r1, _0802E20C @ =0x00000874\nadds r0, r0, r1\nmovs r1, #0x00\nldsh r0, [r0, r1]\nbl sub_08042BE8\nlsls r0, r0, #0x18\nasrs r0, r0, #0x18\npop {r1}\nbx r1\n.byte 0x00, 0x00\n_0802E208: .4byte 0x03000198\n_0802E20C: .4byte 0x00000874");
}
