#include "global.h"

void sub_0806B3E8(struct Unk6B3E8 *arg0)
{
    u8 c;
    s32 count;
    const u8 *cursor;
    struct Unk6B3E8Item *item;

    count = arg0->unk04;
    cursor = arg0->unk10;
    item = arg0->unk00;

    goto check;

    do
    {
        register u8 cc asm("r1") = c;
        const u8 *tableEntry;

        if (cc != 0x20)
        {
            tableEntry = (const u8 *)0x080BB748 + cc;
            sub_0806833C(item, 0, *tableEntry);
            item->unk70 = -1;
            item++;
            count--;
        }

    check:
        if (count == 0)
            break;
        c = *cursor;
        cursor++;
    } while (c != 0);

    count--;
    if (count != -1)
    {
        do
        {
            item->unk70 = 0;
            item++;
            count--;
        } while (count != -1);
    }
}
