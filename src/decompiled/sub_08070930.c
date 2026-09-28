/* match-compiler: old_agbcc */
#define TextGroupAppendString sub_08070930_x
#include "global.h"
#undef TextGroupAppendString
// Appends the glyphs of a string to a text sprite group at x = unk0A, growing
// the sprite chain and advancing x by each glyph width (space: unk28).
#include "ram_map.h"

u8 TextGroupAppendString(struct TextGroup *a, u8 *s, u8 pal)
{
    u32 count;
    struct Sprite *first;
    u32 len;
    u8 defWidth;
    u8 *widths;
    u16 x;
    u16 flip;
    u16 mode;
    struct Sprite *node;
    struct AffineObj *aff;
    u32 bits;
    u8 c;
    u16 w;

    len = StringCountNonSpace(s);
    defWidth = a->font->unk04;
    widths = a->widthTable;
    count = a->glyphs.count;
    x = a->penX;
    flip = 0;
    mode = (a->flags & 0x180) >> 7;
    if (s != NULL && *s != 0)
    {
        node = (struct Sprite *)a->glyphs.tail;
        first = (struct Sprite *)BtlObjPoolResizeChain(&a->glyphs, len + count, a->unk2B);
        if (first == NULL)
        {
            DebugPrint((void *)0x083D22D4, s);
            return 0;
        }
        if (node != NULL)
            first = node->next;
        node = first;
        aff = a->affine;
        if (aff != NULL)
        {
            bits = ((aff->unk08 & 0x3E0) << 20) | 0x100;
            if (!(a->flags & 8))
            {
                if (aff->angle != 0)
                {
                    if (aff->scaleX > 0xB0 || aff->scaleY > 0xB0)
                        bits |= 0x200;
                }
                else if (aff->scaleX > 0xB0 || aff->scaleY > 0xB0)
                    bits |= 0x200;
            }
        }
        while ((c = *s++) != 0)
        {
            w = defWidth;
            if (c == ' ')
            {
                w = a->spaceWidth;
                flip = 0x8000;
            }
            else
            {
                c = gData_080BB748[c];
                SpriteInitFromTemplate(node, a->font, 0, 0, 0, mode, 0, c);
                TextEntrySetPaletteBank(node, pal);
                SpriteSetObjMode(node, a->objMode);
                if (widths != NULL)
                    w = w - widths[c];
                w = w + a->letterSpacing;
                node->unk1E = x | flip;
                flip = 0;
                if (aff != NULL)
                {
                    node->unk10 = (node->unk10 & 0xC1FFFCFF) | bits;
                    node->affine = (struct Sprite *)aff;
                }
                node = node->next;
            }
            x += w;
        }
        sub_080706B0((struct Unk70C98 *)a);
        a->penX = x;
        return 1;
    }
}
