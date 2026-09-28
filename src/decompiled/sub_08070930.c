/* match-compiler: old_agbcc */
#define TextGroupAppendString sub_08070930_x
#include "global.h"
#undef TextGroupAppendString
// Appends the glyphs of a string to a text sprite group at x = unk0A, growing
// the sprite chain and advancing x by each glyph width (space: unk28).
#include "ram_map.h"

u8 TextGroupAppendString(struct Unk7069C *a, u8 *s, u8 pal)
{
    u32 count;
    struct Unk705DC *first;
    u32 len;
    u8 defWidth;
    u8 *widths;
    u16 x;
    u16 flip;
    u16 mode;
    struct Unk705DC *node;
    struct Unk70354Object *aff;
    u32 bits;
    u8 c;
    u16 w;

    len = StringCountNonSpace(s);
    defWidth = a->unk24->unk04;
    widths = a->unk20;
    count = a->unk14.unk08;
    x = a->unk0A;
    flip = 0;
    mode = (a->unk08 & 0x180) >> 7;
    if (s != NULL && *s != 0)
    {
        node = (struct Unk705DC *)a->unk14.unk04;
        first = (struct Unk705DC *)BtlObjPoolResizeChain(&a->unk14, len + count, a->unk2B);
        if (first == NULL)
        {
            DebugPrint((void *)0x083D22D4, s);
            return 0;
        }
        if (node != NULL)
            first = node->unk04;
        node = first;
        aff = a->unk2C;
        if (aff != NULL)
        {
            bits = ((aff->unk08 & 0x3E0) << 20) | 0x100;
            if (!(a->unk08 & 8))
            {
                if (aff->unk18 != 0)
                {
                    if (aff->unk14 > 0xB0 || aff->unk16 > 0xB0)
                        bits |= 0x200;
                }
                else if (aff->unk14 > 0xB0 || aff->unk16 > 0xB0)
                    bits |= 0x200;
            }
        }
        while ((c = *s++) != 0)
        {
            w = defWidth;
            if (c == ' ')
            {
                w = a->unk28;
                flip = 0x8000;
            }
            else
            {
                c = gData_080BB748[c];
                SpriteInitFromTemplate(node, a->unk24, 0, 0, 0, mode, 0, c);
                TextEntrySetPaletteBank(node, pal);
                SpriteSetObjMode(node, a->unk0E);
                if (widths != NULL)
                    w = w - widths[c];
                w = w + a->unk29;
                node->unk1E = x | flip;
                flip = 0;
                if (aff != NULL)
                {
                    node->unk10 = (node->unk10 & 0xC1FFFCFF) | bits;
                    node->unk30 = (struct Unk705DC *)aff;
                }
                node = node->unk04;
            }
            x += w;
        }
        sub_080706B0((struct Unk70C98 *)a);
        a->unk0A = x;
        return 1;
    }
}
