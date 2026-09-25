#include "global.h"
#include "ram_map.h"

/* match-compiler: old_agbcc */
void sub_0804EBF0(void *a)
{
    s32 index;
    u32 cursorX;
    struct Unk4EBF0Entry *entry;
    s32 text;
    s32 *baseLoc;
    struct Unk4EBF0Entry **tableLoc;
    s32 negOne;
    s32 idx;
    struct Unk4EBF0Entry *table;
    s32 fieldOff;

    sub_08061784();
    if (gUnk_030006A8 == 0)
        return;

    index = 0;
    baseLoc = (s32 *)0x0300069C;
    tableLoc = (struct Unk4EBF0Entry **)0x030006A0;
    cursorX = 0x80000;
    negOne = -1;
    do
    {
        idx = *baseLoc + index;
        table = *tableLoc;
        entry = (struct Unk4EBF0Entry *)((idx << 4) + (u32)table);
        if (entry->unk0C > negOne || entry->unk0D == 7)
        {
            sub_080615EC(0, (index << 3) + 0x20);
            fieldOff = 0xD;
            idx = *baseLoc + index;
            table = *tableLoc;
            idx = (idx << 4) + (s32)table;
            text = _080563A8(*(s8 *)(idx + fieldOff), *(s8 *)(idx + 0xC));
            if (text != 0)
                sub_0806171C((void *)text, 0xCC, 1);
            else
            {
                idx = *baseLoc + index;
                table = *tableLoc;
                sub_0806171C(((struct Unk4EBF0Entry *)((idx << 4) + (u32)table))->unk04, 0x4A, 2);
            }
            if (index == gUnk_030006A4)
                sub_08061D68(cursorX >> 16, 0xE, 0xB, 0x1A);
            else
                sub_08061D68(cursorX >> 16, 0xF, 0xB, 0x1A);
        }
        cursorX += 0x10000;
        index++;
    } while (index <= 5);
}
