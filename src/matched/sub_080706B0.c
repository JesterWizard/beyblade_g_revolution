#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080706b0
/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

// Lays out a text sprite group: places each glyph at the group origin plus
// its pen x (unk1E, bit 15 marks a break opportunity), wrapping to a new
// line when a glyph would cross wrapWidth, applying the horizontal alignment
// (flags & 3) and affine x scale per line, then shifts all glyphs up for
// vertical alignment (flags & 0x30).
// Advance of glyph sprite n: font width minus its per-glyph trim.
#define GLYPH_WIDTH(n) (widths != NULL ? defWidth - widths[(n)->unk18] : defWidth)

void sub_080706B0(struct Unk70C98 *arg)
{
    struct TextGroup *g = (struct TextGroup *)arg;
    u8 *widths = g->widthTable;
    u8 defWidth = g->font->unk04;
    s32 x = g->x;
    s32 y = g->y;
    u16 wrapWidth = g->wrapWidth;
    s32 lineStart = 0;
    s32 count = g->glyphs.count;
    struct Sprite *node = (struct Sprite *)g->glyphs.head;
    struct Sprite *breakNode = NULL;
    struct Sprite *lineHead = node;
    s32 scale = 0x100;
    struct AffineObj *aff = g->affine;
    s32 height = 0;
    struct Sprite *last;
    s32 off;
    s32 span;

    g->lineCount = 0;
    if (count == 0)
        return;
    if (aff != NULL)
        scale = aff->scaleX;
    switch (g->flags & 3)
    {
    case 1:
        x += wrapWidth << 8;
        break;
    case 2:
        x += (wrapWidth & ~1) << 7;
        break;
    }
    while (count-- != 0)
    {
        u16 pen = node->unk1E & 0x7FFF;
        s32 spacing;

        if (node->unk1E & 0x8000)
            breakNode = node;
        spacing = g->letterSpacing;
        if ((u32)(pen - lineStart + (spacing + GLYPH_WIDTH(node))) > wrapWidth || count == 0)
        {
            if (count != 0)
            {
                if (breakNode != NULL)
                    last = breakNode->prev;
                else
                    last = node->prev;
            }
            else
            {
                last = node;
            }
            off = 0;
            switch (g->flags & 3)
            {
            case 1:
                span = (last->unk1E & 0x7FFF) - lineStart;
                span += g->letterSpacing + GLYPH_WIDTH(last);
                off = -(span << 8);
                break;
            case 2:
                span = (last->unk1E & 0x7FFF) - lineStart;
                span += g->letterSpacing + GLYPH_WIDTH(last);
                off = -((span & ~1) << 7);
                break;
            case 0:
                break;
            }
            off -= lineStart << 8;
            off = x + ((s32)(off * scale) >> 8);
            last = last->next;
            for (; lineHead != last; lineHead = lineHead->next)
            {
                lineHead->unk08 = off + ((((lineHead->unk1E & 0x7FFF) << 8) * scale) >> 8);
                lineHead->unk0C = y;
            }
            if (last != NULL)
                lineStart = last->unk1E & 0x7FFF;
            else
                lineStart = 0;
            breakNode = NULL;
            y += g->lineHeight << 8;
            height += g->lineHeight << 8;
            g->lineCount++;
        }
        node = node->next;
    }
    count = g->glyphs.count;
    node = (struct Sprite *)g->glyphs.head;
    switch (g->flags & 0x30)
    {
    case 0:
        height = 0;
        break;
    case 0x10:
        height >>= 1;
        break;
    case 0x20:
        break;
    }
    if (height != 0)
    {
        while (count-- != 0)
        {
            node->unk0C -= height;
            node = node->next;
        }
    }
}

