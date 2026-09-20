#include "global.h"

// @ 0x08073988
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
        r0 = 0x080BB748;
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

