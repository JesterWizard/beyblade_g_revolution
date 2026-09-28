#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806211c
/* match-compiler: old_agbcc */
// Attaches a new OAM object (pool tile `tile`) to sprite `a`, positioned at
// (x, y) pixels and optionally parented to `parent`, and resets its motion and
// animation state. Returns FALSE if no object could be allocated.
bool32 sub_0806211C(struct Unk62634 *a, struct Unk6225CSource *parent, struct Unk6FF58Src *src, s32 x, s32 y,
    u8 objMode, u16 tile, u8 flip, u16 h)
{
    struct Unk705DC *obj;
    u8 priority = 0;
    s32 px, py;

    if (a == NULL || src == NULL)
        return FALSE;
    obj = BtlObjPoolAlloc(tile);
    if (obj == NULL)
        return FALSE;
    if (parent != NULL)
        priority = sub_08069C14((struct Unk69C14 *)parent);
    px = x << 8;
    py = y << 8;
    SpriteInitFromTemplate(obj, src, px, py, objMode, priority, flip, h);
    a->unk04 = parent;
    a->unk08 = obj;
    a->unk30 = 0;
    a->unk34 = 0;
    a->unk38 = 0;
    a->unk3C = 0;
    a->unk24 = px;
    a->unk28 = py;
    a->unk40 = 0x10;
    a->unk58 = src->unk04;
    a->unk5A = src->unk05;
    a->unk0C = 0;
    a->unk5E = 0;
    a->unk5C = 0;
    a->unk10 = 0;
    a->unk44 = tile;
    a->unk14 = src;
    a->unk60 = 0;
    a->unk20 = 0;
    a->unk1C = -1;
    a->unk18 = 0;
    a->unk00 = NULL;
    a->unk56 |= -1;
    a->unk54 |= -1;
    a->unk50 = 0;
    a->unk48 = (a->unk58 >> 1) << 8;
    a->unk4C = (a->unk5A >> 1) << 8;
    sub_0806225C(a);
    return TRUE;
}

