#include "global.h"

// @ 0x08052fc8
__attribute__((naked))
void sub_08052FC8(void)
{
    asm(".syntax unified\npush {r4, r5, lr}\nbl sub_08067890\nldr r5, _08053008 @ =0x03000198\nldr r0, [r5, #0x00]\nmovs r4, #0xDB\nlsls r4, r4, #0x02\nadds r0, r0, r4\nbl sub_08068418\nldr r0, [r5, #0x00]\nadds r0, r0, r4\nmovs r1, #0x00\nbl sub_08067CE8\nbl sub_0805D1AC\nbl _0802D9A8\nldr r0, _0805300C @ =0x080BB888\nldr r0, [r0, #0x00]\nbl _08073C40\nbl sub_080674B4\nbl sub_0806A6F8\nbl sub_080474AC\npop {r4, r5}\npop {r0}\nbx r0\n_08053008: .4byte 0x03000198\n_0805300C: .4byte 0x080BB888");
}
