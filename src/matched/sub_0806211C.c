#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806211c
/* match-compiler: old_agbcc */
// Attaches a new OAM object (pool tile `tile`) to sprite `a`, positioned at
// (x, y) pixels and optionally parented to `parent`, and resets its motion and
// animation state. Returns FALSE if no object could be allocated.
bool32 sub_0806211C(struct SceneObjSprite *a, struct MotionAnchor *parent, struct Unk6FF58Src *src, s32 x, s32 y,
    u8 objMode, u16 tile, u8 flip, u16 h)
{
    struct Sprite *obj;
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
    a->anchor = parent;
    a->sprite = obj;
    a->velX = 0;
    a->velY = 0;
    a->accelX = 0;
    a->accelY = 0;
    a->posX = px;
    a->posY = py;
    a->drag = 0x10;
    a->width = src->unk04;
    a->height = src->unk05;
    a->unk0C = 0;
    a->unk5E = 0;
    a->unk5C = 0;
    a->unk10 = 0;
    a->tileId = tile;
    a->unk14 = src;
    a->paletteBank = 0;
    a->unk20 = 0;
    a->unk1C = -1;
    a->unk18 = 0;
    a->frames = NULL;
    a->framesLeft |= -1;
    a->curFrame |= -1;
    a->frameIndex = 0;
    a->halfWidth = (a->width >> 1) << 8;
    a->halfHeight = (a->height >> 1) << 8;
    SceneObjMotionStep(a);
    return TRUE;
}

