#include "global.h"

// @ 0x08062728
// 2/18. Retail: `stm r0!, {r3}` with r3 = 0 inside `for (i = 0; i < a->unk08; i++)`
// — a 16-byte zero fill per iteration. agbcc only emits stm for a 4-word struct
// store pattern; explicit p[0..3] = 0 emits 4 str (size mismatch). Try a 16-byte
// struct assignment from a zero value, or check for a memset-like intrinsic form.
void sub_08062728(struct Unk62728 *a)
{
    u32 i;
    u32 *p = a->unk04;

    for (i = 0; i < a->unk08; i++)
    {
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p += 4;
    }
}
