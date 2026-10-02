#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

/* fn: sub_0802B930 */
// @ 0x0802b930
// The beyblade roster lookup: 62 records of 0x1C bytes at ROM 0x08075AB8. Scans
// for the record whose `id` (s16 +0x04) equals the argument and returns its
// `profile` (s32 +0x00), or -1. The address stays a literal: as a data symbol
// agbcc folds the pool load differently and the bytes stop matching (see the
// note at the top of asm/data_symbols.s).
s32 BeybladeGetProfile(s32 a)
{
    s32 i;
    struct BeybladeDef *p;

    i = 0;
    p = (struct BeybladeDef *)0x08075AB8;
    for (; i <= 0x3D; p++, i++)
    {
        if (p->id == a)
            return p->profile;
    }
    return -1;
}

/* fn: sub_0802E210 */
// @ 0x0802e210
s8 BitBeastLevel(void)
{
    struct Unk42E78 *p;

    p = BeybladeCollectionEntry(gUnk_0300026C->unk4E);
    return ExpBracket(p->bitBeastExp);
}

/* fn: sub_080302E0 */
// @ 0x080302e0
/* match-compiler: old_agbcc */
/* Advance battler spin angle by speed/0x900 (direction from unk1F bit 6) and update its sprite. */
void BeybladeSpinStep(struct Unk346C0 *a)
{
    s32 speed;
    s32 angle;
    s32 delta;
    struct BattleWork **work = gBattleWorkPtrLoc;
    struct BattleWork **dest;

    speed = (*work)->unk013C.values[a->unk30C];
    angle = (*work)->unk0AE8.words[a->unk30C];
    delta = _080740B0(speed << 16, 0x900);
    dest = work;
    if (a->unk04->unk28->unk1F & 0x40)
        angle -= delta;
    else
        angle += delta;
    (*dest)->unk0AE8.words[a->unk30C] = angle;
    angle = (angle >> 8) & 0xFF;
    if (a->unk00->unk00 != NULL)
    {
        if ((delta >> 8) > 0x1F)
            a->unk00->unk00->unk18 = RandRange(2);
        else
            a->unk00->unk00->unk18 = 2;
        if (a->unk00->unk00->affine != NULL)
            SpriteApplyAffine((struct Unk70354 *)a->unk00->unk00, a->unk00->unk00->affine->unk14, a->unk00->unk00->affine->unk16, angle);
    }
}

/* fn: sub_08030638 */
// @ 0x08030638
/* match-compiler: old_agbcc */
// Nudge battler A's motion by the d-pad direction in a->unk302, scaled by b
// and rotated into camera space by -unkAA8.unk14.
void BeybladeSteerByDpad(struct Unk346C0 *a, s32 b)
{
    struct Unk30638AA8 *cam;
    s32 angle;
    s32 step;
    s32 x, y, s, c, rx, ry;
    u8 idx;
    u32 rot;

    angle = 0;
    cam = &gData_03000290->unkAA8;
    if (a->unk302 & 0xC0)
    {
        step = 0x20;
        if (a->unk302 & 0x80)
            angle = 0x80;
        else
            step = -0x20;
        if (a->unk302 & 0x20)
            angle += step;
        if (a->unk302 & 0x10)
            angle -= step;
    }
    else
    {
        if (a->unk302 & 0x20)
            angle = 0xC0;
        if (a->unk302 & 0x10)
            angle = 0x40;
    }
    x = (b * gData_083C9544[(u8)angle]) >> 8;
    y = -(b * gData_083C9544[(u8)angle + 0x40]) >> 8;
    rot = (u32)(-cam->unk14 & 0xFFFF) >> 8;
    s = gData_083C9544[rot];
    c = gData_083C9544[rot + 0x40];
    rx = ((x * c) >> 8) + ((y * s) >> 8);
    ry = ((y * c) >> 8) - ((x * s) >> 8);
    if (a->unk302 & 0xF0)
    {
        gData_03000290->unk328.unk18 += rx;
        gData_03000290->unk328.unk1C += ry;
    }
}

