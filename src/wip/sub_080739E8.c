/* match-compiler: old_agbcc */
#include "global.h"

// @ 0x080739e8
// 11/36 same-size. Scan a NUL-terminated string: return 1 if it contains a newline
// (0x0A) before its terminator, else 0. Retail layout:
//   adds r1,r0,#0; cmp r1,#0; beq bx_lr          (s == 0 -> return r0, known 0)
//   ldrb r0,[r1]; movs r2,#1                     (c = s[0]; i = 1)
//   cmp r0,#0; beq ret0                          (entry guard, FALLS THROUGH to body)
//   loop: cmp r0,#0x0A; bne advance; movs r0,#1; b bx_lr
//   advance: adds r0,r1,r2; ldrb r0,[r0]; adds r2,#1
//   cmp r0,#0; bne loop                          (bottom test -> back to BODY top, not
//                                                 to a condition block)
//   ret0: movs r0,#0; bx_lr
// The body top is the 0x0A compare at 0x0e and the back edge lands there, so the loop
// is a rotated bottom-test loop; the entry guard is a SEPARATE cmp/beq that falls into
// the body. agbcc merged my guard into the loop test and emitted an extra prescan
// `b`/`bne` layout (34 bytes) for every form tried:
//   while + explicit `if (c == 0) return 0;` guard (11/36),
//   do-while + guard (10/36), goto loop + guard (10/36),
//   for (; c != 0; i++) + guard (9/36), no guard at all (4-7/36),
//   guard on `s[0]` instead of `c` (7/36), i declared as an initialiser (5/36).
// Next: permuter.
s32 sub_080739E8(u8 *s)
{
    u8 c;
    u32 i;

    if (s == 0)
        return 0;
    c = s[0];
    i = 1;
    if (c == 0)
        return 0;
    while (c != 0)
    {
        if (c == 0x0A)
            return 1;
        c = s[i];
        i++;
    }
    return 0;
}
