#include "global.h"

void sub_08062988(struct Unk62988 *a)
{
    u32 flags;
    u32 group;
    u32 mode;
    u32 variant;

    flags = a->unk00;
    group = flags >> 8;
    mode = (flags >> 4) & 0x0F;
    variant = a->unk04 & 3;
    if (gUnk_030007A0 == 0)
        return;
    if (mode == 1
        && variant >= 1
        && variant <= 2
        && group != 0)
    {
        sub_080674B4();
        sub_080674AC(a, gUnk_030007A4);
    }
    else
    {
        _08073C4C(
            (void *)0,
            gUnk_030007A4,
            0x2000,
            *(void **)0x080BB8BC);
        _08073C4C(
            a,
            gUnk_030007A4,
            0x2000,
            *(void **)0x080BB8C0);
    }
    sub_0806BC0C(gUnk_030007B0, gUnk_030007A4);
}
