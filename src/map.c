#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"
#include "bgm.h"

/* fn: sub_08043420 */
// @ 0x08043420
/* match-compiler: old_agbcc */
// Steps the 24.8 position (unk0370/unk0374) one unit toward the target
// (unk04/unk06) along the direction in unk00 (0: -unk0374, 1: +unk0374,
// 2: +unk0370, 3: -unk0370), selecting that direction's animation; calls
// sub_08043638 once the target is reached.
void MapCursorMoveStep(void)
{
    struct Unk0554 *move = gUnk_03000554;

    switch (move->unk00)
    {
    case 0:
        if ((gMainWorkPtr->unk0374 >> 8) > move->unk06)
        {
            gMainWorkPtr->unk0374 -= 0x100;
            gMainWorkPtr->unk086C = gMainWorkPtr->unk0374;
            gMainWorkPtr->unk039D = 0;
            gMainWorkPtr->unk1810 = 0x80;
            if (gMainWorkPtr->unk0386 != 10)
                AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk036C, 10);
        }
        else
            sub_08043638();
        break;
    case 1:
        if ((gMainWorkPtr->unk0374 >> 8) < move->unk06)
        {
            gMainWorkPtr->unk0374 += 0x100;
            gMainWorkPtr->unk086C = gMainWorkPtr->unk0374;
            gMainWorkPtr->unk039D = 0;
            gMainWorkPtr->unk1810 = 0x100;
            if (gMainWorkPtr->unk0386 != 11)
                AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk036C, 11);
        }
        else
            sub_08043638();
        break;
    case 2:
        if ((gMainWorkPtr->unk0370 >> 8) < move->unk04)
        {
            gMainWorkPtr->unk0370 += 0x100;
            gMainWorkPtr->unk0868 = gMainWorkPtr->unk0370;
            gMainWorkPtr->unk039D |= 1;
            gMainWorkPtr->unk1810 = 0x20;
            if (gMainWorkPtr->unk0386 != 8)
                AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk036C, 8);
        }
        else
            sub_08043638();
        break;
    case 3:
        if ((gMainWorkPtr->unk0370 >> 8) > move->unk04)
        {
            gMainWorkPtr->unk0370 -= 0x100;
            gMainWorkPtr->unk0868 = gMainWorkPtr->unk0370;
            gMainWorkPtr->unk039D &= 2;
            gMainWorkPtr->unk1810 = 0x40;
            if (gMainWorkPtr->unk0386 != 8)
                AnimObjSelectSeqDefault((struct AnimObjSeqSelect *)&gMainWorkPtr->unk036C, 8);
        }
        else
            sub_08043638();
        break;
    }
}

