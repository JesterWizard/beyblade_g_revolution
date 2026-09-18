#include "global.h"

// @ 0x08033158
__attribute__((naked))
void sub_08033158(void)
{
    asm(".syntax unified\nadds r2, r0, #0x0\nlsrs r3, r2, #0x1F\ncmp r2, #0x00\nbeq _08033182\ncmp r3, #0x00\nbeq _0803316A\nnegs r2, r2\nb _0803316A\n_08033168:\nasrs r1, r1, #0x01\n_0803316A:\ncmp r1, #0x00\nbeq _0803317A\nlsls r0, r1, #0x08\ncmp r2, r0\nble _08033168\nadds r2, r1, #0x0\ncmp r1, #0x00\nbne _0803317C\n_0803317A:\nmovs r2, #0x01\n_0803317C:\ncmp r3, #0x00\nbeq _08033182\nnegs r2, r2\n_08033182:\nadds r0, r2, #0x0\nbx lr");
}
