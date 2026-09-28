#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08070af8
/* match-compiler: old_agbcc */

// Points every glyph of the group at the shared affine object. Bit 9 (OAM
// double size) is set when the scale would clip the sprite, unless the group
// asks for no double size (unk08 bit 3).
#define GROUP_APPLY_AFFINE(g, aff)                                  \
    {                                                               \
        u32 bits = ((aff->unk08 & 0x3E0) << 20) | 0x100;            \
        struct Sprite *node = (struct Sprite *)g->glyphs.head;  \
        s32 n = g->glyphs.count;                                     \
        if (!(g->flags & 8))                                        \
        {                                                           \
            if (aff->angle != 0)                                    \
            {                                                       \
                if (aff->scaleX > 0xB0 || aff->scaleY > 0xB0)         \
                    bits |= 0x200;                                  \
            }                                                       \
            else if (aff->scaleX > 0x100 || aff->scaleY > 0x100)      \
                bits |= 0x200;                                      \
        }                                                           \
        for (n--; n != -1; n--)                                     \
        {                                                           \
            node->affine = (struct Sprite *)aff;                   \
            node->unk10 = (node->unk10 & 0xC1FFFCFF) | bits;        \
            node = node->next;                                     \
        }                                                           \
        AffineObjLock(aff);                                          \
    }

// Sets a text sprite group's scale (x, y): per glyph when the group scales its
// glyphs individually (unk08 bit 2), otherwise re-creates the shared affine
// object and patches every glyph's OAM affine index and double-size bit
// (cleared again if no affine slot is free).
void TextGroupSetScale(struct TextGroup *g, u16 x, u16 y)
{
    struct AffineObj *aff;

    if (g->glyphs.count == 0)
        return;
    if (g->flags & 4)
    {
        struct Sprite *node = (struct Sprite *)g->glyphs.head;
        s32 n;

        for (n = g->glyphs.count - 1; n != -1; n--)
        {
            sub_080703FC((struct Unk703FC *)node, x, y);
            node = node->next;
        }
    }
    else if ((aff = g->affine) != NULL)
    {
        AffineObjUnlock(aff);
        aff = g->affine = BtlObjSetAffine(aff, x, y, aff->angle);
        if (aff == NULL)
        {
            struct Sprite *node = (struct Sprite *)g->glyphs.head;
            s32 n = g->glyphs.count;

            for (n--; n != -1; n--)
            {
                node->affine = NULL;
                node->unk10 &= 0xC1FFFCFF;
                node = node->next;
            }
        }
        else
            GROUP_APPLY_AFFINE(g, aff)
    }
    else
    {
        aff = g->affine = BtlObjSetAffine(NULL, x, y, 0);
        if (aff != NULL)
            GROUP_APPLY_AFFINE(g, aff)
    }
    sub_080706B0((struct Unk70C98 *)g);
}

