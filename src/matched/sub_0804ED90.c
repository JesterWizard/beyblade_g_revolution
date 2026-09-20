#include "global.h"

// @ 0x0804ed90
#include "global.h"

void sub_0804ED90(void *arg)
{
    s32 i;
    u16 value;
    void *table;

    sub_080674B4();
    for (i = 0x0A; i <= 0x19; i++)
    {
        value = (u16)i;
        sub_0806184C(value, 4);
    }
    for (i = 0x0A; i <= 0x19; i++)
    {
        value = (u16)i;
        sub_0806184C(value, 5);
    }
    for (i = 0x0A; i <= 0x19; i++)
    {
        value = (u16)i;
        sub_0806184C(value, 6);
    }
    for (i = 0x0A; i <= 0x19; i++)
    {
        value = (u16)i;
        sub_0806184C(value, 7);
    }
    for (i = 0x0A; i <= 0x19; i++)
    {
        value = (u16)i;
        sub_0806184C(value, 8);
    }
    for (i = 0x0A; i <= 0x19; i++)
    {
        value = (u16)i;
        sub_0806184C(value, 9);
    }

    sub_080617C4((struct Unk617C4 *)0x080D79CC, 0x080B7429);
    sub_080615EC(0, 0x20);
    table = (void *)0x083A8470;
    sub_0806171C(table, 0xDC, 1);
    sub_080615EC(0, 0x28);
    sub_0806171C(table, 0xDC, 1);
    sub_080615EC(0, 0x30);
    sub_0806171C(table, 0xDC, 1);
    sub_080615EC(0, 0x38);
    sub_0806171C(table, 0xDC, 1);
    sub_080615EC(0, 0x40);
    sub_0806171C(table, 0xDC, 1);
    sub_080615EC(0, 0x48);
    sub_0806171C(table, 0xDC, 1);
    sub_080617C4((struct Unk617C4 *)0x082C44A8, 0x080B7258);
    sub_0804EBF0(arg);
}

