#include "global.h"

void sub_080411EC(void *arg)
{
    struct Unk40F4C *a;
    u32 flags;
    register u16 keys;
    u8 mode;

    a = arg;
    if (a->unk2D4 != 1)
        return;
    mode = ((volatile struct Unk40F4C *)a)->unk2D9;
    if (mode == 0)
    {
        flags = sub_08045C5C(0x10, 8);
        if ((flags & 0x20) != 0 && a->unk25C != 0)
        {
            _08073C44(a, a->unk25C);
            return;
        }
        if ((flags & 0x10) != 0 && a->unk260 != 0)
        {
            _08073C44(a, a->unk260);
            return;
        }
        if ((flags & 0x40) != 0 && a->unk264 != 0)
        {
            _08073C44(a, a->unk264);
            return;
        }
        if ((flags & 0x80) != 0 && a->unk268 != 0)
        {
            _08073C44(a, a->unk268);
            return;
        }
        keys = *(vu16 *)gBtlKeysHeld;
        if ((keys & 1) != 0 && a->unk26C != 0)
        {
            _08073C48(a, a->unk26C);
            return;
        }
        if ((keys & 2) != 0 && a->unk270 != 0)
            _08073C44(a, a->unk270);
        return;
    }
    if (mode == 1)
    {
        keys = *(vu16 *)gBtlKeysHeld;
        if ((keys & 0x20) != 0 && a->unk25C != 0)
        {
            _08073C48(a, a->unk25C);
            return;
        }
        if ((keys & 0x10) != 0 && a->unk260 != 0)
        {
            _08073C48(a, a->unk260);
            return;
        }
        if ((keys & 0x40) != 0 && a->unk264 != 0)
        {
            _08073C48(a, a->unk264);
            return;
        }
        if ((keys & 0x80) != 0 && a->unk268 != 0)
        {
            _08073C48(a, a->unk268);
            return;
        }
        if ((keys & 1) != 0 && a->unk26C != 0)
        {
            _08073C48(a, a->unk26C);
            return;
        }
        if ((keys & 2) != 0 && a->unk270 != 0)
            _08073C44(a, a->unk270);
    }
}