/* fn: sub_080436B0 */
// @ 0x080436b0
/* match-compiler: old_agbcc */
// Map cursor input. Phase 0: a press of 0x40/0x80/0x10/0x20 follows the
// matching link (unk04..unk10) if the node allows it (unk02 bits 0x10..0x80),
// moving the cursor to that link's map point; held bit 0 with any of unk02's
// low bits set commits (unk181C = 2); held bit 3 sets unk181C = 3.
// Phase 1 runs sub_08043420.
void MapCursorInput(void)
{
    struct Unk436B0Entry *entry;

    switch (gData_03000554->unk01)
    {
    case 0:
        if (gData_03003F60 & 0x40)
        {
            if ((gData_03000554->unk02 & 0x10) && gData_03000558->unk04 != NULL)
            {
                if (gData_03000558->unk34[0] >= 0)
                {
                    s32 *pos = (s32 *)PosRecordGet((struct Unk6DEF4 *)sub_08062A14(), gData_03000558->unk34[0]);
                    gData_03000554->unk04 = pos[0] >> 3;
                    gData_03000554->unk06 = (pos[1] >> 3) - 16;
                }
                entry = gData_03000558->unk04;
                gData_03000198->unk17F6 = entry->unk01;
                gData_03000554->unk01 = 1;
                gData_03000554->unk00 = 0;
                sub_080435D8();
            }
        }
        else if (gData_03003F60 & 0x80)
        {
            if ((gData_03000554->unk02 & 0x20) && gData_03000558->unk08 != NULL)
            {
                if (gData_03000558->unk34[1] >= 0)
                {
                    s32 *pos = (s32 *)PosRecordGet((struct Unk6DEF4 *)sub_08062A14(), gData_03000558->unk34[1]);
                    gData_03000554->unk04 = pos[0] >> 3;
                    gData_03000554->unk06 = (pos[1] >> 3) - 16;
                }
                entry = gData_03000558->unk08;
                gData_03000198->unk17F6 = entry->unk01;
                gData_03000554->unk01 = 1;
                gData_03000554->unk00 = 1;
                sub_080435D8();
            }
        }
        else if (gData_03003F60 & 0x10)
        {
            if ((gData_03000554->unk02 & 0x40) && gData_03000558->unk0C != NULL)
            {
                if (gData_03000558->unk34[2] >= 0)
                {
                    s32 *pos = (s32 *)PosRecordGet((struct Unk6DEF4 *)sub_08062A14(), gData_03000558->unk34[2]);
                    gData_03000554->unk04 = pos[0] >> 3;
                    gData_03000554->unk06 = (pos[1] >> 3) - 16;
                }
                entry = gData_03000558->unk0C;
                gData_03000198->unk17F6 = entry->unk01;
                gData_03000554->unk01 = 1;
                gData_03000554->unk00 = 2;
                sub_080435D8();
            }
        }
        else if (gData_03003F60 & 0x20)
        {
            if ((gData_03000554->unk02 & 0x80) && gData_03000558->unk10 != NULL)
            {
                if (gData_03000558->unk34[3] >= 0)
                {
                    s32 *pos = (s32 *)PosRecordGet((struct Unk6DEF4 *)sub_08062A14(), gData_03000558->unk34[3]);
                    gData_03000554->unk04 = pos[0] >> 3;
                    gData_03000554->unk06 = (pos[1] >> 3) - 16;
                }
                entry = gData_03000558->unk10;
                gData_03000198->unk17F6 = entry->unk01;
                gData_03000554->unk01 = 1;
                gData_03000554->unk00 = 3;
                sub_080435D8();
            }
        }
        else if (gData_03004060 & 1)
        {
            if (gData_03000554->unk02 & 0x0F)
            {
                SaveBufferCreate(&gData_03000198->unk18B8);
                gData_03000198->unk1833 = 1;
                gData_03000198->unk181C = 2;
                gData_03000554->unk01 = 0xFF;
                gData_03000198->unk1808 &= ~0x200;
                BtlClearUnk1834();
            }
        }
        if (gData_03004060 & 8)
        {
            MenuPageSet(7);
            sub_0804109C((struct MenuState *)&gData_03000198->unk0530, MenuPageDefGet());
            gData_03000198->unk181C = 3;
            sub_08060428();
        }
        break;
    case 1:
        MapCursorMoveStep();
        break;
    }
}

/* fn: sub_08043B58 */
// @ 0x08043b58
/* match-compiler: old_agbcc */
struct Unk447CC *MapGetEntry(void)
{
    u32 key = gMainWorkPtr->unk1690->unk00;
    struct Unk447CC *p = *gData_08096794;
    struct Unk447CC **walk;

    if (p != 0)
    {
        walk = gData_08096794 + 1;
        do
        {
            if (key == (u32)p->unk00)
                return p;
            p = *walk++;
        } while (p != 0);
    }
    return 0;
}

/* fn: sub_08043C70 */
// @ 0x08043c70
/* match-compiler: old_agbcc */
typedef void (*CpuCopyFunc)(const void *, void *, u32);

