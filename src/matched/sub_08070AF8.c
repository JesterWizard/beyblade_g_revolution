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
        struct Unk705DC *node = (struct Unk705DC *)g->unk14.unk00;  \
        s32 n = g->unk14.unk08;                                     \
        if (!(g->unk08 & 8))                                        \
        {                                                           \
            if (aff->unk18 != 0)                                    \
            {                                                       \
                if (aff->unk14 > 0xB0 || aff->unk16 > 0xB0)         \
                    bits |= 0x200;                                  \
            }                                                       \
            else if (aff->unk14 > 0x100 || aff->unk16 > 0x100)      \
                bits |= 0x200;                                      \
        }                                                           \
        for (n--; n != -1; n--)                                     \
        {                                                           \
            node->unk30 = (struct Unk705DC *)aff;                   \
            node->unk10 = (node->unk10 & 0xC1FFFCFF) | bits;        \
            node = node->unk04;                                     \
        }                                                           \
        sub_080705CC(aff);                                          \
    }

// Moves a text sprite group to (x, y): per glyph for scaled groups, otherwise
// re-creates the shared affine object and patches every glyph's OAM affine
// index and double-size bit (cleared again if no affine slot is free).
void sub_08070AF8(struct Unk7069C *g, u16 x, u16 y)
{
    struct Unk70354Object *aff;

    if (g->unk14.unk08 == 0)
        return;
    if (g->unk08 & 4)
    {
        struct Unk705DC *node = (struct Unk705DC *)g->unk14.unk00;
        s32 n;

        for (n = g->unk14.unk08 - 1; n != -1; n--)
        {
            sub_080703FC((struct Unk703FC *)node, x, y);
            node = node->unk04;
        }
    }
    else if ((aff = g->unk2C) != NULL)
    {
        sub_080705D4(aff);
        aff = g->unk2C = BtlObjSetAffine(aff, x, y, aff->unk18);
        if (aff == NULL)
        {
            struct Unk705DC *node = (struct Unk705DC *)g->unk14.unk00;
            s32 n = g->unk14.unk08;

            for (n--; n != -1; n--)
            {
                node->unk30 = NULL;
                node->unk10 &= 0xC1FFFCFF;
                node = node->unk04;
            }
        }
        else
            GROUP_APPLY_AFFINE(g, aff)
    }
    else
    {
        aff = g->unk2C = BtlObjSetAffine(NULL, x, y, 0);
        if (aff != NULL)
            GROUP_APPLY_AFFINE(g, aff)
    }
    sub_080706B0((struct Unk70C98 *)g);
}

