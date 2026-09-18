#include "global.h"

// @ 0x08030938
__attribute__((naked))
void sub_08030938(void)
{
    asm(".syntax unified\npush {r4, r5, r6, r7, lr}\nadd sp, #-0x004\nadds r7, r0, #0x0\nmovs r1, #0xB6\nlsls r1, r1, #0x02\nadds r0, r7, r1\nldr r6, [r0, #0x00]\nsubs r1, #0x04\nadds r0, r7, r1\nldr r4, [r0, #0x00]\nldr r0, [r7, #0x04]\nldr r2, [r0, #0x0C]\nadds r1, #0x20\nadds r0, r7, r1\nldr r1, [r0, #0x00]\nadds r0, r4, #0x0\nmuls r0, r2\nbl sub_080674A0\nadds r3, r0, #0x0\nmovs r5, #0xB4\nsubs r0, r5, r4\nmuls r0, r3\nadds r1, r4, #0x0\nbl sub_080674A0\nsubs r3, r5, r0\nldr r0, [r7, #0x00]\nldr r1, [r0, #0x30]\nldr r2, [r0, #0x34]\nstr r3, [sp, #0x000]\nadds r0, r7, #0x0\nadds r3, r6, #0x0\nbl sub_080346C0\nadd sp, #0x004\npop {r4, r5, r6, r7}\npop {r0}\nbx r0");
}