// Loads map `map`: copies its header to gData_03000560, decompresses each
// compressed layer into a heap buffer, then places `obj` either at the saved
// position (`restore`) or at spawn point `spawn`, and sets the camera.
void MapLoad(struct Actor *obj, const struct Unk0560 *map, u32 modeArg, u32 spawnArg, u32 restore)
{
    u16 mode = modeArg;
    u16 spawn = spawnArg;
    struct Unk0560 *cur;
    struct Unk0560Layer *layer;
    struct Unk0560Handle **slot;
    struct Unk0560LayerSrc *src;
    struct Unk0560Handle *buf;
    s32 i;
    u32 size;
    s32 x;
    s32 y;

    ((CpuCopyFunc)gData_080BB8C0[0])(map, &gData_03000560, sizeof(struct Unk0560));
    sub_08043C28();
    cur = &gData_03000560;
    layer = cur->layers;
    slot = gData_030005F0;
    for (i = 0; i < 4; i++)
    {
        src = layer->unk00;
        if (src != NULL)
        {
            size = src->unk00 >> 8;
            if (src->unk04 != 0x20)
            {
                buf = HeapAlloc(size);
                if (buf == NULL)
                {
                    layer->unk00 = NULL;
                    *slot = NULL;
                }
                else
                {
                    *slot = buf;
                    VBlankIntrWait();
                    LZ77UnCompWram(src, buf->unk00);
                    layer->unk00 = buf->unk00;
                }
            }
        }
        layer++;
        slot++;
    }
    VBlankIntrWait();
    sub_08062988(gData_03000560.unk80);
    if (restore)
    {
        obj->x = gMainWorkPtr->unk0868;
        obj->y = gMainWorkPtr->unk086C;
        x = ((s32)gMainWorkPtr->unk0868 >> 8) - 0x78;
        y = ((s32)gMainWorkPtr->unk086C >> 8) - 0x50;
    }
    else
    {
        s32 *pos = (s32 *)PosRecordGet((struct Unk6DEF4 *)sub_08062A14(), spawn);

        obj->x = (pos[0] << 5) - ((obj->width >> 1) << 8);
        obj->y = (pos[1] << 5) - ((obj->height >> 1) << 8);
        x = (pos[0] >> 3) - 0x78;
        y = (pos[1] >> 3) - 0x50;
    }
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    VBlankIntrWait();
    sub_0806EBF8(gMainWorkPtr, (u32)&gData_03000560, mode, x, y);
}

