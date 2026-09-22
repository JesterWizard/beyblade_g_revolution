#include "global.h"

// @ 0x08032d5c
void sub_08032D5C(struct Unk346C0 *a, u32 b)
{
    u32 v0;
    u32 v1;

    v0 = 0;
    v1 = 0;
    sub_08034788(a, b, &v0, &v1);
    a->unk2E4 = v0;
    a->unk2E8 = v1;
    sub_08035054(a, 2, 13, -1);
    sub_0803559C(a, 2, RandRange(3));
    sub_08060254(1, 0x38, 7);
}

