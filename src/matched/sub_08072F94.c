#include "global.h"

// @ 0x08072f94
__attribute__((naked))
void sub_08072F94(void)
{
    asm(".syntax unified\nldr r1, _08072FA0 @ =0x03004130\nldr r0, _08072FA4 @ =0x03004148\nldr r0, [r0, #0x00]\nadds r0, r0, r1\nldrb r0, [r0, #0x00]\nbx lr\n_08072FA0: .4byte 0x03004130\n_08072FA4: .4byte 0x03004148");
}
