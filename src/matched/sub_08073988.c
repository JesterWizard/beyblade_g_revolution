#include "global.h"

// @ 0x08073988
s32 sub_08073988(void *text_arg, const void *base_arg, u32 delta_arg, u32 space_arg)
{
    register const u8 *text asm("r4");
    const u8 *base;
    register u32 delta asm("r6");
    register u32 space asm("r5");
    register u32 index asm("r2");
    register s32 total asm("r3");
    register u32 ch asm("r1");
    register u32 r0 asm("r0");

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
        asm("" : "+r"(r0));
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