/* fn: sub_08043DB4 */
// @ 0x08043db4
/* match-compiler: old_agbcc */
void FieldEnter(s32 a, void *b, s32 c, s32 d, s32 e)
{
  u32 tmp;
  u32 r;
  void *obj;
  s32 i;
  s8 ok;
  s32 none;
  gData_03000198->unk17F0 = 0;
  gData_03000198->unk17F2 = 0;
  *((vu16 *) (0x4000000 + 0x52)) = 0;
  gData_03000198->unk185A = 0;
  if (d != 0)
  {
    ScreenBrightnessFade(-1);
  }
  MapRunEntryScript();
  BufferClearWords(&gData_03000198->unk0524);
  ActorPoolClear();
  TasksDestroyAll();
  VramSlotsRelease();
  StatusHudMarkerHide();
  sub_0802DEA0();
  sub_08043ADC();
  EventFlagOp(0x18, 4, &tmp);
  if (tmp != 0)
  {
    do
    {
      r = RandRange(BGM_A_NEW_DAY + 1);
    }
    while (gData_03000198->bgmTrack == r);
    _0805FED4((void *) r);
  }
  ok = sub_0806644C();
  none = -1;
  if (ok > (0 - 1))
  {
    SceneObjFreeResources((struct Actor *) (&gData_03000198->unk036C));
    sub_0802DEA0();
    TextWindowClose();
    sub_080632F8();
    VramSlotsInit();
    BgScrollReset();
  }
  if (gData_03000198->unk17A8 != (-0x4000))
  {
    gData_03000198->unk0868 = gData_03000198->unk17A8;
    gData_03000198->unk086C = gData_03000198->unk17AC;
    gData_03000198->unk0370 = gData_03000198->unk0868;
    gData_03000198->unk0374 = gData_03000198->unk086C;
    gData_03000198->unk17A8 = -0x4000;
    gData_03000198->unk17AC = -0x4000;
  }
  sub_080442FC(b, (void *) a, c, e);
  gData_03000198->unk0358 |= 0x800;
  TextWindowOpen((struct Unk617C4 *) 0x082BCD00, 0x080B738E, 0x1C0, 0x1C, 0x10, 1, 4, 0x0F);
  BgSetPriorities(gData_03000198->unk1690->unk74_0, gData_03000198->unk1690->unk74_2, gData_03000198->unk1690->unk74_4, 0);
  SparklesHide();
  MapLoadObjects();
  sub_0806EE24((struct Unk6EE24 *) gData_03000198);
  sub_080473E4();
  if ((gData_03000198->unk1843 == 1) && (gData_03000198->unk18B4 != none))
  {
    obj = ActorFindByIdSide(gData_03000198->unk18B4, 0);
    if (obj != ((void *) 0))
    {
      SceneObjUpdate(obj);
      CameraSetTarget((struct Unk6F174 *) gData_03000198, obj);
      FieldUpdateFrame(0);
      for (i = 0; i < 64; i++)
      {
        CameraUpdate((struct MapView *) gData_03000198);
      }

    }
    else
    {
      CameraSetTarget((struct Unk6F174 *) gData_03000198, b);
    }
  }
  else
  {
    CameraSetTarget((struct Unk6F174 *) gData_03000198, b);
  }
  gData_03000198->unk1794 = -1;
  gData_03000198->unk17E4 = -1;
  gData_03000198->unk1790 = -1;
  gData_03000198->unk178C = -1;
  gData_03000198->unk17CC = 0;
  EventFlagOp(0x18, 4, &tmp);
  if (tmp != 0)
  {
    CursorHistoryReset();
    switch (gData_03000198->unk1828)
    {
      case 0:
        AnimObjSelectSeqDefault((struct AnimObjSeqSelect *) (&gData_03000198->unk036C), 5);
        gData_03000198->unk039D &= 2;
        gData_03000198->unk1810 = 0x40;
        if (gData_03000198->unk182C != 0)
      {
        AnimObjSelectSeqDefault((struct AnimObjSeqSelect *) (&gData_03000198->unk0448), 5);
        gData_03000198->unk0479 &= 2;
        CursorHistoryStartLine();
      }
        break;

      case 1:
        AnimObjSelectSeqDefault((struct AnimObjSeqSelect *) (&gData_03000198->unk036C), 5);
        gData_03000198->unk039D |= 1;
        gData_03000198->unk1810 = 0x20;
        if (gData_03000198->unk182C != 0)
      {
        AnimObjSelectSeqDefault((struct AnimObjSeqSelect *) (&gData_03000198->unk0448), 5);
        gData_03000198->unk0479 |= 1;
        CursorHistoryStartLine();
      }
        break;

      case 2:
        AnimObjSelectSeqDefault((struct AnimObjSeqSelect *) (&gData_03000198->unk036C), 6);
        gData_03000198->unk039D = 0;
        gData_03000198->unk1810 = 0x80;
        if (gData_03000198->unk182C != 0)
      {
        AnimObjSelectSeqDefault((struct AnimObjSeqSelect *) (&gData_03000198->unk0448), 6);
        gData_03000198->unk0479 = 0;
        CursorHistoryStartLine();
      }
        break;

      case 3:
        AnimObjSelectSeqDefault((struct AnimObjSeqSelect *) (&gData_03000198->unk036C), 7);
        gData_03000198->unk039D = 0;
        gData_03000198->unk1810 = 0x100;
        if (gData_03000198->unk182C != 0)
      {
        AnimObjSelectSeqDefault((struct AnimObjSeqSelect *) (&gData_03000198->unk0448), 7);
        gData_03000198->unk0479 = 0;
        CursorHistoryStartLine();
      }
        break;

    }

  }
  if (gData_03000198->unk182C != 0)
  {
    sub_08044A20();
  }
  EventFlagOp(0x18, 1, 0);
  gData_03000198->unk1808 &= ~0x2000;
  sub_0805DA70();
  switch (gData_03000198->unk185F)
  {
    case 10:
      AnimObjSelectSeqDefault((struct AnimObjSeqSelect *) (&gData_03000198->unk036C), 6);
      gData_03000198->unk039D = 0;
      gData_03000198->unk1810 = 0x80;
      break;

    case 11:
      AnimObjSelectSeqDefault((struct AnimObjSeqSelect *) (&gData_03000198->unk036C), 7);
      gData_03000198->unk039D = 0;
      gData_03000198->unk1810 = 0x100;
      break;

    case 8:
      AnimObjSelectSeqDefault((struct AnimObjSeqSelect *) (&(*gData_03000198).unk036C), 5);
      gData_03000198->unk039D &= 2;
      gData_03000198->unk1810 = 0x40;
      break;

    case 9:
      AnimObjSelectSeqDefault((struct AnimObjSeqSelect *) (&gData_03000198->unk036C), 5);
      gData_03000198->unk039D |= 1;
      gData_03000198->unk1810 = 0x20;
      break;

  }

  ScreenBrightnessFade(1);
  BtlClearUnk1834();
  gData_03000198->unk185A = 1;
  gData_03000198->unk185F = -1;
  ((void (*)(s32)) sub_08066440)(-1);
}