/* fn: sub_080348E8 */
// @ 0x080348e8
/* match-compiler: old_agbcc */
// Per-frame update of a battle participant: animation/collision step, input,
// optional attack (sub_08034A68), then the timed states 7 (countdown in unk2FC,
// then switch to 5) and 5 (countdown in unk2F8 with the unk312 start/finish
// animations).
void BeybladeUpdate(struct Unk346C0 *a, u32 b)
{
    s32 *counter;
    u32 flag;
    u8 *flag_ptr;

    a->unk30E = BeybladeHomeToward(a->unk00, 0x10000, 0x10000, 0xC8, 0x8000);
    if (sub_08035D1C(a->unk00, 0x10000, 0x10000) == 1)
        SfxPlayVariant(4, 0x38, 7);
    BeybladeMotionStep((struct BeybladeBody *)a->unk00);
    if (a->unk18 == 1)
        sub_08035884(&a->unk08);
    BtlCaptureInput(a);
    if (a->unk310 != 0 &&
        a->unk2CC != 2 &&
        a->unk2CC != 6 &&
        a->unk2CC != 3 &&
        sub_08034FBC((struct Unk34FF8 *)a) != 0)
    {
        sub_08034A68(a, b);
    }
    sub_08034618(a);
    if (a->unk2CC == 7)
    {
        counter = &a->unk2FC;
        if (*counter >= 0)
        {
            sub_08034810(a, *counter);
            (*counter)--;
        }
        else
        {
            a->unk2CC = 5;
            a->unk310 = 0;
            sub_0803484C((struct Unk3484C *)a);
            a->unk2F8 = -1;
        }
    }
    flag = a->unk310;
    if (flag == 0 && a->unk2CC == 5)
    {
        counter = &a->unk2F8;
        if (*counter >= 0)
        {
            flag_ptr = &a->unk312;
            if (*flag_ptr == 0)
            {
                sub_08035204(a, 0, 0x0A, -1);
                *flag_ptr = 1;
                a->unk2B0 = flag;
                a->unk2B4 = 8;
            }
            (*counter)--;
        }
        else if (a->unk312 == 1)
        {
            sub_08035204(a, 0, 0x0B, -1);
            a->unk08C = AnimDurationForKey(&a->unk1C, 0);
            a->unk2B0 = flag;
            a->unk2B4 = 8;
            a->unk312 = flag;
        }
    }
}

/* fn: sub_0803531C */
// @ 0x0803531c
void BeybladeEffectsUpdate(struct Unk35258 *a)
{
    u32 r0;
    u32 r1;
    u32 r5;

    if (a->unk1C.unk70 == 0)
        BattleAnimStop(a, 0);
    if (a->unk1D4.unk70 == 0)
        BattleAnimStop(a, 2);
    if (a->unkF8.unk70 == 0)
        BattleAnimStop(a, 1);

    r5 = (u32)&a->unk2C5;
    r0 = 1;
    r1 = *(u8 *)r5;
    r0 &= r1;
    if (r0 != 0)
        SceneObjUpdate(&a->unk1C);

    r0 = 4;
    r1 = *(u8 *)r5;
    r0 &= r1;
    if (r0 != 0)
        SceneObjUpdate(&a->unk1D4);

    r1 = *(u8 *)r5;
    r0 = 2;
    r5 = *(u8 *)r5;
    r0 &= r5;
    if (r0 != 0)
        SceneObjUpdate(&a->unkF8);
}

/* fn: sub_080353A0 */
// @ 0x080353a0
/* match-compiler: old_agbcc */
void BeybladeEffectsPlace(struct Unk35258 *a)
{
    if ((1 & a->unk2C5) != 0)
    {
        a->unk2B0 += a->unk2B4;
        sub_080686D8(&a->unk1C);
        BtlPlaceSpriteAtWorld(
            &a->unk1C,
            a->unk00->unk0C,
            a->unk00->unk10,
            a->unk00->unk14,
            0,
            0,
            a->unk2B0 << 8);
    }
    if ((4 & a->unk2C5) != 0)
    {
        sub_080686D8(&a->unk1D4);
        BtlPlaceSpriteAtWorld(&a->unk1D4, a->unk2E4, a->unk2E8, a->unk2EC, 0, 0, 0);
    }
    if ((2 & a->unk2C5) != 0)
    {
        sub_080686D8(&a->unkF8);
        BtlPlaceSpriteAtWorld(
            &a->unkF8,
            a->unk00->unk0C,
            a->unk00->unk10,
            a->unk00->unk14,
            0,
            0x2000,
            a->unk00->unk52 << 8);
    }
}

