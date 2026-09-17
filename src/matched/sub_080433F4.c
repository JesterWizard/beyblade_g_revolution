#include "global.h"

// @ 0x080433f4
__attribute__((naked))
void sub_080433F4(void)
{
    asm(".syntax unified\nldr r2, _08043410 @ =0x03000198\nldr r0, [r2, #0x00]\nldr r1, _08043414 @ =0x00001834\nadds r0, r0, r1\nmovs r1, #0x00\nstrb r1, [r0, #0x00]\nldr r1, [r2, #0x00]\nldr r0, _08043418 @ =0x00001808\nadds r1, r1, r0\nldr r0, [r1, #0x00]\nldr r2, _0804341C @ =0xFFFFFDFF\nands r0, r2\nstr r0, [r1, #0x00]\nbx lr\n_08043410: .4byte 0x03000198\n_08043414: .4byte 0x00001834\n_08043418: .4byte 0x00001808\n_0804341C: .4byte 0xFFFFFDFF");
}
