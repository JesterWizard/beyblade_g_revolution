#include "global.h"

// @ 0x08052fc8

void sub_0806A6F8(void);

// @ 0x08052fc8
void sub_08052FC8(void)
{
    struct MainWork **wp;

    sub_08067890();
    wp = gMainWorkPtrLoc;
    sub_08068418((u8 *)*wp + 0x36C);
    sub_08067CE8((u8 *)*wp + 0x36C, 0);
    sub_0805D1AC();
    _0802D9A8();
    _08073C40(*(void **)0x080BB888);
    sub_080674B4();
    sub_0806A6F8();
    sub_080474AC();
}