/* fn: sub_08035984 */
// @ 0x08035984
// Per-frame motion step: heading byte from the velocity angle, clamp velocity,
// integrate position/velocity/accel, apply damping, advance the sine wobble.
void BeybladeMotionStep(struct BeybladeBody *a)
{
    s32 speed;
    s32 sn;
    s32 cs;
    u32 idx;
    s32 vx;
    s32 vy;
    s32 speed16;
    s32 half;
    s32 table_value;
    s32 factor;
    s32 x;
    s32 y;
    s32 z;
    s32 index;
    const u8 *table8;

    vx = a->velX;
    vy = a->velY;
    speed = Sqrt(vx * vx + vy * vy);
    speed16 = (u16)speed;
    vy = Div(vy << 8, speed16); // vy now holds the angle
    half = vy >> 1;
    if (half > 0x7F)
        half = 0x7F;
    if (half < -0x80)
        half = -0x80;
    table8 = gData_083C97C4;
    index = (s8)half + 0x80;
    table_value = table8[index];
    a->heading = table_value;
    if (a->velX > 0)
        a->heading = 0xFF - table_value;

    if (a->velX > 0x1000)
        a->velX = 0x1000;
    if (a->velX < -0x1000)
        a->velX = -0x1000;
    if (a->velY > 0x1000)
        a->velY = 0x1000;
    if (a->velY < -0x1000)
        a->velY = -0x1000;

    a->posX += a->velX;
    a->posY += a->velY;
    a->posZ += a->velZ;
    a->velX += a->accelX;
    a->velY += a->accelY;
    a->velZ += a->accelZ;

    factor = a->drag;
    x = (a->velX * factor) >> 8;
    y = (a->velY * factor) >> 8;
    z = (a->velZ * factor) >> 8;
    if (factor != 0)
    {
        if (x != 0)
            a->velX -= x;
        else if (a->velX != 0)
        {
            if (a->velX > 0)
                a->velX--;
            else
                a->velX++;
        }
        if (y != 0)
            a->velY -= y;
        else if (a->velY != 0)
        {
            if (a->velY > 0)
                a->velY--;
            else
                a->velY++;
        }
        if (z != 0)
            a->velZ -= z;
        else if (a->velZ != 0)
        {
            if (a->velZ > 0)
                a->velZ--;
            else
                a->velZ++;
        }
    }

    idx = (a->wobblePhase + a->wobbleSpeed) & 0xFFFF;
    a->wobblePhase = idx;
    sn = gData_083C9544[idx >> 8];
    cs = gData_083C9544[(idx >> 8) + 0x40];
    a->wobbleX = (sn * a->wobbleAmp) >> 8;
    a->wobbleY = (cs * a->wobbleAmp) >> 8;
}

/* fn: sub_08035AE0 */
// @ 0x08035ae0
// Sphere overlap response between two motion objects: if closer than the summed
// radii, push both apart along the contact normal and exchange velocity scaled
// by each mass (unk34) and a random 1.0-2.0 factor. Returns 1 on contact.
// (The do/while(0) scope around the setup is needed for register allocation.)
s32 BeybladeCollisionResponse(
    struct Unk346C0Inner *a, struct Unk346C0Inner *b)
{
    s32 result;
    s32 threshold;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 distance;
    s32 length;
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 velocity_distance;
    s32 midpoint_x;
    s32 midpoint_y;
    s32 offset_x;
    s32 offset_y;
    s32 scale;

