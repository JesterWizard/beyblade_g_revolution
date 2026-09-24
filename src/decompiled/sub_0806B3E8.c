#include "global.h"
void sub_0806B3E8(struct Unk6B3E8 *a)
{
    u32 left;
    const u8 *text;
    struct Unk6B3E8Item *item;
    u8 ch;
    s32 prev;

    left = a->unk04;
    text = a->unk10;
    item = a->unk00;
    goto check;
body:
    if (ch != 0x20)
    {
        sub_0806833C((struct Unk68598 *)item, 0, gData_080BB748[ch]);
        item->unk70 = -1;
        item++;
        left--;
    }
check:
    if (left == 0)
        goto zero;
    ch = *text;
    text++;
    if (ch != 0)
        goto body;
zero:
    prev = left;
    left--;
    if (prev == 0)
        return;
    do
    {
        item->unk70 = 0;
        item++;
        prev = left;
        left--;
    } while (prev != 0);
}