/* fn: sub_080444BC */
// @ 0x080444bc
void MapLoadObjects(void)
{
    struct Unk447CC *p;

    p = MapGetEntry();
    ObjPaletteSlotsReset();
    if ((u32)gMainWorkPtr->unk036C == 0x083147C8)
        ObjPalLoadSlot(0, (void *)0x083002E0);
    else
        ObjPalLoadSlot(0, (void *)0x083006E0);
    ObjPalLoadSlot(1, (void *)0x082FDEE0);
    ObjPalLoadSlot(2, (void *)0x0826E320);
    if (p != NULL)
    {
        if (p->unk14 != NULL)
            ScriptRun(0, p->unk14);
        if (p->unk04 != NULL)
            SceneObjSpawnList(p->unk04);
        if (p->unk08 != NULL)
            BeybladeSpawnList(p->unk08);
        if (p->unk0C != NULL)
            sub_08062A1C((u32)p->unk0C);
        if (p->unk10 != NULL)
            TaskCreateList(p->unk10);
        gMainWorkPtr->unk16E0 = p->unk1C;
        gMainWorkPtr->unk16E8 = p->unk20;
        gMainWorkPtr->unk16E4 = p->unk24;
        gMainWorkPtr->unk1825 = 0;
        if (p->unk28 & 1)
            gMainWorkPtr->unk1825 = 1;
        if (p->unk28 & 2)
            sub_0802DEA0();
        else
            sub_0802E048();
        if (p->unk28 & 4)
        {
            TextWindowOpenEx(gMainWorkPtr->unk15DC, (void *)0x082BCD00, (void *)0x080B738E, 0x1C0, 0x1C, 0x10, 1, 4, 0x0D, 2);
            BgSetPriorities(gMainWorkPtr->unk1690->unk74_0, gMainWorkPtr->unk1690->unk74_2, 1, 0);
        }
    }
    else
    {
        gMainWorkPtr->unk16E0 = NULL;
        gMainWorkPtr->unk16E8 = NULL;
        gMainWorkPtr->unk16E4 = NULL;
        gMainWorkPtr->unk1825 = 0;
    }
    sub_0804495C();
}

/* fn: sub_080447CC */
// @ 0x080447cc
void MapRunEntryScript(void)
{
    struct Unk447CC *p;
    void *v;

    p = MapGetEntry();
    if (p != 0)
    {
        v = p->unk18;
        if (v != 0)
            ScriptRun(0, v);
    }
}