    do
    {
        result = 0;
        threshold = a->unk38 + b->unk38;
    } while (0);
    dx = (b->unk0C - a->unk0C) >> 8;
    dy = (b->unk10 - a->unk10) >> 8;
    dz = (b->unk14 - a->unk14) >> 8;
    distance = dx * dx + dy * dy + dz * dz;
    scale = RandRange(0x100) + 0x100;
    if (distance < threshold)
    {
        length = (u16)Sqrt(distance);
        dx = Div(dx << 8, length);
        dy = Div(dy << 8, length);
        dz = Div(dz << 8, length);
        velocity_x = a->unk18 - b->unk18;
        velocity_y = a->unk1C - b->unk1C;
        velocity_z = a->unk20 - b->unk20;
        velocity_distance = (u16)Sqrt(velocity_x * velocity_x + velocity_y * velocity_y + velocity_z * velocity_z);
        midpoint_x = (a->unk0C + b->unk0C) >> 1;
        midpoint_y = (a->unk10 + b->unk10) >> 1;
        a->unk0C = midpoint_x - (dx << 4);
        a->unk10 = midpoint_y - (dy << 4);
        b->unk0C = midpoint_x + (dx << 4);
        b->unk10 = midpoint_y + (dy << 4);
        dx = (dx * velocity_distance) >> 8;
        dy = (dy * velocity_distance) >> 8;
        dz = (dz * velocity_distance) >> 8;
        a->unk18 -= (dx * (s32)a->unk34 * scale) >> 16;
        a->unk1C -= (dy * (s32)a->unk34 * scale) >> 16;
        a->unk20 -= (dz * (s32)a->unk34 * scale) >> 16;
        b->unk18 += (dx * (s32)b->unk34 * scale) >> 16;
        b->unk1C += (dy * (s32)b->unk34 * scale) >> 16;
        b->unk20 += (dz * (s32)b->unk34 * scale) >> 16;
        result = 1;
    }
    return result;
}

/* fn: sub_08035C64 */
// @ 0x08035c64

// @ 0x08035c64
u8 BeybladeHomeToward(struct Unk346C0Inner *a, s32 x, s32 y, s32 z, s32 threshold)
{
    s32 dx;
    s32 dy;
    s32 distSq;
    s32 sumSq;
    s32 randScale;
    u16 speed;
    s32 vx;
    s32 vy;
    u16 curSpeed;
    s32 scale;

    dx = (x - a->unk0C) >> 8;
    dy = (y - a->unk10) >> 8;
    distSq = (z * z) - a->unk38;
    sumSq = (dx * dx) + (dy * dy);
    randScale = RandRange(0x80) + 0x100;
    if (sumSq <= distSq)
        goto ret1;
    if (a->unk14 >= threshold)
        goto ret0;
    speed = Sqrt(sumSq);
    vx = Div(dx << 8, speed);
    vy = Div(dy << 8, speed);
    curSpeed = Sqrt((a->unk18 * a->unk18) + (a->unk1C * a->unk1C));
    do { } while (0);
    curSpeed = (scale = curSpeed);
    scale = (randScale * scale) >> 8;
    vx = (vx * scale) >> 8;
    vy = (vy * scale) >> 8;

    a->unk18 += vx;
    a->unk1C += vy;
ret1:
    return 1;
ret0:
    a->unk2C = 0;
    a->unk20 = 0;
    a->unk1C = 0;
    a->unk18 = 0;
    return 0;
}

/* fn: sub_0803C500 */
// @ 0x0803c500

void LaunchShowPowerMeter(s32 a)
{
    struct BattleWork **btl_loc;
    struct BattleWork *btl;
    s32 remain;
    void *buf_a;
    void *buf_b;
    void **table;

    buf_a = StringAlloc(0x20);
    buf_b = StringAlloc(0x20);
    btl_loc = gBattleWorkPtrLoc;
    GlyphTextInit((struct Unk61E8C *)&(*btl_loc)->powerMeterText, (void *)gData_080B72F3, (struct Unk61E8CSrc *)gData_082BF600, 0xF0, 0x78);
    remain = 0x64 - a;
    TextFormatInt(remain, buf_b, 0x20);
    table = gData_080971EC;
    StringExpandDelim(table[gMainWorkPtr->language], buf_a, buf_b, 0x40, 0x20);
    GlyphTextLayoutWrapped(&(*btl_loc)->powerMeterText, buf_a, 0, 0x3E, 0, 0xFFFF, 0);
    StringFree(buf_a);
    StringFree(buf_b);
    DebugPrint((void *)gData_0833C79C, remain);
    btl = *btl_loc;
    btl->powerRemaining = 0x64 - a;
}

/* fn: sub_0803C5DC */
// @ 0x0803c5dc

