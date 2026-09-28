#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806f910
// Battle object system init: (re)allocate the object pool (nObj <= 0x80 nodes
// of 0x34), the OAM sprite-slot pool (nSpr <= 0x20 nodes of 0x1C) and the
// VRAM span list, link each into a free list, then hide all OAM entries.
#define HeapAllocBlock(size) ((struct Unk6F910Block *(*)(u32))sub_0806A314)(size)

void sub_0806F910(u32 nObj, u32 nSpr)
{
    struct Unk700CCNode *node;
    struct Unk6F910Spr *spr;
    void *prev;
    struct Unk6FBF8Span *span;
    u32 oam;
    s32 i;

    gData_03004164 = 0x800;
    gData_0300415C = 0;
    if (nObj > 0x80)
        nObj = 0x80;
    if (nSpr > 0x20)
        nSpr = 0x20;
    if (gData_030040A0 != NULL)
    {
        sub_0806A434(gData_030040A0);
        gData_030040A0 = NULL;
    }
    if (gData_0300409C != NULL)
    {
        sub_0806A434(gData_0300409C);
        gData_0300409C = NULL;
    }
    if (gData_03004094 != NULL)
    {
        sub_0806A434(gData_03004094);
        gData_03004094 = NULL;
    }
    if (nObj != 0)
    {
        gData_030040A0 = HeapAllocBlock(0x34 * nObj);
        if (gData_030040A0 == NULL)
            sub_08067A9C((void *)0x083D20C8);
    }
    if (nSpr != 0)
    {
        gData_0300409C = HeapAllocBlock(nSpr * 0x1C);
        if (gData_0300409C == NULL)
            sub_08067A9C((void *)0x083D20E4);
    }
    gData_03004094 = HeapAllocBlock(0x100);
    if (gData_03004094 == NULL)
    {
        DebugPrint((void *)0x083D2108);
        gData_0300408C = NULL;
    }
    else
        gData_0300408C = gData_03004094->unk00;
    if (gData_030040A0 != NULL)
        gData_03004090 = gData_030040A0->unk00;
    else
        gData_03004090 = NULL;
    if (gData_0300409C != NULL)
        gData_030040B0 = gData_0300409C->unk00;
    else
        gData_030040B0 = NULL;
    if (gData_03004090 != NULL)
        ((void (*)(u32, void *, u32))gData_080BB8BC[0])(0, gData_03004090, gData_030040A0->unk04);
    if (gData_030040B0 != NULL)
        ((void (*)(u32, void *, u32))gData_080BB8BC[0])(0, gData_030040B0, gData_0300409C->unk04);
    if (nObj != 0)
    {
        node = gData_03004090;
        spr = gData_030040B0;
        prev = NULL;
        for (i = nObj - 2; i != -1; i--)
        {
            node->unk00 = prev;
            node->unk04 = node + 1;
            node->unk24 = -1;
            prev = node;
            node++;
        }
        node->unk00 = prev;
        node->unk04 = NULL;
        gData_030040A4 = NULL;
        gData_030040AC = (struct Unk6FDB4 *)gData_03004090;
        gData_030040B4 = nObj;
    }
    if (nSpr != 0)
    {
        prev = NULL;
        oam = 0x07000000;
        for (i = nSpr - 2; i != -1; i--)
        {
            spr->unk00 = prev;
            spr->unk04 = spr + 1;
            spr->unk08 = oam;
            oam += 0x20;
            prev = spr;
            spr++;
        }
        spr->unk00 = prev;
        spr->unk04 = NULL;
        spr->unk08 = oam;
        *(void **)gData_030040B8 = NULL;
        *(void **)gData_030040A8 = gData_030040B0;
    }
    if (gData_0300408C != NULL)
    {
        gData_03004088 = gData_0300408C;
        gData_03004098 = gData_0300408C + 1;
        gData_0300408C->start = 0;
        gData_0300408C->size = 0x400;
        gData_0300408C->next = NULL;
        span = gData_0300408C + 1;
        for (i = 29; i != -1; i--)
        {
            span->next = span + 1;
            span++;
        }
        span->next = NULL;
    }
    ((void (*)(u32, void *, u32))gData_080BB8BC[0])(0xA0, (void *)0x07000000, 0x400);
}

