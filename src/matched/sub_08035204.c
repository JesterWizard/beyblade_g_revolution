#include "global.h"

// @ 0x08035204
void sub_08035204(void *a, u32 b, u32 c, u32 d)
{
    u8 bb;
    u8 cc;

    bb = b;
    cc = c;
    sub_08035258((struct Unk35258 *)a, bb);
    sub_08035054(a, bb, cc, d);
}