void LaunchShowBoostMeter(s32 a)
{
    struct BattleWork **btl_loc;
    struct BattleWork *btl;
    s8 flag;
    void *buf_a;
    void *buf_b;
    void **table;

    flag = (*(btl_loc = gBattleWorkPtrLoc))->boostShown;
    if (flag != 0)
        return;
    buf_a = StringAlloc(0x20);
    buf_b = StringAlloc(0x20);
    GlyphTextInit((struct Unk61E8C *)&(*btl_loc)->boostMeterText, (void *)gData_080B72F3, (struct Unk61E8CSrc *)gData_082BF600, 0xF0, 0x78);
    TextFormatInt(a, buf_b, 0x20);
    table = gData_080971D8;
    StringExpandDelim(table[gMainWorkPtr->language], buf_a, buf_b, 0x40, 0x20);
    GlyphTextLayoutWrapped(&(*btl_loc)->boostMeterText, buf_a, 0, 0x4E, flag, 0xFFFF, flag);
    StringFree(buf_a);
    StringFree(buf_b);
    btl = *btl_loc;
    btl->boostValue = a;
    btl->boostShown = 1;
}

/* fn: sub_0803DBD0 */
// @ 0x0803dbd0
/* match-flags: -fprologue-bugfix */

u32 BeybladeNameGet(u32 a)
{
    u8 *table;
    u32 offset;
    u32 *fallback;
    u32 value;
    s32 row = a;

    if (row >= 0)
    {
        table = gData_080796DC;
        value = gMainWorkPtr->language;
        offset = value * 4 + row * 40;
        value = *(u32 *)(table + offset);
    }
    else
    {
        fallback = (u32 *)gData_08097458;
        value = fallback[gMainWorkPtr->language];
    }
    return value;
}

/* fn: sub_0803DDB0 */
// @ 0x0803ddb0
/* match-compiler: old_agbcc */
// 40-byte row lookup: tbl[a - 1] is a pointer, indexed by gMainWorkPtr->unk1818.
// Same shape as sub_0803DDD8 (different table).
void *LauncherNameGet(s32 a)
{
    u8 *tbl = gData_0807AEEC;
    u32 *row = (u32 *)(tbl + (a - 1) * 4);
    return (void *)*(u32 *)((u8 *)*row + gMainWorkPtr->language * 4);
}

/* fn: sub_0803DDD8 */
// @ 0x0803ddd8
/* match-compiler: old_agbcc */
// 40-byte row lookup: tbl[a - 1] is a pointer, indexed by gMainWorkPtr->unk1818.
// `tbl` must be a local (re-using the symbol twice folds the pool load); the
// dereference stays inline as `*row` so old_agbcc hoists `ldr r1,=tbl` above
// `subs r0,#1` like retail.
void *RipcordNameGet(s32 a)
{
    u8 *tbl = gData_0807AEFC;
    u32 *row = (u32 *)(tbl + (a - 1) * 4);
    return (void *)*(u32 *)((u8 *)*row + gMainWorkPtr->language * 4);
}

/* fn: sub_0803DEC8 */
// @ 0x0803dec8
/* match-compiler: old_agbcc */
// Claim the first free unk08D0 record (unk087C[i] == 0). A negative `row`
// copies template `id` from gData_0807A1F4 and tags it with (id, slot);
// otherwise the record comes from blade row sub_08042E78(row).
void BeybladeRecordClaim(u16 id, u8 row, u8 slot)
{
    s32 i;
    struct Unk42E78 *blade;

    for (i = 0; i <= 0x52; i++)
    {
        if ((s8)gData_03000198->unk087C[i] == 0)
        {
            if ((s8)row < 0)
            {
                gData_03000198->unk08D0[i].unk1D = gData_0807A1F4[(s16)id].unk1D;
                gData_03000198->unk08D0[i].unk21 = gData_0807A1F4[(s16)id].unk21;
                gData_03000198->unk08D0[i].unk20 = gData_0807A1F4[(s16)id].unk20;
                gData_03000198->unk08D0[i].unk26 = gData_0807A1F4[(s16)id].unk26;
                gData_03000198->unk08D0[i].unk1F = gData_0807A1F4[(s16)id].unk1F;
                gData_03000198->unk08D0[i].unk1E = gData_0807A1F4[(s16)id].unk1E;
                gData_03000198->unk08D0[i].unk1C = id;
                gData_03000198->unk08D0[i].unk23 = slot;
                gData_03000198->unk08D0[i].unk14 = gData_0807A1F4[(s16)id].unk14;
                gData_03000198->unk08D0[i].unk18 = gData_0807A1F4[(s16)id].unk18;
            }
            else
            {
                blade = BeybladeCollectionEntry((s8)row);
                gData_03000198->unk08D0[i].unk1D = blade->unk08.unk1D;
                gData_03000198->unk08D0[i].unk21 = blade->unk08.unk21;
                gData_03000198->unk08D0[i].unk20 = blade->unk08.unk20;
                gData_03000198->unk08D0[i].unk26 = blade->unk08.unk26;
                gData_03000198->unk08D0[i].unk23 = blade->unk08.unk23;
                gData_03000198->unk08D0[i].unk1F = blade->unk08.unk1F;
                gData_03000198->unk08D0[i].unk1C = blade->unk08.unk1C;
                gData_03000198->unk08D0[i].unk1E = blade->unk08.unk1E;
                gData_03000198->unk08D0[i].unk14 = blade->unk08.unk14;
                gData_03000198->unk08D0[i].unk18 = blade->unk08.unk18;
            }
            gData_03000198->unk087C[i] = 1;
            gData_03000198->unk0877++;
            gData_03000198->unk1861[gData_03000198->unk08D0[i].unk1C]++;
            return;
        }
    }
}

