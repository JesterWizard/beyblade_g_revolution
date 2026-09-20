#define sub_08073988 sub_08073988_old_proto
#include "global.h"
#undef sub_08073988

s32 sub_08073988(
    void *text_arg,
    const u8 *base,
    u32 delta_arg,
    u32 space_arg)
{
    register const u8 *text asm("r4");
    register const u8 *saved_base asm("r7");
    register u32 delta asm("r6");
    register u32 space asm("r5");
    register u32 index asm("r2");
    register s32 total asm("r3");
    register u32 ch asm("r1");
    register u32 value;

    text = text_arg;
    saved_base = base;
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
        {
            if (ch == 10)
                goto loop_tail;
            if (ch == 32)
            {
                total += space;
                goto loop_tail;
            }
            goto default_char;
        }
char7:
        index += 2;
        goto loop_tail;
char8:
        index++;
        goto loop_tail;
default_char:
        value = *(const u8 *)(0x080BB748 + ch);
        value = saved_base[value];
        total += delta - value;
loop_tail:
        ;
    } while (ch != 0);
done:
    return total;
}
