#include "global.h"

void sub_08066FB8(void)
{
    u32 *table;
    u32 *index_loc;
    void *image;
    u32 value;
    u32 mode;

    sub_080674B4();
    sub_08061BE8();
    BgMapSetPaletteBankRun(5, 0x0F, 3, 0x1A);
    BgMapSetPaletteBankRun(6, 0x0F, 3, 0x1A);
    BgMapSetPaletteBankRun(7, 0x0F, 3, 0x1A);
    BgMapSetPaletteBankRun(8, 0x0F, 3, 0x1A);
    BgMapSetPaletteBankRun(9, 0x0F, 3, 0x1A);
    BgMapSetPaletteBankRun(0x0A, 0x0F, 3, 0x1A);
    sub_080674B4();
    table = (u32 *)0x080BB110;
    table += 3;
    index_loc = (u32 *)0x03000674;

    sub_080615EC(0, 8);
    image = (void *)table[*index_loc * 4];
    value = sub_08061784();
    sub_0806171C(image, value >> 1, 0);

    sub_080615EC(0, 0x18);
    image = (void *)table[(*index_loc + 1) * 4];
    value = sub_08061784();
    sub_0806171C(image, value >> 1, 0);

    sub_080615EC(0, 0x28);
    image = (void *)table[(*index_loc + 2) * 4];
    value = sub_08061784();
    sub_0806171C(image, value >> 1, 0);

    mode = gUnk_03000678;
    if (mode == 0)
    {
        BgMapSetPaletteBankRun(5, 0x0E, 3, 0x1A);
        BgMapSetPaletteBankRun(6, 0x0E, 3, 0x1A);
    }
    else if (mode == 1)
    {
        BgMapSetPaletteBankRun(7, 0x0E, 3, 0x1A);
        BgMapSetPaletteBankRun(8, 0x0E, 3, 0x1A);
    }
    else if (mode == 2)
    {
        BgMapSetPaletteBankRun(9, 0x0E, 3, 0x1A);
        BgMapSetPaletteBankRun(0x0A, 0x0E, 3, 0x1A);
    }
}