/* fn: sub_08046E7C */
// @ 0x08046e7c
/* match-compiler: old_agbcc */
// Per-frame field update: refresh the two main objects' sort keys, tick objects,
// timers and effects, read d-pad movement (when active and allowed) into a
// direction for _08041E88, run collision (sub_0806C7D4) and proximity
// triggers, and handle the countdown and menu buttons.
void FieldUpdateFrame(u32 active)
{
    u32 dir;
    s32 speed;
    u32 mesh;

    VBlankIntrWait();
    gData_03000198->unk0428 = ~(gData_03000198->unk0374 >> 8);
    if (gData_03000198->unk0424 != NULL)
        BtlObjListResort((struct Unk6FDB4 *)gData_03000198->unk0424, gData_03000198->unk0428);
    if (gData_03000198->unk0500 != NULL)
    {
        gData_03000198->unk0504 = ~((s32)gData_03000198->unk0450 >> 8);
        BtlObjListResort((struct Unk6FDB4 *)gData_03000198->unk0500, gData_03000198->unk0504);
    }
    CameraUpdate((struct MapView *)gData_03000198);
    SceneObjUpdate(&gData_03000198->unk036C);
    SceneObjsUpdateAll();
    sub_08067CE8((struct AnimObj *)&gData_03000198->unk036C, 0);
    if (gData_03000198->unk182C != 0)
    {
        SceneObjUpdate(&gData_03000198->unk0448);
        sub_08067CE8((struct AnimObj *)&gData_03000198->unk0448, 0);
    }
    ((void (*)(void))gData_080BB888[0])();
    InputUpdate();
    SparklesUpdate();
    TimerAdvance();
    sub_080462D4();
    dir = 0;
    gData_03000198->unk03AC = 0;
    gData_03000198->unk03B0 = 0;
    gData_03000198->unk180C = 0;
    if ((gData_03003F60 & 2) && gData_03000198->unk17CC > 0x10)
        speed = 0x200;
    else
        speed = 0x100;
    if (active != 0)
    {
        if (gData_03000198->unk180C == 0 && *(u32 *)gData_03000634 == 0 && gData_03000198->unk182B != 0)
        {
            if (gData_03003F60 & 0x20)
            {
                dir = 1;
                *(u32 *)gData_0300063C = dir;
                *(u32 *)gData_03000634 = CursorStepsToTile(0);
                CursorHistoryPush(1);
            }
            else if (gData_03003F60 & 0x10)
            {
                dir = 2;
                *(u32 *)gData_0300063C = dir;
                *(u32 *)gData_03000634 = CursorStepsToTile(1);
                CursorHistoryPush(2);
            }
            else if (gData_03003F60 & 0x40)
            {
                dir = 4;
                *(u32 *)gData_0300063C = dir;
                *(u32 *)gData_03000634 = CursorStepsToTile(2);
                CursorHistoryPush(4);
            }
            else if (gData_03003F60 & 0x80)
            {
                dir = 8;
                *(u32 *)gData_0300063C = dir;
                *(u32 *)gData_03000634 = CursorStepsToTile(3);
                CursorHistoryPush(8);
            }
            else if (gData_03004060 & 1)
            {
                dir = 0x10;
            }
            else if (gData_03004060 & 0x100)
            {
                sub_08060428();
                MenuPageSet(9);
                sub_0804109C((struct MenuState *)&gData_03000198->unk0530, MenuPageDefGet());
                gData_03000198->unk181C = 4;
                gData_03000198->unk1808 |= 0x100;
            }
        }
        else if (*(u32 *)gData_03000634 != 0)
        {
            (*(u32 *)gData_03000634)--;
            dir = *(u32 *)gData_0300063C;
            CursorHistoryPush(dir);
        }
    }
    _08041E88((void *)dir, speed);
    gData_03000198->unk1838 = 0xFFFF;
    mesh = sub_08062A14();
    sub_0806C7D4((struct CollisionBody *)&gData_03000198->unk036C, (struct Unk6C388Mesh *)mesh, NULL, 0);
    sub_08062758(&gData_03000198->unk0524, (struct Actor *)&gData_03000198->unk036C);
    CursorHistoryReplayStep();
    TasksRunAll();
    HudRefreshStats();
    gData_03000198->unk1788++;
    if ((*(u32 *)&gData_03000198->unk1854 & 0xFF00FF00) == 0x100 && BtlCountLiveSlots() == 0x53)
    {
        if (--gData_03000198->unk1858 <= 0)
        {
            gData_03000198->unk1857 = 1;
            ScriptRun(0, gData_080979EC);
        }
    }
    if ((gData_03004060 & 8) && gData_03000198->unk180C == 0 && gData_03000198->unk185A == 1)
    {
        gData_03000198->unk184D = 1;
        MenuPageSet(7);
        sub_0804109C((struct MenuState *)&gData_03000198->unk0530, MenuPageDefGet());
        gData_03000198->unk181C = 3;
        sub_08060428();
    }
}

/* fn: sub_08062790 */
// @ 0x08062790
/* match-compiler: old_agbcc */
// Proximity trigger: if obj's centre is within (rangeX, rangeY) pixels of a's
// centre, run obj's script (unkC4), or for a side-1 object whose profile
// passes sub_0802BC14, fire the one-shot event for slot. Returns 1 when in
// range; out of range re-arms the slot's flag.
s32 ProximityTriggerCheck(struct Actor *a, struct Actor *obj, u32 rangeX, u32 rangeY, s32 slot)
{
    s32 ax, ay, ox, oy;
    u32 dx, dy;
    s32 profile;

    ax = a->x + ((a->width >> 1) << 8);
    ay = a->y + ((a->height >> 1) << 8);
    ox = obj->x + ((obj->width >> 1) << 8);
    oy = obj->y + ((obj->height >> 1) << 8);
    dx = (ax - ox >= 0 ? ax - ox : ox - ax) >> 8;
    dy = (ay - oy >= 0 ? ay - oy : oy - ay) >> 8;
    if (dx <= rangeX && dy <= rangeY)
    {
        if (obj->unkD8 == (void *)1)
        {
            profile = BeybladeGetProfile((s32)obj->unkD4);
            if (CollectionIsFull(profile) == 0 || profile == -1)
            {
                if (obj->unkC4 != NULL)
                    ScriptRun((u32)obj, obj->unkC4);
            }
            else if (slot != -1 && gData_03000510[slot] == 0)
            {
                sub_080473E4();
                sub_08041F88();
                sub_0803FDD0(0xA72);
                gData_03000510[slot] = 1;
            }
        }
        else if (obj->unkC4 != NULL)
            ScriptRun((u32)obj, obj->unkC4);
        return 1;
    }
    if (slot != -1)
        gData_03000510[slot] = 0;
    return 0;
}
