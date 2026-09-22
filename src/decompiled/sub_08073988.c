#include "global.h"

// @ 0x08073988
// 94/96 same-size (97.9%). Remaining 2 bytes: at the `default_char` block retail
// emits `ldr r0,=0x080BB748; adds r0,r1,r0` (pool constant lands in r0, the same
// register that receives the sum) while agbcc puts the constant in r2
// (`ldr r2,=...; adds r0,r1,r2`). Only the `index = 0x080BB748` side-effect form
// below reproduces retail's prologue; rewriting that statement as a plain
// expression (`r0 = ch + 0x080BB748`, `r0 = 0x080BB748; r0 += ch`, ...) all floor
// at 89/96 because they re-colour r7/r12. Permuter chain (strict branches) best 10.
s32 sub_08073988(void *text_arg, const void *base_arg, u32 delta_arg, u32 space_arg)
{
    const u8 *text;
    const u8 *base;
    u32 delta;
    u32 space;
    u32 index;
    s32 total;
    u32 ch;
    u32 r0;

    text = text_arg;
    base = base_arg;
    delta = delta_arg;
    space = space_arg;
    index = 0;
    total = 0;
    if (text == 0)
        return 0;
    do
    {
        ch = text[index];
        index++;
        if (ch == 0)
            goto done;
        if (ch == 8)
            goto char8;
        if (ch > 8)
            goto high_char;
        if (ch == 7)
            goto char7;
        goto default_char;
high_char:
        if (ch == 10)
            goto loop_tail;
        if (ch == 32)
        {
            total += space;
            goto loop_tail;
        }
        goto default_char;
char7:
        index += 2;
        goto loop_tail;
char8:
        index++;
        goto loop_tail;
default_char:
        r0 = (index = 0x080BB748);
        r0 = ch + r0;
        r0 = *(const u8 *)r0;
        r0 = r0 + (u32)base;
        r0 = *(const u8 *)r0;
        total += delta - r0;
loop_tail:
        ;
    } while (ch != 0);
done:
    return total;
}
