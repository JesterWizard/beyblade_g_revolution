#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080737c0
/* match-compiler: old_agbcc */
s32 StringNextWord(const u8 *src, u8 *dst, s32 size);

// Word-wrap `text` into at most `count` line buffers of `lineSize` bytes, breaking
// before a word that would reach `maxWidth` (glyph metrics from `widths`) and
// after a word that ends in a newline. Returns the number of lines used, or -1.
s32 SplitStringIntoStringArray(void **lines, u8 *text, u8 count, u32 widths, u16 maxWidth, u16 glyph, u16 space, u32 lineSize)
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
    if (lines == NULL || text == NULL || widths == 0 || *text == 0)
        return -1;
    if (count == 0)
        return -1;
    word = StringAlloc(0x40);
    if (word == NULL)
    {
        DebugPrint((void *)0x083D2720);
        return -1;
    }
    while (!done)
    {
        MemClear(word, 0x40);
        used = StringNextWord(text, word, 0x40);
        w = StringLength(word);
        if (used != 0 && w != 0)
        {
            text += used;
            w = TextMeasureWidth(word, (const u8 *)widths, glyph, space);
            if (x + w + space >= maxWidth)
            {
                x = 0;
                line++;
            }
            if (line < count)
            {
                if (x != 0)
                {
                    StringAppendChar(((u8 **)lines)[line], ' ', lineSize);
                    x += space;
                }
                if (TextHasNewline(word) == 1)
                {
                    StringAppend(word, ((u8 **)lines)[line], lineSize);
                    x = 0;
                    line++;
                }
                else
                {
                    StringAppend(word, ((u8 **)lines)[line], lineSize);
                    x += w;
                }
            }
            else
            {
                DebugPrint((void *)0x083D2760);
                break;
            }
        }
        else
        {
            done = TRUE;
        }
    }
    StringFree(word);
    return line + 1;
}


