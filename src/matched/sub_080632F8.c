#include "global.h"

// @ 0x080632f8

void sub_080632F8(void)
{
    struct Unk632F8 work;
    void **palettePtr;
    u32 done;

    done = 0;
    palettePtr = (void **)0x080BB8BC;
    _08073C4C(
        (void *)0,
        &work,
        sizeof(work),
        *palettePtr);
    sub_08066390(0x0F);
    sub_0804109C((struct Unk40F4C *)&work, sub_0806639C());
    do
    {
        sub_080674B4();
        sub_0806A6F8();
        if ((work.unk324 & 1) == 0)
            _08073C40(*(void **)0x080BB888);
        switch (work.unk2D4)
        {
        case 0:
            if (work.unk24C != 0)
                _08073C44(&work, work.unk24C);
            break;
        case 1:
            if (work.unk250 != 0)
                _08073C44(&work, work.unk250);
            sub_080411EC(&work);
            break;
        case 2:
            if (work.unk254 != 0)
                _08073C44(&work, work.unk254);
            break;
        case 3:
            done = 1;
            break;
        }
        if (work.unk258 != 0)
            _08073C44(&work, work.unk258);
    } while (done == 0);
}

