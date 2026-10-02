#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806c388
/* match-compiler: old_agbcc */
// Build the collision quadtree over [x0, x1] x [y0, y1]: collect the mesh
// edges whose (16px-padded) bounds touch the box, and split into four
// children while more than unk3C edges touch it and it is at least 128px
// square; otherwise make it a leaf listing those edges (NULL if none).
typedef u8 (*EdgeFilter)(struct Unk6C388Mesh *, struct Unk6C388Edge *);

struct Unk6C388Node *CollisionQuadtreeBuild(struct Unk6C388Tree *t, struct Unk6C388Node *n, s32 x0, s32 y0, s32 x1, s32 y1, EdgeFilter filter)
{
    struct Unk6C388Mesh *mesh;
    struct Unk6C388Edge *e;
    struct Unk6C388Vert *verts;
    struct Unk6C388Vert *a, *b;
    s32 w, h;
    s32 i;
    s32 count;
    s32 start;
    s32 full;
    s32 minX, maxX, minY, maxY, tmp;
    u16 flags;
    s32 midX, midY;

    mesh = t->unk10;
    e = mesh->unk0C;
    verts = mesh->unk04;
    count = 0;
    start = t->unk3A;
    full = 0;
    n->unk18 = x0;
    n->unk20 = x1;
    n->unk1C = y0;
    n->unk24 = y1;
    w = x1 - x0;
    h = y1 - y0;
    for (i = 0; i < mesh->unk00->unk08; e++, i++)
    {
        a = &verts[e->unk00];
        b = &verts[e->unk04];
        if (e->unk11 & 8)
            continue;
        if (filter != NULL && !filter(mesh, e))
            continue;
        if (e->unk00 < 0 || e->unk04 < 0)
            continue;
        minX = a->unk00;
        minY = a->unk04;
        maxX = b->unk00;
        maxY = b->unk04;
        if (minX > maxX)
        {
            tmp = maxX;
            maxX = minX;
            minX = tmp;
        }
        if (minY > maxY)
        {
            tmp = maxY;
            maxY = minY;
            minY = tmp;
        }
        minX -= 16;
        maxX += 16;
        minY -= 16;
        maxY += 16;
        flags = 0;
        if (minX >= x0 && minX <= x1)
            flags = 1;
        if (maxX >= x0 && maxX <= x1)
            flags |= 1;
        if (minY >= y0 && minY <= y1)
            flags |= 2;
        if (maxY >= y0 && maxY <= y1)
            flags |= 2;
        if (minX <= x0 && maxX >= x1 && (flags & 2))
            flags = 3;
        if (minY <= y0 && maxY >= y1 && (flags & 1))
            flags = 3;
        if (minX <= x0 && maxX >= x1 && minY <= y0 && maxY >= y1)
        {
            flags = 3;
            full++;
        }
        if (flags == 3)
        {
            if (start < t->unk40)
            {
                t->unk30[start] = e;
                start++;
            }
            else
            {
                DebugPrint((void *)0x083D1EE8);
            }
            count++;
        }
    }
    if (count > t->unk3C && full < t->unk3C && w > 0x7F && h > 0x7F)
    {
        midX = x0 + ((x1 - x0) >> 1);
        midY = y0 + ((y1 - y0) >> 1);
        n->unk10 = NULL;
        n->unk14 = 0;
        n->unk28 = 0;
        n->unk2A = 0;
        if (t->unk38 + 4 >= t->unk3E)
            DebugPrint((void *)0x083D1F14);
        n->unk00 = &t->unk2C[t->unk38++];
        n->unk04 = &t->unk2C[t->unk38++];
        n->unk08 = &t->unk2C[t->unk38++];
        n->unk0C = &t->unk2C[t->unk38++];
        n->unk00 = CollisionQuadtreeBuild(t, n->unk00, x0, y0, midX, midY, filter);
        n->unk04 = CollisionQuadtreeBuild(t, n->unk04, midX, y0, x1, midY, filter);
        n->unk08 = CollisionQuadtreeBuild(t, n->unk08, x0, midY, midX, y1, filter);
        n->unk0C = CollisionQuadtreeBuild(t, n->unk0C, midX, midY, x1, y1, filter);
        return n;
    }
    n->unk28 = count;
    n->unk2A = 0;
    n->unk14 = 0;
    n->unk10 = &t->unk30[t->unk3A];
    t->unk3A = start;
    if (count > 32)
        DebugPrint((void *)0x083D1F5C, count, 32);
    if (count == 0)
        return NULL;
    return n;
}

