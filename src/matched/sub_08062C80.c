#include "global.h"

// @ 0x08062c80
void sub_08062C80(void)
{
    void **src;

    sub_080674B4();
    sub_080608D4();

    *(u16 *)0x04000050 = 0xFF;
    *(u16 *)0x04000054 = 0x1F;

    src = (void **)0x080BB8BC;
    _08073C4C(0, (void *)0x05000000, 0x200, *src);
    _08073C4C(0, (void *)0x05000200, 0x200, *src);
}

