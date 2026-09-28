// Typewriter text tick: counts down the per-character delay (quartered while
// fastKeys are held), starts and measures a new line, and prints one glyph or
// control code (7 = cursor, 8 = palette).
#include "global.h"
#include "ram_map.h"

s32 TextTypewriterTick(struct TextTypewriter *t, s32 x, u32 align, u32 stopLine)
{
    u8 *str;
    u8 c;
    s32 width;
    u16 keys;
    s32 state;

    if (t == NULL)
        return -1;
    state = t->state;
    if (state != 1)
        return (s8)t->state;
    keys = gData_03003F60;
    if (t->skipKeys & keys)
        goto finish;
    if (t->timer > 0)
    {
        t->timer--;
        return 1;
    }
    if (t->fastKeys & keys)
        t->timer = (s16)t->delay >> 2;
    else
        t->timer = t->delay;
    if (t->pos == 0 && t->len == 0)
    {
        if (t->line >= t->lineCount)
        {
            t->state = state | 0xFF;
            return -1;
        }
        t->len = StringLength(t->lines[t->line]);
        if (t->len == 0)
        {
        finish:
            t->state = 0xFF;
            return -1;
        }
        width = TextMeasureWidth(t->lines[t->line], (const u8 *)gData_03000798->widthTable, gData_03000798->glyphWidth, gData_03000798->spacing);
        switch (align)
        {
        case 0:
            gData_03000798->penX = x - ((u32)width >> 1);
            break;
        case 1:
            gData_03000798->penX = x - width;
            break;
        case 2:
            gData_03000798->penX = x;
            break;
        }
        gData_03000798->penY += gData_03000798->lineHeight;
        if (stopLine == t->line && t->len != 0)
        {
            gData_03000798->penY -= gData_03000798->lineHeight;
            return 2;
        }
    }
    str = t->lines[t->line];
    c = str[t->pos++];
    switch (c)
    {
    case 7:
        TextSetCursor(str[t->pos++] - 1, str[t->pos++] - 1);
        break;
    case 8:
        TextSetPaletteBank(str[t->pos++] - 1);
        break;
    case 10:
        break;
    default:
        if (t->pos > t->len)
        {
            t->pos = 0;
            t->len = 0;
            t->line++;
        }
        else
        {
            ((void (*)(u32))gData_080BB644[0])(c);
        }
        break;
    }
    return 1;
}