/* fn: sub_0803E2AC */
// @ 0x0803e2ac
/* match-compiler: old_agbcc */

s32 BeybladeGetType(struct BeybladeBuild *a)
{
    const u8 *t1;
    u32 i1;
    u32 v1;
    u32 v2;
    s32 red;
    s32 green;
    s32 blue;

    if (a == 0)
        return 0;

    t1 = gData_0807BDB8;
    i1 = a->weightDisk * 4;
    red = ((struct Unk3E374Row *)(t1 + i1))->unk00;
    v2 = gData_0807BB80[(s8)a->bladeBase * 4];
    red += ((struct Unk3E374Row *)(gData_0807BB80 + (s8)a->bladeBase * 4))->unk00;

    green = ((struct Unk3E374Row *)(t1 + i1))->unk01;
    v2 = gData_0807BB80[(s8)a->bladeBase * 4];
    green += ((struct Unk3E374Row *)(gData_0807BB80 + (s8)a->bladeBase * 4))->unk01;

    blue = ((struct Unk3E374Row *)(t1 + i1))->unk02;
    v2 = gData_0807BB80[(s8)a->bladeBase * 4];
    blue += ((struct Unk3E374Row *)(gData_0807BB80 + (s8)a->bladeBase * 4))->unk02;

    v2 = gData_0807B6F0[a->attackRing * 4];
    red += ((struct Unk3E374Row *)(gData_0807B6F0 + a->attackRing * 4))->unk00;
    green += ((struct Unk3E374Row *)(gData_0807B6F0 + a->attackRing * 4))->unk01;
    blue += ((struct Unk3E374Row *)(gData_0807B6F0 + a->attackRing * 4))->unk02;

    if (red > 8)
        return 0;
    if (green > 8)
        return 1;
    if (green > 5 && blue > 5)
        return 2;
    return 3;
}

/* fn: sub_0803E328 */
// @ 0x0803e328
/* match-compiler: old_agbcc */

s32 BeybladeAttackRating(struct BeybladeBuild *a)
{
    const u8 *t1 = gData_0807BDB8;
    u32 i1 = a->weightDisk * 4;
    u32 v1;
    u32 v2;

    v1 = t1[i1 + 0];
    v2 = gData_0807BB80[(s8)a->bladeBase * 4 + 0];
    v1 += v2;
    v1 += gData_0807B6F0[a->attackRing * 4 + 0];
    return _080741EC(v1, 3) - 1;
}

/* fn: sub_0803E374 */
// @ 0x0803e374
/* match-compiler: old_agbcc */
// Byte 1 of the 4-byte rows at gData_0807BDB8 / gData_0807BB80 / gData_0807B6F0.
// The discarded `v2 = table[index]` reads hoist each pool load above the index
// math (`ldr r3,=table` before `movs r1,#imm`). Dropping either one misses.
s32 BeybladeDefenseRating(struct BeybladeBuild *a)
{
    const u8 *t1 = gData_0807BDB8;
    u32 i1 = a->weightDisk * 4;
    u32 v1;
    u32 v2;

    v1 = ((struct Unk3E374Row *)(t1 + i1))->unk01;
    v2 = gData_0807BB80[(s8)a->bladeBase * 4];
    v2 = ((struct Unk3E374Row *)(gData_0807BB80 + (s8)a->bladeBase * 4))->unk01;
    v1 += v2;
    v2 = gData_0807B6F0[a->attackRing * 4];
    v1 += ((struct Unk3E374Row *)(gData_0807B6F0 + a->attackRing * 4))->unk01;
    return _080741EC(v1, 3) - 1;
}

