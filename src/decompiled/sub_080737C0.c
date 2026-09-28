/* match-compiler: old_agbcc */
#define sub_080737C0 sub_080737C0_x
#include "global.h"
#include "ram_map.h"
#undef sub_080737C0

s32 StringNextWord(const u8 *src, u8 *dst, s32 size);

s32 sub_080737C0(u8 **lines, const u8 *text, u8 count, const u8 *widths, u16 maxWidth, u16 glyph, u16 space, u32 lineSize)
{
    u32 x;
    u8 line;
    bool32 done;
    u8 *word;
    s32 used;
    s32 w;

    x = 0;
    line = 0;
    done = FALSE;
    if (lines == NULL || text == NULL || widths == NULL || *text == 0 || count == 0)
        return -1;
    word = BtlObjTableAdd(0x40);
    if (word == NULL)
    {
        sub_08067B98((void *)0x083D2720);
        return -1;
    }
    while (!done)
    {
        MemClear(word, 0x40);
        used = StringNextWord(text, word, 0x40);
        w = sub_08073078(word);
        if (used == 0 || w == 0)
        {
            done = TRUE;
        }
        else
        {
            text += used;
            w = TextMeasureWidth(word, widths, glyph, space);
            if (x + w + space >= maxWidth)
            {
                x = 0;
                line++;
            }
            if (line >= count)
            {
                sub_08067B98((void *)0x083D2760);
                break;
            }
            if (x != 0)
            {
                sub_080733BC(lines[line], ' ', lineSize);
                x += space;
            }
            if (TextHasNewline(word) == 1)
            {
                StringAppend(word, lines[line], lineSize);
                x = 0;
                line++;
            }
            else
            {
                StringAppend(word, lines[line], lineSize);
                x += w;
            }
        }
    }
    BtlObjTableRemove(word);
    return line + 1;
}

