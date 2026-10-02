#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806b3e8
#include "global.h"

void AnimTextRowFill(struct AnimTextRow *a)
{
    u32 left;
    const u8 *text;
    struct AnimTextItem *item;
    u8 ch;
    s32 prev;

    left = a->count;
    text = a->text;
    item = a->items;
    goto check;
body:
    if (ch != 0x20)
    {
        AnimObjSetRecordAt((struct AnimObjPlayback *)item, 0, gData_080BB748[ch]);
        item->visible = -1;
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
        goto done;
    do
    {
        item->visible = 0;
        item++;
        prev = left;
        left--;
    } while (prev != 0);
done:
    left = prev;
}