/* fn: sub_0803E3C0 */
// @ 0x0803e3c0
/* match-compiler: old_agbcc */
// Byte 2 of the same 4-byte rows as sub_0803E374. Same discarded reads: they
// hoist `ldr r3,=table` above the index math.
s32 BeybladeEnduranceRating(struct BeybladeBuild *a)
{
    const u8 *t1 = gData_0807BDB8;
    u32 i1 = a->weightDisk * 4;
    u32 v1;
    u32 v2;

    v1 = ((struct Unk3E374Row *)(t1 + i1))->unk02;
    v2 = gData_0807BB80[(s8)a->bladeBase * 4];
    v2 = ((struct Unk3E374Row *)(gData_0807BB80 + (s8)a->bladeBase * 4))->unk02;
    v1 += v2;
    v2 = gData_0807B6F0[a->attackRing * 4];
    v1 += ((struct Unk3E374Row *)(gData_0807B6F0 + a->attackRing * 4))->unk02;
    return _080741EC(v1, 3) - 1;
}

/* fn: sub_08042B00 */
// @ 0x08042b00
void *BeybladeGetName(u32 i)
{
    u32 **tbl = (u32 **)gData_08090FF0;
    u8 *p = (u8 *)gData_03000198;

    return (void *)tbl[*(u8 *)(p + 0x1818)][i];
}

/* fn: sub_08042B28 */
// @ 0x08042b28
void *BeybladeGetActorSprite(u32 i)
{
    u32 *t = gData_08091004;

    if (t[i] == 0)
        DebugPrint((void *)0x083A2CD0, i);
    return (void *)t[i];
}

/* fn: sub_08044648 */
// @ 0x08044648
/* match-compiler: old_agbcc */

// Walks a -1-terminated list of Beyblade ids and spawns a scene object for
// each roster entry (side 1), or parks its position record (side 2).
void BeybladeSpawnList(void *arg)
{
    s32 *ids;
    struct Unk6DEF4 *records;
    struct MapView *state;
    s32 id;
    s16 key;
    u16 side;
    s32 *pos;
    struct Actor *obj;
    struct BeybladeDef *def;
    struct BeybladeDef *tbl;

    ids = arg;
    records = (struct Unk6DEF4 *)sub_08062A14();
    state = (struct MapView *)CameraGetActive((struct MapView *)gData_03000198);
    while (*ids != -1)
    {
        id = *ids;
        key = *ids;
        side = GetIndexedRecordWord(key);
        if (side == 1)
        {
            tbl = gData_08075AB8;
            def = &tbl[id];
            pos = (s32 *)PosRecordGet(records, def->variant);
            if (pos != NULL)
            {
                obj = SceneObjSpawn((u32)state, gData_08075AB8[id].param, pos[0] >> 3, pos[1] >> 3);
                obj->unkD4 = (void *)id;
                obj->unkD8 = (void *)(u32)side;
                if (gData_08075AB8[id].type > -1)
                    obj->unk3B = gData_08075AB8[id].type;
                if (obj != NULL)
                {
                    obj->y -= obj->height << 8;
                    obj->x -= (obj->width >> 1) << 8;
                    if ((s16)def->flags != -1)
                        AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)obj, def->flags);
                    if (gData_08075AB8[id].script != 0)
                    {
                        obj->unkC4 = (void *)gData_08075AB8[id].script;
                        sub_080626B8((struct Unk626B8 *)&gData_03000198->unk0524, (u32)obj);
                        obj->unkCC = 8;
                        obj->unkD0 = 8;
                    }
                    if (gData_08075AB8[id].part != 0)
                        ((void (*)(u32, struct Actor *))TaskCreateWithOwner)(gData_08075AB8[id].part, obj);
                    else
                        obj->unkC8 = (void *)gData_08075AB8[id].part;
                }
            }
        }
        else if (GetIndexedRecordWord(key) == 2)
        {
            pos = (s32 *)PosRecordGet(records, gData_08075AB8[id].variant);
            if (pos != NULL)
            {
                pos[0] = -0x400;
                pos[1] = -0x400;
            }
        }
        ids++;
    }
}
