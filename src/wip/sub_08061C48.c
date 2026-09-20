#include "global.h"

// @ 0x08061c48
#include "global.h"

// @ 0x08061c48
void sub_08061C48(void)
{
    register s32 *r4;
    register struct Unk0770 *r5;
    s32 n;
    void *obj;
    u32 tmp[2];

    tmp[0] = gUnk_03000794;
    tmp[1] = gUnk_03000770;
    r4 = (s32 *)tmp[0];
    n = *r4;
    n--;
    if (n < 0)
        return;
    *r4 = n;
    r5 = (struct Unk0770 *)tmp[1];
    obj = r5[n].unk00;
    if (obj == 0)
        return;
    sub_0806A434(obj);
    n = *r4;
    r5[n].unk00 = 0;
}

