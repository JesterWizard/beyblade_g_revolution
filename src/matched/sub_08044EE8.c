#include "global.h"

// @ 0x08044ee8
__attribute__((naked))
void sub_08044EE8(void)
{
    asm(".syntax unified\nldr r1, _08044F0C @ =0x03000198\nldr r1, [r1, #0x00]\nldr r2, _08044F10 @ =0x00001688\nadds r1, r1, r2\nlsls r2, r0, #0x01\nadds r2, r2, r0\nlsls r2, r2, #0x03\nldr r1, [r1, #0x00]\nadds r1, r1, r2\nmovs r0, #0x00\nstr r0, [r1, #0x04]\nstr r0, [r1, #0x00]\nstr r0, [r1, #0x08]\nstrh r0, [r1, #0x10]\nstrh r0, [r1, #0x12]\nstrh r0, [r1, #0x14]\nstrh r0, [r1, #0x16]\nbx lr\n_08044F0C: .4byte 0x03000198\n_08044F10: .4byte 0x00001688");
}
