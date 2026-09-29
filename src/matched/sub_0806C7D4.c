#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806c7d4
/* match-compiler: old_agbcc */
// Sweep `body` (bounding box + this frame's velocity) against every edge of
// `mesh`. Edge endpoints are 19.5 fixed point. A crossed horizontal side snaps
// the body to it and reflects vy by the edge's bounce factor (x likewise).
// Edges overlapping on both axes are collected into `out` (up to `max`) and
// reported to hooks->onTouch; any bounce is reported to hooks->onBounce.
u16 sub_0806C7D4(struct CollisionBody *body, struct Unk6C388Mesh *mesh, struct Unk6C388Edge **out, u16 max)
{
    struct Unk6C388Edge *e;
    u16 count;
    u16 hitMask;
    s32 i;
    s32 minY, maxY;
    s32 sweepMin, sweepMax;
    s32 bottom;
    s32 minX, maxX;
    u8 bounced;
    u8 overlap;
    s32 checked;
    u8 solid;
    u16 side;
    struct Unk6C388Vert *a, *b;
    s32 aX, aY, bX, bY;
    s32 xMin, xMax;
    s32 top;
    s32 left, right;
    s32 topOff, bottomOff, y, ay;

    count = 0;
    hitMask = 0;
    for (i = 0; i < mesh->unk00->unk08; i++)
    {
        overlap = 0;
        bounced = 0;
        e = &mesh->unk0C[i];
        solid = e->solid;
        checked = 0;
        side = 0;
        a = &mesh->unk04[e->unk00];
        b = &mesh->unk04[e->unk04];
        aX = a->unk00 << 5;
        aY = a->unk04 << 5;
        bX = b->unk00 << 5;
        bY = b->unk04 << 5;

        if (a->unk00 < b->unk00)
        {
            minX = aX;
            maxX = bX;
        }
        else
        {
            minX = bX;
            maxX = aX;
        }
        if (a->unk04 < b->unk04)
        {
            minY = aY;
            maxY = bY;
        }
        else
        {
            minY = bY;
            maxY = aY;
        }

        topOff = body->top << 8;
        bottomOff = body->bottom << 8;
        y = body->y;
        ay = body->ay;
        if (body->vy > 0)
        {
            sweepMin = y + bottomOff;
            sweepMax = sweepMin + body->vy + ay;
            top = y + topOff;
            bottom = sweepMax;
        }
        else
        {
            sweepMax = y + topOff;
            sweepMin = sweepMax + body->vy + ay;
            top = sweepMin;
            bottom = y + bottomOff;
        }
        left = body->x + (body->left << 8);
        right = body->x + (body->right << 8);

        if ((right < minX || maxX < left) && (bottom < minY || maxY < top))
            continue;

        if (right > minX && maxX > left)
        {
            overlap |= 1;
            if (sweepMin <= minY && sweepMax >= minY && (solid & 3))
            {
                if (!checked)
                {
                    if (body->vy > 0)
                        side |= 1;
                    else
                        side |= 2;
                    if (!sub_0806D748((struct Unk6D748 *)body, mesh, (u32)e, side))
                        solid = 0;
                    checked = 1;
                }
                if (body->vy > 0)
                {
                    if (solid & 1)
                    {
                        body->y = minY - (body->bottom << 8);
                        bottom = minY;
                        bounced = 1;
                        hitMask |= 1;
                    }
                }
                else if (solid & 2)
                {
                    body->y = minY - (body->top << 8) + 0x80;
                    top = minY;
                    bounced = 1;
                    hitMask |= 2;
                }
            }
            if (sweepMin <= maxY && sweepMax >= maxY && (solid & 0xC))
            {
                if (!checked)
                {
                    if (body->vy > 0)
                        side |= 4;
                    else
                        side |= 8;
                    if (!sub_0806D748((struct Unk6D748 *)body, mesh, (u32)e, side))
                        solid = 0;
                    checked = 1;
                }
                if (body->vy > 0)
                {
                    if (solid & 4)
                    {
                        body->y = maxY - (body->bottom << 8);
                        bottom = maxY;
                        bounced = 1;
                        hitMask |= 4;
                    }
                }
                else if (solid & 8)
                {
                    body->y = maxY - (body->top << 8) + 0x80;
                    top = maxY;
                    bounced = 1;
                    hitMask |= 8;
                }
            }
        }

        if (body->vx > 0)
        {
            xMin = body->x + (body->right << 8);
            xMax = xMin + body->vx + body->ax;
        }
        else
        {
            xMax = body->x + (body->left << 8);
            xMin = xMax + body->vx + body->ax;
        }
        if (bottom > minY && maxY > top)
        {
            overlap |= 2;
            if (xMin <= minX && xMax >= minX && (solid & 0x30))
            {
                if (!checked)
                {
                    if (body->vx > 0)
                        side |= 0x10;
                    else
                        side |= 0x20;
                    if (!sub_0806D748((struct Unk6D748 *)body, mesh, (u32)e, side))
                        solid = 0;
                    checked = 1;
                }
                if (body->vx > 0)
                {
                    if (solid & 0x10)
                    {
                        body->x = minX - (body->right << 8);
                        bounced |= 2;
                        hitMask |= 0x10;
                    }
                }
                else if (solid & 0x20)
                {
                    body->x = minX - (body->left << 8) + 0x80;
                    bounced |= 2;
                    hitMask |= 0x20;
                }
            }
            if (xMin <= maxX && xMax >= maxX && (solid & 0xC0))
            {
                if (!checked)
                {
                    if (body->vx > 0)
                        side |= 0x40;
                    else
                        side |= 0x80;
                    if (!sub_0806D748((struct Unk6D748 *)body, mesh, (u32)e, side))
                        solid = 0;
                    checked = 1;
                }
                if (body->vx > 0)
                {
                    if (solid & 0x40)
                    {
                        body->x = maxX - (body->right << 8);
                        bounced |= 2;
                        hitMask |= 0x40;
                    }
                }
                else if (solid & 0x80)
                {
                    body->x = maxX - (body->left << 8) + 0x80;
                    bounced |= 2;
                    hitMask |= 0x80;
                }
            }
        }

        if (overlap == 3)
        {
            if (out != NULL && count < max)
            {
                out[count] = e;
                count++;
            }
            if (body->hooks != NULL && body->hooks->onTouch != NULL)
                body->hooks->onTouch(body, mesh, e);
        }
        if (bounced & 1)
        {
            s32 v = (body->vy * e->bounce) >> 7;
            if ((v < 0 ? -v : v) <= 0xFF)
                v = 0;
            body->vy = -v;
        }
        if (bounced & 2)
        {
            s32 v = (body->vx * e->bounce) >> 7;
            if ((v < 0 ? -v : v) <= 0xFF)
                v = 0;
            body->vx = -v;
        }
        if (bounced != 0 && body->hooks != NULL && body->hooks->onBounce != NULL)
            body->hooks->onBounce(body, mesh, e, hitMask);
    }
    return count;
}

