#include "global.h"

// @ 0x0806105c
#include "global.h"

void sub_0806105C(void *a, u8 *s)
{
    register u8 *sp asm("r5");
    register s32 i asm("r4");
    u8 c;

    sp = s;
    if (sp == 0 || a == 0)
        return;
    c = sp[0];
    i = 1;
    if (c == 0)
        return;
    do
    {
        sub_08060E48(a, c);
        c = sp[i];
        i++;
    } while (c != 0);
}

